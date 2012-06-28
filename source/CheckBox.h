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

#ifndef CHECK_BOX_H
    #define CHECK_BOX_H

    #include <QCheckBox>
    #include "FenCheckBox.h"

    class CheckBox : public QCheckBox
    {
        Q_OBJECT
    public:
        CheckBox(QPushButton *modif,
                 Vetement *vet, QLabel* label, QLabel* bonus, QLabel* malus);
        CheckBox(QPushButton *modif,
                 Protection *pr, QLabel* label, QLabel* bonus, QLabel* malus, QLabel* nombrePr);
        CheckBox(QPushButton *modif,
                 Arme *arme, QLabel* label, QLabel* bonus, QLabel* malus, QLabel* DEGATS);
        CheckBox(QPushButton *modif,
                 Fleche *fleche, QLabel* label, QLineEdit* nombre, QLabel* bonus,
                 QPushButton *plus, QPushButton *moins);
        CheckBox(QPushButton *modif,
                 QString *equipement, QTextEdit* label);

        ~CheckBox();

    public slots:
        void modifier_vetement();
        void modifier_protection();
        void modifier_arme();
        void modifier_fleche();
        void modifier_equipement();

        void annuler();

        void changerVet(int etat);
        void validVet();

        void changerPr(int etat);
        void validProtection();

        void changerArme(int etat);
        void validArme();

        void changerFleche(int etat);
        void validFleche();

        void changerEquipement(int etat);
        void validEquipement();

        void fleche_plus();
        void fleche_moins();

    signals:
        void bonus_malus_change();

    private:
        FenCheckBox fenChangement;
        QPushButton* modifier;

        // Objets à modifier
        Vetement* m_vet;
        Protection* m_pr;
        Arme* m_arme;
        Fleche* m_fleche;
        QString* m_equipement;

        // Pour afficher
        QTextEdit* m_label_text;
        QLabel* m_label;
        QLabel* m_bonus;
        QLabel* m_malus;
        QLabel* m_pr_nombreLabel;
        QLabel* m_degats;
        QLineEdit* m_nombre;

        // Boutons pour les flèches
        QPushButton *m_plus;
        QPushButton *m_moins;
    };

#endif // CHECK_BOX_H
