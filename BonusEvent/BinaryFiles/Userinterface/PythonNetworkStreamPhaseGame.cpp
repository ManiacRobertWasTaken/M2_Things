#ifdef ENABLE_ITEM_BONUS_EVENT
			case HEADER_GC_BONUS_INFORMATION:
				ret = RecvBonusEvent();
				break;
#endif

//[...]

#ifdef ENABLE_ITEM_BONUS_EVENT
bool CPythonNetworkStream::RecvBonusEvent()
{
	TPacketGCBonusEvent p;
	if (!Recv(sizeof(TPacketGCBonusEvent), &p))
		return false;

	CPythonBonusEvent& rkBonus = CPythonBonusEvent::Instance();
	rkBonus.SetEventData(1, p.info);

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OpenItemEvent", Py_BuildValue("()"));
	return true;
}
#endif
