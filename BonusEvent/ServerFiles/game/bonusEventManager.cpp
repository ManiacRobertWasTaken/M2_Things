#include "stdafx.h"

#include "utils.h"
#include "vector.h"
#include "char.h"
#include "sectree_manager.h"
#include "char_manager.h"
#include "mob_manager.h"
#include "packet.h"
#include "item_manager.h"
#include "item.h"
#include "bonusEventManager.h"
#include "config.h"
#include "db.h"
#include "desc_client.h"
#include "questmanager.h"

//Compare bonuses
#include <vector>
#include <algorithm>
template<typename T>
bool compare(std::vector<T>& v1, std::vector<T>& v2)
{
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    return v1 == v2;
}
//Compare bonuses

CBonusEvent::CBonusEvent()
{
	ClearEventMap();
	ClearItemMap();

	itemReward = 0;
}

CBonusEvent::~CBonusEvent()
{
}


void CBonusEvent::InitializeRewardMap()
{
	if (g_bAuthServer)
		return;

	ClearEventMap(); //Clear for Reload Commands

	std::unique_ptr<SQLMsg> pkMsg(DBManager::instance().DirectQuery("SELECT id, itemReward, itemCount FROM bonusEvent_rewardTable;"));

	auto pRes = pkMsg->Get();
	MYSQL_ROW row;
	TRewardStructure table;

	if (pRes && pRes->uiNumRows > 0)
    {
		while ((row = mysql_fetch_row(pRes->pSQLResult)))
		{
			table.itemVnum = std::stoi(row[ROW_TYPE_ID]);
			table.itemReward = std::stoi(row[ROW_TYPE_REWARD]);
			table.itemRewardCount = std::stoi(row[ROW_TYPE_ITEM_COUNT]);

			m_itemsRewards.insert(std::make_pair(table.itemVnum, table));
		}
	}
	InitializeItemMap();
}

void CBonusEvent::SetEventMap(DWORD dwVnum, TRewardStructure& rInfo)
{
	auto it = m_itemsRewards.find(dwVnum);
	if (it != m_itemsRewards.end())
	{
		it->second = rInfo;
	}
	else{
		m_itemsRewards.insert(std::make_pair(dwVnum, rInfo));
	}
}

bool CBonusEvent::GetEventMap(DWORD dwVnum, TRewardStructure** pInfo)
{
	auto it = m_itemsRewards.find(dwVnum);

	if (m_itemsRewards.end() == it)
		return false;

	*pInfo = (TRewardStructure*)&(it->second);
	return true;
}


void CBonusEvent::InitializeItemMap()
{
	if (g_bAuthServer)
		return;

	ClearItemMap(); //Clear for Reload Commands

	std::unique_ptr<SQLMsg> pkMsg(DBManager::instance().DirectQuery("SELECT * FROM bonusEvent_itemTable;"));

	auto pRes = pkMsg->Get();
	MYSQL_ROW row;
	
	auto col = 0;
	if (pRes && pRes->uiNumRows > 0)
    {
		while ((row = mysql_fetch_row(pRes->pSQLResult)))
		{
			col = 0;
			TItemStructure itemTable{};

			itemTable.itemVnum = std::stoi(row[col++]);
			for (auto i = 0; i < ITEM_MAX_BONUSES; i++)
			{
				itemTable.itemAttrs[i].bType = std::stoi(row[col++]);
				itemTable.itemAttrs[i].sValue = std::stoi(row[col++]);
			}
			m_itemMap.insert(std::make_pair(itemTable.itemVnum, itemTable));
			itemReward = itemTable.itemVnum;
		}
	}
}

void CBonusEvent::SetItemMap(DWORD dwVnum, TItemStructure& rInfo)
{
	auto it = m_itemMap.find(dwVnum);
	if (it != m_itemMap.end())
	{
		it->second = rInfo;
	}
	else{
		m_itemMap.insert(std::make_pair(dwVnum, rInfo));
	}
}

bool CBonusEvent::GetItemMap(DWORD dwVnum, TItemStructure** pInfo)
{
	auto it = m_itemMap.find(dwVnum);

	if (m_itemMap.end() == it)
		return false;

	*pInfo = (TItemStructure*)&(it->second);
	return true;
}


