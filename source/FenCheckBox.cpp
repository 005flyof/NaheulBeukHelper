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

#include "FenCheckBox.h"
#include "ClassePourPersonnage.h"

FenCheckBox::FenCheckBox()
{}
FenCheckBox::FenCheckBox(QWidget *parent, TypeObjet obj)
    : m_parent(parent)
{
    QString nomfenetre = "Changer ";
    dialogue = new QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    layout = new QGridLayout();

    // Initialisation des affichages
    switch (obj)
    {
    case vet:
        nomfenetre += "le vêtement !";
        initialiserVet();
        break;

    case protect:
        nomfenetre += "la protection !";
        initialiserPr();
        break;

    case arme:
        nomfenetre += "l'arme !";
        initialiserArme();
        break;

    case fleche:
        nomfenetre += "les flêches !";
        initialiserFleche();
        break;

    case equip:
        nomfenetre += "l'équipement !";
        initialiserEquip();
        break;

    default:
        fatalError("Type d'objet inconnu !\n        |-> Numero de l'objet : " + QString::number(obj));
        break;
    }


    dialogue->setWindowTitle(nomfenetre);
    dialogue->setModal(true);
    setIcone(dialogue);

    boutonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(boutonBox, 12, 1, 1, 4);

    // Connexion des boutons
    switch (obj)
    {
    case vet:
        QObject::connect(boutonBox, SIGNAL(accepted()), parent, SLOT(validVet()));
        break;

    case protect:
        QObject::connect(boutonBox, SIGNAL(accepted()), parent, SLOT(validProtection()));
        break;

    case arme:
        QObject::connect(boutonBox, SIGNAL(accepted()), parent, SLOT(validArme()));
        break;

    case fleche:
        QObject::connect(boutonBox, SIGNAL(accepted()), parent, SLOT(validFleche()));
        break;

    case equip:
        QObject::connect(boutonBox, SIGNAL(accepted()), parent, SLOT(validEquipement()));
        break;

    default:
        fatalError("Type d'objet inconnu !\n        |-> Numero de l'objet : " + QString::number(obj));
        break;
    }
    QObject::connect(boutonBox, SIGNAL(rejected()), dialogue, SLOT(close()));
    QObject::connect(boutonBox, SIGNAL(rejected()), parent, SLOT(annuler()));

    dialogue->setLayout(layout);
}
FenCheckBox::~FenCheckBox()
{}

void FenCheckBox::afficher()
{
    dialogue->show();
}

