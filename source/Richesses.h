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
        Richesses(int OR = 0, int ARGENT = 0, int CUIVRE = 0);

        void setRichesses_Or(unsigned int OR);
        void setRichesses_Argent(unsigned int Argent);
        void setRichesses_Cuivre(unsigned int Cuivre);
        void or_plus(int valeur);
        void argent_plus(int valeur);
        void cuivre_plus(int valeur);
        void or_moins(int valeur);
        void argent_moins(int valeur);
        void cuivre_moins(int valeur);

        int getRichesses_Or() const;
        int getRichesses_Argent() const;
        int getRichesses_Cuivre() const;

        void conversionPAPC_PO();
        void conversionPO_PA();
        void conversionPO_PC();
        void conversionPA_PC();

        QString getRichesses() const;

    private:
        int m_or;
        int m_argent;
        int m_cuivre;

        QWidget *pb;
    };

#endif // RICHESSES_H