void CBonusEvent::SendInformation(LPCHARACTER pkChr)
{
	auto isEvent = quest::CQuestManager::instance().GetEventFlag("bonusevent.status");
	if (!isEvent)
		return;
	auto rewardItem = GetItemReward();
	if (rewardItem && pkChr && pkChr->GetDesc())
	{
		TItemStructure* info;
		const bool itemTable = GetItemMap(rewardItem, &info);
		if (!itemTable)
		{
			sys_err("Wtf? how? %s", pkChr->GetName());
			return;
		}

		TPacketGCBonusEvent pack;
		pack.header = HEADER_GC_BONUS_INFORMATION;
		pack.isEvent = true;
		pack.requestItem = rewardItem;
		TRewardStructure* items;

		for (auto itemList : m_itemsRewards)
		{
			auto rewardTableItems = GetEventMap(itemList.first, &items);
			if (rewardTableItems)
			{
				pack.rewards[itemList.first].itemVnum = items->itemVnum;
				pack.rewards[itemList.first].itemReward = items->itemReward;
				pack.rewards[itemList.first].itemRewardCount = items->itemRewardCount;
			}
		}

		for (auto i = 0; i < ITEM_MAX_BONUSES; i++)
		{
			pack.itemAttrs[i].bType = info->itemAttrs[i].bType; 
			pack.itemAttrs[i].sValue = info->itemAttrs[i].sValue; 
		}

		pkChr->GetDesc()->Packet(&pack, sizeof(pack));

	}
}

void CBonusEvent::RequestValidation(LPITEM pkItem, LPCHARACTER pkChar)
{
	auto isEvent = quest::CQuestManager::instance().GetEventFlag("bonusevent.status");
	if (!isEvent)
		return;

	if (!pkItem)
		return;

	if (!pkChar)
		return;

	auto rewardItem = CBonusEvent::instance().GetItemReward();
	if (rewardItem && rewardItem == pkItem->GetVnum())
	{
		TItemStructure* info;
		const bool itemTable = CBonusEvent::instance().GetItemMap(rewardItem, &info);
		if (itemTable)
		{
			std::vector<BYTE> bonusEventList = { info->itemAttrs[0].bType, info->itemAttrs[1].bType, info->itemAttrs[2].bType, info->itemAttrs[3].bType, info->itemAttrs[4].bType };
			std::vector<BYTE> bonusEventItem = { pkItem->GetAttributeType(0), pkItem->GetAttributeType(1), pkItem->GetAttributeType(2), pkItem->GetAttributeType(3), pkItem->GetAttributeType(4) };

			std::vector<short> valueEventList = { info->itemAttrs[0].sValue, info->itemAttrs[1].sValue, info->itemAttrs[2].sValue, info->itemAttrs[3].sValue, info->itemAttrs[4].sValue };
			std::vector<short> valueEventItem = { pkItem->GetAttributeValue(0), pkItem->GetAttributeValue(1), pkItem->GetAttributeValue(2), pkItem->GetAttributeValue(3), pkItem->GetAttributeValue(4) };

			if (compare(bonusEventList, bonusEventItem) && compare(valueEventList, valueEventItem))
			{
				char buf[CHAT_MAX_LEN];
				snprintf(buf, sizeof(buf), LC_TEXT("[Bonus Event]%s a livrat item-ul castigator!"), pkChar->GetName());
				SendNotice(buf);
				TRewardStructure* items;
				ITEM_MANAGER::instance().RemoveItem(pkItem, "BONUS_EVENT");
				for (auto itemList : m_itemsRewards)
				{
					auto rewardTableItems = GetEventMap(itemList.first, &items);
					if (rewardTableItems)
						pkChar->AutoGiveItem(items->itemReward, items->itemRewardCount);
				}
				quest::CQuestManager::instance().RequestSetEventFlag("bonusevent.status", 0);
				pkChar->ChatPacket(CHAT_TYPE_COMMAND, "ClearEventWindow");
			}
		}
	}
}
