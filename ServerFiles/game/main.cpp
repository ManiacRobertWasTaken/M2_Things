#ifdef ENABLE_ITEM_BONUS_EVENT
#include "bonusEventManager.h"
#endif

//Search
DSManager dsManager;

//Add

#ifdef ENABLE_ITEM_BONUS_EVENT
	CBonusEvent	itemBonus_manager;
#endif

//Search
    OXEvent_manager.Initialize();
//Add

#ifdef ENABLE_ITEM_BONUS_EVENT
	CBonusEvent::instance().InitializeRewardMap();
#endif
