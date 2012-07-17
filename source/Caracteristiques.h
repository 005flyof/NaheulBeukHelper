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

#ifndef CARACTERISTIQUES_H
    #define CARACTERISTIQUES_H

    #include <QtGui>

    #define MIN_CARAC 2
    #define MAX_CARAC 18

    class Caracteristiques
    {
    public:
        Caracteristiques(int COU, int INT, int CHA, int AD, int FO);
        Caracteristiques(int COU, int INT, int CHA, int AD, int F0, int AT, int PRD);

        bool estEgal(Caracteristiques const& b) const;
        bool estInfOuEgal(Caracteristiques const& b) const;
        bool estSupOuEgal(Caracteristiques const& b) const;
        Caracteristiques& operator=(Caracteristiques const& b);
        Caracteristiques& operator+=(Caracteristiques const& b);
        Caracteristiques& operator-=(Caracteristiques const& b);

        void caracRemplir(int COU, int INT, int CHA, int AD, int FO);
        void caracRemplir(int COU, int INT, int CHA, int AD, int FO, int AT, int PRD);

        QString caracAffichage(bool plus);
        QString caracEnregistrement() const;

        int getCourage() const;
        int getIntelligence() const;
        int getCharisme() const;
        int getAdresse() const;
        int getForce() const;
        int getAttaque() const;
        int getParade() const;

        void setCourage(int COU);
        void setIntelligence(int INT);
        void setCharisme(int CHA);
        void setAdresse(int AD);
        void setForce(int FO);
        void setAttaque(int AT);
        void setParade(int PRD);

    private:
        int m_courage;
        int m_intelligence;
        int m_charisme;
        int m_adresse;
        int m_force;

        bool utilisation_AT_PRD;
        int m_attaque;
        int m_parade;
    };

    bool operator==(Caracteristiques const& a, Caracteristiques const& b);
    bool operator<=(Caracteristiques const& a, Caracteristiques const& b);
    bool operator>=(Caracteristiques const& a, Caracteristiques const& b);


#endif // CARACTERISTIQUES_H
