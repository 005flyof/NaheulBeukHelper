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

#include "Personnage.h"
#include "CheckBox.h"
#include <QtGui>
#include <vector>

#define INIT_SPACER		for (int i = 0; i < NB_SPACER; i++)\
                            spacer[i] = new QSpacerItem(20, 20)

using namespace std;

Personnage::Personnage(Personnage const& b)
    : QTabWidget(), m_totalProtection(0), lecteurLabel(0)
{
    INIT_SPACER;

    for (lecteurLabel = 0; lecteurLabel < 4; lecteurLabel++)

    m_nomPerso = b.m_nomPerso;
    m_sexePerso = b.m_sexePerso;

    m_originePersonnage = b.m_originePersonnage;
    m_metierPersonnage = b.m_metierPersonnage;

    m_energieVitale = b.m_energieVitale;
    m_energieVitale_modif = b.m_energieVitale_modif;

    m_energieAstrale = b.m_energieAstrale;
    m_energieAstrale_modif = b.m_energieAstrale_modif;
    typeEnergieAstrale = b.typeEnergieAstrale;
    presenceEnergieAstrale = b.presenceEnergieAstrale;

    m_caracInitiales = b.m_caracInitiales;
    m_caracModifiees = b.m_caracModifiees;

    m_pointsDestin = b.m_pointsDestin;
    m_experience = b.m_experience;
    m_niveau = b.m_niveau;
    level = new QLineEdit();
    setNiveau();

    m_pieces = b.m_pieces;

    for (int i = 0; i < MAX_VETEMENT; i++)
        m_vetements[i] = new Vetement(PAS_VETEMENT, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_PROTECTION; i++)
        m_protections[i] = new Protection(PAS_PROTECTION, 0,
                                          0, 0, 0, 0, 0, 0, 0,
                                          0, 0, 0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_ARME; i++)
        m_armes[i] = new Arme(PAS_ARME, 1, -2,
                              0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_FLECHE; i++)
        m_fleches[i] = new Fleche(PAS_FLECHE, 0, 0, 0);

    for (int i = 0; i < MAX_EQUIPEMENT; i++)
        m_equipements[i] = new QString(PAS_EQUIPEMENTS);
}

Personnage::Personnage(QString nom, QString sexe, QString nomOrigine, QString nomMetier,
                       int cou, int intel, int cha, int ad, int fo, int at, int prd,
                       int cou_modif, int intel_modif, int cha_modif, int ad_modif, int fo_modif, int at_modif, int prd_modif,
                       int ptsDestin, int xp, int ev, int OR, int ARGENT, int CUIVRE)
    : QTabWidget(), m_totalProtection(0), lecteurLabel(0)
{
    INIT_SPACER;

    for (lecteurLabel = 0; lecteurLabel < 4; lecteurLabel++)
    {
        labelPourSaut[lecteurLabel] = new QLabel();
            QImage epee(":prog-data/img/epee.png");
            labelPourSaut[lecteurLabel]->setPixmap(QPixmap::fromImage(epee));
            labelPourSaut[lecteurLabel]->adjustSize();
    }

    m_nomPerso = nom;
    m_sexePerso = sexe;

    m_originePersonnage = nomOrigine;
    m_metierPersonnage = nomMetier;

    m_energieVitale = ev;
    m_energieVitale_modif = ev;

    m_energieAstrale = 0;
    m_energieAstrale_modif = 0;
    typeEnergieAstrale = "Pas d'énergie astrale";
    presenceEnergieAstrale = false;

    m_caracInitiales.remplir(cou, intel, cha, ad, fo, at, prd);
    m_caracModifiees.remplir(cou_modif, intel_modif, cha_modif, ad_modif, fo_modif, at_modif, prd_modif);

    m_pointsDestin = ptsDestin;
    m_experience = xp;
    m_niveau = 0;
    level = new QLineEdit();
    setNiveau();

    m_pieces = new Richesses(OR, ARGENT, CUIVRE);

    for (int i = 0; i < MAX_VETEMENT; i++)
        m_vetements[i] = new Vetement(PAS_VETEMENT, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_PROTECTION; i++)
        m_protections[i] = new Protection(PAS_PROTECTION, 0,
                                          0, 0, 0, 0, 0, 0, 0,
                                          0, 0, 0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_ARME; i++)
        m_armes[i] = new Arme(PAS_ARME, 1, -2,
                              0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_FLECHE; i++)
        m_fleches[i] = new Fleche(PAS_FLECHE, 0, 0, 0);

    for (int i = 0; i < MAX_EQUIPEMENT; i++)
        m_equipements[i] = new QString(PAS_EQUIPEMENTS);
}

Personnage& Personnage::operator=(Personnage const& b)
{
    if(this != &b) 	// Vérification que « objet& != de objetACopier »
    {
        m_totalProtection = b.m_totalProtection;

        INIT_SPACER;

        for (lecteurLabel = 0; lecteurLabel < 4; lecteurLabel++)
        {
            labelPourSaut[lecteurLabel] = new QLabel();
                QImage epee(":prog-data/img/epee.png");
                labelPourSaut[lecteurLabel]->setPixmap(QPixmap::fromImage(epee));
                labelPourSaut[lecteurLabel]->adjustSize();
        }

        m_nomPerso = b.m_nomPerso;
        m_sexePerso = b.m_sexePerso;

        m_originePersonnage = b.m_originePersonnage;
        m_metierPersonnage = b.m_metierPersonnage;

        m_energieVitale = b.m_energieVitale;
        m_energieVitale_modif = b.m_energieVitale_modif;

        m_energieAstrale = b.m_energieAstrale;
        m_energieAstrale_modif = b.m_energieAstrale_modif;
        typeEnergieAstrale = b.typeEnergieAstrale;
        presenceEnergieAstrale = b.presenceEnergieAstrale;

        m_caracInitiales = b.m_caracInitiales;
        m_caracModifiees = b.m_caracModifiees;

        m_pointsDestin = b.m_pointsDestin;
        m_experience = b.m_experience;
        m_niveau = b.m_niveau;
        level = new QLineEdit();
        setNiveau();

        m_pieces = b.m_pieces;

        for (int i = 0; i < MAX_VETEMENT; i++)
            m_vetements[i] = b.m_vetements[i];

        for (int i = 0; i < MAX_PROTECTION; i++)
            m_protections[i] = b.m_protections[i];

        for (int i = 0; i < MAX_ARME; i++)
            m_armes[i] = b.m_armes[i];

        for (int i = 0; i < MAX_FLECHE; i++)
            m_fleches[i] = b.m_fleches[i];

        for (int i = 0; i < MAX_EQUIPEMENT; i++)
            m_equipements[i] = b.m_equipements[i];
    }

    return *this;
}

Personnage::~Personnage()
{}


