#include "StdAfx.h"
#include "PythonBonusEvent.h"

#include "../EterBase/Poly/Poly.h"
#include "../EterPack/EterPackManager.h"
#include "InstanceBase.h"
#include "PythonPlayer.h"

CPythonBonusEvent::CPythonBonusEvent()
{

}
CPythonBonusEvent::~CPythonBonusEvent()
{
	m_bonusEvent.clear();
}



void CPythonBonusEvent::SetEventData(int16_t info, TBonusInfo& crInfo)
{
	auto it = m_bonusEvent.find(1);
	if (it != m_bonusEvent.end())
	{
		it->second = crInfo;
	}
	else {
		m_bonusEvent.insert(std::make_pair(info, crInfo));
	}
}

bool CPythonBonusEvent::GetBonusData(int16_t info, TBonusInfo& data)
{
	auto it = m_bonusEvent.find(1);
	if (it != m_bonusEvent.end())
	{
		data = it->second;
		return true;
	}

	return false;
}

PyObject* eventGetBonusValues(PyObject* poSelf, PyObject* poArgs)
{
	int bonusID;
	if (!PyTuple_GetInteger(poArgs, 0, &bonusID))
		return Py_BuildException();


	CPythonBonusEvent& rkBonus = CPythonBonusEvent::Instance();
	TBonusInfo pInfo;

	if (!rkBonus.GetBonusData(1, pInfo))
		return Py_BuildValue("ii", 0, 0);

	return Py_BuildValue("ii", pInfo.itemAttrs[bonusID].bType, pInfo.itemAttrs[bonusID].sValue);
}

PyObject* eventGetBonusReward(PyObject* poSelf, PyObject* poArgs)
{
	int bonusID;
	if (!PyTuple_GetInteger(poArgs, 0, &bonusID))
		return Py_BuildException();


	CPythonBonusEvent& rkBonus = CPythonBonusEvent::Instance();
	TBonusInfo pInfo;

	if (!rkBonus.GetBonusData(1, pInfo))
		return Py_BuildValue("ii", 0, 0);

	return Py_BuildValue("ii", pInfo.rewards[bonusID].itemReward, pInfo.rewards[bonusID].itemRewardCount);
}

PyObject* eventGetExtraData(PyObject* poSelf, PyObject* poArgs)
{
	CPythonBonusEvent& rkBonus = CPythonBonusEvent::Instance();
	TBonusInfo pInfo;

	if (!rkBonus.GetBonusData(1, pInfo))
		return Py_BuildValue("ii", 0, 0);

	return Py_BuildValue("ii", pInfo.isEvent, pInfo.requestItem);
}

void initBonusEvent()
{
	static PyMethodDef s_methods[] =
	{
		{ "GetBonusReward",					eventGetBonusReward,						METH_VARARGS },
		{ "GetExtraData",					eventGetExtraData,						METH_VARARGS },
		{ "GetBonusValues",					eventGetBonusValues,						METH_VARARGS },
		{ NULL,								NULL,										NULL },
	};

	PyObject * poModule = Py_InitModule("bonusEvent", s_methods);
}
