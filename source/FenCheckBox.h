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

#ifndef FENCHECKBOX_H
    #define FENCHECKBOX_H

    #include "ClassePourPersonnage.h"
    #include <QtGui>

    enum TypeObjet
    {
        vet,
        protect,
        arme,
        fleche,
        equip
    };

    class FenCheckBox
    {
    public:
        FenCheckBox();
        FenCheckBox(QWidget* parent, TypeObjet obj);
        ~FenCheckBox();

        void afficher();

        // Réception des éléments
        void modif_vetement(Vetement const& objet);
        void modif_protection(Protection const& objet);
        void modif_arme(Arme const& objet);
        void modif_fleche(Fleche const& objet);
        void modif_equipement(QString* objet);

        // Renvoie des éléments
        Vetement return_vetement();
        Protection return_protection();
        Arme return_arme();
        Fleche return_fleche();
        QString return_equipement();

    private:
        QWidget *m_parent;
        QVector<QSpacerItem *> tableau_spacers;

        void initialiserVet();
        void initialiserPr();
        void initialiserArme();
        void initialiserFleche();
        void initialiserEquip();

        // Pour la modification
        QDialog *dialogue;
        QGridLayout *layout;
        QDialogButtonBox *boutonBox;

        QLabel* degats;
            QLabel* plusDegats;
            QSpinBox *des_spin;
            QSpinBox *degats_spin;

        QLineEdit *nom;
        QTextEdit *nom_equip;
        QLabel *bonusCOU;
            QSpinBox *COU;
        QLabel *bonusINT;
            QSpinBox *INT;
        QLabel *bonusCHA;
            QSpinBox *CHA;
        QLabel *bonusAD;
            QSpinBox *AD;
        QLabel *bonusFO;
            QSpinBox *FO;
        QLabel *bonusAT;
            QSpinBox *AT;
        QLabel *bonusPRD;
            QSpinBox *PRD;

        QLabel* bonusPI;
            QSpinBox *PI;
        QLabel* nb_label;
            QSpinBox *nb;
        QLabel* pr_label;
            QSpinBox* pr;

        QLabel *malusCOU;
            QSpinBox *cou;
        QLabel *malusINT;
            QSpinBox *intel;
        QLabel *malusCHA;
            QSpinBox *cha;
        QLabel *malusAD;
            QSpinBox *ad;
        QLabel *malusFO;
            QSpinBox *fo;
        QLabel *malusAT;
            QSpinBox *at;
        QLabel *malusPRD;
            QSpinBox *prd;
    };

#endif // FENCHECKBOX_H
