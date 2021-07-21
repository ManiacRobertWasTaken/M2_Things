#ifdef ENABLE_ITEM_BONUS_EVENT
enum eventHeaders
{
	HEADER_GC_BONUS_INFORMATION = 180, // Check your packet before adding
};
typedef struct SPacketGCBonusEvent
{
	BYTE header;

	bool	isEvent;
	uint16_t requestItem;

	TRewardStructure rewards[REWARD_MAX_ITEMS];
	TPlayerItemAttribute itemAttrs[ITEM_MAX_BONUSES];

} TPacketGCBonusEvent;
#endif
