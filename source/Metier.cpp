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

Metier::Metier(QString nom, int AT, int PRD,
               int cou, int intel, int cha, int ad, int fo)
{
    m_nom = nom;
    m_caracMini = new Caracteristiques(cou, intel, cha, ad, fo);
    m_AT = AT;
    m_PRD = PRD;

    m_EV_pourClassesModifiees = 0;
    m_EV_pourAutresClasses = 0;

    m_EA = 0;
    m_typeEA = "";
    m_presenceEA = false;
    m_pourcent = false;
}


void Metier::setEV(QStringList classesModifiees, int EV_pourClasseModifiees, int EV_pourAutresClasses, bool pourcent)
{
    m_classesModifiees = classesModifiees;
    m_EV_pourClassesModifiees = EV_pourClasseModifiees;
    m_EV_pourAutresClasses = EV_pourAutresClasses;
    m_pourcent = pourcent;
}
void Metier::setEA(QString typeEA, int EA)
{
    m_EA = EA;
    m_typeEA = typeEA;
    m_presenceEA = true;
}
/*
void Metier::addCompetence(QString nom, QString description, bool obligatoire)
{
    if (obligatoire)
        m_competenceObligatoires.append(new Competence(nom, description));
    else
        m_competenceChoisir.append(new Competence(nom, description));
}
*/

QString Metier::getNom() const
{
    return m_nom;
}
Caracteristiques Metier::getCaracMini() const
{
    return *m_caracMini;
}
int Metier::getAT() const
{
    return m_AT;
}
int Metier::getPRD() const
{
    return m_PRD;
}
QStringList Metier::getClassesModifiees_EV() const
{
    return m_classesModifiees;
}
int Metier::getEV_pourClassesModifiees() const
{
    return m_EV_pourClassesModifiees;
}
int Metier::getEV_pourAutresClasses() const
{
    return m_EV_pourAutresClasses;
}
bool Metier::getEV_pourAutresClasses_pourcent() const
{
    return m_pourcent;
}

bool Metier::getPresenceEA() const
{
    return m_presenceEA;
}
int Metier::getEA() const
{
    return m_EA;
}
QString Metier::getTypeEA() const
{
    return m_typeEA;
}
/*
QVector<Competence *> Metier::getCompetences(bool obligatoire)
{
    if (obligatoire)
        return m_competenceObligatoires;
    else
        return m_competenceChoisir;
}
*/
