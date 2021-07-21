#ifdef ENABLE_ITEM_BONUS_EVENT
enum eventHeaders
{
	HEADER_GC_BONUS_INFORMATION = 180,
};

typedef struct packet_bonus_info
{
	bool	isEvent;
	uint16_t requestItem;

	TRewardStructure rewards[REWARD_MAX_ITEMS];
	TPlayerItemAttribute itemAttrs[ITEM_MAX_BONUSES];

} TBonusInfo;

typedef struct SPacketGCBonusEvent
{
	BYTE header;
	packet_bonus_info	info;

} TPacketGCBonusEvent;

#endif