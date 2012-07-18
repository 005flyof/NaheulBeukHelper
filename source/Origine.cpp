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

Origine::Origine(QString nom, int EV, int AT,
                 int cou, int intel, int cha, int ad, int fo,
                 int COU, int INTEL, int CHA, int AD, int FO)
{
    m_nom = nom;
    m_caracMini = new Caracteristiques(cou, intel, cha, ad, fo);
    m_caracMax = new Caracteristiques(COU, INTEL, CHA, AD, FO);
    m_EV = EV;
    m_AT = AT;
}
/*
void Origine::addCompetence(QString nom, QString description, bool obligatoire)
{
    if (obligatoire)
        m_competenceObligatoires.append(new Competence(nom, description));
    else
        m_competenceChoisir.append(new Competence(nom, description));
}
*/
QString Origine::getNom() const
{
    return m_nom;
}
int Origine::getEV() const
{
    return m_EV;
}
int Origine::getAT() const
{
    return m_AT;
}
Caracteristiques Origine::getCaracMini() const
{
    return *m_caracMini;
}
Caracteristiques Origine::getCaracMaxi() const
{
    return *m_caracMax;
}
/*
QVector<Competence *> Origine::getCompetences(bool obligatoire = true)
{
    if (obligatoire)
        return m_competenceObligatoires;
    else
        return m_competenceChoisir;
}
*/
