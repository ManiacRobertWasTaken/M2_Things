#ifdef ENABLE_ITEM_BONUS_EVENT
	ALUA(pc_setitemevent)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		CBonusEvent::instance().SendInformation(ch);
		return 0;
	}
#endif

#ifdef ENABLE_ITEM_BONUS_EVENT
			{ "set_itemEvent",		pc_setitemevent		},
#endif