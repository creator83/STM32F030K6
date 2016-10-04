#include "qenc.h"




Qenc::Qenc (uint16_t range)
:Ftm (QdDef::N)
{
	high = range;
	setMode ();
}


void Qenc::setMode ()
{
	//===Setings pin===//
	//pha
	pha.settingPinPort(QdDef::PhaPort);
	pha.settingPin(QdDef::PhaPin, QdDef::PhaAlt);
	//phb
	pha.settingPinPort(QdDef::PhbPort);
	pha.settingPin(QdDef::PhbPin, QdDef::PhbAlt);

	//===Settings timer===//
	FTM_SC_REG(ftm_ptr[num_ftm]) = 0;
	setPeriod(4);
	FTM_CNTIN_REG(ftm_ptr[num_ftm]) = 0;
	FTM_CnSC_REG(ftm_ptr[num_ftm], 0) = 0;
	FTM_CnSC_REG(ftm_ptr[num_ftm], 1) = 0;
	FTM_QDCTRL_REG(ftm_ptr[num_ftm]) |= FTM_QDCTRL_QUADEN_MASK;
	FTM_MODE_REG (ftm_ptr[num_ftm]) |= FTM_MODE_WPDIS_MASK|FTM_MODE_FTMEN_MASK;
	interruptEnable();
	start ();
}

uint16_t Qenc::getValue ()
{
	clearTof();
	value = FTM_CNT_REG (ftm_ptr[num_ftm]);
	if (value>high)
	{
		value = high;
		FTM_CNT_REG (ftm_ptr[num_ftm]) = high;
	}
	return value;
}

void Qenc::setRange (uint16_t r)
{

}
