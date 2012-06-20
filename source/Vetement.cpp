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

Vetement::Vetement(QString nom, Caracteristiques bonus_recup, Caracteristiques malus_recup)
{
	m_nomVetement = nom;
	m_bonus = bonus_recup;
	m_malus = malus_recup;
}

Vetement::Vetement(QString nom,
				   int cou, int intel, int cha, int ad, int fo,
				   int COU, int INTEL, int CHA, int AD, int FO)
{
	m_nomVetement = nom;
	m_bonus = Caracteristiques(false, COU, INTEL, CHA, AD, FO);
	m_malus = Caracteristiques(false, cou, intel, cha, ad, fo);
}


Vetement::Vetement(Vetement *ACopier)
{
	m_nomVetement = ACopier->m_nomVetement;
	m_bonus = ACopier->m_bonus;
	m_malus = ACopier->m_malus;
}


void Vetement::setBonus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup)
{
	m_bonus.remplir(COU_recup, INT_recup, CHA_recup, AD_recup, FO_recup);
}
void Vetement::setMalus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup)
{
	m_malus.remplir(COU_recup, INT_recup, CHA_recup, AD_recup, FO_recup);
}
void Vetement::setNom(QString nom)
{
	m_nomVetement = nom;
}


QString Vetement::getNom() const
{
	return m_nomVetement;
}
QString Vetement::getBonus()
{
	QString bonus_string = m_bonus.getCarac(true);

	return bonus_string;
}
QString Vetement::getMalus()
{
	QString malus_string = m_malus.getCarac(false);

	return malus_string;
}


QString Vetement::getVetement() const
{
	QString vetement = "";

	vetement += m_nomVetement + "\n";
	vetement += m_bonus.getCaracteristiques() + "\n";
	vetement += m_malus.getCaracteristiques();

	return vetement;
}


Caracteristiques Vetement::bonus() const
{
	return m_bonus;
}
Caracteristiques Vetement::malus() const
{
	return m_malus;
}
