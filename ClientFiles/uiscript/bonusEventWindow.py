import localeInfo, uiScriptLocale

BUTTON_ROOT = "d:/ymir work/ui/public/"

window = {
	"name" : "bonusEventWindow",

	"x" : 0,
	"y" : 0,

	"style" : ("movable", "float",),

	"width" : 255 + 50 + 206 + 15,
	"height" : 390,

	"children" :
	(
		{
			"name" : "board",
			"type" : "board",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : 255 + 50 + 206 + 10,
			"height" : 223 + 10 - 40,
		
			"children" :
			(
				## Title
				{
					"name" : "TitleBar",
					"type" : "titlebar",
					"style" : ("attach",),

					"x" : 6,
					"y" : 6,

					"width" : 508,				
					"color" : "yellow",

					"children" :
					(
						{ "name":"TitleName", "type":"text", "x": -2, "y": -2, "text": "Eveniment Schimbare Bonus", "all_align":"center" },
					),
				},
			),
		},
		{
			"name" : "FristItemBoard",
			"type" : "border_a",
			"style" : ("attach",),
			
			"x" : 8,
			"y" : 30,
	
			"width" : 88 + 10,
			"height" : 182 + 10 - 40,
			
			"children" :
			(

				{
					"name" : "ItemSlotBack",
					"type" : "image",
					
					"x" : 20 + 6,
					"y" : 10,
					
					"image" : "d:/ymir work/ui/game/attr6th7th/regist_slot.sub",
					
					"children" :
					(
						{
							"name" : "ItemSlot",
							"type" : "slot",
			
							"x" : 6,
							"y" : 6,
			
							"width" : 32,
							"height" : 32,

							"slot":
							(
								{ "index": 0, "x": 0,"y": 0, "width":32, "height":32*3 },
							),
						},
					),
				},				
			),
		},
		{
			"name" : "BonusBoard",
			"type" : "border_a",
			"style" : ("attach",),
			
			"x" : 100 + 7,
			"y" : 30,
	
			"width" : 200 + 110,
			"height" : 182 + 10 - 40,
			
			"children" :
			(
				{
					"name" : "firstBonus", "type" : "image",
					"x" : 3, "y" : 3,
					"image" : "d:/ymir work/ui/game/cube/cube_menu_tab1.sub",
					"children" : ({"name":"firstBonusText", "type":"text", "x":0, "y":-1, "text": "BonusName0", "all_align" : "center"},),
				},		

				{
					"name" : "secondBonus", "type" : "image",
					"x" : 3, "y" : 3 + 20,
					"image" : "d:/ymir work/ui/game/cube/cube_menu_tab1.sub",
					"children" : ({"name":"secondBonusText", "type":"text", "x":0, "y":-1, "text": "BonusName1", "all_align" : "center"},),
				},		

				{
					"name" : "thirdBonus", "type" : "image",
					"x" : 3, "y" : 3 + 20*2,
					"image" : "d:/ymir work/ui/game/cube/cube_menu_tab1.sub",
					"children" : ({"name":"thirdBonusText", "type":"text", "x":0, "y":-1, "text": "BonusName2", "all_align" : "center"},),
				},

				{
					"name" : "fourthBonus", "type" : "image",
					"x" : 3, "y" : 3 + 20*3,
					"image" : "d:/ymir work/ui/game/cube/cube_menu_tab1.sub",
					"children" : ({"name":"fourthBonusText", "type":"text", "x":0, "y":-1, "text": "BonusName3", "all_align" : "center"},),
				},											

				{
					"name" : "fifthBonus", "type" : "image",
					"x" : 3, "y" : 3 + 20*4,
					"image" : "d:/ymir work/ui/game/cube/cube_menu_tab1.sub",
					"children" : ({"name":"fifthBonusText", "type":"text", "x":0, "y":-1, "text": "BonusName4", "all_align" : "center"},),
				},	

				{
				
					"name" : "ItemBoard",
					"type" : "border_a",
					
					"x" : 24,
					"y" : 105,
			
					"width" : 263,
					"height" : 38,	
					"children" :
					(							
						{
							"name" : "ItemGrid",
							"type" : "grid_table",
			
							"x" : 3,
							"y" : 3,
			
							"start_index" : 0,
							"x_count" : 8,
							"y_count" : 1,
							"x_step" : 32,
							"y_step" : 32,
			
							"image" : "d:/ymir work/ui/public/Slot_Base.sub"
							
						},				
					),
				},	
			),
		},

		{
			"name" : "NeedItemBoard",
			"type" : "border_a",
			"style" : ("attach",),
			
			"x" : 414 + 4,
			"y" : 30,
	
			"width" : 88 + 5,
			"height" : 182 + 10 - 40,
			
			"children" :
			(

				## Close Button
				{ 
					"name" : "DeliverButton", 
					"type" : "button", 
					"x" : 4, 
					"y" : 124,
					"default_image" : "d:/ymir work/ui/game/battle_pass/reward_normal.tga",
					"over_image" : "d:/ymir work/ui/game/battle_pass/reward_over.tga",
					"down_image" : "d:/ymir work/ui/game/battle_pass/reward_down.tga",
				},
				{
					"name" : "ItemSlotReward",
					"type" : "image",
					
					"x" : 20 + 5,
					"y" : 10,
					
					"image" : "d:/ymir work/ui/game/attr6th7th/regist_slot.sub",
					
					"children" :
					(
						{
							"name" : "ItemSlotComplete",
							"type" : "slot",
			
							"x" : 6,
							"y" : 6,
			
							"width" : 32,
							"height" : 32,

							"slot":
							(
								{ "index": 0, "x": 0,"y": 0, "width":32, "height":32*3 },
							),
						},
					),
				},				
			),
		},		
	),
}