void FenCheckBox::initialiserVet()
{
    nom = new QLineEdit();
    QLabel *nom_label = new QLabel("Nom :");

    tableau_spacers.append(new QSpacerItem(10, 10));

    bonusCOU = new QLabel("Bonus -> COU :");
        COU = new QSpinBox();
            COU->setMaximum(20);
    bonusINT = new QLabel("Bonus -> INT :");
        INT = new QSpinBox();
            INT->setMaximum(20);
    bonusCHA = new QLabel("Bonus -> CHA :");
        CHA = new QSpinBox();
            CHA->setMaximum(20);
    bonusAD = new QLabel("Bonus -> AD :");
        AD = new QSpinBox();
            AD->setMaximum(20);
    bonusFO = new QLabel("Bonus -> FO :");
        FO = new QSpinBox();
            FO->setMaximum(20);

    tableau_spacers.append(new QSpacerItem(10, 10));

    malusCOU = new QLabel("Malus -> COU :");
        cou = new QSpinBox();
            cou->setMaximum(20);
    malusINT = new QLabel("Malus -> INT :");
        intel = new QSpinBox();
            intel->setMaximum(20);
    malusCHA = new QLabel("Malus -> CHA :");
        cha = new QSpinBox();
            cha->setMaximum(20);
    malusAD = new QLabel("Malus -> AD :");
        ad = new QSpinBox();
            ad->setMaximum(20);
    malusFO = new QLabel("Malus -> FO :");
        fo = new QSpinBox();
            fo->setMaximum(20);


    layout->addWidget(nom_label, 1, 1, 1, 1);
    layout->addWidget(nom, 1, 2, 1, 4);
    layout->addItem(tableau_spacers.at(0), 2, 1, 1, 5);

    layout->addWidget(bonusCOU, 3, 1, 1, 1);
    layout->addWidget(COU,      3, 2, 1, 1);
    layout->addWidget(bonusINT, 4, 1, 1, 1);
    layout->addWidget(INT,      4, 2, 1, 1);
    layout->addWidget(bonusCHA, 5, 1, 1, 1);
    layout->addWidget(CHA,      5, 2, 1, 1);
    layout->addWidget(bonusAD,  6, 1, 1, 1);
    layout->addWidget(AD,       6, 2, 1, 1);
    layout->addWidget(bonusFO,  7, 1, 1, 1);
    layout->addWidget(FO,       7, 2, 1, 1);

    layout->addItem(tableau_spacers.at(1), 3, 3, 5, 1);

    layout->addWidget(malusCOU, 3, 4, 1, 1);
    layout->addWidget(cou,      3, 5, 1, 1);
    layout->addWidget(malusINT, 4, 4, 1, 1);
    layout->addWidget(intel,    4, 5, 1, 1);
    layout->addWidget(malusCHA, 5, 4, 1, 1);
    layout->addWidget(cha,      5, 5, 1, 1);
    layout->addWidget(malusAD,  6, 4, 1, 1);
    layout->addWidget(ad,       6, 5, 1, 1);
    layout->addWidget(malusFO,  7, 4, 1, 1);
    layout->addWidget(fo,       7, 5, 1, 1);
}
void FenCheckBox::initialiserPr()
{
    nom = new QLineEdit();
    QLabel *nom_label = new QLabel("Nom :");

    tableau_spacers.append(new QSpacerItem(10, 10));

    bonusCOU = new QLabel("Bonus -> COU :");
        COU = new QSpinBox();
            COU->setMaximum(20);
    bonusINT = new QLabel("Bonus -> INT :");
        INT = new QSpinBox();
            INT->setMaximum(20);
    bonusCHA = new QLabel("Bonus -> CHA :");
        CHA = new QSpinBox();
            CHA->setMaximum(20);
    bonusAD = new QLabel("Bonus -> AD :");
        AD = new QSpinBox();
            AD->setMaximum(20);
    bonusFO = new QLabel("Bonus -> FO :");
        FO = new QSpinBox();
            FO->setMaximum(20);
    bonusAT = new QLabel("Bonus -> AT :");
        AT = new QSpinBox();
            AT->setMaximum(20);
    bonusPRD = new QLabel("Bonus -> PRD :");
        PRD = new QSpinBox();
            PRD->setMaximum(20);

    tableau_spacers.append(new QSpacerItem(10, 10));

    malusCOU = new QLabel("Malus -> COU :");
        cou = new QSpinBox();
            cou->setMaximum(20);
    malusINT = new QLabel("Malus -> INT :");
        intel = new QSpinBox();
            intel->setMaximum(20);
    malusCHA = new QLabel("Malus -> CHA :");
        cha = new QSpinBox();
            cha->setMaximum(20);
    malusAD = new QLabel("Malus -> AD :");
        ad = new QSpinBox();
            ad->setMaximum(20);
    malusFO = new QLabel("Malus -> FO :");
        fo = new QSpinBox();
            fo->setMaximum(20);
    malusAT = new QLabel("Malus -> AT :");
        at = new QSpinBox();
            at->setMaximum(20);
    malusPRD = new QLabel("Malus -> PRD :");
        prd = new QSpinBox();
            prd->setMaximum(20);

    tableau_spacers.append(new QSpacerItem(10, 10));

    pr_label = new QLabel("Protection :");
        pr = new QSpinBox();

    layout->addWidget(nom_label, 1, 1, 1, 1);
    layout->addWidget(nom, 1, 2, 1, 4);
    layout->addItem(tableau_spacers.at(0), 2, 1, 1, 5);

    layout->addWidget(bonusCOU, 3, 1, 1, 1);
    layout->addWidget(COU,      3, 2, 1, 1);
    layout->addWidget(bonusINT, 4, 1, 1, 1);
    layout->addWidget(INT,      4, 2, 1, 1);
    layout->addWidget(bonusCHA, 5, 1, 1, 1);
    layout->addWidget(CHA,      5, 2, 1, 1);
    layout->addWidget(bonusAD,  6, 1, 1, 1);
    layout->addWidget(AD,       6, 2, 1, 1);
    layout->addWidget(bonusFO,  7, 1, 1, 1);
    layout->addWidget(FO,       7, 2, 1, 1);

    layout->addItem(tableau_spacers.at(1), 3, 3, 5, 1);

    layout->addWidget(malusCOU, 3, 4, 1, 1);
    layout->addWidget(cou,      3, 5, 1, 1);
    layout->addWidget(malusINT, 4, 4, 1, 1);
    layout->addWidget(intel,    4, 5, 1, 1);
    layout->addWidget(malusCHA, 5, 4, 1, 1);
    layout->addWidget(cha,      5, 5, 1, 1);
    layout->addWidget(malusAD,  6, 4, 1, 1);
    layout->addWidget(ad,       6, 5, 1, 1);
    layout->addWidget(malusFO,  7, 4, 1, 1);
    layout->addWidget(fo,       7, 5, 1, 1);
    layout->addItem(tableau_spacers.at(0), 8, 1, 1, 5);

    layout->addWidget(pr_label, 9, 1, 1, 2);
    layout->addWidget(pr,       9, 3, 1, 3);
}
void FenCheckBox::initialiserArme()
{
    nom = new QLineEdit();
    QLabel *nom_label = new QLabel("Nom :");

    tableau_spacers.append(new QSpacerItem(10, 10));

    bonusCOU = new QLabel("Bonus -> COU :");
        COU = new QSpinBox();
            COU->setMaximum(20);
    bonusINT = new QLabel("Bonus -> INT :");
        INT = new QSpinBox();
            INT->setMaximum(20);
    bonusCHA = new QLabel("Bonus -> CHA :");
        CHA = new QSpinBox();
            CHA->setMaximum(20);
    bonusAD = new QLabel("Bonus -> AD :");
        AD = new QSpinBox();
            AD->setMaximum(20);
    bonusFO = new QLabel("Bonus -> FO :");
        FO = new QSpinBox();
            FO->setMaximum(20);
    bonusAT = new QLabel("Bonus -> AT :");
        AT = new QSpinBox();
            AT->setMaximum(20);
    bonusPRD = new QLabel("Bonus -> PRD :");
        PRD = new QSpinBox();
            PRD->setMaximum(20);

    tableau_spacers.append(new QSpacerItem(10, 10));

    malusCOU = new QLabel("Malus -> COU :");
        cou = new QSpinBox();
            cou->setMaximum(20);
    malusINT = new QLabel("Malus -> INT :");
        intel = new QSpinBox();
            intel->setMaximum(20);
    malusCHA = new QLabel("Malus -> CHA :");
        cha = new QSpinBox();
            cha->setMaximum(20);
    malusAD = new QLabel("Malus -> AD :");
        ad = new QSpinBox();
            ad->setMaximum(20);
    malusFO = new QLabel("Malus -> FO :");
        fo = new QSpinBox();
            fo->setMaximum(20);
    malusAT = new QLabel("Malus -> AT :");
        at = new QSpinBox();
            at->setMaximum(20);
    malusPRD = new QLabel("Malus -> PRD :");
        prd = new QSpinBox();
            prd->setMaximum(20);

    tableau_spacers.append(new QSpacerItem(10, 10));

    degats = new QLabel("Dégats :");
        plusDegats = new QLabel("D +");
        des_spin = new QSpinBox();
        degats_spin = new QSpinBox();
            degats_spin->setMinimum(-50);
            degats_spin->setMaximum(50);

    layout->addWidget(nom_label, 1, 1, 1, 1);
    layout->addWidget(nom, 1, 2, 1, 4);
    layout->addItem(tableau_spacers.at(0), 2, 1, 1, 5);

    layout->addWidget(bonusCOU, 3, 1, 1, 1);
    layout->addWidget(COU,      3, 2, 1, 1);
    layout->addWidget(bonusINT, 4, 1, 1, 1);
    layout->addWidget(INT,      4, 2, 1, 1);
    layout->addWidget(bonusCHA, 5, 1, 1, 1);
    layout->addWidget(CHA,      5, 2, 1, 1);
    layout->addWidget(bonusAD,  6, 1, 1, 1);
    layout->addWidget(AD,       6, 2, 1, 1);
    layout->addWidget(bonusFO,  7, 1, 1, 1);
    layout->addWidget(FO,       7, 2, 1, 1);
    layout->addWidget(bonusAT,  8, 1, 1, 1);
    layout->addWidget(AT,       8, 2, 1, 1);
    layout->addWidget(bonusPRD, 9, 1, 1, 1);
    layout->addWidget(PRD,      9, 2, 1, 1);

    layout->addItem(tableau_spacers.at(1), 3, 3, 7, 1);

    layout->addWidget(malusCOU, 3, 4, 1, 1);
    layout->addWidget(cou,      3, 5, 1, 1);
    layout->addWidget(malusINT, 4, 4, 1, 1);
    layout->addWidget(intel,    4, 5, 1, 1);
    layout->addWidget(malusCHA, 5, 4, 1, 1);
    layout->addWidget(cha,      5, 5, 1, 1);
    layout->addWidget(malusAD,  6, 4, 1, 1);
    layout->addWidget(ad,       6, 5, 1, 1);
    layout->addWidget(malusFO,  7, 4, 1, 1);
    layout->addWidget(fo,       7, 5, 1, 1);
    layout->addWidget(malusAT,  8, 4, 1, 1);
    layout->addWidget(at,       8, 5, 1, 1);
    layout->addWidget(malusPRD, 9, 4, 1, 1);
    layout->addWidget(prd,      9, 5, 1, 1);
    layout->addItem(tableau_spacers.at(0), 10, 1, 1, 5);

    layout->addWidget(degats,       11, 1, 1, 1);
    layout->addWidget(des_spin,     11, 2, 1, 1);
    layout->addWidget(plusDegats,   11, 3, 1, 1);
    layout->addWidget(degats_spin,  11, 4, 1, 1);
}
void FenCheckBox::initialiserFleche()
{
    nom = new QLineEdit();
    QLabel *nom_label = new QLabel("Nom :");

    tableau_spacers.append(new QSpacerItem(10, 10));

    nb_label = new QLabel("Nombre de ces flèches :");
        nb = new QSpinBox();

    tableau_spacers.append(new QSpacerItem(10, 10));

    bonusPI = new QLabel("Points d'impacts en plus :");
        PI = new QSpinBox();
            PI->setMaximum(20);
    bonusAD = new QLabel("Bonus -> AD :");
        AD = new QSpinBox();
            AD->setMaximum(20);

    layout->addWidget(nom_label, 1, 1, 1, 1);
    layout->addWidget(nom, 1, 2, 1, 4);
    layout->addItem(tableau_spacers.at(0), 2, 1, 1, 5);

    layout->addWidget(nb_label, 3, 1, 1, 1);
    layout->addWidget(nb,       3, 2, 1, 1);
    layout->addItem(tableau_spacers.at(0), 4, 1, 1, 5);

    layout->addWidget(bonusPI,  5, 1, 1, 1);
    layout->addWidget(PI,       5, 2, 1, 1);
    layout->addWidget(bonusAD,  6, 1, 1, 1);
    layout->addWidget(AD,       6, 2, 1, 1);
}
void FenCheckBox::initialiserEquip()
{
    nom_equip = new QTextEdit();

    layout->addWidget(nom_equip, 1, 1, 1, 4);
}