// Pour récupérer le widget représentant le personnage
QTabWidget* Personnage::afficher()
{
    ongletsCarac();
    ongletsEquip();

// Compétences
    layoutCompetences = new QVBoxLayout();
        layoutCompetences->setSpacing(10);
        afficherCompetences();
    QVBoxLayout *layoutCompetences_Bouton = new QVBoxLayout();

    ajoutCompetence = new QPushButton("Ajouter");
        ajoutCompetence->setMaximumSize(100, 25);
        QObject::connect(ajoutCompetence, SIGNAL(clicked()), this, SLOT(addCompetence()));
        layoutCompetences_Bouton->addWidget(ajoutCompetence, Qt::AlignCenter);

    QScrollArea *scroll = new QScrollArea;
        QWidget *conteneur = new QWidget();
            conteneur->setLayout(layoutCompetences);
        scroll->setWidget(conteneur);
        scroll->setWidgetResizable(false);
        layoutCompetences_Bouton->addWidget(scroll);

    QWidget *e = new QWidget();
        e->setLayout(layoutCompetences_Bouton);
    this->addTab(e, "Compétences");

// On renvoie le objet lui-même
    return this;
}
void Personnage::ongletsCarac()
{
    lecteurLabel = 0;
//    setCaracModif();
// Layout 1
    // Informations génériques
        QGroupBox *perso_infos = new QGroupBox("Informations générales");
        QGridLayout *perso_layoutInfos = new QGridLayout;
            QLabel *nom = new QLabel("Nom :	" + m_nomPerso);
            QLabel *sexe = new QLabel("Sexe :	" + m_sexePerso);
            QLabel *origineNom = new QLabel("Origine :	" + m_originePersonnage);
            QLabel *metierNom = new QLabel("Métier :	" + m_metierPersonnage);

            QLabel *XP_label = new QLabel("Expérience : ");
                XP = new QLineEdit(QString::number(m_experience));
                    XP->setReadOnly(true);
                    XP->setAlignment(Qt::AlignCenter);
                XP_plus = new QPushButton("+");
            QLabel *level_label = new QLabel("Niveau : ");
                level->setText(QString::number(m_niveau));
                    level->setEnabled(false);
                    level->setAlignment(Qt::AlignCenter);
            QLabel *ptsDeDestin_label = new QLabel("Points de destin : ");
                ptsDeDestin = new QLineEdit(QString::number(m_pointsDestin));
                    ptsDeDestin->setReadOnly(true);
                    ptsDeDestin->setAlignment(Qt::AlignCenter);
                ptsDeDestin_moins = new QPushButton("-");
                    if (m_pointsDestin > 0)
                        ptsDeDestin_moins->setEnabled(true);
                    else
                        ptsDeDestin_moins->setEnabled(false);

            perso_layoutInfos->addWidget(nom, 1, 1, 1, 2);
            perso_layoutInfos->addWidget(sexe, 1, 3, 1, 2);
            perso_layoutInfos->addWidget(origineNom, 2, 1, 1, 2);
            perso_layoutInfos->addWidget(metierNom, 2, 3, 1, 2);
            perso_layoutInfos->addWidget(labelPourSaut[lecteurLabel], 3, 1, 1, 5, Qt::AlignCenter);
            lecteurLabel++;
            perso_layoutInfos->addWidget(XP_label, 4, 1, 1, 1);
            perso_layoutInfos->addWidget(XP, 4, 2, 1, 2);
            perso_layoutInfos->addWidget(XP_plus, 4, 4, 1, 2);
            perso_layoutInfos->addWidget(level_label, 5, 1, 1, 1);
            perso_layoutInfos->addWidget(level, 5, 2, 1, 2);
            perso_layoutInfos->addWidget(ptsDeDestin_label, 6, 1, 1, 1);
            perso_layoutInfos->addWidget(ptsDeDestin, 6, 2, 1, 2);
            perso_layoutInfos->addWidget(ptsDeDestin_moins, 6, 4, 1, 2);

            perso_layoutInfos->setSpacing(15);
            perso_layoutInfos->setAlignment(Qt::AlignCenter);

            perso_infos->setLayout(perso_layoutInfos);

    // Richesses
        QGroupBox *perso_richesse = new QGroupBox("Richesses de " + m_nomPerso);
        QGridLayout *perso_layoutRichesse = new QGridLayout;
            QLabel *PO_label = new QLabel("- Pièces d'or (PO) : ");
                PO = new QLineEdit(QString::number(m_pieces->getRichesses_Or()));
                    PO->setReadOnly(true);
                    PO->setAlignment(Qt::AlignCenter);
                PO_plus = new QPushButton("+");
                PO_moins = new QPushButton("-");
                    if (m_pieces->getRichesses_Or() != 999999)
                        PO_plus->setEnabled(true);
                    else
                        PO_plus->setEnabled(false);

                    if (m_pieces->getRichesses_Or() != 0)
                        PO_moins->setEnabled(true);
                    else
                        PO_moins->setEnabled(false);

            QLabel *PA_label = new QLabel("- Pièces d'argent (PA) : ");
                PA = new QLineEdit(QString::number(m_pieces->getRichesses_Argent()));
                    PA->setReadOnly(true);
                    PA->setAlignment(Qt::AlignCenter);
                PA_plus = new QPushButton("+");
                PA_moins = new QPushButton("-");
                    if (m_pieces->getRichesses_Argent() != 999999)
                        PA_plus->setEnabled(true);
                    else
                        PA_plus->setEnabled(false);

                    if (m_pieces->getRichesses_Argent() != 0)
                        PA_moins->setEnabled(true);
                    else
                        PA_moins->setEnabled(false);

            QLabel *PC_label = new QLabel("- Pièces de cuivre (PC) : ");
                PC = new QLineEdit(QString::number(m_pieces->getRichesses_Cuivre()));
                    PC->setReadOnly(true);
                    PC->setAlignment(Qt::AlignCenter);
                PC_plus = new QPushButton("+");
                PC_moins = new QPushButton("-");
                    if (m_pieces->getRichesses_Cuivre() != 999999)
                        PC_plus->setEnabled(true);
                    else
                        PC_plus->setEnabled(false);

                    if (m_pieces->getRichesses_Cuivre() != 0)
                        PC_moins->setEnabled(true);
                    else
                        PC_moins->setEnabled(false);

            QPushButton *convertirPAPC_PO = new QPushButton("Tout convertir en PO");
                QObject::connect(convertirPAPC_PO, SIGNAL(clicked()), this, SLOT(conversionPAPC_PO()));
            QPushButton *convertirPO_PA = new QPushButton("Convertir 1 PO en PA");
                QObject::connect(convertirPO_PA, SIGNAL(clicked()), this, SLOT(conversionPO_PA()));
            QPushButton *convertirPO_PC = new QPushButton("Convertir 1 PO en PC");
                QObject::connect(convertirPO_PC, SIGNAL(clicked()), this, SLOT(conversionPO_PC()));
            QPushButton *convertirPA_PC = new QPushButton("Convertir 1 PA en PC");
                QObject::connect(convertirPA_PC, SIGNAL(clicked()), this, SLOT(conversionPA_PC()));

            QVBoxLayout *layoutBoutonsConversion = new QVBoxLayout();
                layoutBoutonsConversion->addWidget(convertirPAPC_PO);
                layoutBoutonsConversion->addWidget(convertirPO_PA);
                layoutBoutonsConversion->addWidget(convertirPO_PC);
                layoutBoutonsConversion->addWidget(convertirPA_PC);

            perso_layoutRichesse->addWidget(PO_label, 1, 1, 1, 1);
            perso_layoutRichesse->addWidget(PO, 1, 2, 1, 1);
            perso_layoutRichesse->addWidget(PO_plus, 1, 3, 1, 1);
            perso_layoutRichesse->addWidget(PO_moins, 1, 4, 1, 1);

            perso_layoutRichesse->addWidget(PA_label, 2, 1, 1, 1);
            perso_layoutRichesse->addWidget(PA, 2, 2, 1, 1);
            perso_layoutRichesse->addWidget(PA_plus, 2, 3, 1, 1);
            perso_layoutRichesse->addWidget(PA_moins, 2, 4, 1, 1);

            perso_layoutRichesse->addWidget(PC_label, 3, 1, 1, 1);
            perso_layoutRichesse->addWidget(PC, 3, 2, 1, 1);
            perso_layoutRichesse->addWidget(PC_plus, 3, 3, 1, 1);
            perso_layoutRichesse->addWidget(PC_moins, 3, 4, 1, 1);

            perso_layoutRichesse->addLayout(layoutBoutonsConversion, 1, 5, 3, 1);

            perso_layoutRichesse->setSpacing(10);
            perso_layoutRichesse->setAlignment(Qt::AlignCenter);

            perso_richesse->setLayout(perso_layoutRichesse);

    // On ajoute les widgets au layout
        QVBoxLayout *infos_pieces = new QVBoxLayout();
            infos_pieces->addWidget(perso_infos);
            infos_pieces->addItem(spacer[0]);
            infos_pieces->addWidget(perso_richesse);

        QWidget *partie1 = new QWidget();
            partie1->setLayout(infos_pieces);

    this->addTab(partie1, "Informations générales && richesses");

    // Caractéristiques
        QGridLayout *perso_layoutCarac = new QGridLayout;

            QLabel *explicCarac = new QLabel("Nrom de la caractéristique");
                explicCarac->setAlignment(Qt::AlignCenter);
            QLabel *explicCaracInitiale = new QLabel("Initiale");
                explicCaracInitiale->setAlignment(Qt::AlignCenter);
            QLabel *explicCaracModif = new QLabel("Modifiée");
                explicCaracModif->setAlignment(Qt::AlignCenter);
            QPushButton *recalculer = new QPushButton("Recalculer...");

            QLabel *EV_label = new QLabel("Energie Vitale (EV) :");
                EV = new QLineEdit(QString::number(m_energieVitale));
                    EV->setEnabled(false);
                    EV->setAlignment(Qt::AlignCenter);
                EV_modif = new QLineEdit(QString::number(m_energieVitale_modif));
                    EV_modif->setReadOnly(true);
                    EV_modif->setAlignment(Qt::AlignCenter);
                EV_plus = new QPushButton("+");
                    if (m_energieVitale_modif != m_energieVitale)
                        EV_plus->setEnabled(true);
                    else
                        EV_plus->setEnabled(false);
                EV_moins = new QPushButton("-");
                    if (m_energieVitale_modif != 0)
                        EV_moins->setEnabled(true);
                    else
                        EV_moins->setEnabled(false);


            QLabel *magieResist_label = new QLabel("Résistance à la magie :");
                magieResist = new QLineEdit(QString::number( (m_caracModifiees.getINT() + m_caracModifiees.getCOU() + m_caracModifiees.getFO()) / 3) );
                    magieResist->setEnabled(false);
                    magieResist->setAlignment(Qt::AlignCenter);


            QLabel *COU_label = new QLabel("Courage (COU) :");
                COU = new QLineEdit(QString::number(m_caracInitiales.getCOU()));
                    COU->setEnabled(false);
                    COU->setAlignment(Qt::AlignCenter);
                COU_modif = new QLineEdit(QString::number(m_caracModifiees.getCOU()));
                    COU_modif->setReadOnly(true);
                    COU_modif->setAlignment(Qt::AlignCenter);
                COU_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getCOU() != 18)
                        COU_plus->setEnabled(true);
                    else
                        COU_plus->setEnabled(false);
                COU_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getCOU() != 2)
                        COU_moins->setEnabled(true);
                    else
                        COU_moins->setEnabled(false);

            QLabel *INT_label = new QLabel("Intelligence (INT) :");
                INT = new QLineEdit(QString::number(m_caracInitiales.getINT()));
                    INT->setEnabled(false);
                    INT->setAlignment(Qt::AlignCenter);
                INT_modif = new QLineEdit(QString::number(m_caracModifiees.getINT()));
                    INT_modif->setReadOnly(true);
                    INT_modif->setAlignment(Qt::AlignCenter);
                INT_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getINT() != 18)
                        INT_plus->setEnabled(true);
                    else
                        INT_plus->setEnabled(false);
                INT_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getINT() != 2)
                        INT_moins->setEnabled(true);
                    else
                        INT_moins->setEnabled(false);

            QLabel *CHA_label = new QLabel("Charisme (CHA) :");
                CHA = new QLineEdit(QString::number(m_caracInitiales.getCHA()));
                    CHA->setEnabled(false);
                    CHA->setAlignment(Qt::AlignCenter);
                CHA_modif = new QLineEdit(QString::number(m_caracModifiees.getCHA()));
                    CHA_modif->setReadOnly(true);
                    CHA_modif->setAlignment(Qt::AlignCenter);
                CHA_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getCHA() != 18)
                        CHA_plus->setEnabled(true);
                    else
                        CHA_plus->setEnabled(false);
                CHA_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getCHA() != 2)
                        CHA_moins->setEnabled(true);
                    else
                        CHA_moins->setEnabled(false);

            QLabel *AD_label = new QLabel("Adresse (AD) :");
                AD = new QLineEdit(QString::number(m_caracInitiales.getAD()));
                    AD->setEnabled(false);
                    AD->setAlignment(Qt::AlignCenter);
                AD_modif = new QLineEdit(QString::number(m_caracModifiees.getAD()));
                    AD_modif->setReadOnly(true);
                    AD_modif->setAlignment(Qt::AlignCenter);
                AD_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getAD() != 18)
                        AD_plus->setEnabled(true);
                    else
                        AD_plus->setEnabled(false);
                AD_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getAD() != 2)
                        AD_moins->setEnabled(true);
                    else
                        AD_moins->setEnabled(false);

            QLabel *FO_label = new QLabel("Force (FO) :");
                FO = new QLineEdit(QString::number(m_caracInitiales.getFO()));
                    FO->setEnabled(false);
                    FO->setAlignment(Qt::AlignCenter);
                FO_modif = new QLineEdit(QString::number(m_caracModifiees.getFO()));
                    FO_modif->setReadOnly(true);
                    FO_modif->setAlignment(Qt::AlignCenter);
                FO_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getFO() != 18)
                        FO_plus->setEnabled(true);
                    else
                        FO_plus->setEnabled(false);
                FO_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getFO() != 2)
                        FO_moins->setEnabled(true);
                    else
                        FO_moins->setEnabled(false);

            QLabel *AT_label = new QLabel("Attaque (AT) :");
                AT = new QLineEdit(QString::number(m_caracInitiales.getAT()));
                    AT->setEnabled(false);
                    AT->setAlignment(Qt::AlignCenter);
                AT_modif = new QLineEdit(QString::number(m_caracModifiees.getAT()));
                    AT_modif->setReadOnly(true);
                    AT_modif->setAlignment(Qt::AlignCenter);
                AT_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getAT() != 18)
                        AT_plus->setEnabled(true);
                    else
                        AT_plus->setEnabled(false);

                    AT_plus->setEnabled(false);
                AT_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getAT() != 2)
                        AT_moins->setEnabled(true);
                    else
                        AT_moins->setEnabled(false);

                    AT_moins->setEnabled(false);

            QLabel *PRD_label = new QLabel("Parade (PRD) :");
                PRD = new QLineEdit(QString::number(m_caracInitiales.getPRD()));
                    PRD->setEnabled(false);
                    PRD->setAlignment(Qt::AlignCenter);
                PRD_modif = new QLineEdit(QString::number(m_caracModifiees.getPRD()));
                    PRD_modif->setReadOnly(true);
                    PRD_modif->setAlignment(Qt::AlignCenter);
                PRD_plus = new QPushButton("+ 1");
                    if (m_caracModifiees.getPRD() != 18)
                        PRD_plus->setEnabled(true);
                    else
                        PRD_plus->setEnabled(false);

                    PRD_plus->setEnabled(false);
                PRD_moins = new QPushButton("- 1");
                    if (m_caracModifiees.getPRD() != 2)
                        PRD_moins->setEnabled(true);
                    else
                        PRD_moins->setEnabled(false);

                    PRD_moins->setEnabled(false);

            int i = 1;

            perso_layoutCarac->addWidget(explicCarac, i, 1, 1, 1);
            perso_layoutCarac->addWidget(explicCaracInitiale, i, 2, 1, 1);
            perso_layoutCarac->addWidget(explicCaracModif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(recalculer, i, 4, 1, 2);
            i++;
            perso_layoutCarac->addWidget(EV_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(EV, i, 2, 1, 1);
            perso_layoutCarac->addWidget(EV_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(EV_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(EV_moins, i, 5, 1, 1);
            i++;
            perso_layoutCarac->addWidget(labelPourSaut[lecteurLabel], i, 1, 1, 5, Qt::AlignCenter);
            i++;
            lecteurLabel++;

            if (presenceEnergieAstrale)
            {
                QLabel *EA_label = new QLabel("Energie Astrale (EA) :");
                    EA = new QLineEdit(QString::number(m_energieAstrale));
                        EA->setEnabled(false);
                        EA->setAlignment(Qt::AlignCenter);
                    EA_modif = new QLineEdit(QString::number(m_energieAstrale_modif));
                        EA_modif->setReadOnly(true);
                        EA_modif->setAlignment(Qt::AlignCenter);
                EA_plus = new QPushButton("+");
                    if (m_energieAstrale_modif != m_energieAstrale)
                        EA_plus->setEnabled(true);
                    else
                        EA_plus->setEnabled(false);
                EA_moins = new QPushButton("-");
                    if (m_energieAstrale_modif != 0)
                        EA_moins->setEnabled(true);
                    else
                        EA_moins->setEnabled(false);

                QLabel *typeEA_label = new QLabel("Type d'énergie astrale :");
                    typeEA = new QLineEdit(typeEnergieAstrale);
                    typeEA->setEnabled(false);
                QLabel *magiePhys_label = new QLabel("Magie physique :");
                    magiePhys = new QLineEdit(QString::number( (m_caracModifiees.getINT() + m_caracModifiees.getAD()) / 2));
                        magiePhys->setEnabled(false);
                        magiePhys->setAlignment(Qt::AlignCenter);
                QLabel *magiePsy_label = new QLabel("Magie psychique :");
                    magiePsy = new QLineEdit(QString::number( (m_caracModifiees.getINT() + m_caracModifiees.getCHA()) / 2));
                        magiePsy->setEnabled(false);
                        magiePsy->setAlignment(Qt::AlignCenter);

                perso_layoutCarac->addWidget(EA_label, i, 1, 1, 1);
                perso_layoutCarac->addWidget(EA, i, 2, 1, 1);
                perso_layoutCarac->addWidget(EA_modif, i, 3, 1, 1);
                perso_layoutCarac->addWidget(EA_plus, i, 4, 1, 1);
                perso_layoutCarac->addWidget(EA_moins, i, 5, 1, 1);
                i++;
                perso_layoutCarac->addWidget(typeEA_label, i, 1, 1, 1);
                perso_layoutCarac->addWidget(typeEA, i, 2, 1, 2);
                i++;
                perso_layoutCarac->addWidget(magiePhys_label, i, 1, 1, 1);
                perso_layoutCarac->addWidget(magiePhys, i, 2, 1, 2);
                i++;
                perso_layoutCarac->addWidget(magiePsy_label, i, 1, 1, 1);
                perso_layoutCarac->addWidget(magiePsy, i, 2, 1, 2);
                i++;

                QObject::connect(EA_plus, SIGNAL(clicked()), this, SLOT(plus_ea()));
                QObject::connect(EA_moins, SIGNAL(clicked()), this, SLOT(moins_ea()));
            }

            perso_layoutCarac->addWidget(magieResist_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(magieResist, i, 2, 1, 2);
            i++;
            perso_layoutCarac->addWidget(labelPourSaut[lecteurLabel], i, 1, 1, 5, Qt::AlignCenter);
            i++;
            lecteurLabel++;

            perso_layoutCarac->addWidget(COU_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(COU, i, 2, 1, 1);
            perso_layoutCarac->addWidget(COU_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(COU_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(COU_moins, i, 5, 1, 1);
            i++;
            perso_layoutCarac->addWidget(INT_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(INT, i, 2, 1, 1);
            perso_layoutCarac->addWidget(INT_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(INT_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(INT_moins, i, 5, 1, 1);
            i++;
            perso_layoutCarac->addWidget(CHA_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(CHA, i, 2, 1, 1);
            perso_layoutCarac->addWidget(CHA_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(CHA_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(CHA_moins, i, 5, 1, 1);
            i++;
            perso_layoutCarac->addWidget(AD_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(AD, i, 2, 1, 1);
            perso_layoutCarac->addWidget(AD_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(AD_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(AD_moins, i, 5, 1, 1);
            i++;
            perso_layoutCarac->addWidget(FO_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(FO, i, 2, 1, 1);
            perso_layoutCarac->addWidget(FO_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(FO_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(FO_moins, i, 5, 1, 1);
            i++;

            perso_layoutCarac->addWidget(labelPourSaut[lecteurLabel], i, 1, 1, 5, Qt::AlignCenter);
            i++;
            lecteurLabel++;

            perso_layoutCarac->addWidget(AT_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(AT, i, 2, 1, 1);
            perso_layoutCarac->addWidget(AT_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(AT_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(AT_moins, i, 5, 1, 1);
            i++;
            perso_layoutCarac->addWidget(PRD_label, i, 1, 1, 1);
            perso_layoutCarac->addWidget(PRD, i, 2, 1, 1);
            perso_layoutCarac->addWidget(PRD_modif, i, 3, 1, 1);
            perso_layoutCarac->addWidget(PRD_plus, i, 4, 1, 1);
            perso_layoutCarac->addWidget(PRD_moins, i, 5, 1, 1);
            i++;

            perso_layoutCarac->setSpacing(10);
            perso_layoutCarac->setAlignment(Qt::AlignCenter);

        QGroupBox *carac = new QGroupBox("Caractéristiques");
            carac->setLayout(perso_layoutCarac);

        QGridLayout *bonus_layout = new QGridLayout;
            QLabel *carac_degatsBonus_label = new QLabel("Dégâts dus à la FO");
                carac_degatsBonus = new QLineEdit(QString::number(m_degatsBonus));
                    carac_degatsBonus->setReadOnly(true);
                    carac_degatsBonus->setAlignment(Qt::AlignCenter);
            QLabel *carac_attaqueBonus_label = new QLabel("Points d'AT dus à l'AD");
                carac_attaqueBonus = new QLineEdit(QString::number(m_attaqueBonus));
                    carac_attaqueBonus->setReadOnly(true);
                    carac_attaqueBonus->setAlignment(Qt::AlignCenter);
            QLabel *carac_paradeBonus_label = new QLabel("Points de PRD dus à l'AD");
                carac_paradeBonus = new QLineEdit(QString::number(m_paradeBonus));
                    carac_paradeBonus->setReadOnly(true);
                    carac_paradeBonus->setAlignment(Qt::AlignCenter);
            QLabel *carac_degatsBonusSorts_label = new QLabel("Dégâts dus à l'INT\n(valable seulement pour les sorts)");
                carac_degatsBonusSorts = new QLineEdit(QString::number(m_degatsBonusSorts));
                    carac_degatsBonusSorts->setReadOnly(true);
                    carac_degatsBonusSorts->setAlignment(Qt::AlignCenter);

            bonus_layout->addWidget(carac_degatsBonus_label, 1, 1);
            bonus_layout->addWidget(carac_degatsBonus, 1, 2);
            bonus_layout->addWidget(carac_attaqueBonus_label, 2, 1);
            bonus_layout->addWidget(carac_attaqueBonus, 2, 2);
            bonus_layout->addWidget(carac_paradeBonus_label, 3, 1);
            bonus_layout->addWidget(carac_paradeBonus, 3, 2);
            bonus_layout->addWidget(carac_degatsBonusSorts_label, 4, 1);
            bonus_layout->addWidget(carac_degatsBonusSorts, 4, 2);

        QGroupBox *bonus = new QGroupBox("Caractéristiques supérieures/inférieures à la moyenne");
            bonus->setLayout(bonus_layout);

        QVBoxLayout *perso_layoutCarac_total = new QVBoxLayout;
            perso_layoutCarac_total->addWidget(carac);
            perso_layoutCarac_total->addWidget(bonus);
        QWidget *partie2 = new QWidget();
        partie2->setLayout(perso_layoutCarac_total);
    this->addTab(partie2, "Caractéristiques");
// On crée les connexions
    QObject::connect(recalculer, SIGNAL(clicked()), this, SLOT(setCaracModif_Affichage()));

    QObject::connect(COU_plus, SIGNAL(clicked()), this, SLOT(plus_cou()));
    QObject::connect(INT_plus, SIGNAL(clicked()), this, SLOT(plus_int()));
    QObject::connect(CHA_plus, SIGNAL(clicked()), this, SLOT(plus_cha()));
    QObject::connect(AD_plus, SIGNAL(clicked()), this, SLOT(plus_ad()));
    QObject::connect(FO_plus, SIGNAL(clicked()), this, SLOT(plus_fo()));
    QObject::connect(AT_plus, SIGNAL(clicked()), this, SLOT(plus_at()));
    QObject::connect(PRD_plus, SIGNAL(clicked()), this, SLOT(plus_prd()));

    QObject::connect(COU_moins, SIGNAL(clicked()), this, SLOT(moins_cou()));
    QObject::connect(INT_moins, SIGNAL(clicked()), this, SLOT(moins_int()));
    QObject::connect(CHA_moins, SIGNAL(clicked()), this, SLOT(moins_cha()));
    QObject::connect(AD_moins, SIGNAL(clicked()), this, SLOT(moins_ad()));
    QObject::connect(FO_moins, SIGNAL(clicked()), this, SLOT(moins_fo()));
    QObject::connect(AT_moins, SIGNAL(clicked()), this, SLOT(moins_at()));
    QObject::connect(PRD_moins, SIGNAL(clicked()), this, SLOT(moins_prd()));

    QObject::connect(PO_plus, SIGNAL(clicked()), this, SLOT(plus_po()));
    QObject::connect(PA_plus, SIGNAL(clicked()), this, SLOT(plus_pa()));
    QObject::connect(PC_plus, SIGNAL(clicked()), this, SLOT(plus_pc()));

    QObject::connect(PO_moins, SIGNAL(clicked()), this, SLOT(moins_po()));
    QObject::connect(PA_moins, SIGNAL(clicked()), this, SLOT(moins_pa()));
    QObject::connect(PC_moins, SIGNAL(clicked()), this, SLOT(moins_pc()));

    QObject::connect(EV_plus, SIGNAL(clicked()), this, SLOT(plus_ev()));
    QObject::connect(EV_moins, SIGNAL(clicked()), this, SLOT(moins_ev()));

    QObject::connect(ptsDeDestin_moins, SIGNAL(clicked()), this, SLOT(moins_destin()));
    QObject::connect(XP_plus, SIGNAL(clicked()), this, SLOT(plus_xp()));
}
void Personnage::ongletsEquip()
{
// Vêtements
    QGridLayout *perso_layoutVetements = new QGridLayout();
        perso_layoutVetements->setSpacing(15);
        perso_layoutVetements->setAlignment(Qt::AlignCenter);

        QLabel *vetement_explic[4];
        vetement_explic[0] = new QLabel("Type :");
        vetement_explic[1] = new QLabel("Nom :");
        vetement_explic[2] = new QLabel("Bonus :");
        vetement_explic[3] = new QLabel("Malus :");

        perso_layoutVetements->addWidget(vetement_explic[0], 1, 2, 1, 1, Qt::AlignCenter);
        perso_layoutVetements->addWidget(vetement_explic[1], 1, 3, 1, 1, Qt::AlignCenter);
        perso_layoutVetements->addWidget(vetement_explic[2], 1, 4, 1, 1, Qt::AlignCenter);
        perso_layoutVetements->addWidget(vetement_explic[3], 1, 5, 1, 1, Qt::AlignCenter);

        int lecteurVetement = 0, lecteurLigne = 2;

        while (lecteurVetement < MAX_VETEMENT)
        {
            switch (lecteurVetement)
            {
            case 0:
                vetement_type[lecteurVetement] = new QLabel("Châpeau");
                break;
            case 1:
                vetement_type[lecteurVetement] = new QLabel("Haut");
                break;
            case 2:
                vetement_type[lecteurVetement] = new QLabel("Bas");
                break;
            case 3:
                vetement_type[lecteurVetement] = new QLabel("Chaussures");
                break;
            case 4:
                vetement_type[lecteurVetement] = new QLabel("Divers");
                break;
            }

            vetement_nom[lecteurVetement] = new QLabel(m_vetements[lecteurVetement]->getNom());
            vetement_modif[lecteurVetement] = new QPushButton("Modifier");

            if (m_vetements[lecteurVetement]->getNom() == PAS_VETEMENT)
            {
                vetement_bonus[lecteurVetement] = new QLabel("-");
                vetement_malus[lecteurVetement] = new QLabel("-");

                vetement_check[lecteurVetement] = new CheckBox(vetement_modif[lecteurVetement],
                                                               m_vetements[lecteurVetement],
                                                               vetement_nom[lecteurVetement],
                                                               vetement_bonus[lecteurVetement],
                                                               vetement_malus[lecteurVetement]);
                vetement_check[lecteurVetement]->setChecked(false);
                vetement_modif[lecteurVetement]->setEnabled(false);
            }
            else
            {
                vetement_bonus[lecteurVetement] = new QLabel(m_vetements[lecteurVetement]->getBonus());
                vetement_malus[lecteurVetement] = new QLabel(m_vetements[lecteurVetement]->getMalus());

                vetement_check[lecteurVetement] = new CheckBox(vetement_modif[lecteurVetement],
                                                               m_vetements[lecteurVetement],
                                                               vetement_nom[lecteurVetement],
                                                               vetement_bonus[lecteurVetement],
                                                               vetement_malus[lecteurVetement]);
                vetement_check[lecteurVetement]->setChecked(true);
                vetement_modif[lecteurVetement]->setEnabled(true);
            }

            perso_layoutVetements->addWidget(vetement_check[lecteurVetement], lecteurLigne, 1, 1, 1);
            perso_layoutVetements->addWidget(vetement_type[lecteurVetement], lecteurLigne, 2, 1, 1, Qt::AlignCenter);
            perso_layoutVetements->addWidget(vetement_nom[lecteurVetement], lecteurLigne, 3, 1, 1, Qt::AlignCenter);
            perso_layoutVetements->addWidget(vetement_bonus[lecteurVetement], lecteurLigne, 4, 1, 1, Qt::AlignCenter);
            perso_layoutVetements->addWidget(vetement_malus[lecteurVetement], lecteurLigne, 5, 1, 1, Qt::AlignCenter);
            perso_layoutVetements->addWidget(vetement_modif[lecteurVetement], lecteurLigne, 6, 1, 1, Qt::AlignCenter);

            QObject::connect(vetement_check[lecteurVetement], SIGNAL(stateChanged(int)),
                             vetement_check[lecteurVetement], SLOT(changerVet(int)));
            QObject::connect(vetement_check[lecteurVetement], SIGNAL(bonus_malus_change()),
                             this, SLOT(setCaracModif_Affichage()));
            QObject::connect(vetement_modif[lecteurVetement], SIGNAL(clicked()),
                             vetement_check[lecteurVetement], SLOT(modifier_vetement()));

            lecteurVetement++;
            lecteurLigne++;
        }

    QWidget *a = new QWidget();
    a->setLayout(perso_layoutVetements);
    this->addTab(a, "Vêtements");

// Protections
    QGridLayout *perso_layoutProtections = new QGridLayout();
        perso_layoutProtections->setSpacing(15);
        perso_layoutProtections->setAlignment(Qt::AlignCenter);

        QLabel *protection_explic[5];
        protection_explic[0] = new QLabel("Nom :");
        protection_explic[1] = new QLabel("PR :");
        protection_explic[2] = new QLabel("Bonus :");
        protection_explic[3] = new QLabel("Malus :");

        perso_layoutProtections->addWidget(protection_explic[0], 1, 2, 1, 1, Qt::AlignCenter);
        perso_layoutProtections->addWidget(protection_explic[1], 1, 3, 1, 1, Qt::AlignCenter);
        perso_layoutProtections->addWidget(protection_explic[2], 1, 4, 1, 1, Qt::AlignCenter);
        perso_layoutProtections->addWidget(protection_explic[3], 1, 5, 1, 1, Qt::AlignCenter);

        int lecteurProtection = 0;
        lecteurLigne = 2;

        while (lecteurProtection < MAX_PROTECTION)
        {
            protection_nom[lecteurProtection] = new QLabel(m_protections[lecteurProtection]->getNom());
            protection_modif[lecteurProtection] = new QPushButton("Modifier");

            if (m_protections[lecteurProtection]->getNom() == PAS_PROTECTION)
            {
                protection_PR[lecteurProtection] = new QLabel("-");
                protection_bonus[lecteurProtection] = new QLabel("-");
                protection_malus[lecteurProtection] = new QLabel("-");

                protection_check[lecteurProtection] = new CheckBox(protection_modif[lecteurProtection],
                                                                   m_protections[lecteurProtection],
                                                                   protection_nom[lecteurProtection],
                                                                   protection_bonus[lecteurProtection],
                                                                   protection_malus[lecteurProtection],
                                                                   protection_PR[lecteurProtection]);
                protection_check[lecteurProtection]->setChecked(false);
                protection_modif[lecteurProtection]->setEnabled(false);
            }
            else
            {
                protection_PR[lecteurProtection] = new QLabel(m_protections[lecteurProtection]->getNombrePR());
                protection_bonus[lecteurProtection] = new QLabel(m_protections[lecteurProtection]->getBonus());
                protection_malus[lecteurProtection] = new QLabel(m_protections[lecteurProtection]->getMalus());

                protection_check[lecteurProtection] = new CheckBox(protection_modif[lecteurProtection],
                                                                   m_protections[lecteurProtection],
                                                                   protection_nom[lecteurProtection],
                                                                   protection_bonus[lecteurProtection],
                                                                   protection_malus[lecteurProtection],
                                                                   protection_PR[lecteurProtection]);
                protection_check[lecteurProtection]->setChecked(true);
                protection_modif[lecteurProtection]->setEnabled(true);
            }

            perso_layoutProtections->addWidget(protection_check[lecteurProtection], lecteurLigne, 1, 1, 1);
            perso_layoutProtections->addWidget(protection_nom[lecteurProtection], lecteurLigne, 2, 1, 1, Qt::AlignCenter);
            perso_layoutProtections->addWidget(protection_PR[lecteurProtection], lecteurLigne, 3, 1, 1, Qt::AlignCenter);
            perso_layoutProtections->addWidget(protection_bonus[lecteurProtection], lecteurLigne, 4, 1, 1, Qt::AlignCenter);
            perso_layoutProtections->addWidget(protection_malus[lecteurProtection], lecteurLigne, 5, 1, 1, Qt::AlignCenter);
            perso_layoutProtections->addWidget(protection_modif[lecteurProtection], lecteurLigne, 6, 1, 1, Qt::AlignCenter);

            QObject::connect(protection_check[lecteurProtection], SIGNAL(stateChanged(int)),
                             protection_check[lecteurProtection], SLOT(changerPr(int)));
            QObject::connect(protection_check[lecteurProtection], SIGNAL(bonus_malus_change()),
                             this, SLOT(setCaracModif_Affichage()));
            QObject::connect(protection_modif[lecteurProtection], SIGNAL(clicked()),
                             protection_check[lecteurProtection], SLOT(modifier_protection()));

            lecteurProtection++;
            lecteurLigne++;
        }

        QLabel *txtPrTotale = new QLabel("Total :");
        prTotale = new QLabel(QString::number(m_totalProtection));
        prTotale->setAlignment(Qt::AlignCenter);
        perso_layoutProtections->addWidget(txtPrTotale, lecteurLigne, 2, 1, 1, Qt::AlignCenter);
        perso_layoutProtections->addWidget(prTotale, lecteurLigne, 3, 1, 1, Qt::AlignCenter);

    QWidget *b = new QWidget();
    b->setLayout(perso_layoutProtections);
    this->addTab(b, "Protections");

// Armement
    armement = new QGroupBox("Armes de " + m_nomPerso);
        QGridLayout *perso_layoutArmement = new QGridLayout();
        perso_layoutArmement->setSpacing(15);
        perso_layoutArmement->setAlignment(Qt::AlignCenter);

        QLabel *armement_explic[5];

        armement_explic[0] = new QLabel("N° :");
        armement_explic[1] = new QLabel("Nom :");
        armement_explic[2] = new QLabel("Dégâts :");
        armement_explic[3] = new QLabel("Bonus :");
        armement_explic[4] = new QLabel("Malus :");

        perso_layoutArmement->addWidget(armement_explic[0], 1, 2, 1, 1, Qt::AlignCenter);
        perso_layoutArmement->addWidget(armement_explic[1], 1, 3, 1, 1, Qt::AlignCenter);
        perso_layoutArmement->addWidget(armement_explic[2], 1, 4, 1, 1, Qt::AlignCenter);
        perso_layoutArmement->addWidget(armement_explic[3], 1, 5, 1, 1, Qt::AlignCenter);
        perso_layoutArmement->addWidget(armement_explic[4], 1, 6, 1, 1, Qt::AlignCenter);

        int lecteurArmement = 0;
        lecteurLigne = 2;

        while (lecteurArmement < MAX_ARME)
        {
            armement_num[lecteurArmement] = new QLabel(QString::number(lecteurArmement+1));
            armement_nom[lecteurArmement] = new QLabel(m_armes[lecteurArmement]->getNom());
            armement_modif[lecteurArmement] = new QPushButton("Modifier");

            if (m_armes[lecteurArmement]->getNom() == PAS_ARME)
            {
                armement_degats[lecteurArmement] = new QLabel(m_armes[lecteurArmement]->getDegats());
                armement_bonus[lecteurArmement] = new QLabel("-");
                armement_malus[lecteurArmement] = new QLabel("-");

                arme_check[lecteurArmement] = new CheckBox(armement_modif[lecteurArmement],
                                                           m_armes[lecteurArmement],
                                                           armement_nom[lecteurArmement],
                                                           armement_bonus[lecteurArmement],
                                                           armement_malus[lecteurArmement],
                                                           armement_degats[lecteurArmement]);
                arme_check[lecteurArmement]->setChecked(false);
                armement_modif[lecteurArmement]->setEnabled(false);
            }
            else
            {
                armement_degats[lecteurArmement] = new QLabel(m_armes[lecteurArmement]->getDegats());
                armement_bonus[lecteurArmement] = new QLabel(m_armes[lecteurArmement]->getBonus());
                armement_malus[lecteurArmement] = new QLabel(m_armes[lecteurArmement]->getMalus());

                arme_check[lecteurArmement] = new CheckBox(armement_modif[lecteurArmement],
                                                           m_armes[lecteurArmement],
                                                           armement_nom[lecteurArmement],
                                                           armement_bonus[lecteurArmement],
                                                           armement_malus[lecteurArmement],
                                                           armement_degats[lecteurArmement]);
                arme_check[lecteurArmement]->setChecked(true);
                armement_modif[lecteurArmement]->setEnabled(true);
            }

            perso_layoutArmement->addWidget(arme_check[lecteurArmement], lecteurLigne, 1, 1, 1);
            perso_layoutArmement->addWidget(armement_num[lecteurArmement], lecteurLigne, 2, 1, 1, Qt::AlignCenter);
            perso_layoutArmement->addWidget(armement_nom[lecteurArmement], lecteurLigne, 3, 1, 1, Qt::AlignCenter);
            perso_layoutArmement->addWidget(armement_degats[lecteurArmement], lecteurLigne, 4, 1, 1, Qt::AlignCenter);
            perso_layoutArmement->addWidget(armement_bonus[lecteurArmement], lecteurLigne, 5, 1, 1, Qt::AlignCenter);
            perso_layoutArmement->addWidget(armement_malus[lecteurArmement], lecteurLigne, 6, 1, 1, Qt::AlignCenter);
            perso_layoutArmement->addWidget(armement_modif[lecteurArmement], lecteurLigne, 7, 1, 1, Qt::AlignCenter);

            QObject::connect(arme_check[lecteurArmement], SIGNAL(stateChanged(int)),
                             arme_check[lecteurArmement], SLOT(changerArme(int)));
            QObject::connect(arme_check[lecteurArmement], SIGNAL(bonus_malus_change()),
                             this, SLOT(setCaracModif_Affichage()));
            QObject::connect(armement_modif[lecteurArmement], SIGNAL(clicked()),
                             arme_check[lecteurArmement], SLOT(modifier_arme()));

            lecteurArmement++;
            lecteurLigne++;
        }

    armement->setLayout(perso_layoutArmement);

// Flèches
    fleche = new QGroupBox("Flèches de " + m_nomPerso);
        QGridLayout *perso_layoutFleches = new QGridLayout();
        perso_layoutFleches->setSpacing(15);
        perso_layoutFleches->setAlignment(Qt::AlignCenter);

        QLabel *Fleche_explic[4];
        Fleche_explic[0] = new QLabel("Nombre :");
        Fleche_explic[1] = new QLabel("Nom :");
        Fleche_explic[2] = new QLabel("Bonus :");

        perso_layoutFleches->addWidget(Fleche_explic[0], 1, 2, 1, 1, Qt::AlignCenter);
        perso_layoutFleches->addWidget(Fleche_explic[1], 1, 3, 1, 1, Qt::AlignCenter);
        perso_layoutFleches->addWidget(Fleche_explic[2], 1, 4, 1, 1, Qt::AlignCenter);

        int lecteurFleche = 0;
        lecteurLigne = 2;

        while (lecteurFleche < MAX_FLECHE)
        {
            fleche_nombre[lecteurFleche] = new QLineEdit(QString::number(m_fleches[lecteurFleche]->getNombre()));
                fleche_nombre[lecteurFleche]->setReadOnly(true);
                fleche_nombre[lecteurFleche]->setAlignment(Qt::AlignCenter);
                fleche_nombre[lecteurFleche]->setEnabled(true);
            fleche_plus[lecteurFleche] = new QPushButton("+");
                fleche_plus[lecteurFleche]->setEnabled(true);
            fleche_moins[lecteurFleche] = new QPushButton("-");
                fleche_moins[lecteurFleche]->setEnabled(true);

            fleche_modif[lecteurFleche] = new QPushButton("Modifier");

            if (m_fleches[lecteurFleche]->getNom() == PAS_FLECHE)
            {
                fleche_nombre[lecteurFleche]->setEnabled(false);
                fleche_plus[lecteurFleche]->setEnabled(false);
                fleche_moins[lecteurFleche]->setEnabled(false);
                fleche_nom[lecteurFleche] = new QLabel(m_fleches[lecteurFleche]->getNom());
                fleche_bonus[lecteurFleche] = new QLabel("-");

                fleche_check[lecteurFleche] = new CheckBox(fleche_modif[lecteurFleche],
                                                           m_fleches[lecteurFleche],
                                                           fleche_nom[lecteurFleche],
                                                           fleche_nombre[lecteurFleche],
                                                           fleche_bonus[lecteurFleche],
                                                           fleche_plus[lecteurFleche],
                                                           fleche_moins[lecteurFleche]);
                fleche_check[lecteurFleche]->setChecked(false);

                fleche_modif[lecteurFleche]->setEnabled(false);
            }
            else
            {
                fleche_nom[lecteurFleche] = new QLabel(m_fleches[lecteurFleche]->getNom());
                fleche_bonus[lecteurFleche] = new QLabel(m_fleches[lecteurFleche]->getBonus());

                fleche_check[lecteurFleche] = new CheckBox(fleche_modif[lecteurFleche],
                                                           m_fleches[lecteurFleche],
                                                           fleche_nom[lecteurFleche],
                                                           fleche_nombre[lecteurFleche],
                                                           fleche_bonus[lecteurFleche],
                                                           fleche_plus[lecteurFleche],
                                                           fleche_moins[lecteurFleche]);
                fleche_check[lecteurFleche]->setChecked(true);

                fleche_modif[lecteurFleche]->setEnabled(true);
            }

            perso_layoutFleches->addWidget(fleche_check[lecteurFleche], lecteurLigne, 1, 1, 1);
            perso_layoutFleches->addWidget(fleche_nombre[lecteurFleche], lecteurLigne, 2, 1, 1, Qt::AlignCenter);
            perso_layoutFleches->addWidget(fleche_nom[lecteurFleche], lecteurLigne, 3, 1, 1, Qt::AlignCenter);
            perso_layoutFleches->addWidget(fleche_bonus[lecteurFleche], lecteurLigne, 4, 1, 1, Qt::AlignCenter);
            perso_layoutFleches->addWidget(fleche_plus[lecteurFleche], lecteurLigne, 5, 1, 1);
            perso_layoutFleches->addWidget(fleche_moins[lecteurFleche], lecteurLigne, 6, 1, 1);
            perso_layoutFleches->addWidget(fleche_modif[lecteurFleche], lecteurLigne, 7, 1, 1);

            QObject::connect(fleche_check[lecteurFleche], SIGNAL(stateChanged(int)),
                             fleche_check[lecteurFleche], SLOT(changerFleche(int)));
            QObject::connect(fleche_modif[lecteurFleche], SIGNAL(clicked()),
                             fleche_check[lecteurFleche], SLOT(modifier_fleche()));

            lecteurFleche++;
            lecteurLigne++;
        }

    fleche->setLayout(perso_layoutFleches);

    // On ajoute les groupbox au layout2
        QVBoxLayout *fleche_arme = new QVBoxLayout();
            fleche_arme->addWidget(armement);
            fleche_arme->addItem(spacer[1]);
            fleche_arme->addWidget(fleche);

            QWidget *c = new QWidget();
            c->setLayout(fleche_arme);

            this->addTab(c, "Armement");

// Equipement
    QGridLayout *perso_layoutEquipements = new QGridLayout();

        int lecteurEquipement = 0;
        lecteurLigne = 1;

        while (lecteurEquipement < MAX_EQUIPEMENT)
        {
            equipement_num[lecteurEquipement] = new QLabel("Equipement n° " + QString::number(lecteurLigne) + " :");
            equipement_nom[lecteurEquipement] = new QTextEdit(*m_equipements[lecteurEquipement]);
                equipement_nom[lecteurEquipement]->setReadOnly(true);
                equipement_nom[lecteurEquipement]->setMinimumWidth(300);

            equipement_modif[lecteurEquipement] = new QPushButton("Modifier");
                equipement_modif[lecteurEquipement]->setEnabled(true);

            equipement_check[lecteurEquipement] = new CheckBox(equipement_modif[lecteurEquipement],
                                                               m_equipements[lecteurEquipement],
                                                               equipement_nom[lecteurEquipement]);
                equipement_check[lecteurEquipement]->setChecked(true);

            if (*m_equipements[lecteurEquipement] == PAS_EQUIPEMENTS)
            {
                equipement_check[lecteurEquipement]->setChecked(false);
                equipement_modif[lecteurEquipement]->setEnabled(false);
            }

            perso_layoutEquipements->addWidget(equipement_check[lecteurEquipement], lecteurLigne, 1, 1, 1);
            perso_layoutEquipements->addWidget(equipement_num[lecteurEquipement], lecteurLigne, 2, 1, 1);
            perso_layoutEquipements->addWidget(equipement_nom[lecteurEquipement], lecteurLigne, 3, 1, 1, Qt::AlignCenter);
            perso_layoutEquipements->addWidget(equipement_modif[lecteurEquipement], lecteurLigne, 4, 1, 1);

            QObject::connect(equipement_check[lecteurEquipement], SIGNAL(stateChanged(int)),
                             equipement_check[lecteurEquipement], SLOT(changerEquipement(int)));
            QObject::connect(equipement_modif[lecteurEquipement], SIGNAL(clicked()),
                             equipement_check[lecteurEquipement], SLOT(modifier_equipement()));

            lecteurEquipement++;
            lecteurLigne++;
        }

    QWidget *d = new QWidget();
    d->setLayout(perso_layoutEquipements);
    this->addTab(d, "Equipements");
}
QTabWidget* Personnage::getAffichage()
{
    return this;
}
void Personnage::afficherCompetences(bool nouvelleCompetence)
{
    // si le tableau est vide, on demande si on veut le remplir
    if (m_competences.isEmpty())
    {
        bool ok(true);
        int nb = QInputDialog::getInt(this, m_nomPerso + " -> Aucunes compétences",
                                     "Ce pesonnage ne semble pas avoir de compétence, est-il si nul que ça ?\n"
                                     "Combien de compétences voulez-vous lui rajouter ?\n"
                                     "Cliquez sur annuler pour ne pas en ajouter !", 1, 1, 50, 1, &ok);
        if (ok)
            for (int i(0); i < nb; i++)
                addCompetence();
    }

    // Si nouvelle compétence -> ajout du dernier widget
    if (nouvelleCompetence)
        layoutCompetences->addWidget(m_competences.at(m_competences.count() - 1)->getWidget());
    // Sinon, ajout du tableau
    else
        for (int i(0); i < m_competences.count(); i++)
            layoutCompetences->addWidget(m_competences.at(i)->getWidget());
}

// Pour récuérer le nom de l'individu
QString Personnage::getNom() const
{
    return m_nomPerso;
}

// Pour récupérer l'adresse
QString Personnage::getAdresse() const
{
    return m_adresseFichierPerso;
}


// Pour calculer le niveau
bool Personnage::setNiveau()
{
    int niveauAncien = m_niveau;

    if (m_experience == 0 || m_experience < 100)
    {
        m_niveau = 1;
    }
    else if (m_experience == 100 || m_experience < 300)
    {
        m_niveau = 2;
    }
    else if (m_experience == 300 || m_experience < 600)
    {
        m_niveau = 3;
    }
    else if (m_experience == 600 || m_experience < 1000)
    {
        m_niveau = 4;
    }
    else if (m_experience == 1000 || m_experience < 1500)
    {
        m_niveau = 5;
    }
    else if (m_experience == 1500 || m_experience < 2100)
    {
        m_niveau = 6;
    }
    else if (m_experience == 2100 || m_experience < 2800)
    {
        m_niveau = 7;
    }
    else if (m_experience == 2800 || m_experience < 3600)
    {
        m_niveau = 8;
    }
    else if (m_experience == 3600 || m_experience < 4500)
    {
        m_niveau = 9;
    }
    else if (m_experience == 4500 || m_experience < 5500)
    {
        m_niveau = 10;
    }
    else if (m_experience == 5500 || m_experience < 6600)
    {
        m_niveau = 11;
    }
    else if (m_experience == 6600 || m_experience < 7800)
    {
        m_niveau = 12;
    }
    else if (m_experience == 7800 || m_experience < 9100)
    {
        m_niveau = 13;
    }
    else if (m_experience == 9100 || m_experience < 10500)
    {
        m_niveau = 14;
    }
    else if (m_experience == 10500 || m_experience < 12000)
    {
        m_niveau = 15;
    }
    else if (m_experience == 12000 || m_experience < 13600)
    {
        m_niveau = 16;
    }
    else if (m_experience == 13600 || m_experience < 15300)
    {
        m_niveau = 17;
    }
    else if (m_experience == 15300 || m_experience < 17100)
    {
        m_niveau = 18;
    }
    else if (m_experience == 17100 || m_experience < 19000)
    {
        m_niveau = 19;
    }
    else if (m_experience == 19000 || m_experience < 21000)
    {
        m_niveau = 20;
    }
    else if (m_experience == 21000 || m_experience < 24000)
    {
        m_niveau = 21;
    }
    else if (m_experience == 24000 || m_experience < 29000)
    {
        m_niveau = 22;
    }
    else if (m_experience == 29000 || m_experience < 35000)
    {
        m_niveau = 23;
    }
    else if (m_experience == 35000 || m_experience < 45000)
    {
        m_niveau = 24;
    }
    else if (m_experience == 45000 || m_experience < 60000)
    {
        m_niveau = 25;
    }
    else if (m_experience >= 6000)
    {
        m_niveau = 26;
    }

    level->setText(QString::number(m_niveau));

    // Si le niveau est modifié, on renvoie 'true'
    if (niveauAncien != m_niveau)
        return true;
    else
        return false;
}

// Pour initialiser les variables des mages, ...
void Personnage::setEA(int EA, QString typeEA)
{
    m_energieAstrale = EA;
    m_energieAstrale_modif = EA;
    typeEnergieAstrale = typeEA;
    presenceEnergieAstrale = true;
}

// Pour appliquer une adresse de fichier
void Personnage::setAdresse(QString const& adresse)
{
    m_adresseFichierPerso = adresse;
}

// Pour recalculer les caractèristiques
void Personnage::setCaracModif_Affichage()
{
    m_totalProtection = 0;
    m_caracModifiees = m_caracInitiales;
// Vêtements
    for (int lecteur = 0; lecteur < MAX_VETEMENT; lecteur++)
    {
        m_caracModifiees += m_vetements[lecteur]->bonus();
        m_caracModifiees -= m_vetements[lecteur]->malus();
    }

// Protections
    for (int lecteur = 0; lecteur < MAX_PROTECTION; lecteur++)
    {
        m_totalProtection += m_protections[lecteur]->nombreProtection();

        m_caracModifiees += m_protections[lecteur]->bonus();
        m_caracModifiees -= m_protections[lecteur]->malus();
    }

// Armes
    for (int lecteur = 0; lecteur < MAX_ARME; lecteur++)
    {
        m_caracModifiees += m_armes[lecteur]->bonus();
        m_caracModifiees -= m_armes[lecteur]->malus();
    }

    rafraichir();
}
void Personnage::setBonus_Malus_caracSup_Inf_moyenne(int degatsBonus, int bonusAttaque, int bonusParade, int degatsBonusSorts)
{
    m_degatsBonus = 0;
    m_degatsBonusSorts = 0;
// Bonus / Malus de FO
    if (degatsBonus == 0)
    {
        for (int fo(m_caracModifiees.getFO()); fo > 12; fo--)
            m_degatsBonus++;
        for (int fo(m_caracModifiees.getFO()); fo <8; fo++)
            m_degatsBonus--;
    }
    else // si provient chargement perso
        m_degatsBonus = degatsBonus;

// bonus / malus de AD
    if (bonusAttaque == 0 && bonusParade == 0) // si pas renseigné
    {
//        if (m_caracModifiees.getAT() + 1 == m_caracInitiales.getAT()
//                || m_caracModifiees.getAT() - 1 == m_caracInitiales.getAT()
//                || m_caracModifiees.getPRD() + 1 == m_caracInitiales.getPRD()
//                || m_caracModifiees.getPRD() - 1 == m_caracInitiales.getPRD()) // si déjà modifié
//        {
        m_caracModifiees.setAT(m_caracModifiees.getAT() - m_attaqueBonus);
        m_caracModifiees.setPRD(m_caracModifiees.getPRD() - m_paradeBonus);
            m_attaqueBonus = 0;
            m_paradeBonus = 0;

            if (m_caracModifiees.getAD() > 12)
            {
                bool ok(false);
                QStringList at_prd;
                at_prd << "Attaque" << "Parade";
                QString choix("");

                while (!ok)
                    choix = QInputDialog::getItem(this, m_nomPerso + " -> Caractéristiques inférieures à la normale.",
                                                  "Ce personnage a un malus de 1 point, en raison de son adresse nullissime, sur :",
                                                  at_prd, 0, false, &ok);
                if (choix == "Attaque")
                {
                    m_caracModifiees.AT_1();
                    m_attaqueBonus = 1;
                }
                if (choix == "Parade")
                {
                    m_caracModifiees.PRD_1();
                    m_paradeBonus = 1;
                }
            }
            if (m_caracModifiees.getAD() < 8)
            {
                bool ok(false);
                QStringList at_prd;
                at_prd << "Attaque" << "Parade";
                QString choix("");

                while (!ok)
                    choix = QInputDialog::getItem(this, m_nomPerso + " -> Caractéristiques inférieures à la normale.",
                                                  "Ce personnage a un malus de 1 point, en raison de son adresse nullissime, sur :",
                                                  at_prd, 0, false, &ok);
                if (choix == "Attaque")
                {
                    m_caracModifiees.AT_1(false);
                    m_attaqueBonus = -1;
                }
                if (choix == "Parade")
                {
                    m_caracModifiees.PRD_1(false);
                    m_paradeBonus = -1;
                }
            }
//        }
    }
    else
    {
        m_attaqueBonus = bonusAttaque;
        m_paradeBonus = bonusParade;
    }


//    problème de vérification si déjà fait !!!

// bonus / malus de INT
    if (degatsBonusSorts == 0)
    {
        for (int intel(m_caracModifiees.getINT()); intel > 12; intel--)
            m_degatsBonusSorts++;
        for (int intel(m_caracModifiees.getINT()); intel <8; intel++)
            m_degatsBonusSorts--;
    }
    else
        m_degatsBonusSorts = degatsBonusSorts;

}


// Pour rafraîchir les widgets
void Personnage::rafraichir()
{
    setBonus_Malus_caracSup_Inf_moyenne();

// Total de protection
    prTotale->setText(QString::number(m_totalProtection));

// Points de destin + XP
    XP->setText(QString::number(m_experience));
    level->setText(QString::number(m_niveau));
    ptsDeDestin->setText(QString::number(m_pointsDestin));
        if (m_pointsDestin == 0)
            ptsDeDestin_moins->setEnabled(false);

// Richesses
    PO->setText(QString::number(m_pieces->getRichesses_Or()));
        if (m_pieces->getRichesses_Or() != 999999)
            PO_plus->setEnabled(true);
        else
            PO_plus->setEnabled(false);

        if (m_pieces->getRichesses_Or() != 0)
            PO_moins->setEnabled(true);
        else
            PO_moins->setEnabled(false);

    PA->setText(QString::number(m_pieces->getRichesses_Argent()));
        if (m_pieces->getRichesses_Argent() != 999999)
            PA_plus->setEnabled(true);
        else
            PA_plus->setEnabled(false);

        if (m_pieces->getRichesses_Argent() != 0)
            PA_moins->setEnabled(true);
        else
            PA_moins->setEnabled(false);

    PC->setText(QString::number(m_pieces->getRichesses_Cuivre()));
        if (m_pieces->getRichesses_Cuivre() != 999999)
            PC_plus->setEnabled(true);
        else
            PC_plus->setEnabled(false);

        if (m_pieces->getRichesses_Cuivre() != 0)
            PC_moins->setEnabled(true);
        else
            PC_moins->setEnabled(false);


// EV et EA + Résistance magie + magie Physique + magie psychique
    EV->setText(QString::number(m_energieVitale));
    EV_modif->setText(QString::number(m_energieVitale_modif));
        if (m_energieVitale_modif != m_energieVitale)
            EV_plus->setEnabled(true);
        else
            EV_plus->setEnabled(false);

        if (m_energieVitale_modif != 0)
            EV_moins->setEnabled(true);
        else
            EV_moins->setEnabled(false);

    magieResist->setText(QString::number((m_caracModifiees.getINT()
                                          + m_caracModifiees.getCOU()
                                          + m_caracModifiees.getFO()) / 3));

    if (presenceEnergieAstrale)
    {
        EA->setText(QString::number(m_energieAstrale));
        EA_modif->setText(QString::number(m_energieAstrale_modif));
            if (m_energieAstrale_modif != m_energieAstrale)
                EA_plus->setEnabled(true);
            else
                EA_plus->setEnabled(false);

            if (m_energieAstrale_modif != 0)
                EA_moins->setEnabled(true);
            else
                EA_moins->setEnabled(false);

        magiePhys->setText(QString::number((m_caracModifiees.getINT()
                                            + m_caracModifiees.getAD()) / 2));
        magiePsy->setText(QString::number((m_caracModifiees.getINT()
                                           + m_caracModifiees.getCHA()) / 2));
    }


// Autres caractéristiques
    COU->setText(QString::number(m_caracInitiales.getCOU()));
    COU_modif->setText(QString::number(m_caracModifiees.getCOU()));
        if (m_caracModifiees.getCOU() != 18)
            COU_plus->setEnabled(true);
        else
            COU_plus->setEnabled(false);

        if (m_caracModifiees.getCOU() != 2)
            COU_moins->setEnabled(true);
        else
            COU_moins->setEnabled(false);

    INT->setText(QString::number(m_caracInitiales.getINT()));
    INT_modif->setText(QString::number(m_caracModifiees.getINT()));
        if (m_caracModifiees.getINT() != 18)
            INT_plus->setEnabled(true);
        else
            INT_plus->setEnabled(false);

        if (m_caracModifiees.getINT() != 2)
            INT_moins->setEnabled(true);
        else
            INT_moins->setEnabled(false);

    CHA->setText(QString::number(m_caracInitiales.getCHA()));
    CHA_modif->setText(QString::number(m_caracModifiees.getCHA()));
        if (m_caracModifiees.getCHA() != 18)
            CHA_plus->setEnabled(true);
        else
            CHA_plus->setEnabled(false);
        if (m_caracModifiees.getCHA() != 2)
            CHA_moins->setEnabled(true);
        else
            CHA_moins->setEnabled(false);

    AD->setText(QString::number(m_caracInitiales.getAD()));
    AD_modif->setText(QString::number(m_caracModifiees.getAD()));
        if (m_caracModifiees.getAD() != 18)
            AD_plus->setEnabled(true);
        else
            AD_plus->setEnabled(false);

        if (m_caracModifiees.getAD() != 2)
            AD_moins->setEnabled(true);
        else
            AD_moins->setEnabled(false);

    FO->setText(QString::number(m_caracInitiales.getFO()));
    FO_modif->setText(QString::number(m_caracModifiees.getFO()));
        if (m_caracModifiees.getFO() != 18)
            FO_plus->setEnabled(true);
        else
            FO_plus->setEnabled(false);

        if (m_caracModifiees.getFO() != 2)
            FO_moins->setEnabled(true);
        else
            FO_moins->setEnabled(false);

    AT->setText(QString::number(m_caracInitiales.getAT()));
    AT_modif->setText(QString::number(m_caracModifiees.getAT()));
        if (m_caracModifiees.getAT() != 18)
            AT_plus->setEnabled(true);
        else
            AT_plus->setEnabled(false);
        AT_plus->setEnabled(false);

        if (m_caracModifiees.getAT() != 2)
            AT_moins->setEnabled(true);
        else
            AT_moins->setEnabled(false);
        AT_moins->setEnabled(false);

    PRD->setText(QString::number(m_caracInitiales.getPRD()));
    PRD_modif->setText(QString::number(m_caracModifiees.getPRD()));
        if (m_caracModifiees.getPRD() != 18)
            PRD_plus->setEnabled(true);
        else
            PRD_plus->setEnabled(false);
        PRD_plus->setEnabled(false);
        if (m_caracModifiees.getPRD() != 2)
            PRD_moins->setEnabled(true);
        else
            PRD_moins->setEnabled(false);
        PRD_moins->setEnabled(false);

    carac_degatsBonus->setText(QString::number(m_degatsBonus));
    carac_attaqueBonus->setText(QString::number(m_attaqueBonus));
    carac_paradeBonus->setText(QString::number(m_paradeBonus));
    carac_degatsBonusSorts->setText(QString::number(m_degatsBonusSorts));
}


// Achat
void Personnage::achatATPRD()
{
    if (m_pieces->getRichesses_Or() < 500)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QStringList a;
    a << "AT" << "PRD";
    bool ok(false);
    QString b = QInputDialog::getItem(this, m_nomPerso + " -> Achat de puissance",
                                      "Ce personnage achète un stage pour 500 PO pour obtenir un point de :", a, 0, ok);
    if (b == "AT" && ok)
    {
        QMessageBox::information(this, m_nomPerso + " -> Achat de puissance",
                                "Ce personnage achète 500 PO un stage d'un mois pour acheter un point de AT");
        m_caracInitiales.AT_1();

        log(m_nomPerso + " achète un point de AT.");
    }
    else if (b == "PRD" && ok)
    {
        QMessageBox::information(this, m_nomPerso + " -> Achat de puissance",
                                "Ce personnage achète 500 PO un stage d'un mois pour acheter un point de PRD");
        m_caracInitiales.PRD_1();

        log(m_nomPerso + " achète un point de de PRD.");
    }

    if (ok)
        m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 500);

    rafraichir();
}
void Personnage::achatINT()
{
    if (m_pieces->getRichesses_Or() < 500)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nomPerso + " -> Achat de puissance",
                      "Ce personnage va acheter pour 500 PO en stage de 6 mois pour obtenir un point de INT...");
    QPushButton *continuer = verif.addButton("Valider", QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nomPerso + " -> Achat de puissance",
                            "Ce personnage achète 500 PO un stage de 6 mois pour obtenir un point de INT");
    m_caracInitiales.INT_1();

    m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 500);

    log(m_nomPerso + " achète un point de INT.");

    rafraichir();
}
void Personnage::achatCHA()
{
    if (m_pieces->getRichesses_Or() < 400)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nomPerso + " -> Achat de puissance",
                      "Ce personnage va acheter pour 400 PO en stage de 1 semaine pour obtenir un point de CHA...");
    QPushButton *continuer = verif.addButton("Valider", QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nomPerso + " -> Achat de puissance",
                             "Ce personnage achète 400 PO un stage de 1 semaine (max 1 par mois) pour obtenir un point de CHA");
    m_caracInitiales.CHA_1();

    m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 400);

    log(m_nomPerso + " achète un point de CHA.");

    rafraichir();
}
void Personnage::achatFO()
{
    if (m_pieces->getRichesses_Or() < 400)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nomPerso + " -> Achat de puissance",
                      "Ce personnage va acheter pour 400 PO en stage de 1 mois pour obtenir un point de FO...");
    QPushButton *continuer = verif.addButton("Valider", QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nomPerso + " -> Achat de puissance",
                            "Ce personnage achète 400 PO un stage de 1 mois pour obtenir un point de FO");
    m_caracInitiales.FO_1();

    m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 400);

    log(m_nomPerso + " achète un point de FO.");

    rafraichir();
}
void Personnage::achatCOU()
{
    if (m_pieces->getRichesses_Or() < 400)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nomPerso + " -> Achat de puissance",
                      "Ce personnage va acheter pour 400 PO en stage de 1 mois pour obtenir un point de COU...");
    QPushButton *continuer = verif.addButton("Valider", QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nomPerso + " -> Achat de puissance",
                            "Ce personnage achète 400 PO un stage de 1 mois pour obtenir un point de COU");
    m_caracInitiales.COU_1();

    m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 400);

    log(m_nomPerso + " achète un point de COU.");

    rafraichir();
}
void Personnage::achatEV()
{
    if (m_pieces->getRichesses_Or() < 200)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nomPerso + " -> Achat d'énergie",
                      "Ce personnage va acheter pour 200 PO en stage de 2 semaine2 pour obtenir un point de EV...");
    QPushButton *continuer = verif.addButton("Valider", QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nomPerso + " -> Achat d'énergie",
                            "Ce personnage achète 200 PO un stage de 2 semaines pour obtenir un point de EV");
    m_energieVitale++;
    m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 200);

    log(m_nomPerso + " achète un point de EV.");

    rafraichir();
}
void Personnage::achatEA()
{
    if (!presenceEnergieAstrale)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'est pas un mage ; "
                                 "il ne peut donc pas suivre un stage pour gagner de l'EA!");
        return;
    }

    if (m_pieces->getRichesses_Or() < 200)
    {
        QMessageBox::information(this, "Action impossible !",
                                 "Ce personnage n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nomPerso + " -> Achat d'énergie",
                      "Ce personnage va acheter pour 200 PO en stage de 1 mois pour obtenir un point de EA...");
    QPushButton *continuer = verif.addButton("Valider", QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nomPerso + " -> Achat d'énergie",
                            "Ce personnage achète 200 PO un stage de 1 mois pour obtenir un point de EA");
    m_energieAstrale++;
    m_pieces->setRichesses_Or(m_pieces->getRichesses_Or() - 200);

    log(m_nomPerso + " achète un point de EA.");

    rafraichir();
}


// Ajout d'équipements lors du chargement du fichier d'enregistrement
void Personnage::addVetement(Vetement *VetementAAjouter, int num)
{
    if (num < MAX_VETEMENT)
        m_vetements[num] = new Vetement(VetementAAjouter);
    else
    {
        log("ERREUR : Il y a trop de vêtements pour '" + m_nomPerso + "' !");
        QMessageBox::information(labelPourSaut[0], "Erreur", "ERREUR :\nIl y a trop de vêtements pour ce personnage !\n\nCe problème peut venir du fait que vous ayez fait vous même le fichier *.perso !\nEvitez de faire cela !");
    }
}
void Personnage::addProtection(Protection *protectionAAjouter, int num)
{
    if (num < MAX_PROTECTION)
        m_protections[num] = new Protection(protectionAAjouter);
    else
    {
        log("ERREUR : Il y a trop de protections pour '" + m_nomPerso + "' !");
        QMessageBox::information(labelPourSaut[0], "Erreur", "ERREUR :\nIl y a trop de protection pour ce personnage !\n\nCe problème peut venir du fait que vous ayez fait vous même le fichier *.perso !\nEvitez de faire cela !");
    }
}
void Personnage::addArme(Arme *armeAAjouter, int num)
{
    if (num < MAX_ARME)
        m_armes[num] = new Arme(armeAAjouter);
    else
    {
        log("ERREUR : Il y a trop d'armes pour '" + m_nomPerso + "' !");
        QMessageBox::information(labelPourSaut[0], "Erreur", "ERREUR :\nIl y a trop d'arme pour ce personnage !\n\nCe problème peut venir du fait que vous ayez fait vous même le fichier *.perso !\nEvitez de faire cela !");
    }
}
void Personnage::addFleche(Fleche *flecheAAjouter, int num)
{
    if (num < MAX_FLECHE)
        m_fleches[num] = new Fleche(flecheAAjouter);
    else
    {
        log("ERREUR : Il y a trop de flêches pour '" + m_nomPerso + "' !");
        QMessageBox::information(labelPourSaut[0], "Erreur", "ERREUR :\nIl y a trop de flèches pour ce personnage !\n\nCe problème peut venir du fait que vous ayez fait vous même le fichier *.perso !\nEvitez de faire cela !");
    }
}
void Personnage::addEquipement(QString nom, int num)
{
    if (num < MAX_EQUIPEMENT)
        m_equipements[num] = new QString(nom);
    else
    {
        log("ERREUR : Il y a trop d'équipements pour '" + m_nomPerso + "' !");
        QMessageBox::information(labelPourSaut[0], "Erreur", "ERREUR :\nIl y a trop d'équipement pour ce personnage !\n\nCe problème peut venir du fait que vous ayez fait vous même le fichier *.perso !\nEvitez de faire cela !");
    }
}
void Personnage::addCompetence(QString nom, QString description)
{
    if (nom != "" && description != "")
    {
        m_competences.push_back(new Competence(nom, description));
    }
    else
    {
        fenAjoutCompetence = new QDialog(this, Qt::WindowCancelButtonHint | Qt::WindowOkButtonHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
            fenAjoutCompetence->setWindowTitle(m_nomPerso + " -> ajout d'une compétence !");

        QGroupBox nom_group("Nom");
            competence_nom = new QLineEdit();
            QVBoxLayout layout1;
                layout1.addWidget(competence_nom);
            nom_group.setLayout(&layout1);

        QGroupBox description_group("Description");
            competence_description = new QTextEdit();
            QVBoxLayout layout2;
                layout2.addWidget(competence_description);
            description_group.setLayout(&layout2);

        QDialogButtonBox boutons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            QObject::connect(&boutons, SIGNAL(accepted()), this, SLOT(addCompetence2()));
            QObject::connect(&boutons, SIGNAL(rejected()), fenAjoutCompetence, SLOT(close()));

        QVBoxLayout total;
            total.addWidget(&nom_group);
            total.addWidget(&description_group);
            total.addWidget(&boutons);

        fenAjoutCompetence->setLayout(&total);

        fenAjoutCompetence->exec();
    }
}
void Personnage::addCompetence2()
{
    m_competences.push_back(new Competence(competence_nom->text(), competence_description->toPlainText()));
    afficherCompetences(true);

    delete competence_nom;
    delete competence_description;

    fenAjoutCompetence->close();
}


// Pour l'enregistrement
QString Personnage::getPersoEntier() const
{
    QString total = "";

    total += m_nomPerso + "\n";
    total += m_sexePerso + "\n";
    total += m_originePersonnage + "\n";
    total += m_metierPersonnage + "\n";
    total += QString::number(m_energieVitale) + "\n";
    total += QString::number(m_pointsDestin) + "\n";
    total += QString::number(m_experience) + "\n";
    total += m_caracInitiales.getCaracteristiques() + "\n";
    total += m_caracModifiees.getCaracteristiques() + "\n";

    total += m_pieces->getRichesses() + "\n";

    total += "~!carac_sup_inf!~\n";
    total += QString::number(m_degatsBonus) + "\n";
    total += QString::number(m_attaqueBonus) + "\n";
    total += QString::number(m_paradeBonus) + "\n";
    total += QString::number(m_degatsBonusSorts) + "\n";

    if (presenceEnergieAstrale)
    {
        total += "~!magie!~\n" + QString::number(m_energieAstrale) + "\n" + typeEnergieAstrale + "\n";
    }

    total += "~!chapeau!~\n" + m_vetements[0]->getVetement() + "\n";
    total += "~!haut!~\n" + m_vetements[1]->getVetement() + "\n";
    total += "~!bas!~\n" + m_vetements[2]->getVetement() + "\n";
    total += "~!chaussures!~\n" + m_vetements[3]->getVetement() + "\n";
    total += "~!divers!~\n" + m_vetements[4]->getVetement() + "\n";

    for (int lecteur = 0; lecteur < MAX_PROTECTION; lecteur++)
    {
        total += m_protections[lecteur]->getProtection() + "\n";
    }

    for (int lecteur = 0; lecteur < MAX_ARME; lecteur++)
    {
        total += m_armes[lecteur]->getArme() + "\n";
    }

    for (int lecteur = 0; lecteur < MAX_FLECHE; lecteur++)
    {
        total += m_fleches[lecteur]->getFleche() + "\n";
    }

    for (int lecteur = 0; lecteur < MAX_EQUIPEMENT; lecteur++)
    {
        total += "~!equipement!~\n" + *m_equipements[lecteur] + "\n";
    }

    for (int lecteur = 0; lecteur < m_competences.count(); lecteur++)
    {
        total += "~!competence!~\n";
        total += m_competences.at(lecteur)->getNom() + "\n";
        total += m_competences.at(lecteur)->getDescription() + "\n";
    }

    total += "~!FIN_ENREGISTREMENT!~";

    return total;
}


// Pour les tests d'origines et de métiers
bool Personnage::testOrigine(Origine const& a)
{
    bool possible = false;

    if (a.getMini() <= m_caracInitiales && a.getMaxi() >= m_caracInitiales)
        possible = true;

    return possible;
}
bool Personnage::testMetier(Metier const& a)
{
    bool possible = false;

    if (a.getMini() <= m_caracInitiales)
        possible = true;

    return possible;
}

// Pour appliquer une origine et un métier
void Personnage::setOrigine(Origine &a)
{
    m_energieVitale = a.getEV();
    m_energieVitale_modif = m_energieVitale;

    m_originePersonnage = a.getNom();

    if (a.getAT() != 0)
        m_caracInitiales.setAT(a.getAT());

    QVector<Competence *> compet_obli = a.getCompetences();
    for (int i(0); i < compet_obli.count(); i++)
        m_competences.append(compet_obli.at(i));
}
void Personnage::setMetier(Metier& a)
{
    m_metierPersonnage = a.getNom();

    if (a.getAT() != 0)
        m_caracInitiales.setAT(a.getAT());

    if (a.getPRD() != 0)
        m_caracInitiales.setPRD(a.getPRD());

// Modification pour certains métiers :
    if (a.getEV_pourClassesModifiees() != 0)
    {
        QStringList listeClasseModifiees = a.getClassesModifiees();
        bool persoEstClasseModifiee(false);

        for(int i = 0; i < listeClasseModifiees.size(); i++)
        {
            if (listeClasseModifiees.at(i) == m_originePersonnage)
                persoEstClasseModifiee = true;
        }

        if (persoEstClasseModifiee)
            m_energieVitale = a.getEV_pourClassesModifiees();
        else
        {
            if (a.getEV_pourAutresClasses_pourcent()) // Si la modif est en pourcent
            {
                int modif = a.getEV_pourAutresClasses();    // On demande combien de pourcent
                // On calcule 1 pourcent de l'actuelle EV
                double unPourcent_EV = static_cast<double>(m_energieVitale) / static_cast<double>(100);
                int ajout = unPourcent_EV * modif;          // On calcule le résultat à ajouter

                m_energieVitale += ajout;
            }
            else // Sinon
                m_energieVitale += a.getEV_pourAutresClasses();
        }

        m_energieVitale_modif = m_energieVitale;
    }

    if (a.getPresenceEA())
    {
        setEA(a.getEA(), a.getTypeEA());
    }

// Copie des caractéristiques
    QVector<Competence *> compet_obli = a.getCompetences();
    for (int i(0); i < compet_obli.count(); i++)
        m_competences.append(compet_obli.at(i));
}



// Slots pour les connexions des boutons
void Personnage::conversionPAPC_PO()
{
    m_pieces->conversionPAPC_PO();
    rafraichir();
}
void Personnage::conversionPO_PA()
{
    m_pieces->conversionPO_PA();
    rafraichir();
}
void Personnage::conversionPO_PC()
{
    m_pieces->conversionPO_PC();
    rafraichir();
}
void Personnage::conversionPA_PC()
{
    m_pieces->conversionPA_PC();
    rafraichir();
}

// Ajout différents de 1
void Personnage::plus_xp(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int XP_EnPlus = QInputDialog::getInteger(labelPourSaut[0], "Ajouter de l'expérience", "Ajouter de l'expérience à " + m_nomPerso, 1, 1, 999999, 1, &ok);

        if (ok)
        {
            m_experience += XP_EnPlus;

            log(m_nomPerso + " gagne de l'expérience : " + QString::number(XP_EnPlus) + " point(s) !");
        }
    }
    else
    {
        m_experience += value;

        log(m_nomPerso + " gagne de l'expérience : " + QString::number(value) + " point(s) !");
    }

    bool niveauChange(setNiveau());
    if (niveauChange)
    {
        QString D;
        QMessageBox::information(this, "Niveau", m_nomPerso + " a gagné un niveau, nous allons voir les modifications...");
        QStringList D6_D4;
        D6_D4 << "D6" << "D4";
        D = QInputDialog::getItem(this, m_nomPerso + " -> Passage d'un niveau -> EV",
                                  "Quel type de dé l'origine de ce personnage a besoin pour l'ajout d'EV ?",
                                  D6_D4);
        int ev;
        if (D == "D6")
        {
            ev = QInputDialog::getInt(this, m_nomPerso + " -> Passage d'un niveau -> EV",
                                      "Quel score le D6 indique-t-il ?", 1, 1, 6);
            m_energieVitale += ev;
            QMessageBox::information(this, "Information sur l'EV de " + m_nomPerso,
                                     "Ce personnage gagne " + QString::number(ev) + " pt d'EV en plus");
        }
        else if (D == "D4")
        {
            ev = QInputDialog::getInt(this, m_nomPerso + " -> Passage d'un niveau -> EV",
                                      "Quel score le D4 indique-t-il ?", 1, 1, 4);
            m_energieVitale += ev;
            QMessageBox::information(this, "Information sur l'EV de " + m_nomPerso,
                                     "Ce personnage gagne " + QString::number(ev) + " pt d'EV en plus");
        }

        if (m_metierPersonnage == "Mage / Sorcier")
        {
            int ea = QInputDialog::getInt(this, m_nomPerso + " -> Passage d'un niveau -> EA",
                                          "EA -> Quel score le D6 indique-t-il ?", 1, 1, 6);
            m_energieAstrale += ea;
            QMessageBox::information(this, "Information sur l'EA de " + m_nomPerso,
                                     "Ce personnage gagne " + QString::number(ea) + " pt d'EA en plus");
        }

        QStringList carac;
        carac << "COU" << "INT" << "AD" << "FO";
        D = QInputDialog::getItem(this, m_nomPerso + " -> Passage d'un niveau -> Caractéristiques",
                                  "Ce personnage a droit à un point en plus sur les caractéristiques suivantes.\n"
                                  "Choisissez en une !",
                                  carac);
        if (D == "COU")
        {
            m_caracInitiales.COU_1();
            QMessageBox::information(this, "Information sur le COU de " + m_nomPerso,
                                     "Ce personnage gagne 1 pt de COU en plus");
        }
        else if (D == "INT")
        {
            m_caracInitiales.INT_1();
            QMessageBox::information(this, "Information sur l'INT de " + m_nomPerso,
                                     "Ce personnage gagne 1 pt d'INT en plus");
        }
        else if (D == "AD")
        {
            m_caracInitiales.AD_1();
            QMessageBox::information(this, "Information sur l'AD de " + m_nomPerso,
                                     "Ce personnage gagne 1 pt d'AD en plus");
        }
        else if (D == "FO")
        {
            m_caracInitiales.FO_1();
            QMessageBox::information(this, "Information sur la FO de " + m_nomPerso,
                                     "Ce personnage gagne 1 pt de FO en plus");
        }

        if (m_originePersonnage == "Elfe Sylvain" || m_originePersonnage == "Haut-elfe")
        {
            QMessageBox::information(this, "Information sur le CHA de " + m_nomPerso,
                                     "Ce personnage gagne 1 pt de CHA en plus, en raison de son origine");
            m_caracInitiales.CHA_1();
        }

        if (m_caracInitiales.getAT() < 18 && m_caracInitiales.getPRD() < 17)
        {
            QStringList At_Prd;
            At_Prd << "AT" << "PRD";
            D = QInputDialog::getItem(this, m_nomPerso + " -> Passage d'un niveau -> AT / PRD",
                                      "Ce personnage a droit à un point en plus sur les caractéristiques suivantes.\n"
                                      "Choisissez en une !",
                                      At_Prd);
            if (D == "AT")
            {
                QMessageBox::information(this, "Gain d'un point d'AT",
                                         m_nomPerso + " gagne un point d'AT.");
                m_caracInitiales.AT_1();
            }
            else if (D == "PRD")
            {
                QMessageBox::information(this, "Gain d'un point de PRD",
                                         m_nomPerso + " gagne un point de PRD.");
                m_caracInitiales.PRD_1();
            }
        }
        else if (m_caracInitiales.getAT() < 18 && m_caracInitiales.getPRD() == 17)
        {
            QMessageBox::information(this, "Gain d'un point d'AT",
                                     m_nomPerso + " gagne un point d'AT car il passe un niveau !");
            m_caracInitiales.AT_1();
        }
        else if (m_caracInitiales.getAT() == 18 && m_caracInitiales.getPRD() < 17)
        {
            QMessageBox::information(this, "Gain d'un point de PRD",
                                     m_nomPerso + " gagne un point de PRD car il passe un niveau !");
            m_caracInitiales.PRD_1();
        }

        // Test de niveau
        if (m_niveau == 3)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nomPerso + " doit choisir une compétence supplémentaire.");
        }
        else if (m_niveau == 5 && m_metierPersonnage == "Mage / Sorcier")
        {
            QMessageBox::information(this, "Choix d'une spécialisation supplémentaire",
                                     m_nomPerso + " doit choisir une spécialisation supplémentaire");
        }
        else if (m_niveau == 6)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nomPerso + " doit choisir une compétence supplémentaire.");
        }
        else if (m_niveau == 10)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nomPerso + " doit choisir une compétence supplémentaire.");
        }
        else if (m_niveau == 15 && m_metierPersonnage == "Mage / Sorcier")
        {
            QMessageBox::information(this, "Choix d'une spécialisation supplémentaire",
                                     m_nomPerso + " doit choisir une spécialisation supplémentaire");
        }

        log(m_nomPerso + " gagne un niveau.");
    }

    rafraichir();
}
void Personnage::plus_ev()
{
    bool ok(false);

    int EV_EnPlus = QInputDialog::getInteger(labelPourSaut[0],
                                             "Ajouter de l'EV",
                                             "Ajouter de l'énergie vitale à " + m_nomPerso,
                                             1, 1, 999, 1, &ok);

    if (ok && (m_energieVitale_modif + EV_EnPlus) <= m_energieVitale)
        m_energieVitale_modif += EV_EnPlus;
    else if (ok)
        m_energieVitale_modif = m_energieVitale;

    rafraichir();
}
void Personnage::plus_ea()
{
    bool ok(false);

    int EA_EnPlus = QInputDialog::getInteger(labelPourSaut[0],
                                             "Ajouter de l'EA",
                                             "Ajouter de l'énergie astrale à " + m_nomPerso,
                                             1, 1, 999, 1, &ok);

    if (ok && (m_energieAstrale_modif + EA_EnPlus) <= m_energieAstrale)
        m_energieAstrale_modif += EA_EnPlus;
    else if (ok)
        m_energieAstrale_modif = m_energieAstrale;

    rafraichir();
}
void Personnage::plus_po(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int PO_EnPlus = QInputDialog::getInteger(labelPourSaut[0],
                                                 "Ajouter des PO",
                                                 "Ajouter des Pièces d'Or à " + m_nomPerso,
                                                 1, 1, (999999 - m_pieces->getRichesses_Or()), 1, &ok);

        if (ok)
            m_pieces->or_plus(PO_EnPlus);
    }
    else
        m_pieces->or_plus(value);

    rafraichir();
}
void Personnage::plus_pa(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int PA_EnPlus = QInputDialog::getInteger(labelPourSaut[0],
                                                 "Ajouter des PA",
                                                 "Ajouter des Pièces d'Argent à " + m_nomPerso,
                                                 1, 1, (999999 - m_pieces->getRichesses_Argent()), 1, &ok);

        if (ok)
            m_pieces->argent_plus(PA_EnPlus);
    }
    else
        m_pieces->argent_plus(value);

    rafraichir();
}
void Personnage::plus_pc(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int PC_EnPlus = QInputDialog::getInteger(labelPourSaut[0],
                                                 "Ajouter des PC",
                                                 "Ajouter des Pièces de Cuivre à " + m_nomPerso,
                                                 1, 1, (999999 - m_pieces->getRichesses_Cuivre()), 1, &ok);

        if (ok)
            m_pieces->cuivre_plus(PC_EnPlus);
    }
    else
        m_pieces->cuivre_plus(value);

    rafraichir();
}

// Retrait différents de 1
void Personnage::moins_ev()
{
    bool ok(false);

    int EV_Enmoins = QInputDialog::getInteger(labelPourSaut[0],
                                             "Retirer de l'EV",
                                             "Retirer de l'énergie vitale à " + m_nomPerso,
                                             1, 1, 999, 1, &ok);

    if (ok && (m_energieVitale_modif - EV_Enmoins) >= 0)
        m_energieVitale_modif -= EV_Enmoins;
    else if (ok)
        m_energieVitale_modif = 0;

    rafraichir();
}
void Personnage::moins_ea()
{
    bool ok(false);

    int EA_Enmoins = QInputDialog::getInteger(labelPourSaut[0],
                                             "Retirer de l'EA",
                                             "Retirer de l'énergie astrale à " + m_nomPerso,
                                             1, 1, 999, 1, &ok);

    if (ok && (m_energieAstrale_modif - EA_Enmoins) >= 0)
        m_energieAstrale_modif -= EA_Enmoins;
    else if (ok)
        m_energieAstrale_modif = 0;

    rafraichir();
}
void Personnage::moins_po(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int PO_Enmoins = QInputDialog::getInteger(labelPourSaut[0],
                                                 "Retirer des PO",
                                                 "Retirer des Pièces d'Or à " + m_nomPerso,
                                                 1, 1, 999999, 1, &ok);

        if (ok)
            m_pieces->or_moins(PO_Enmoins);
    }
    else
        m_pieces->or_moins(value);

    rafraichir();
}
void Personnage::moins_pa(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int PA_Enmoins = QInputDialog::getInteger(labelPourSaut[0],
                                                 "Retirer des PA",
                                                 "Retirer des Pièces d'Argent à " + m_nomPerso,
                                                 1, 1, 999999, 1, &ok);

        if (ok)
            m_pieces->argent_moins(PA_Enmoins);
    }
    else
        m_pieces->argent_moins(value);

    rafraichir();
}
void Personnage::moins_pc(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int PC_Enmoins = QInputDialog::getInteger(labelPourSaut[0],
                                                 "Retirer des PC",
                                                 "Retirer des Pièces de Cuivre à " + m_nomPerso,
                                                 1, 1, 999999, 1, &ok);

        if (ok)
            m_pieces->cuivre_moins(PC_Enmoins);
    }
    else
        m_pieces->cuivre_moins(value);

    rafraichir();
}

