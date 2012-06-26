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

/*
 * Constructeurs
 */
Arme::Arme(QString nom,
           int nbDes, int degatsEnPlus,
           int cou, int intel, int cha, int ad, int fo, int at, int prd,
           int COU, int INTEL, int CHA, int AD, int FO, int AT, int PRD)
{
    m_nomArme = nom;
    m_nombreDes = nbDes;
    m_degats = degatsEnPlus;
    m_bonus = Caracteristiques(COU, INTEL, CHA, AD, FO, AT, PRD);
    m_malus = Caracteristiques(cou, intel, cha, ad, fo, at, prd);
}


/*
 * Accesseurs
 */
void Arme::setBonus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup, int AT_recup, int PRD_recup)
{
    m_bonus.remplir(COU_recup, INT_recup, CHA_recup, AD_recup, FO_recup, AT_recup, PRD_recup);
}
void Arme::setMalus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup, int AT_recup, int PRD_recup)
{
    m_malus.remplir(COU_recup, INT_recup, CHA_recup, AD_recup, FO_recup, AT_recup, PRD_recup);
}

void Arme::setNom(QString nom)
{
    m_nomArme = nom;
}

void Arme::setDegats(int des, int degats)
{
    m_nombreDes = des;
    m_degats = degats;
}

void Arme::setRupture(int maximum)
{
    m_rupture_max = maximum;
}

void Arme::setType(Arme::typeArme type)
{
    m_type = type;
}


QString Arme::getNom() const
{
    return m_nomArme;
}

QString Arme::getBonusAffichage() const
{
    QString bonus_string = m_bonus.getCarac(true);

    return bonus_string;
}
QString Arme::getMalusAffichage() const
{
    QString malus_string = m_malus.getCarac(false);

    return malus_string;
}
Caracteristiques Arme::getBonus() const
{
    return m_bonus;
}
Caracteristiques Arme::getMalus() const
{
    return m_malus;
}

QString Arme::getDegatsAffichage() const
{
    QString degats = "";

    if (m_degats > 0)
        degats = QString::number(m_nombreDes) + "D + " + QString::number(m_degats);
    else if (m_degats < 0)
        degats = QString::number(m_nombreDes) + "D " + QString::number(m_degats);
    else
        degats = QString::number(m_nombreDes) + "D";

    return degats;
}
int Arme::getNbDes() const
{
    return m_nombreDes;
}
int Arme::getDegatsEnPlus() const
{
    return m_degats;
}


/*
 * Enregistrement
 */
QString Arme::armeEnregistrement() const
{
    QString arme = "";

    arme += "~!arme!~\n";
    arme += m_nomArme + "\n";
    arme += QString::number(m_nombreDes) + "\n";
    arme += QString::number(m_degats) + "\n";
    arme += m_bonus.getCaracteristiques() + "\n";
    arme += m_malus.getCaracteristiques() + "\n";

    arme += QString::number(m_type) + "\n";
    arme += QString::number(m_rupture_max);


    return arme;
}