void FenCheckBox::modif_vetement(Vetement const& objet)
{
    QObject::disconnect(boutonBox, SIGNAL(rejected()), m_parent, SLOT(annuler()));

    nom->setText(objet.getNom());

    COU->setValue(objet.bonus().getCOU());
    INT->setValue(objet.bonus().getINT());
    CHA->setValue(objet.bonus().getCHA());
    AD->setValue(objet.bonus().getAD());
    FO->setValue(objet.bonus().getFO());

    cou->setValue(objet.malus().getCOU());
    intel->setValue(objet.malus().getINT());
    cha->setValue(objet.malus().getCHA());
    ad->setValue(objet.malus().getAD());
    fo->setValue(objet.malus().getFO());
}
void FenCheckBox::modif_protection(Protection const& objet)
{
    QObject::disconnect(boutonBox, SIGNAL(rejected()), m_parent, SLOT(annuler()));

    nom->setText(objet.getNom());

    COU->setValue(objet.bonus().getCOU());
    INT->setValue(objet.bonus().getINT());
    CHA->setValue(objet.bonus().getCHA());
    AD->setValue(objet.bonus().getAD());
    FO->setValue(objet.bonus().getFO());

    cou->setValue(objet.malus().getCOU());
    intel->setValue(objet.malus().getINT());
    cha->setValue(objet.malus().getCHA());
    ad->setValue(objet.malus().getAD());
    fo->setValue(objet.malus().getFO());

    pr->setValue(objet.nombreProtection());
}
void FenCheckBox::modif_arme(Arme const& objet)
{
    QObject::disconnect(boutonBox, SIGNAL(rejected()), m_parent, SLOT(annuler()));

    nom->setText(objet.getNom());

    COU->setValue(objet.bonus().getCOU());
    INT->setValue(objet.bonus().getINT());
    CHA->setValue(objet.bonus().getCHA());
    AD->setValue(objet.bonus().getAD());
    FO->setValue(objet.bonus().getFO());

    cou->setValue(objet.malus().getCOU());
    intel->setValue(objet.malus().getINT());
    cha->setValue(objet.malus().getCHA());
    ad->setValue(objet.malus().getAD());
    fo->setValue(objet.malus().getFO());

    des_spin->setValue(objet.des());
    degats_spin->setValue(objet.degats());
}
void FenCheckBox::modif_fleche(Fleche const& objet)
{
    QObject::disconnect(boutonBox, SIGNAL(rejected()), m_parent, SLOT(annuler()));

    nom->setText(objet.getNom());

    nb->setValue(objet.getNombre());
    PI->setValue(objet.getPI());
    AD->setValue(objet.getAD());
}
void FenCheckBox::modif_equipement(QString* objet)
{
    QObject::disconnect(boutonBox, SIGNAL(rejected()), m_parent, SLOT(annuler()));

    nom_equip->setText(*objet);
}

Vetement FenCheckBox::return_vetement()
{
    dialogue->close();
    return Vetement(nom->text(),
                    cou->value(), intel->value(), cha->value(), ad->value(), fo->value(),
                    COU->value(), INT->value(), CHA->value(), AD->value(), FO->value());
}
Protection FenCheckBox::return_protection()
{
    dialogue->close();
    return Protection(nom->text(), pr->value(),
                      cou->value(), intel->value(), cha->value(), ad->value(), fo->value(), at->value(), prd->value(),
                      COU->value(), INT->value(), CHA->value(), AD->value(), FO->value(), AT->value(), PRD->value());
}
Arme FenCheckBox::return_arme()
{
    dialogue->close();
    return Arme(nom->text(),
                des_spin->value(), degats_spin->value(),
                cou->value(), intel->value(), cha->value(), ad->value(), fo->value(), at->value(), prd->value(),
                COU->value(), INT->value(), CHA->value(), AD->value(), FO->value(), AT->value(), PRD->value());
}
Fleche FenCheckBox::return_fleche()
{
    dialogue->close();
    return Fleche(nom->text(), nb->value(), PI->value(), AD->value());
}
QString FenCheckBox::return_equipement()
{
    dialogue->close();
    return nom_equip->toPlainText();
}
