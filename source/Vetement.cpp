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
Vetement::Vetement(QString nom,
                   int cou, int intel, int cha, int ad, int fo,
                   int COU, int INTEL, int CHA, int AD, int FO)
{
    m_nomVetement = nom;
    m_bonus = new Caracteristiques(COU, INTEL, CHA, AD, FO);
    m_malus = new Caracteristiques(cou, intel, cha, ad, fo);
}


/*
 * Accesseurs
 */
void Vetement::setNom(QString nom)
{
    m_nomVetement = nom;
}

QString Vetement::getNom() const
{
    return m_nomVetement;
}
QString Vetement::getBonusAffichage() const
{
    QString bonus_string = m_bonus->caracAffichage(true);

    return bonus_string;
}
QString Vetement::getMalusAffichage() const
{
    QString malus_string = m_malus->caracAffichage(false);

    return malus_string;
}
Caracteristiques Vetement::getBonus() const
{
    return *m_bonus;
}
Caracteristiques Vetement::getMalus() const
{
    return *m_malus;
}

/*
 * Enregistrement
 */
QString Vetement::getVetement() const
{
    QString vetement = "";

    vetement += m_nomVetement + "\n";
    vetement += m_bonus->caracEnregistrement() + "\n";
    vetement += m_malus->caracEnregistrement();

    return vetement;
}