// Ajout de 1
void Personnage::moins_destin()
{
    m_pointsDestin--;

    log(m_nomPerso + " pert un point de destin !");

    rafraichir();
}
void Personnage::plus_cou()
{
    m_caracModifiees.COU_1();

    rafraichir();
}
void Personnage::plus_int()
{
    m_caracModifiees.INT_1();

    rafraichir();
}
void Personnage::plus_cha()
{
    m_caracModifiees.CHA_1();

    rafraichir();
}
void Personnage::plus_ad()
{
    m_caracModifiees.AD_1();

    rafraichir();
}
void Personnage::plus_fo()
{
    m_caracModifiees.FO_1();

    rafraichir();
}
void Personnage::plus_at()
{
    m_caracModifiees.AT_1();

    rafraichir();
}
void Personnage::plus_prd()
{
    m_caracModifiees.PRD_1();

    rafraichir();
}

// Retrait de 1
void Personnage::moins_cou()
{
    m_caracModifiees.COU_1(false);

    rafraichir();
}
void Personnage::moins_int()
{
    m_caracModifiees.INT_1(false);

    rafraichir();
}
void Personnage::moins_cha()
{
    m_caracModifiees.CHA_1(false);

    rafraichir();
}
void Personnage::moins_ad()
{
    m_caracModifiees.AD_1(false);

    rafraichir();
}
void Personnage::moins_fo()
{
    m_caracModifiees.FO_1(false);

    rafraichir();
}
void Personnage::moins_at()
{
    m_caracModifiees.AT_1(false);

    rafraichir();
}
void Personnage::moins_prd()
{
    m_caracModifiees.PRD_1(false);

    rafraichir();
}


