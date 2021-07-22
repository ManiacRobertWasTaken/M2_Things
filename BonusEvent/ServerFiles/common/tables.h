#ifdef ENABLE_ITEM_BONUS_EVENT
enum rewardTableItems
{
	ROW_TYPE_ID,
	ROW_TYPE_REWARD,
	ROW_TYPE_ITEM_COUNT,
};

enum eventInformations
{
	ITEM_MAX_BONUSES = 5,
	REWARD_MAX_ITEMS = 8,
};

typedef struct BonusEventStructure
{
	uint16_t itemVnum = 0;
	uint16_t itemReward = 0;
	uint16_t itemRewardCount = 0;

} TRewardStructure;


typedef struct itemStructure
{
	uint16_t itemVnum = 0;
	TPlayerItemAttribute itemAttrs[ITEM_MAX_BONUSES];

} TItemStructure;
#endif