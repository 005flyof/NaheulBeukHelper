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

#ifndef VETEMENT_H
    #define VETEMENT_H

    #include <QtGui>
    #include "Caracteristiques.h"

    class Vetement
    {
    public:
        Vetement(QString nom,
                 int cou, int intel, int cha, int ad, int fo,
                 int COU, int INTEL, int CHA, int AD, int FO);

        void setNom(QString nom);
        void setBonus(Caracteristiques carac);
        void setMalus(Caracteristiques carac);
        void setVisible(bool visible);

    // Récupérer pour afficher
        QString getNom() const;
        QString getBonusAffichage() const;
        QString getMalusAffichage() const;
        bool isVisible() const;

    // Récupérer pour enregistrer
        QString vetementEnregistrement() const;

    // Récupérer les caractéristiques
        Caracteristiques getBonus() const;
        Caracteristiques getMalus() const;

    private:
        QString m_nomVetement;
        Caracteristiques *m_bonus;
        Caracteristiques *m_malus;

        bool m_visible;
    };

#endif // VETEMENT_H
