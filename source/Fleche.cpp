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
Fleche::Fleche(QString nom, int nb, int PI, int AD)
{
    m_nombre = nb;
    m_nomFleche = nom;
    m_degats = PI;
    m_bonusAD = AD;
}


/*
 * Accesseurs
 */
int Fleche::getNombre() const
{
    return m_nombre;
}
QString Fleche::getNom() const
{
    return m_nomFleche;
}
QString Fleche::getBonusAffichage() const
{
    QString bonus = "PI : " + QString::number(m_degats);
    bonus += " / AD+" + QString::number(m_bonusAD);

    return bonus;
}
int Fleche::getAD() const
{
    return m_bonusAD;
}
int Fleche::getPI() const
{
    return m_degats;
}


void Fleche::setNom(QString nom)
{
    m_nomFleche = nom;
}
void Fleche::setNombre(int nb)
{
    if (nb < 0)
        m_nombre = 0;
    else
        m_nombre = nb;
}
void Fleche::setPI(int degats)
{
    m_degats = degats;
}
void Fleche::setAD(int ad_bonus)
{
    m_bonusAD = ad_bonus;
}


/*
 * Enregistrement
 */
QString Fleche::flechesEnregistrement() const
{
    QString fleche = "";

    fleche += "~!fleche!~\n";
    fleche += m_nomFleche + "\n";
    fleche += QString::number(m_nombre) + "\n";
    fleche += QString::number(m_degats) + "\n";

    if (m_bonusAD < 10)
        fleche += "0" + QString::number(m_bonusAD);
    else
        fleche += QString::number(m_bonusAD);

    return fleche;
}
