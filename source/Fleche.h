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
        Fleche(Fleche *ACopier);

        int getNombre() const;
        QString getNom() const;
        QString getBonus() const;
        int getAD() const;
        int getPI() const;

        void setNom(QString nom);
        void setNombre(int nb);
        void setDegats(int degats);
        void setBonus(int ad_bonus);

        QString getFleche() const;

    private:
        int m_nombre;
        QString m_nomFleche;
        int m_degats;
        int m_bonusAD;
    };

#endif // FLECHE_H
