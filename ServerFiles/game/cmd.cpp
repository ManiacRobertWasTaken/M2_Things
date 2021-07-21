
#ifdef ENABLE_ITEM_BONUS_EVENT
ACMD(do_bonus_event);
ACMD(do_deliver_item_bonus);
#endif


#ifdef ENABLE_ITEM_BONUS_EVENT
	{ "bonus_event",		do_bonus_event,			0,	POS_DEAD,	GM_IMPLEMENTOR	},	
	{ "deliver_event_item",		do_deliver_item_bonus,			0,	POS_DEAD,	GM_PLAYER	},	
#endif