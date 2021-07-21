#ifdef ENABLE_ITEM_BONUS_EVENT
#include "bonusEventManager.h"
#endif

#ifdef ENABLE_ITEM_BONUS_EVENT
ACMD(do_bonus_event)
{

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Usage: /bonus_event 0 / 1");
		return;
	}

	auto dwInfo = 0;
	str_to_number(dwInfo, arg1);

	if (dwInfo == 1)
		BroadcastNotice("[ItemBonus]Eveniment-ul a fost activat!");
	else
		BroadcastNotice("[ItemBonus]Eveniment-ul a fost dezactivat!");

	quest::CQuestManager::instance().RequestSetEventFlag("bonusevent.status", dwInfo);

}
#endif