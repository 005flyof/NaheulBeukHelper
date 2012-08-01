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

#ifndef EQUIPMODIF_H
    #define EQUIPMODIF_H

    #include <QDialog>
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class EquipModif;
    }

    class EquipModif : public QDialog
    {
        Q_OBJECT

    public:
        explicit EquipModif(Protection* objet);
        explicit EquipModif(Arme* objet);
        explicit EquipModif(Fleche* objet);
        explicit EquipModif(Vetement* objet);
        ~EquipModif();

    public slots:
        void accept();

    private slots:
        void on_vider_clicked();

    private:
        Ui::EquipModif *ui;

        void chargerAffichage();

        Protection *m_pr;
        Arme *m_arme;
        Fleche *m_fleche;
        Vetement *m_vet;

    };

#endif // EQUIPMODIF_H
