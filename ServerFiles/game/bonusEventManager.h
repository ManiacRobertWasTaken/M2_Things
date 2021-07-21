#ifndef	__HEADER_EVENT_MANAGER__
#define	__HEADER_EVENT_MANAGER__

#include "../../common/tables.h"
class CBonusEvent : public singleton<CBonusEvent>
{
	public:
		CBonusEvent();
		~CBonusEvent();
		//Reward Tables
		void	InitializeRewardMap();
		
		void 	ClearEventMap() { m_itemsRewards.clear(); }
		void 	SetEventMap(DWORD dwVnum, TRewardStructure& rInfo);
		bool 	GetEventMap(DWORD dwVnum, TRewardStructure** pInfo);
		//End Reward Tables

		//Starting Item Map
		void	InitializeItemMap();
		
		void 	ClearItemMap() { m_itemMap.clear(); }
		void 	SetItemMap(DWORD dwVnum, TItemStructure& rInfo);
		bool 	GetItemMap(DWORD dwVnum, TItemStructure** pInfo);

		uint16_t GetItemReward() { return itemReward;}
		bool	IsEventEnabled()  {return isEvent;}
		//End Item Map		
		
		//Starting Networking
		void SendInformation(LPCHARACTER pkChr);
		//End Networking

		void RequestValidation(LPITEM pkItem, LPCHARACTER pkChar);

	private:
		std::map<uint16_t, TRewardStructure>	m_itemsRewards;
		std::map<uint16_t, TItemStructure>	m_itemMap;

		uint16_t itemReward;
		bool	isEvent;
};
#endif