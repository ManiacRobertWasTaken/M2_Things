#pragma once

#include "../gamelib/ItemData.h"
#include "../EterBase/Poly/Poly.h"
#include "packet.h"
class CPythonBonusEvent : public CSingleton<CPythonBonusEvent>
{
	public:
		CPythonBonusEvent();
		virtual ~CPythonBonusEvent();

		void SetEventData(int16_t info, TBonusInfo& crInfo);
		bool GetBonusData(int16_t info, TBonusInfo& data);
		
	private:
		typedef	std::map<int16_t, TBonusInfo> TEventBonusMap;
		TEventBonusMap	m_bonusEvent;

};