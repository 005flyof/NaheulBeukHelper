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

#ifndef PROTECTION_H
    #define PROTECTION_H

    #include <QtGui>
    #include "Caracteristiques.h"

    class Protection
    {
    public:
        Protection(QString nom, int nb_PR,
                   int cou, int intel, int cha, int ad, int fo, int at, int prd,
                   int COU, int INTEL, int CHA, int AD, int FO, int AT, int PRD);

        void setNom(QString nom);
        void setPR(int pr);
        void setBonus(Caracteristiques carac);
        void setMalus(Caracteristiques carac);

    // Récupérer pour afficher
        QString getNom() const;
        QString getBonusAffichage() const;
        QString getMalusAffichage() const;
        QString getNbPR_Affichage() const;
        int getNbPR() const;

    // Récupérer pour enregistrer
        QString protectionEnregistrement() const;

    // Récupérer les caractéristiques
        Caracteristiques getBonus() const;
        Caracteristiques getMalus() const;

    private:
        QString m_nomProtection;
        int m_nombreProtection;
        Caracteristiques *m_bonus;
        Caracteristiques *m_malus;
    };

#endif // PROTECTION_H
