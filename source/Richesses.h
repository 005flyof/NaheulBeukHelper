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

#ifndef RICHESSES_H
    #define RICHESSES_H

    #include <QtGui>

    class Richesses
    {
    public:
        Richesses(int OR, int ARGENT, int CUIVRE);

        void setOr(int value);
        void setArgent(int value);
        void setCuivre(int value);

        int getOr() const;
        int getArgent() const;
        int getCuivre() const;

        enum conversion
        {
            PO_en_PA,
            PO_en_PC,
            PA_en_PC,
            PA_PC_en_PO
        };
        void convertir(conversion convert);

        QString richessesEnregistrement() const;

    private:
        int m_or;
        int m_argent;
        int m_cuivre;

        QWidget *pb;
    };

#endif // RICHESSES_H
