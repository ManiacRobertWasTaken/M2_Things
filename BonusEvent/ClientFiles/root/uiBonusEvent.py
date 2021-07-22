import uiCommon, snd, chat, app, net, player, item, wndMgr, mouseModule, localeInfo, constInfo, uiToolTip, ui, grp, uiScriptLocale, pack, event, nonplayer, bonusEvent

class BonusEventWindow(ui.ScriptWindow):	

	bonusListText		= []
	def __init__(self):
		ui.ScriptWindow.__init__(self)

		self.itemSlot = None
		self.ItemSlotReward = None

		self.tooltipItem = None
		self.inven = None
		self.itemPos = -1

		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __LoadWindow(self):
		try:
			PythonScriptLoader = ui.PythonScriptLoader()
			PythonScriptLoader.LoadScriptFile(self, "uiscript/bonusEventWindow.py")

			textList = ["firstBonusText", "secondBonusText", "thirdBonusText", "fourthBonusText", "fifthBonusText"]
			for item in textList:
				self.bonusListText.append(self.GetChild(item))

			self.itemSlot = self.GetChild("ItemSlot")
			self.ItemSlotReward = self.GetChild("ItemSlotComplete")

			self.ItemGrid = self.GetChild("ItemGrid")

		except:
			import exception
			exception.Abort("bonusWindow.__LoadWindow.BindObject")

		self.SetCenterPosition()
		self.ClearInformations()

		self.ItemSlotReward.SetOverInItemEvent(ui.__mem_func__(self.OnOverInItem))
		self.ItemSlotReward.SetOverOutItemEvent(ui.__mem_func__(self.OnOverOutItem))

		self.itemSlot.SetSelectEmptySlotEvent(ui.__mem_func__(self.SelectEmptySlot))
		self.itemSlot.SetOverInItemEvent(ui.__mem_func__(self.OnOverInItemer))
		self.itemSlot.SetOverOutItemEvent(ui.__mem_func__(self.OnOverOutItemer))
		self.itemSlot.SetUnselectItemSlotEvent(ui.__mem_func__(self.UseItemSlot))
		self.itemSlot.SetUseSlotEvent(ui.__mem_func__(self.UseItemSlot))
		self.itemSlot.SetSelectItemSlotEvent(ui.__mem_func__(self.UseItemSlot))	

		self.GetChild("DeliverButton").SetEvent(ui.__mem_func__(self.SendDeliverButton))

		self.tooltipItem = uiToolTip.ItemToolTip()


	def SelectEmptySlot(self, selectedSlotPos):
		if mouseModule.mouseController.isAttached():
			attachedSlotType = mouseModule.mouseController.GetAttachedType()
			attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
			attachedItemVNum = mouseModule.mouseController.GetAttachedItemIndex()
			
			mouseModule.mouseController.DeattachObject()

			self.AttachItemToSelectSlot(selectedSlotPos, attachedSlotType, attachedSlotPos)


	def SendDeliverButton(self):
		net.SendChatPacket("/deliver_event_item %d" % self.itemPos)

	def AttachItemToSelectSlot(self, selectSlot, slotType, slotIndex):
		ItemVNum = player.GetItemIndex(slotIndex)
		
		if not ItemVNum:
			return

		self.itemPos = slotIndex

	def ClearInformations(self):
		for item in xrange(len(self.bonusListText)):
			self.bonusListText[item].SetText("")

		self.itemSlot.ClearSlot(0)
		self.ItemSlotReward.ClearSlot(0)

	def UseItemSlot(self, index):
		self.itemPos = -1
		self.itemSlot.ClearSlot(0)

	def GetAffectString(self, affectType, affectValue):
		if 0 == affectType:
			return None
		try:
			return uiToolTip.ItemToolTip.AFFECT_DICT[affectType](affectValue)
		except TypeError:
			return "UNKNOWN_VALUE[%s] %s" % (affectType, affectValue)
		except KeyError:
			return "UNKNOWN_TYPE[%s] %s" % (affectType, affectValue)

	def Open(self):
		self.Show()
		self.itemPos = -1
		self.SetCenterPosition()

	def OnOverInItem(self, slotIndex):
		if self.tooltipItem:		
			self.tooltipItem.ClearToolTip()
			
			(_, itemIndex) = bonusEvent.GetExtraData()
			if itemIndex:
				self.tooltipItem.AddItemData(itemIndex, [0, 0, 0, 0])
				self.tooltipItem.ShowToolTip()
		
	def OnOverOutItem(self):
		if self.tooltipItem:
			self.tooltipItem.HideToolTip()
			
	def OnOverInItemer(self, slotIndex):
		if self.tooltipItem:		
			self.tooltipItem.ClearToolTip()
			
		if self.itemPos >= 0:
			metinSlot = [player.GetItemMetinSocket(player.INVENTORY, self.itemPos, i) for i in xrange(player.METIN_SOCKET_MAX_NUM)]
			attrSlot = [player.GetItemAttribute(player.INVENTORY, self.itemPos, i) for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM)]
			itemIndex = player.GetItemIndex(player.INVENTORY, self.itemPos)
			self.tooltipItem.AddItemData(itemIndex, metinSlot, attrSlot)
		
	def OnOverOutItemer(self):
		if self.tooltipItem:
			self.tooltipItem.HideToolTip()

	def Close(self):
		if self.tooltipItem:
			self.tooltipItem.HideToolTip()
		self.itemPos = -1
		self.Hide()

	def Destroy(self):

		self.itemSlot = None
		self.ItemSlotReward = None

		self.tooltipItem = None
		self.inven = None

		self.itemPos = -1

		if self.bonusListText: 
			del self.bonusListText[:]

	def OnUpdate(self):
		self.ClearInformations()
		(isEvent, itemReward) = bonusEvent.GetExtraData()
		
		self.ItemSlotReward.SetItemSlot(0, itemReward, 0)
		for item in xrange(len(self.bonusListText)):
			(apply, value) = bonusEvent.GetBonusValues(item)
			self.bonusListText[item].SetText(self.GetAffectString(apply, value))

		for x in xrange(0, 8):
			(item, count) = bonusEvent.GetBonusReward(x)
			if item:
				self.ItemGrid.SetItemSlot(x, item, count)

		if self.itemPos >= 0:
			itemIndex = player.GetItemIndex(player.INVENTORY, self.itemPos)
			itemCount = player.GetItemCount(player.INVENTORY, self.itemPos)
			self.itemSlot.SetItemSlot(0, itemIndex, itemCount)


	def OnPressEscapeKey(self):
		self.Close()
		return True

