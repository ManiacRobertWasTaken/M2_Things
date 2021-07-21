import uiBonusEvent

[....]

        self.wndBonusWindow = None
[....]

		self.wndBonusWindow = uiBonusEvent.BonusEventWindow()
		self.wndBonusWindow.Hide()

[....]

	def ShowBonusEventWindow(self): ### Teste
		if False == self.wndBonusWindow.IsShow():
			self.wndBonusWindow.Open()
			self.wndBonusWindow.SetTop()
		else:
			self.wndBonusWindow.Close()


