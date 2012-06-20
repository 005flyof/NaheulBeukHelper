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

#include "CheckBox.h"
#include <QtGui>
#include "Personnage.h"
#include "FenCheckBox.h"
#include <stdio.h>
#include <stdlib.h>

CheckBox::CheckBox(QPushButton *modif, Vetement* vet, QLabel* label, QLabel* bonus, QLabel* malus)
    : QCheckBox(), modifier(modif), m_vet(vet), m_label(label), m_bonus(bonus), m_malus(malus)
{
    fenChangement = FenCheckBox(this, TypeObjet::vet);

    // Objets
    m_pr = 0;
    m_arme = 0;
    m_fleche = 0;
    m_equipement = 0;

    // Boutons
    m_plus = 0;
    m_moins = 0;

    // Label
    m_nombre = 0;
    m_pr_nombreLabel = 0;
    m_degats = 0;
}
CheckBox::CheckBox(QPushButton *modif, Protection *pr, QLabel* label, QLabel* bonus, QLabel* malus, QLabel* nombrePr)
    : QCheckBox(), modifier(modif), m_pr(pr), m_label(label), m_bonus(bonus), m_malus(malus), m_pr_nombreLabel(nombrePr)
{
    fenChangement = FenCheckBox(this, protect);

    // Objets
    m_vet = 0;
    m_arme = 0;
    m_fleche = 0;
    m_equipement = 0;

    // Boutons
    m_plus = 0;
    m_moins = 0;

    // Label
    m_nombre = 0;
    m_degats = 0;
}
CheckBox::CheckBox(QPushButton *modif, Arme *arme, QLabel* label, QLabel* bonus, QLabel* malus, QLabel* DEGATS)
    : QCheckBox(), modifier(modif), m_arme(arme), m_label(label), m_bonus(bonus), m_malus(malus), m_degats(DEGATS)
{
    fenChangement = FenCheckBox(this, TypeObjet::arme);

    // Objets
    m_vet = 0;
    m_pr = 0;
    m_fleche = 0;
    m_equipement = 0;

    // Boutons
    m_plus = 0;
    m_moins = 0;

    // Label
    m_nombre = 0;
    m_pr_nombreLabel = 0;
}
CheckBox::CheckBox(QPushButton *modif, Fleche *fleche, QLabel* label, QLineEdit* nombre, QLabel* bonus,
                   QPushButton *plus, QPushButton *moins)
    : QCheckBox(), modifier(modif), m_fleche(fleche), m_label(label), m_bonus(bonus),
      m_nombre(nombre), m_plus(plus), m_moins(moins)
{
    fenChangement = FenCheckBox(this, TypeObjet::fleche);

    // Objets
    m_vet = 0;
    m_pr = 0;
    m_arme = 0;
    m_equipement = 0;

    // Label
    m_malus = 0;
    m_pr_nombreLabel = 0;
    m_degats = 0;

    QObject::connect(m_plus, SIGNAL(clicked()), this, SLOT(fleche_plus()));
    QObject::connect(m_moins, SIGNAL(clicked()), this, SLOT(fleche_moins()));
}
CheckBox::CheckBox(QPushButton *modif, QString *equipement, QTextEdit* label)
    : QCheckBox(), modifier(modif), m_equipement(equipement), m_label_text(label), m_label(0)
{
    fenChangement = FenCheckBox(this, equip);

    // Objets
    m_vet = 0;
    m_pr = 0;
    m_arme = 0;
    m_fleche = 0;

    // Boutons
    m_plus = 0;
    m_moins = 0;

    // Label
    m_bonus = 0;
    m_malus = 0;
    m_nombre = 0;
    m_pr_nombreLabel = 0;
    m_degats = 0;
}

CheckBox::~CheckBox()
{
}


void CheckBox::modifier_vetement()
{
    fenChangement.afficher();
    fenChangement.modif_vetement(m_vet);
}
void CheckBox::modifier_protection()
{
    fenChangement.afficher();
    fenChangement.modif_protection(m_pr);
}
void CheckBox::modifier_arme()
{
    fenChangement.afficher();
    fenChangement.modif_arme(m_arme);
}
void CheckBox::modifier_fleche()
{
    fenChangement.afficher();
    fenChangement.modif_fleche(m_fleche);
}
void CheckBox::modifier_equipement()
{
    fenChangement.afficher();
    fenChangement.modif_equipement(m_equipement);
}

void CheckBox::annuler()
{
    this->setChecked(false);
    modifier->setEnabled(false);
}


