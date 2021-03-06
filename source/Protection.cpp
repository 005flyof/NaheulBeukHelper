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

#include "ClassesPourPersonnage.h"

/*
 * Constructeurs
 */
Protection::Protection(QString nom, int nb_PR,
                       int cou, int intel, int cha, int ad, int fo, int at, int prd,
                       int COU, int INTEL, int CHA, int AD, int FO, int AT, int PRD)
{
    m_nomProtection = nom;
    m_nombreProtection = nb_PR;
    m_bonus = new Caracteristiques(COU, INTEL, CHA, AD, FO, AT, PRD);
    m_malus = new Caracteristiques(cou, intel, cha, ad, fo, at, prd);
    m_rupture_max = 0;
}


/*
 * Accesseurs
 */
void Protection::setNom(QString nom)
{
    m_nomProtection = nom;
}
void Protection::setPR(int pr)
{
    m_nombreProtection = pr;
}
void Protection::setBonus(Caracteristiques carac)
{
    *m_bonus = carac;
}
void Protection::setMalus(Caracteristiques carac)
{
    *m_malus = carac;
}
void Protection::setRupture(int value)
{
    m_rupture_max = value;
}


QString Protection::getNom() const
{
    return m_nomProtection;
}
QString Protection::getRuptAffichage() const
{
    if (m_nomProtection == "Pas de protection")
        return QString("-");
    else if (m_rupture_max == 0)
        return QString("Incassable !");
    else
        return QString("1 à " + QString::number(m_rupture_max));
}
QString Protection::getBonusAffichage() const
{
    QString bonus_string = m_bonus->caracAffichage(true);

    return bonus_string;
}
QString Protection::getMalusAffichage() const
{
    QString malus_string = m_malus->caracAffichage(false);

    return malus_string;
}
QString Protection::getNbPR_Affichage() const
{
    QString nb_PR = QString::number(m_nombreProtection);
    return nb_PR;
}
int Protection::getNbPR() const
{
    return m_nombreProtection;
}
Caracteristiques Protection::getBonus() const
{
    return *m_bonus;
}
Caracteristiques Protection::getMalus() const
{
    return *m_malus;
}
int Protection::getRupture() const
{
    return m_rupture_max;
}


/*
 * Enregistrement
 */
QString Protection::protectionEnregistrement() const
{
    QString pr = "";

    pr += "~!protection!~\n";
    pr += m_nomProtection + "\n";
    pr += QString::number(m_nombreProtection) + "\n";
    pr += m_bonus->caracEnregistrement() + "\n";
    pr += m_malus->caracEnregistrement() + "\n";

    pr += QString::number(m_rupture_max);

    return pr;
}
