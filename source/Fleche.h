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

#ifndef FLECHE_H
    #define FLECHE_H

    #include <QtGui>
    #include "Caracteristiques.h"

    class Fleche
    {
    public:
        Fleche(QString nom, int nb, int PI, int AD);

        int getNombre() const;
        QString getNom() const;
        QString getBonusAffichage() const;
        int getAD() const;
        int getPI() const;
        int getNbDes() const;
        int getRupture() const;
        QString getRuptAffichage() const;


        void setNom(QString nom);
        void setNombre(int nb);
        void setPI(int degats);
        void setAD(int ad_bonus);
        void setNbDes(int value);
        void setRupture(int value);

        QString flechesEnregistrement() const;

    private:
        int m_nombre;
        QString m_nomFleche;
        int m_nbDes;
        int m_degats;
        int m_bonusAD;
        int m_rupture_max;
    };

#endif // FLECHE_H
