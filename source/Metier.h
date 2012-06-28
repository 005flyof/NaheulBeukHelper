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

#ifndef METIER_H
    #define METIER_H

    #include <QtGui>
    #include "Caracteristiques.h"
    #include "Competence.h"

    class Metier
    {
    public:
        Metier(QString nom = "Métier sans nom !", int AT = 0, int PRD = 0,
               int cou = 0, int intel = 0, int cha = 0, int ad = 0, int fo = 0);

        void setCarac_mini(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup);
        void setEV(QStringList classesModifiees, int EV_pourClasseModifiees, int EV_pourAutresClasses, bool pourcent);
        void setEA(QString typeEA, int EA);
        void addCompetence(QString nom, QString description, bool obligatoire = true);

        QString getNom() const;
        Caracteristiques getMini() const;
        int getAT() const;
        int getPRD() const;
        QStringList getClassesModifiees() const;
        int getEV_pourClassesModifiees() const;
        int getEV_pourAutresClasses() const;
        bool getEV_pourAutresClasses_pourcent() const;


        bool getPresenceEA() const;
        int getEA() const;
        QString getTypeEA() const;

        QVector<Competence *> getCompetences(bool obligatoire = true);

    private:
        QString m_nomMetier;
        Caracteristiques m_caracMini;

        int m_AT;
        int m_PRD;

        int m_EV_pourClassesModifiees;
        QStringList m_classesModifiees;
        int m_EV_pourAutresClasses;

        bool m_presenceEA;
        int m_EA;
        QString m_typeEA;
        bool m_pourcent;

        QVector<Competence *> m_competenceObligatoires;
        QVector<Competence *> m_competenceChoisir;
    };

#endif // METIER_H
