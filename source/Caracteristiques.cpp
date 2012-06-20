/*
	Copyright (C) 2011 Florent FAYOLLAS

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "ClassePourPersonnage.h"

Caracteristiques::Caracteristiques(bool at_prd_vrai,
								   int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup,
								   int AT_recup, int PRD_recup)
	: AT_PRD_vrai(at_prd_vrai),
	  COU(COU_recup), INT(INT_recup), CHA(CHA_recup), AD(AD_recup), FO(FO_recup),
	  AT(AT_recup), PRD(PRD_recup)
{}
Caracteristiques::Caracteristiques(Caracteristiques const& b)
{
	AT_PRD_vrai = b.AT_PRD_vrai;

	COU = b.COU;
	INT = b.INT;
	CHA = b.CHA;
	AD = b.AD;
	FO = b.FO;
	AT = b.AT;
	PRD = b.PRD;
}


bool Caracteristiques::estEgal(Caracteristiques const& b) const
{
	if (COU == b.COU && INT == b.INT && CHA == b.CHA && AD == b.AD && FO == b.FO && AT == b.AT && PRD == b.PRD)
		return true;
	else
		return false;
}
bool operator==(Caracteristiques const& a, Caracteristiques const& b)
{
	return a.estEgal(b);
}
bool Caracteristiques::estInfOuEgal(Caracteristiques const& b) const
{
	if (COU <= b.COU && INT <= b.INT && CHA <= b.CHA && AD <= b.AD && FO <= b.FO)
		return true;
	else
		return false;
}
bool operator<=(Caracteristiques const& a, Caracteristiques const& b)
{
	return a.estInfOuEgal(b);
}
bool Caracteristiques::estSupOuEgal(Caracteristiques const& b) const
{
	if (COU >= b.COU && INT >= b.INT && CHA >= b.CHA && AD >= b.AD && FO >= b.FO)
		return true;
	else
		return false;
}
bool operator>=(Caracteristiques const& a, Caracteristiques const& b)
{
	return a.estSupOuEgal(b);
}


Caracteristiques& Caracteristiques::operator=(Caracteristiques const& b)
{
	if(this != &b)
	{
		AT_PRD_vrai = b.AT_PRD_vrai;

		COU = b.COU;
		INT = b.INT;
		CHA = b.CHA;
		AD = b.AD;
		FO = b.FO;
		AT = b.AT;
		PRD = b.PRD;
	}

	return *this;
}
Caracteristiques& Caracteristiques::operator+=(Caracteristiques const& b)
{
	if ((COU + b.COU) > 18)
		COU = 18;
	else
		COU += b.COU;

	if ((INT + b.INT) > 18)
		INT = 18;
	else
		INT += b.INT;

	if ((CHA + b.CHA) > 18)
		CHA = 18;
	else
		CHA += b.CHA;

	if ((AD + b.AD) > 18)
		AD = 18;
	else
		AD += b.AD;

	if ((FO + b.FO) > 18)
		FO = 18;
	else
		FO += b.FO;

	return *this;
}
Caracteristiques& Caracteristiques::operator-=(Caracteristiques const& b)
{
	if (COU != 0)
		COU -= b.COU;
	else if ((COU - b.COU) < 0)
		COU = 0;

	if (INT != 0)
		INT -= b.INT;
	else if ((INT - b.INT) < 0)
		INT = 0;

	if (CHA != 0)
		CHA -= b.CHA;
	else if ((CHA - b.CHA) < 0)
		CHA = 0;

	if (AD != 0)
		AD -= b.AD;
	else if ((AD - b.AD) < 0)
		AD = 0;

	if (FO != 0)
		FO -= b.FO;
	else if ((FO - b.FO) < 0)
		FO = 0;

	return *this;
}


void Caracteristiques::remplir(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup,
							   int AT_recup, int PRD_recup)
{
	if (AT_recup != 0 && PRD_recup != 0)
		AT_PRD_vrai = true;
	else
		AT_PRD_vrai = false;

	COU = COU_recup;
	INT = INT_recup;
	CHA = CHA_recup;
	AD = AD_recup;
	FO = FO_recup;
	AT = AT_recup;
	PRD = PRD_recup;
}


int Caracteristiques::getCOU()
{
	return COU;
}
int Caracteristiques::getCHA()
{
	return CHA;
}
int Caracteristiques::getINT()
{
	return INT;
}
int Caracteristiques::getAD()
{
	return AD;
}
int Caracteristiques::getFO()
{
	return FO;
}
int Caracteristiques::getAT()
{
	return AT;
}
int Caracteristiques::getPRD()
{
	return PRD;
}


QString Caracteristiques::getCarac(bool plus)
{
	QString string = "";

	if (plus)
	{
		if (COU != 0)
			string = "COU+" + QString::number(COU);

		if (INT != 0 && string != "")
			string += " ; INT+" + QString::number(INT);
		else if (INT != 0 && string == "")
			string += "INT+" + QString::number(INT);

		if (CHA != 0 && string != "")
			string += " ; CHA+" + QString::number(CHA);
		else if (CHA != 0 && string == "")
			string += "CHA+" + QString::number(CHA);

		if (AD != 0 && string != "")
			string += " ; AD+" + QString::number(AD);
		else if (AD != 0 && string == "")
			string += "AD+" + QString::number(AD);

		if (FO != 0 && string != "")
			string += " ; FO+" + QString::number(FO);
		else if (FO != 0 && string == "")
			string += "FO+" + QString::number(FO);

		if (AT != 0 && string != "")
			string += " ; AT+" + QString::number(AT);
		else if (AT != 0 && string == "")
			string += "AT+" + QString::number(AT);

		if (PRD != 0 && string != "")
			string += " ; PRD+" + QString::number(PRD);
		else if (PRD != 0 && string == "")
			string += "PRD+" + QString::number(PRD);

		if (string == "")
			string += "aucun";
	}
	else
	{
		if (COU != 0)
			string = "COU-" + QString::number(COU);

		if (INT != 0 && string != "")
			string += " ; INT-" + QString::number(INT);
		else if (INT != 0 && string == "")
			string += "INT-" + QString::number(INT);

		if (CHA != 0 && string != "")
			string += " ; CHA-" + QString::number(CHA);
		else if (CHA != 0 && string == "")
			string += "CHA-" + QString::number(CHA);

		if (AD != 0 && string != "")
			string += " ; AD-" + QString::number(AD);
		else if (AD != 0 && string == "")
			string += "AD-" + QString::number(AD);

		if (FO != 0 && string != "")
			string += " ; FO-" + QString::number(FO);
		else if (FO != 0 && string == "")
			string += "FO-" + QString::number(FO);

		if (AT != 0 && string != "")
			string += " ; AT-" + QString::number(AT);
		else if (AT != 0 && string == "")
			string += "AT-" + QString::number(AT);

		if (PRD != 0 && string != "")
			string += " ; PRD-" + QString::number(PRD);
		else if (PRD != 0 && string == "")
			string += "PRD-" + QString::number(PRD);

		if (string == "")
			string += "aucun";
	}

	return string;
}


QString Caracteristiques::getCaracteristiques() const
{
	QString string;

	if (COU < 10)
		string += "0" + QString::number(COU) + "_";
	else
		string += QString::number(COU) + "_";

	if (INT < 10)
		string += "0" + QString::number(INT) + "_";
	else
		string += QString::number(INT) + "_";

	if (CHA < 10)
		string += "0" + QString::number(CHA) + "_";
	else
		string += QString::number(CHA) + "_";

	if (AD < 10)
		string += "0" + QString::number(AD) + "_";
	else
		string += QString::number(AD) + "_";

	if (AT_PRD_vrai)
	{
		if (FO < 10)
			string += "0" + QString::number(FO) + "_";
		else
			string += QString::number(FO) + "_";

		if (AT < 10)
			string += "0" + QString::number(AT) + "_";
		else
			string += QString::number(AT) + "_";

		if (PRD < 10)
			string += "0" + QString::number(PRD);
		else
			string += QString::number(PRD);
	}
	else
	{
		if (FO < 10)
			string += "0" + QString::number(FO);
		else
			string += QString::number(FO);
	}

	return string;
}


void Caracteristiques::setCOU(int nb)
{
	COU = nb;
}
void Caracteristiques::setINT(int nb)
{
	INT = nb;
}
void Caracteristiques::setCHA(int nb)
{
	CHA = nb;
}
void Caracteristiques::setAD(int nb)
{
	AD = nb;
}
void Caracteristiques::setFO(int nb)
{
	FO = nb;
}
void Caracteristiques::setAT(int nb)
{
	AT = nb;
}
void Caracteristiques::setPRD(int nb)
{
	PRD = nb;
}


void Caracteristiques::COU_1(bool plus)
{
	if (plus)
	{
		if (COU+1 <= 18)
			COU++;
		else
			return;
	}
	else
	{
		if (COU-1 <= 18)
			COU--;
		else
			return;
	}
}
void Caracteristiques::INT_1(bool plus)
{
	if (plus)
	{
		if (INT+1 <= 18)
			INT++;
		else
			return;
	}
	else
	{
		if (INT-1 <= 18)
			INT--;
		else
			return;
	}
}
void Caracteristiques::CHA_1(bool plus)
{
	if (plus)
	{
		if (CHA+1 <= 18)
			CHA++;
		else
			return;
	}
	else
	{
		if (CHA-1 <= 18)
			CHA--;
		else
			return;
	}
}
void Caracteristiques::AD_1(bool plus)
{
	if (plus)
	{
		if (AD+1 <= 18)
			AD++;
		else
			return;
	}
	else
	{
		if (AD-1 <= 18)
			AD--;
		else
			return;
	}
}
void Caracteristiques::FO_1(bool plus)
{
	if (plus)
	{
		if (FO+1 <= 18)
			FO++;
		else
			return;
	}
	else
	{
		if (FO-1 <= 18)
			FO--;
		else
			return;
	}
}
void Caracteristiques::AT_1(bool plus)
{
	if (plus)
	{
		if (AT+1 <= 18)
			AT++;
		else
			return;
	}
	else
	{
		if (AT-1 <= 18)
			AT--;
		else
			return;
	}
}
void Caracteristiques::PRD_1(bool plus)
{
	if (plus)
	{
		if (PRD+1 <= 18)
			PRD++;
		else
			return;
	}
	else
	{
		if (PRD-1 <= 18)
			PRD--;
		else
			return;
	}
}
