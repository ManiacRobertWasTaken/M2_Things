#ifdef ENABLE_ITEM_BONUS_EVENT
#include "bonusEventManager.h"
#endif

#ifdef ENABLE_ITEM_BONUS_EVENT
ACMD(do_deliver_item_bonus)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;
	
	WORD itemPos = -1;
	str_to_number(itemPos, arg1);
	auto pkItem = ch->GetInventoryItem(itemPos);
	if (pkItem)
		CBonusEvent::instance().RequestValidation(pkItem, ch);	

}
#endif
