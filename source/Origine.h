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

#ifndef ORIGINE_H
    #define ORIGINE_H

    #include <QtGui>
    #include "Caracteristiques.h"
    #include "Competence.h"

    class Origine
    {
    public:
        Origine(QString nom, int EV, int AT,
                Caracteristiques mini, Caracteristiques maxi);

        void addCompetence(QString nom, QString description, bool obligatoire = true);

        QString getNom() const;
        int getEV() const;
        int getAT() const;
        Caracteristiques getCaracMini() const;
        Caracteristiques getCaracMaxi() const;

        QVector<Competence *> getCompetences(bool obligatoire = true);

    private:
        QString m_nom;
        Caracteristiques *m_caracMini;
        Caracteristiques *m_caracMax;
        int m_EV;
        int m_AT;

        QVector<Competence *> m_competenceObligatoires;
        QVector<Competence *> m_competenceChoisir;
    };

#endif // ORIGINE_H