// Attaque
void Personnage::attaquer()
{
    QStringList nomArmes;
    for (int i(0); i < MAX_ARME; i++)
        nomArmes.push_back(m_armes[i]->getNom());
    bool ok(false);

    QString nom_arme = QInputDialog::getItem(this, m_nomPerso + " -> Attaque",
                                             "Avec quelle arme ce personnage souhaite-t-il attaquer ?",
                                             nomArmes, 0, false, &ok);

    if (!ok)
        return;

    int i(0);
    bool attaqueFaite(false);
    while (!attaqueFaite)
    {
        // On teste si c'est l'arme choisi est celle correspondant à i
        if (nom_arme == m_armes[i]->getNom())
        {
            // Valeur de D20 pour savoir s'il peut attaquer
            int vingt = QInputDialog::getInt(this, m_nomPerso + " -> Attaque -> Test au D20",
                                             "Lancez et rentrez la valeur du D20 :",
                                             1, 1, 20, 1, &ok);

            // Echec critique
            if (ok && (vingt == 19 || vingt == 20))
            {
                QMessageBox::information(this, m_nomPerso + " -> Attaque -> Echec critique",
                                         "Ce personnage a fait un échec critique en essayant d'attaquer.");
                log(m_nomPerso + " fait un échec critique.");
            }
            // Coup critique
            if (ok && (vingt == 1 || vingt == 2))
            {
                QMessageBox::information(this, m_nomPerso + " -> Attaque -> Coup critique",
                                         "Ce personnage a fait un coup critique en attaquant.");
                log(m_nomPerso + " fait un coup critique.");
            }
            // Attaque
            if (ok && (vingt < m_caracModifiees.getAT()))
            {
                // Erreur si les dés sont à 0
                if (m_armes[i]->des() == 0)
                {
                    QMessageBox::information(this, m_nomPerso + " -> Attaque -> Impossible",
                                             "L'arme choisie a un nombre de dés égal à 0.\nElle ne sert à rien");
                    return;
                }

                // On continu
                int i2(1), totalDegats(m_armes[i]->degats());
                while (i2 <= m_armes[i]->des()) // On demande les résultats des dés
                {
                    totalDegats += QInputDialog::getInt(this, m_nomPerso + " -> Attaque -> Dégâts",
                                                        "Rentrez le score indiqué par le D6 :", 1, 1, 6, 1);
                    i2++;
                }

                // Si "à mains nues" => message
                if (m_armes[i]->getNom() == PAS_ARME)
                {
                    QMessageBox::information(this, m_nomPerso + " -> Attaque -> Récapitulatif",
                                             "Ce personnage attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                             "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué !");
                    log(m_nomPerso + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.");
                }
                // Si arme => message
                else
                {
                    QMessageBox::information(this, m_nomPerso + " -> Attaque -> Récapitulatif",
                                             "Ce personnage attaque avec son/sa " + m_armes[i]->getNom() + " et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                             "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué !");
                    log(m_nomPerso + " attaque avec son/sa " + m_armes[i]->getNom() + " et fait " + QString::number(totalDegats) + " de dégâts.");
                }
            }
            // Attaque pas
            if (ok && vingt > m_caracModifiees.getAT() && vingt != 19 && vingt != 20)
            {
                QMessageBox::information(this, m_nomPerso + " -> Attaque -> Impossible",
                                         "Ce personnage ne peut pas attaquer.");
                log(m_nomPerso + " essaye d'attaquer, mais se rate royalement son attaque.");
            }

            // On dit au while que l'attaque a été faite
            attaqueFaite = true;
        }
        // On dit au while que l'attaque a été faite
        if (i >= MAX_ARME)
            attaqueFaite = true;

        i++;
    }
}
