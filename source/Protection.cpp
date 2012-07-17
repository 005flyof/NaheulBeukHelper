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
Protection::Protection(QString nom, int nb_PR,
                       int cou, int intel, int cha, int ad, int fo, int at, int prd,
                       int COU, int INTEL, int CHA, int AD, int FO, int AT, int PRD)
{
    m_nomProtection = nom;
    m_nombreProtection = nb_PR;
    m_bonus = new Caracteristiques(COU, INTEL, CHA, AD, FO, AT, PRD);
    m_malus = new Caracteristiques(cou, intel, cha, ad, fo, at, prd);
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

QString Protection::getNom() const
{
    return m_nomProtection;
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
    pr += m_malus->caracEnregistrement();

    return pr;
}