void CheckBox::changerVet(int etat)
{
    if (etat == Qt::Checked)
        fenChangement.afficher();
    else
    {
        m_vet->setNom(PAS_VETEMENT);
        m_vet->setBonus(0, 0, 0, 0, 0);
        m_vet->setMalus(0, 0, 0, 0, 0);

        m_label->setText(m_vet->getNom());
        m_bonus->setText("-");
        m_malus->setText("-");

        modifier->setEnabled(false);

        emit bonus_malus_change();
    }
}
void CheckBox::validVet()
{
    *m_vet = fenChangement.return_vetement();

// On affiche ce que l'on a fait
    m_label->setText(m_vet->getNom());
    m_bonus->setText(m_vet->getBonus());
    m_malus->setText(m_vet->getMalus());

    emit bonus_malus_change();

    modifier->setEnabled(true);
}

void CheckBox::changerPr(int etat)
{
    if (etat == Qt::Checked)
        fenChangement.afficher();
    else
    {
        m_pr->setNom(PAS_PROTECTION);
        m_pr->setPr(0);
        m_pr->setBonus(0, 0, 0, 0, 0, 0, 0);
        m_pr->setMalus(0, 0, 0, 0, 0, 0, 0);

        m_label->setText(m_pr->getNom());
        m_pr_nombreLabel->setText("-");
        m_bonus->setText("-");
        m_malus->setText("-");

        modifier->setEnabled(false);

        emit bonus_malus_change();
    }
}
void CheckBox::validProtection()
{
    *m_pr = fenChangement.return_protection();

// On affiche ce que l'on a fait
    m_label->setText(m_pr->getNom());
    m_pr_nombreLabel->setText(m_pr->getNombrePR());
    m_bonus->setText(m_pr->getBonus());
    m_malus->setText(m_pr->getMalus());

    emit bonus_malus_change();

    modifier->setEnabled(true);
}

void CheckBox::changerArme(int etat)
{
    if (etat == Qt::Checked)
        fenChangement.afficher();
    else
    {
        m_arme->setNom(PAS_ARME);
        m_arme->setDegats(1, -2);
        m_arme->setBonus(0, 0, 0, 0, 0, 0, 0);
        m_arme->setMalus(0, 0, 0, 0, 0, 0, 0);

        m_label->setText(m_arme->getNom());
        m_degats->setText(QString::number(m_arme->des()) + "D " + QString::number(m_arme->degats()));
        m_bonus->setText("-");
        m_malus->setText("-");

        modifier->setEnabled(false);

        emit bonus_malus_change();
    }
}
void CheckBox::validArme()
{
    *m_arme = fenChangement.return_arme();

// On affiche ce que l'on a fait
    m_label->setText(m_arme->getNom());
    m_degats->setText(m_arme->getDegats());
    m_bonus->setText(m_arme->getBonus());
    m_malus->setText(m_arme->getMalus());

    emit bonus_malus_change();

    modifier->setEnabled(true);
}

void CheckBox::changerFleche(int etat)
{
    if (etat == Qt::Checked)
        fenChangement.afficher();
    else
    {
        m_fleche->setNom(PAS_FLECHE);
        m_fleche->setNombre(0);
        m_fleche->setDegats(0);
        m_fleche->setBonus(0);

        m_label->setText(m_fleche->getNom());
        m_nombre->setText(QString::number(m_fleche->getNombre()));
            m_nombre->setEnabled(false);
        m_bonus->setText("-");

        modifier->setEnabled(false);

        m_plus->setEnabled(false);
        m_moins->setEnabled(false);
    }
}
void CheckBox::validFleche()
{
    *m_fleche = fenChangement.return_fleche();

// On affiche ce que l'on a fait
    m_label->setText(m_fleche->getNom());
    m_nombre->setText(QString::number(m_fleche->getNombre()));
        m_nombre->setEnabled(true);
    m_bonus->setText(m_fleche->getBonus());

    m_plus->setEnabled(true);
    m_moins->setEnabled(true);

    emit bonus_malus_change();

    modifier->setEnabled(true);
}

void CheckBox::changerEquipement(int etat)
{
    if (etat == Qt::Checked)
        fenChangement.afficher();
    else
    {
        *m_equipement = PAS_EQUIPEMENTS;
        m_label_text->setText(*m_equipement);

        modifier->setEnabled(false);
    }
}
void CheckBox::validEquipement()
{
    *m_equipement = fenChangement.return_equipement();

// On affiche ce que l'on a fait
    m_label_text->setText(*m_equipement);

    emit bonus_malus_change();

    modifier->setEnabled(true);
}


void CheckBox::fleche_plus()
{
    m_fleche->setNombre(m_fleche->getNombre() + 1);
    m_nombre->setText(QString::number(m_fleche->getNombre()));
}
void CheckBox::fleche_moins()
{
    m_fleche->setNombre(m_fleche->getNombre() - 1);
    m_nombre->setText(QString::number(m_fleche->getNombre()));
}
