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

Protection::Protection(QString nom, int nb_PR,
					   int cou, int intel, int cha, int ad, int fo, int at, int prd,
					   int COU, int INTEL, int CHA, int AD, int FO, int AT, int PRD)
{
	m_nomProtection = nom;
	m_nombreProtection = nb_PR;
	m_bonus = Caracteristiques(true, COU, INTEL, CHA, AD, FO, AT, PRD);
	m_malus = Caracteristiques(true, cou, intel, cha, ad, fo, at, prd);
}

Protection::Protection(Protection *ACopier)
{
	m_nomProtection = ACopier->m_nomProtection;
	m_nombreProtection = ACopier->m_nombreProtection;
	m_bonus = ACopier->m_bonus;
	m_malus = ACopier->m_malus;
}


void Protection::setBonus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup, int AT_recup, int PRD_recup)
{
	m_bonus.remplir(COU_recup, INT_recup, CHA_recup, AD_recup, FO_recup, AT_recup, PRD_recup);
}
void Protection::setMalus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup, int AT_recup, int PRD_recup)
{
	m_malus.remplir(COU_recup, INT_recup, CHA_recup, AD_recup, FO_recup, AT_recup, PRD_recup);
}
void Protection::setNom(QString nom)
{
	m_nomProtection = nom;
}
void Protection::setPr(int pr)
{
	m_nombreProtection = pr;
}


QString Protection::getNom() const
{
	return m_nomProtection;
}
QString Protection::getBonus()
{
	QString bonus_string = m_bonus.getCarac(true);

	return bonus_string;
}
QString Protection::getMalus()
{
	QString malus_string = m_malus.getCarac(false);

	return malus_string;
}
QString Protection::getNombrePR()
{
	QString nb_PR = QString::number(m_nombreProtection);
	return nb_PR;
}
int Protection::nombreProtection() const
{
	return m_nombreProtection;
}


QString Protection::getProtection() const
{
	QString pr = "";

	pr += "~!protection!~\n";
	pr += m_nomProtection + "\n";
	pr += QString::number(m_nombreProtection) + "\n";
	pr += m_bonus.getCaracteristiques() + "\n";
	pr += m_malus.getCaracteristiques();

	return pr;
}


Caracteristiques Protection::bonus() const
{
	return m_bonus;
}
Caracteristiques Protection::malus() const
{
	return m_malus;
}
