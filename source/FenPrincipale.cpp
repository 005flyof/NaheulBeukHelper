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

#include "FenPrincipale.h"
#include <QtGui>

#define NOTES_BASE "Vos notes par rapport à ce que l'on pert dans le programme une fois sur l'autre !\n\n" \
                   "Comme les maladies, etc...\n\n" \
                   "	------------\n\n" \
                   "Merci d'utiliser ce programme !\n\n" \
                   "	------------\n\n" \
                   "Pour commencer :\n" \
                      "* créer un groupe\n" \
                      "* créer / ajouter un personnage au groupe créé\n" \
                      "* ouvrir le groupe\n" \
                      "* enjoy the features of this program !!!\n\n" \
                   "	------------\n\n" \
                   "Vous utilisez la version " VERSION " de ce programme.\n" \
                   "Ce programme est développé en C++ avec QtCreator, par Florent Fayollas.\n"

using namespace std;

// Fenêtre principale
FenPrincipale::FenPrincipale() : QMainWindow(), compteurOnglets(0)
{
// On s'occupe de la fenêtre
    setWindowTitle("NBH     --     NaheulBeuk Helper");
    setIcone(this);
    setMinimumSize(910, 540);

// Création de la statusBar
    statusBar = new QStatusBar();
    statusBar->addWidget(new QLabel("Prêt"));
    setStatusBar(statusBar);

// Initialisation diverses
    initMenus_ToolBars();
    initWidget();

// Initialisation des options
    QSettings *settings = new QSettings("config.ini", QSettings::IniFormat, this);

    if (!settings->value("FenPrincipale/geometry").isNull())
        restoreGeometry(settings->value("FenPrincipale/geometry").toByteArray());

    if (!settings->value("FenPrincipale/windowState").isNull())
        restoreState(settings->value("FenPrincipale/windowState").toByteArray());

    if (!settings->value("FenPrincipale/toolBar/Fichier").isNull())
        afficher_fichier->setChecked(settings->value("FenPrincipale/toolBar/Fichier").toBool());

    if (!settings->value("FenPrincipale/toolBar/Action").isNull())
        afficher_action->setChecked(settings->value("FenPrincipale/toolBar/Action").toBool());

    if (!settings->value("FenPrincipale/toolBar/Achat").isNull())
        afficher_achat->setChecked(settings->value("FenPrincipale/toolBar/Achat").toBool());
}
void FenPrincipale::initMenus_ToolBars()
{
    QMenuBar *barreDeMenu = new QMenuBar(this);

// Menu : Fichier
    QMenu *fichier = barreDeMenu->addMenu("&Fichier");

    QAction *nouveauPerso = fichier->addAction("Créer un personnage de niveau  1");
        nouveauPerso->setShortcut(QKeySequence("Ctrl+N"));
        nouveauPerso->setIcon(QIcon(":prog-data/img/new.png"));
        nouveauPerso->setStatusTip("Créer un personnage de niveau puis l'ajouter à un groupe de personnage créé auparavant.");
    QAction *nouveauGroupe = fichier->addAction("Créer un groupe de personnage");
        nouveauGroupe->setIcon(QIcon(":prog-data/img/new-group.png"));
        nouveauGroupe->setStatusTip("Créer un groupe de personnage.");
    fichier->addSeparator();

    QAction *ajouterPerso = fichier->addAction("Ajouter un personnage");
        ajouterPerso->setShortcut(QKeySequence("Ctrl+Shift+N"));
        ajouterPerso->setIcon(QIcon(":prog-data/img/add.png"));
        ajouterPerso->setStatusTip("Ajouter un personnage que vous aviez créé auparavant.");
    fichier->addSeparator();

    QAction *ouvrirPersos = fichier->addAction("Ouvrir un groupe de personnages déjà créés");
        ouvrirPersos->setShortcut(QKeySequence("Ctrl+O"));
        ouvrirPersos->setIcon(QIcon(":prog-data/img/open.png"));
        ouvrirPersos->setStatusTip("Ouvrir un groupe de personnage");
    enregistrer = fichier->addAction("Enregistrer les modifications apportées au groupe");
        enregistrer->setShortcut(QKeySequence("Ctrl+S"));
        enregistrer->setIcon(QIcon(":prog-data/img/save.png"));
        enregistrer->setStatusTip("Forcer l'enregistrement des personnages du groupe ouvert.");
        enregistrer->setEnabled(false);
    fichier->addSeparator();

    quitterGroupe = fichier->addAction("Fermer le groupe");
        quitterGroupe->setStatusTip("Fermer le groupe de personnage actuellement ouvert.");
        quitterGroupe->setIcon(QIcon(":prog-data/img/quit-group.png"));
        quitterGroupe->setEnabled(false);
    fichier->addSeparator();

    QAction *quitter = fichier->addAction("Quitter");
        quitter->setShortcut(QKeySequence("Ctrl+Q"));
        quitter->setIcon(QIcon(":prog-data/img/quit.png"));
        quitter->setStatusTip("Quitter ce programme...");


// Menu : Action
    QMenu *mode = barreDeMenu->addMenu("&Mode");

    attaque = mode->addAction("Attaque");
        attaque->setShortcut(QKeySequence("Ctrl+A"));
        attaque->setStatusTip("Passer en mode \"Attaque\"");
        attaque->setIcon(QIcon(":prog-data/img/attaque.png"));
        attaque->setCheckable(true);
        attaque->setChecked(false);
        attaque->setEnabled(false);
    passif = mode->addAction("Passif");
        passif->setShortcut(QKeySequence("Ctrl+P"));
        passif->setStatusTip("Passer en mode \"Passif\"");
        passif->setIcon(QIcon(":prog-data/img/passif.png"));
        passif->setCheckable(true);
        passif->setChecked(true);
        passif->setEnabled(false);


// Menu : Groupe
    QMenu *groupe = barreDeMenu->addMenu("Modification sur le &groupe");

    xpGroupe = groupe->addAction("XP de groupe");
        xpGroupe->setIcon(QIcon(":prog-data/img/XP.png"));
        xpGroupe->setStatusTip("Ajouter de l'expérience au groupe entier.");
        xpGroupe->setEnabled(false);
    groupe->addSeparator();

    POGroupe = groupe->addAction("Ajout PO en groupe");
        POGroupe->setIcon(QIcon(":prog-data/img/PO+.png"));
        POGroupe->setStatusTip("Ajouter des Pièces d'Or à chacun des personnages du groupe.");
        POGroupe->setEnabled(false);
    PAGroupe = groupe->addAction("Ajout PA en groupe");
        PAGroupe->setIcon(QIcon(":prog-data/img/PA+.png"));
        PAGroupe->setStatusTip("Ajouter des Pièces d'Argent à chacun des personnages du groupe.");
        PAGroupe->setEnabled(false);
    PCGroupe = groupe->addAction("Ajout PC en groupe");
        PCGroupe->setIcon(QIcon(":prog-data/img/PC+.png"));
        PCGroupe->setStatusTip("Ajouter des Pièces de Cuivre à chacun des personnages du groupe.");
        PCGroupe->setEnabled(false);
    groupe->addSeparator();

    poGroupe = groupe->addAction("Retrait PO en groupe");
        poGroupe->setIcon(QIcon(":prog-data/img/PO-.png"));
        poGroupe->setStatusTip("Retirer des Pièces d'Or à chacun des personnages du groupe.");
        poGroupe->setEnabled(false);
    paGroupe = groupe->addAction("Retrait PA en groupe");
        paGroupe->setIcon(QIcon(":prog-data/img/PA-.png"));
        paGroupe->setStatusTip("Retirer des Pièces d'Argent à chacun des personnages du groupe.");
        paGroupe->setEnabled(false);
    pcGroupe = groupe->addAction("Retrait PC en groupe");
        pcGroupe->setIcon(QIcon(":prog-data/img/PC-.png"));
        pcGroupe->setStatusTip("Retirer des Pièces de Cuivre à chacun des personnages du groupe.");
        pcGroupe->setEnabled(false);

// Menu : Perso en cours
    QMenu *perso = barreDeMenu->addMenu("Personnage en cours");

    achatATPRD = perso->addAction("Achat de point d'AT / PRD");
        achatATPRD->setIcon(QIcon(":prog-data/img/at_prd+.png"));
        achatATPRD->setStatusTip("Achat d'un point d'AT ou de PRD (500 PO -> 1 mois de stage)");
        achatATPRD->setEnabled(false);
    achatINT = perso->addAction("Achat de point d'INT");
        achatINT->setIcon(QIcon(":prog-data/img/int+.png"));
        achatINT->setStatusTip("Achat d'un point d'INT (500 PO -> 6 mois de stage)");
        achatINT->setEnabled(false);
    achatCHA = perso->addAction("Achat de point de CHA");
        achatCHA->setIcon(QIcon(":prog-data/img/cha+.png"));
        achatCHA->setStatusTip("Achat d'un point de CHA (400 PO -> 1 semaine maximum un par mois !)");
        achatCHA->setEnabled(false);
    achatFO = perso->addAction("Achat de point de FO");
        achatFO->setIcon(QIcon(":prog-data/img/fo+.png"));
        achatFO->setStatusTip("Achat d'un point de FO (400 PO -> 6 mois de stage)");
        achatFO->setEnabled(false);
    achatCOU = perso->addAction("Achat de point de COU");
        achatCOU->setIcon(QIcon(":prog-data/img/cou+.png"));
        achatCOU->setStatusTip("Achat d'un point de COU (400 PO -> 1 mois de stage)");
        achatCOU->setEnabled(false);
    perso->addSeparator();

    achatEV = perso->addAction("Achat de point d'EV");
        achatEV->setIcon(QIcon(":prog-data/img/ev+.png"));
        achatEV->setStatusTip("Achat d'un point d'EV (200 PO -> 2 semaines de stage)");
        achatEV->setEnabled(false);
    achatEA = perso->addAction("Achat de point d'EA");
        achatEA->setIcon(QIcon(":prog-data/img/ea+.png"));
        achatEA->setStatusTip("Achat d'un point d'EA (200 PO -> 1 mois de stage)");
        achatEA->setEnabled(false);


// Menu : Affichage
    QMenu *affichage = barreDeMenu->addMenu("&Affichage");
        QMenu *affichage_barreOutils = affichage->addMenu("Barre d'outils");

        afficher_fichier = affichage_barreOutils->addAction("Fichier");
            afficher_fichier->setEnabled(true);
            afficher_fichier->setCheckable(true);
            afficher_fichier->setChecked(true);
        afficher_action = affichage_barreOutils->addAction("Actions");
            afficher_action->setEnabled(true);
            afficher_action->setCheckable(true);
            afficher_action->setChecked(true);
        afficher_achat = affichage_barreOutils->addAction("Achat");
            afficher_achat->setEnabled(true);
            afficher_achat->setCheckable(true);
            afficher_achat->setChecked(true);


// Menu : ?
    QMenu *question = barreDeMenu->addMenu("&?");

    QAction *aPropos = question->addAction("A propos...");
        aPropos->setIcon(QIcon(":/prog-data/img/icone.png"));
    QAction *aProposDeQt = question->addAction("A propos de Qt");
        aProposDeQt->setIcon(QIcon(":prog-data/img/about-Qt.png"));
    QAction *licence = question->addAction("Licence");
        licence->setIcon(QIcon(":prog-data/img/licence.png"));
    question->addSeparator();

    QAction *maj = question->addAction("Mise à jour");
        maj->setIcon(QIcon(":prog-data/img/maj.png"));
    question->addSeparator();

    QAction *aide = question->addAction("Aide");
        aide->setShortcut(QKeySequence("F1"));
        aide->setIcon(QIcon(":prog-data/img/help.png"));

    // Ajout de la barre des menus à la fenêtre
    setMenuBar(barreDeMenu);


// Création des connexion
    QObject::connect(nouveauPerso, SIGNAL(triggered()), this, SLOT(creerNouveauPersonnage()));
    QObject::connect(nouveauGroupe, SIGNAL(triggered()), this, SLOT(creerNouveauGroupe()));
    QObject::connect(ajouterPerso, SIGNAL(triggered()), this, SLOT(ajouterPersonnage()));
    QObject::connect(ouvrirPersos, SIGNAL(triggered()), this, SLOT(ouvrir()));
    QObject::connect(enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerTout()));
    QObject::connect(quitterGroupe, SIGNAL(triggered()), this, SLOT(fermerGroupe()));
    QObject::connect(quitter, SIGNAL(triggered()), this, SLOT(quitterNBH()));

    QObject::connect(attaque, SIGNAL(triggered()), this, SLOT(modeAttaque()));
    QObject::connect(passif, SIGNAL(triggered()), this, SLOT(modePassif()));

    QObject::connect(xpGroupe, SIGNAL(triggered()), this, SLOT(xp()));
    QObject::connect(POGroupe, SIGNAL(triggered()), this, SLOT(PO()));
    QObject::connect(PAGroupe, SIGNAL(triggered()), this, SLOT(PA()));
    QObject::connect(PCGroupe, SIGNAL(triggered()), this, SLOT(PC()));
    QObject::connect(poGroupe, SIGNAL(triggered()), this, SLOT(po()));
    QObject::connect(paGroupe, SIGNAL(triggered()), this, SLOT(pa()));
    QObject::connect(pcGroupe, SIGNAL(triggered()), this, SLOT(pc()));

    QObject::connect(achatATPRD, SIGNAL(triggered()), this, SLOT(ATPRD()));
    QObject::connect(achatINT, SIGNAL(triggered()), this, SLOT(INT()));
    QObject::connect(achatCHA, SIGNAL(triggered()), this, SLOT(CHA()));
    QObject::connect(achatFO, SIGNAL(triggered()), this, SLOT(FO()));
    QObject::connect(achatCOU, SIGNAL(triggered()), this, SLOT(COU()));
    QObject::connect(achatEV, SIGNAL(triggered()), this, SLOT(EV()));
    QObject::connect(achatEA, SIGNAL(triggered()), this, SLOT(EA()));

    QObject::connect(afficher_fichier, SIGNAL(toggled(bool)), this, SLOT(afficherFichier(bool)));
    QObject::connect(afficher_action, SIGNAL(toggled(bool)), this, SLOT(afficherAction(bool)));
    QObject::connect(afficher_achat, SIGNAL(toggled(bool)), this, SLOT(afficherAchat(bool)));

    QObject::connect(aPropos, SIGNAL(triggered()), this, SLOT(aProposDeNBH()));
    QObject::connect(aProposDeQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(licence, SIGNAL(triggered()), this, SLOT(licence()));
    QObject::connect(maj, SIGNAL(triggered()), this, SLOT(MAJ()));
    QObject::connect(aide, SIGNAL(triggered()), this, SLOT(help()));

// ToolBars
    fichierToolBar = addToolBar("Barre d'outils de fichier");
        fichierToolBar->setObjectName("toolBar-Fichier");

        fichierToolBar->addAction(nouveauPerso);
        fichierToolBar->addAction(nouveauGroupe);
        fichierToolBar->addSeparator();

        fichierToolBar->addAction(ajouterPerso);
        fichierToolBar->addSeparator();

        fichierToolBar->addAction(ouvrirPersos);
        fichierToolBar->addAction(enregistrer);
        fichierToolBar->addSeparator();

        fichierToolBar->addAction(quitterGroupe);
        fichierToolBar->addSeparator();

        fichierToolBar->addAction(quitter);


    actionsToolBar = addToolBar("Barre d'outils d'Actions");
        actionsToolBar->setObjectName("toolBar-Actions");

        actionsToolBar->addAction(attaque);
        actionsToolBar->addAction(passif);
        actionsToolBar->addSeparator();

        actionsToolBar->addAction(xpGroupe);
        actionsToolBar->addSeparator();

        actionsToolBar->addAction(POGroupe);
        actionsToolBar->addAction(PAGroupe);
        actionsToolBar->addAction(PCGroupe);
        actionsToolBar->addSeparator();

        actionsToolBar->addAction(poGroupe);
        actionsToolBar->addAction(paGroupe);
        actionsToolBar->addAction(pcGroupe);


    achatToolBar = addToolBar("Barre d'outils d'Achat de puissance");
        achatToolBar->setObjectName("toolBar-Achat");

        achatToolBar->addAction(achatATPRD);
        achatToolBar->addAction(achatINT);
        achatToolBar->addAction(achatCHA);
        achatToolBar->addAction(achatFO);
        achatToolBar->addAction(achatCOU);
        achatToolBar->addSeparator();

        achatToolBar->addAction(achatEV);
        achatToolBar->addAction(achatEA);
}
void FenPrincipale::initWidget()
{
// Création du widget central
    zoneCentrale = new QMdiArea(this);
    zoneCentrale->setViewMode(QMdiArea::TabbedView);
    zoneCentrale->setTabsMovable(true); // pour Qt 4.8 et sup

    // On valide le widget "zoneCentrale"
    setCentralWidget(zoneCentrale);


// Création du widget pour les notes
    QDockWidget *notes = new QDockWidget("Notes :");
    notes->setFeatures(QDockWidget::NoDockWidgetFeatures);
    notes->setObjectName("dock-notes");

    notes_txt = new QTextEdit();
    notes_txt->setPlainText(NOTES_BASE);
    notes_txt->setEnabled(false);
    notes_txt->setUndoRedoEnabled(true);

    // On ajoute le widget au Dock
    notes->setWidget(notes_txt);
    notes->setMinimumWidth(170);
    notes->setMaximumWidth(250);
    addDockWidget(Qt::LeftDockWidgetArea, notes);


// Création du widget pour les monstres
//    QDockWidget *monstres_dock = new QDockWidget("Monstres :");
//    monstres_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
//    monstres_dock->setObjectName("dock-monstres");

//    monstres = new QTabWidget();
//    monstres_dock->setWidget(monstres);
//    monstres_dock->setMinimumWidth(130);
//    monstres_dock->setMaximumWidth(180);

//    addDockWidget(Qt::RightDockWidgetArea, monstres_dock);

//    Monstre *fenetre = new Monstre("Mendiant 1", 5, 5, 5, 15, 1, 0, 2, 5, "Combat à mains nues");
//    monstres->addTab(fenetre->afficher(), fenetre->nom());


// Création du widget pour l'ordre de marche
    QDockWidget *ordreMarche_dock = new QDockWidget("Ordre de marche :");
    ordreMarche_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    ordreMarche_dock->setObjectName("dock-marche");

    QStringList listeNomVide("Pas de groupe\nde personnages\nouverts");
    ordreMarche = new FenOrdreMarche(listeNomVide);
    ordreMarche->setEnabled(false);
    ordreMarche_dock->setWidget(ordreMarche);
    ordreMarche_dock->setMinimumWidth(130);
    ordreMarche_dock->setMaximumWidth(180);

    addDockWidget(Qt::RightDockWidgetArea, ordreMarche_dock);


// Création du widget de gestion des attaques
    attaque_dock = new QDockWidget("Gestion des attaques :");
    attaque_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    attaque_dock->setObjectName("attack-dock");

    attaque_fen = new FenAttaque(listeNomVide);
    attaque_fen->setEnabled(false);
        QObject::connect(attaque_fen, SIGNAL(attaque()), this, SLOT(attaquer()));
    attaque_dock->setWidget(attaque_fen);
    attaque_dock->setMinimumWidth(130);
    attaque_dock->setMaximumWidth(180);

    addDockWidget(Qt::RightDockWidgetArea, attaque_dock);
//        passif->setChecked(false);
//        attaque->setChecked(true);
}

FenPrincipale::~FenPrincipale()
{}

// Fenêtre de création des personnages
void FenPrincipale::creerNouveauPersonnage()
{
    progressBar_status = new QProgressBar();
    statusBar->addWidget(progressBar_status);

    int lecteur_spacer(0);
    for (int i = 0; i < NB_SPACER_FENPRINCIPALE; i++)
        spacer[i] = new QSpacerItem(30, 10);

    nouveau_fenetre = new QDialog(this, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    nouveau_fenetre->setWindowTitle("Créer un personnage -> informations génériques");
    nouveau_fenetre->setModal(true);
    setIcone(nouveau_fenetre);

// On rempli la fenêtre
    nouveau_nom = new QLineEdit;
    nouveau_sexe = new QLineEdit;

    nouveau_ptsDestin = new QSpinBox;
        nouveau_ptsDestin->setMinimum(0);
        nouveau_ptsDestin->setMaximum(3);
        nouveau_ptsDestin->setSingleStep(1);

    nouveau_PO = new QSpinBox;
        nouveau_PO->setMinimum(20);
        nouveau_PO->setMaximum(120);
        nouveau_PO->setSingleStep(10);

    nouveau_COU = new QSpinBox;
        nouveau_COU->setMinimum(8);
        nouveau_COU->setMaximum(13);
        nouveau_COU->setSingleStep(1);
    nouveau_INT = new QSpinBox;
        nouveau_INT->setMinimum(8);
        nouveau_INT->setMaximum(13);
        nouveau_INT->setSingleStep(1);
    nouveau_CHA = new QSpinBox;
        nouveau_CHA->setMinimum(8);
        nouveau_CHA->setMaximum(13);
        nouveau_CHA->setSingleStep(1);
    nouveau_AD = new QSpinBox;
        nouveau_AD->setMinimum(8);
        nouveau_AD->setMaximum(13);
        nouveau_AD->setSingleStep(1);
    nouveau_FO = new QSpinBox;
        nouveau_FO->setMinimum(8);
        nouveau_FO->setMaximum(13);
        nouveau_FO->setSingleStep(1);

    QFormLayout *nouveau_layout1 = new QFormLayout();
        nouveau_layout1->addRow("Nom du personnage :", nouveau_nom);
        nouveau_layout1->addRow("Sexe :", nouveau_sexe);
        nouveau_layout1->addItem(spacer[lecteur_spacer]);
        lecteur_spacer++;

        nouveau_layout1->addRow("Points de destin :\n"
                               "(1D4 - 1)", nouveau_ptsDestin);
        nouveau_layout1->addItem(spacer[lecteur_spacer]);
        lecteur_spacer++;

        nouveau_layout1->addRow("PO (pièces d'or) :\n"
                               "(2D6 x 10)", nouveau_PO);
        nouveau_layout1->addItem(spacer[lecteur_spacer]);
        lecteur_spacer++;

    QFormLayout *nouveau_layout2 = new QFormLayout();
        nouveau_layout2->addRow("COU (courage) :\n"
                               "(1D6 + 7)", nouveau_COU);
        nouveau_layout2->addRow("INT (intelligence) :\n"
                               "(1D6 + 7)", nouveau_INT);
        nouveau_layout2->addRow("CHA (charisme) :\n"
                               "(1D6 + 7)", nouveau_CHA);
        nouveau_layout2->addRow("AD (adresse) :\n"
                               "(1D6 + 7)", nouveau_AD);
        nouveau_layout2->addRow("FO (force) :\n"
                               "(1D6 + 7)", nouveau_FO);
        nouveau_layout2->addItem(spacer[lecteur_spacer]);
        lecteur_spacer++;

    QHBoxLayout *nouveau_layout_sansBox = new QHBoxLayout();
        nouveau_layout_sansBox->addLayout(nouveau_layout1);
        nouveau_layout_sansBox->addItem(spacer[lecteur_spacer]);
        lecteur_spacer++;
        nouveau_layout_sansBox->addLayout(nouveau_layout2);

    QVBoxLayout *nouveau_layout_total = new QVBoxLayout();
        nouveau_layout_total->addLayout(nouveau_layout_sansBox);

        QDialogButtonBox *nouveau_boutonsBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            QObject::connect(nouveau_boutonsBox, SIGNAL(accepted()), this, SLOT(creerNouveauPersonnage_Origine()));
            QObject::connect(nouveau_boutonsBox, SIGNAL(rejected()), this, SLOT(creerNouveauPersonnage_close()));

        nouveau_layout_total->addWidget(nouveau_boutonsBox);

// On ajoute les pages
    nouveau_fenetre->setLayout(nouveau_layout_total);
    nouveau_fenetre->show();
}
void FenPrincipale::creerNouveauPersonnage_close()
{
    nouveau_fenetre->close();

    statusBar->removeWidget(progressBar_status);
    delete progressBar_status;
    progressBar_status = 0;
}
void FenPrincipale::creerNouveauPersonnage_Origine()
{
    progressBar_status->setValue(20);

    QVBoxLayout *layout_vertical = new QVBoxLayout();
    QHBoxLayout *layout = new QHBoxLayout();
        QLabel *explication = new QLabel("Voici les origines que vous pouvez utiliser :");
        layout_vertical->addWidget(explication);

    int totalOrigine = 0;
// On crée le personnage !
    tableauDePersonnages[nouveau_nom->text()] = Personnage(nouveau_nom->text(), nouveau_sexe->text(),
                                                           "Origine à définir !", "Métier à définr",
                                                           nouveau_COU->value(), nouveau_INT->value(), nouveau_CHA->value(),
                                                           nouveau_AD->value(), nouveau_FO->value(), 8, 10,
                                                           nouveau_COU->value(), nouveau_INT->value(), nouveau_CHA->value(),
                                                           nouveau_AD->value(), nouveau_FO->value(), 8, 10,
                                                           nouveau_ptsDestin->value(), 0,
                                                           0, nouveau_PO->value(), 0, 0);

// On affiche la fenêtre proposant les origines possibles
    nouveau_fenetre2 = new QDialog(this, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    nouveau_fenetre2->setWindowTitle("Créer un personnage -> choix de l'origine");
    nouveau_fenetre2->setModal(true);
    setIcone(nouveau_fenetre2);

    layout_vertical->addLayout(layout);

    QDialogButtonBox *nouveau_boutonsBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        QObject::connect(nouveau_boutonsBox, SIGNAL(accepted()), this, SLOT(creerNouveauPersonnage_Metier()));
        QObject::connect(nouveau_boutonsBox, SIGNAL(rejected()), this, SLOT(creerNouveauPersonnage_Origine_close()));

    layout_vertical->addWidget(nouveau_boutonsBox);

    nouveau_fenetre2->setLayout(layout_vertical);
    nouveau_fenetre2->show();
}
void FenPrincipale::creerNouveauPersonnage_Origine_close()
{
    progressBar_status->setValue(0);

    nouveau_fenetre2->close();
    tableauDOrigines.clear();
    tableauDeRadioButton_Origine.clear();
}
void FenPrincipale::creerNouveauPersonnage_Metier()
{
    progressBar_status->setValue(40);

    QVBoxLayout *layout_vertical = new QVBoxLayout();
    QHBoxLayout *layout = new QHBoxLayout();
        QLabel *explication = new QLabel("Voici les métiers que vous pouvez choisir :");
        layout_vertical->addWidget(explication);

    int totalMetiers = 0;

// Test de la capacité du personnage à faire ce métier
    ///////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < tableauDeMetiers.size(); i++)
    {
        bool possible = tableauDePersonnages[nouveau_nom->text()].testMetier(tableauDeMetiers.at(i));

        if (possible)
        {
            QRadioButton *temp = new QRadioButton(tableauDeMetiers.at(i)->getNom());
            tableauDeRadioButton_Metier.push_back(temp);

            QVector<QRadioButton>::iterator it = tableauDeRadioButton_Metier.at(totalMetiers);
            layout->addWidget(&*it);
            totalMetiers++;
        }
    }

// On affiche la fenêtre proposant les métiers possibles
    nouveau_fenetre3 = new QDialog(this, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    nouveau_fenetre3->setWindowTitle("Créer un personnage -> choix du métier");
    nouveau_fenetre3->setModal(true);
    setIcone(nouveau_fenetre3);

    layout_vertical->addLayout(layout);

    QDialogButtonBox *nouveau_boutonsBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        QObject::connect(nouveau_boutonsBox, SIGNAL(accepted()), this, SLOT(creerNouveauPersonnage_Set()));
        QObject::connect(nouveau_boutonsBox, SIGNAL(rejected()), this, SLOT(creerNouveauPersonnage_Metier_close()));

    layout_vertical->addWidget(nouveau_boutonsBox);

    nouveau_fenetre3->setLayout(layout_vertical);
    nouveau_fenetre3->show();
}
void FenPrincipale::creerNouveauPersonnage_Metier_close()
{
    progressBar_status->setValue(20);

    nouveau_fenetre3->close();
    tableauDeMetiers.clear();
    tableauDeRadioButton_Metier.clear();
}
void FenPrincipale::creerNouveauPersonnage_Set()
{
    progressBar_status->setValue(60);

    for (int i = 0; i < tableauDeRadioButton_Origine.size(); i++)
    {
        if (tableauDeRadioButton_Origine[i]->isChecked())
        {
        // On capte le nom du métier
            QString nomOrigine = tableauDeRadioButton_Origine[i]->text();
        // On crée un iterator sur le métier
            QMap<QString, Origine*>::iterator it = tableauDOrigines.find(nomOrigine);
        // On valide le métier
            tableauDePersonnages[nouveau_nom->text()].setOrigine(*it);
        }
    }
    for (int i = 0; i < tableauDeRadioButton_Metier.size(); i++)
    {
        if (tableauDeRadioButton_Metier[i]->isChecked())
        {
        // On capte le nom du métier
            QString nomMetier = tableauDeRadioButton_Metier[i]->text();
        // On valide le métier
            for (int i = 0; i < tableauDeMetiers.size(); i++)
                if (tableauDeMetiers.at(i)->getNom() == nomMetier)
                    tableauDePersonnages[nouveau_nom->text()].setMetier(*it);
        }
    }

// On demande où l'enregistrer et on ouvre le fichier
    QString cheminPerso = QFileDialog::getSaveFileName(zoneCentrale, "Enregistrer un personnage",
                                                       QString("enregistrements"), "Personnages (*.perso)");

    if (cheminPerso.isEmpty())
    {
        QMap<QString, Personnage>::Iterator iterateurPerso = tableauDePersonnages.find(nouveau_nom->text());
        tableauDePersonnages.erase(iterateurPerso);

        return;
    }

    // On modifie le chemin de l'application si win32
    if (OS == 0)
        cheminPerso.replace("/", "\\");

    bool ouvert = testOuverture(cheminPerso);
    if (ouvert)
    {
        QMessageBox::critical(this, "Erreur",
                              "ERREUR :\nVous essayez d'enregistrer le nouveau personnage "
                              "sur un autre déjà créé et ouvert !");

        QMessageBox *msgBox1 = new QMessageBox(QMessageBox::Information, "Information",
                                               "Si vous voulez recréer ce personnage,"
                                               "il va falloir re-rentrer toutes les caractéristiques de celui-ci !\n\n"
                                               "C'est votre punition !");
            merci = msgBox1->addButton("Oh non !", QMessageBox::AcceptRole);
            setIcone(msgBox1);
            msgBox1->exec();

        QMessageBox *msgBox2 = new QMessageBox(QMessageBox::Information, "Information",
                                               "Alors, vous enragez ?\n\n"
                                               "Eh ben, vous avez de la chance, je suis de bonne humeur aujourd'hui !\n"
                                               "En conséquent, vous n'aurez pas besoin de re-remplir ce formulaire !\n\n"
                                               "Qu'est-ce qu'on dit ?");
            ohNon = msgBox2->addButton("Merci !", QMessageBox::AcceptRole);
            setIcone(msgBox2);
            msgBox2->exec();

        QMap<QString, Personnage>::Iterator iterateurPerso = tableauDePersonnages.find(nouveau_nom->text());
        tableauDePersonnages.erase(iterateurPerso);

        return;
    }
    // On dit au prog que ce perso est ouvert
    nomPersoOuverts << nouveau_nom->text();

    QFile persoRec(cheminPerso);
    if (!persoRec.open(QIODevice::WriteOnly | QIODevice::Text))
        fatalError("Impossible de créer le fichier personnage sélectionné. C'est une erreur impossible normalement. Réessayez d'ajouter le personnage.");

    log("Enregistrement du personnage créé précédemment.");
    QTextStream sortie(&persoRec);
    sortie << tableauDePersonnages[nouveau_nom->text()].getPersoEntier();

    tableauDePersonnages[nouveau_nom->text()].setAdresse(cheminPerso);

    progressBar_status->setValue(80);

// On ajoute le fichier personnage au groupe
    bool erreur(false);
    QString cheminGroupe;
    while (!erreur)
    {
        cheminGroupe = QFileDialog::getOpenFileName(zoneCentrale, "Modifier un groupe",
                                                    QString("enregistrements"), "Groupes de personnages (*.nbh)");

        if (cheminGroupe.isEmpty())
            QMessageBox::critical(zoneCentrale, "ERREUR !", "Erreur :\nVous devez choisir un groupe à modifier !");
        else
            erreur = true;
    }

    if (OS == 0)
        cheminGroupe.replace("/", "\\");
    QFile groupeRec(cheminGroupe);
    if (!groupeRec.open(QIODevice::Append | QIODevice::Text))
        fatalError("Impossible d'ouvrir le fichier de groupe sélectionné. C'est une erreur impossible normalement. Réessayez de créer le personnage.");

    log("Ajout du personnage à un groupe !");

    QTextStream groupe(&groupeRec);

    QString cheminApp = QCoreApplication::applicationDirPath();
    cheminApp.remove("/debug");
    cheminApp.remove("/release");
    if (OS == 0)
        cheminApp.replace("/", "\\");
    cheminPerso = cheminPerso.remove(cheminApp);
    groupe << cheminPerso + "\n";

    progressBar_status->setValue(100);

// On ferme le dialogue d'ouverture
    nouveau_fenetre->close();
    nouveau_fenetre2->close();
    nouveau_fenetre3->close();

// On l'affiche
    if (compteurOnglets != 0)
    {
        QTabWidget *nouveauWidget = tableauDePersonnages[nouveau_nom->text()].afficher();
        QString nouveauNom = tableauDePersonnages[nouveau_nom->text()].getNom();

        MdiSubWindow *sousFenetre = new MdiSubWindow();
        sousFenetre->setWidget(nouveauWidget);
        sousFenetre->setWindowTitle(nouveauNom);
        sousFenetre->setAttribute(Qt::WA_DeleteOnClose);
        zoneCentrale->addSubWindow(sousFenetre)->show();

        ordreMarche->setNomPersos(nomPersoOuverts);
        ordreMarche->setEnabled(true);
    }

    if (compteurOnglets == 0)
    {
        for (QList<QString>::iterator it = fichiersOuverts.begin(); it < fichiersOuverts.end(); it++)
        {
            if (*it == cheminPerso)
            {
                fichiersOuverts.erase(it);
            }
        }
        for (QStringList::iterator it = nomPersoOuverts.begin(); it < nomPersoOuverts.end(); it++)
        {
            if (*it == nouveau_nom->text())
            {
                nomPersoOuverts.erase(it);
            }
        }
    }

    statusBar->removeWidget(progressBar_status);
    delete progressBar_status;
    progressBar_status = 0;
    statusBar->showMessage("Personnage créé et ajouté au groupe", 2000);

    QMessageBox::information(this, "Compétences",
                             "Les compétences acquises de naissance par le personnage ont été ajoutées au personnage, mais pas celle qu'il peut développer.\n\n"
                             "Merci de les ajouter par vous-même, la fonction d'ajout automatique est en développement.");
}

// Créer un nouveau groupe
void FenPrincipale::creerNouveauGroupe()
{
// Choix des chemins
    QString cheminGroupe = QFileDialog::getSaveFileName(zoneCentrale, "Créer un groupe -> Fichier 'NBH'",
                                                       QString("enregistrements"), "Groupe de personnages (*.nbh)");

    if (cheminGroupe.isEmpty())
        return;

    bool erreur(false);
    QString cheminNotes;
    while (!erreur)
    {
        QMessageBox::information(zoneCentrale, "Notes",
                                 "Dans la fenêtre suivante, vous devrez rentrer un nom pour le fichier qui contiendra vos notes.");

        cheminNotes = QFileDialog::getSaveFileName(zoneCentrale, "Créer un groupe -> Fichier 'notes'",
                                                           QString("enregistrements"), "Fichier Notes (*.notes)");

        if (cheminNotes.isEmpty())
            QMessageBox::critical(zoneCentrale, "ERREUR !", "Erreur :\nVous devez enregistrer un fichier contenant vos notes !");
        else
            erreur = true;
    }

// Enregistrement
    QFile notesRec(cheminNotes);
    if (!notesRec.open(QIODevice::WriteOnly | QIODevice::Text))
        fatalError("Impossible de créer le fichier de note sélectionné. C'est une erreur impossible normalement. Réessayez de créer le groupe.");

    log("Création d'un fichier de notes.");

    QFile groupeRec(cheminGroupe);
    if (!groupeRec.open(QIODevice::WriteOnly | QIODevice::Text))
        fatalError("Impossible de créer le fichier de groupe sélectionné. C'est une erreur impossible normalement. Réessayez de créer le groupe.");

    log("Création d'un fichier groupe.");

    QTextStream sortie(&groupeRec);

    if (OS == 0)
        cheminNotes.replace("/", "\\");
    QString cheminApp = QCoreApplication::applicationDirPath();
        cheminApp.remove("/debug");
        cheminApp.remove("/release");
        if (OS == 0)
            cheminApp.replace("/", "\\");
    cheminNotes = cheminNotes.remove(cheminApp);
    sortie << cheminNotes + "\n";

    log("Groupe bien crée !");
    statusBar->showMessage("Groupe bien créé", 2000);
}

// Ajouter un personnage
void FenPrincipale::ajouterPersonnage()
{
    progressBar_status = new QProgressBar();
    statusBar->addWidget(progressBar_status);

    int lecteur_spacer(0);
    for (int i = 0; i < NB_SPACER_FENPRINCIPALE; i++)
        spacer[i] = new QSpacerItem(30, 10);

// On crée la fenêtre !
    ajouter_fenetre = new QDialog(this, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
        setIcone(ajouter_fenetre);
        ajouter_fenetre->setWindowTitle("Ajouter un personnage créé auparavant");
        ajouter_fenetre->setModal(true);

        ajouter_nom = new QLineEdit();
        ajouter_sexe = new QLineEdit();
        ajouter_origineNom = new QLineEdit();
        ajouter_metierNom = new QLineEdit();

        ajouter_COU = new QSpinBox();
            ajouter_COU->setMaximum(20);
        ajouter_INT = new QSpinBox();
            ajouter_INT->setMaximum(20);
        ajouter_CHA = new QSpinBox();
            ajouter_CHA->setMaximum(20);
        ajouter_AD = new QSpinBox();
            ajouter_AD->setMaximum(20);
        ajouter_FO = new QSpinBox();
            ajouter_FO->setMaximum(20);
        ajouter_AT = new QSpinBox();
            ajouter_AT->setMaximum(20);
        ajouter_PRD = new QSpinBox();
            ajouter_PRD->setMaximum(20);

        ajouter_XP = new QSpinBox();
            ajouter_XP->setMaximum(999999999);
        ajouter_ptsDestin = new QSpinBox();
            ajouter_ptsDestin->setMaximum(3);

        ajouter_EV = new QSpinBox();
        ajouter_EA = new QSpinBox();
        ajouter_EA_type = new QLineEdit();

        ajouter_PO = new QSpinBox();
            ajouter_PO->setMaximum(999999);
        ajouter_PA = new QSpinBox();
            ajouter_PA->setMaximum(999999);
        ajouter_PC = new QSpinBox();
            ajouter_PC->setMaximum(999999);

        QFormLayout *ajouter_layout1 = new QFormLayout();
            ajouter_layout1->addRow("Nom du personnage à ajouter :", ajouter_nom);
            ajouter_layout1->addRow("Sexe :", ajouter_sexe);
            ajouter_layout1->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

            ajouter_layout1->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;
            ajouter_layout1->addRow("EV :", ajouter_EV);
            ajouter_layout1->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;
            ajouter_layout1->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

            ajouter_layout1->addRow("COU :", ajouter_COU);
            ajouter_layout1->addRow("INT :", ajouter_INT);
            ajouter_layout1->addRow("CHA :", ajouter_CHA);
            ajouter_layout1->addRow("AD :", ajouter_AD);
            ajouter_layout1->addRow("FO :", ajouter_FO);
            ajouter_layout1->addRow("AT :", ajouter_AT);
            ajouter_layout1->addRow("PRD :", ajouter_PRD);
            ajouter_layout1->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

        QFormLayout *ajouter_layout2 = new QFormLayout();
            ajouter_layout2->addRow("Nom de l'origine", ajouter_origineNom);
            ajouter_layout2->addRow("Nom du métier :", ajouter_metierNom);
            ajouter_layout2->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

            ajouter_layout2->addRow("EA :", ajouter_EA);
            ajouter_layout2->addRow("Type d'énergie astrale :", ajouter_EA_type);
            ajouter_layout2->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

            ajouter_layout2->addRow("Expérience déjà acquise :", ajouter_XP);
            ajouter_layout2->addRow("Points de destin :", ajouter_ptsDestin);
            ajouter_layout2->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

            ajouter_layout2->addRow("PO :", ajouter_PO);
            ajouter_layout2->addRow("PA :", ajouter_PA);
            ajouter_layout2->addRow("PC :", ajouter_PC);
            ajouter_layout2->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;

        QHBoxLayout *ajouter_layout = new QHBoxLayout();
            ajouter_layout->addLayout(ajouter_layout1);
            ajouter_layout->addItem(spacer[lecteur_spacer]);
            lecteur_spacer++;
            ajouter_layout->addLayout(ajouter_layout2);

        QLabel *explication = new QLabel("- Si le personnage n'est pas magicien, laisser à zéro l'EA et laisser vide le champs \"Type d'énergie astrale\".\n"
                                         "- Vous pourrez habiller le personnage, lui donner des protections, des armes, et des flèches lorsque celui-ci sera ouvert.");

        QDialogButtonBox *ajouter_boutonsBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            QObject::connect(ajouter_boutonsBox, SIGNAL(accepted()), this, SLOT(ajouterPersonnage_Save()));
            QObject::connect(ajouter_boutonsBox, SIGNAL(rejected()), ajouter_fenetre, SLOT(close()));

        QVBoxLayout *ajouter_layoutTotal = new QVBoxLayout();
            ajouter_layoutTotal->addLayout(ajouter_layout);
            ajouter_layoutTotal->addWidget(explication);
            ajouter_layoutTotal->addItem(spacer[lecteur_spacer]);
            ajouter_layoutTotal->addWidget(ajouter_boutonsBox);

        ajouter_fenetre->setLayout(ajouter_layoutTotal);

// On affiche la fenêtre
    ajouter_fenetre->show();
}
void FenPrincipale::ajouterPersonnage_Save()
{
    progressBar_status->setValue(50);

// On crée le personnage !
    tableauDePersonnages[ajouter_nom->text()] = Personnage(ajouter_nom->text(), ajouter_sexe->text(),
                                                           ajouter_origineNom->text(), ajouter_metierNom->text(),
                                                           ajouter_COU->value(), ajouter_INT->value(), ajouter_CHA->value(), ajouter_AD->value(),
                                                           ajouter_FO->value(), ajouter_AT->value(), ajouter_PRD->value(),
                                                           ajouter_COU->value(), ajouter_INT->value(), ajouter_CHA->value(), ajouter_AD->value(),
                                                           ajouter_FO->value(), ajouter_AT->value(), ajouter_PRD->value(),
                                                           ajouter_ptsDestin->value(), ajouter_XP->value(),
                                                           ajouter_EV->value(),
                                                           ajouter_PO->value(), ajouter_PA->value(), ajouter_PC->value());

// Si le personnage ajouté est mage
    if (ajouter_EA_type->text() != "" && ajouter_EA->value() != 0)
        tableauDePersonnages[ajouter_nom->text()].setEA(ajouter_EA->value(), ajouter_EA_type->text());

// On demande où l'enregistrer et on ouvre le fichier
    QString cheminPerso = QFileDialog::getSaveFileName(zoneCentrale, "Enregistrer un personnage",
                                                       QString("enregistrements"), "Personnages (*.perso)");
    if (cheminPerso.isEmpty())
    {
        QMap<QString, Personnage>::Iterator iterateurPerso = tableauDePersonnages.find(ajouter_nom->text());
        tableauDePersonnages.erase(iterateurPerso);

        return;
    }

    cheminPerso = cheminPerso.remove(QCoreApplication::applicationDirPath());
    if (OS == 0)
        cheminPerso.replace("/", "\\");

    bool ouvert = testOuverture(cheminPerso);
    if (ouvert)
    {
        QMessageBox::critical(this, "Erreur",
                              "ERREUR :\nVous essayez d'enregistrer le nouveau personnage\nsur un autre déjà créé et ouvert !");

        QMessageBox *msgBox1 = new QMessageBox(QMessageBox::Information, "Information",
                                               "Si vous voulez recréer ce personnage,"
                                               "il va falloir re-rentrer toutes les caractéristiques de celui-ci !\n\n"
                                               "C'est votre punition !");
            merci = msgBox1->addButton("Oh non !", QMessageBox::AcceptRole);
            setIcone(msgBox1);
            msgBox1->exec();

        QMessageBox *msgBox2 = new QMessageBox(QMessageBox::Information, "Information",
                                               "Alors, vous enragez ?\n\n"
                                               "Eh ben, vous avez de la chance, je suis de bonne humeur aujourd'hui !\n"
                                               "En conséquent, vous n'aurez pas besoin de re-remplir ce formulaire !\n\n"
                                               "Qu'est-ce qu'on dit ?");
            ohNon = msgBox2->addButton("Merci !", QMessageBox::AcceptRole);
            setIcone(msgBox2);
            msgBox2->exec();

        QMap<QString, Personnage>::Iterator iterateurPerso = tableauDePersonnages.find(ajouter_nom->text());
        tableauDePersonnages.erase(iterateurPerso);

        return;
    }

    // On dit au prog que ce perso est ouvert
    nomPersoOuverts << ajouter_nom->text();

    QFile persoRec(cheminPerso);
    if (!persoRec.open(QIODevice::WriteOnly | QIODevice::Text))
        fatalError("Impossible de créer le fichier personnage sélectionné. C'est une erreur impossible normalement. Réessayez d'ajouter le personnage.");

    log("Enregistrement du personnage ajouté !");

    QTextStream sortie(&persoRec);

    sortie << tableauDePersonnages[ajouter_nom->text()].getPersoEntier();

    tableauDePersonnages[ajouter_nom->text()].setAdresse(cheminPerso);

    progressBar_status->setValue(75);

// On ajoute le fichier personnage au groupe
    bool erreur(false);
    QString cheminGroupe;
    while (!erreur)
    {
        cheminGroupe = QFileDialog::getOpenFileName(zoneCentrale, "Modifier un groupe",
                                                    QString("enregistrements"), "Groupes de personnages (*.nbh)");

        if (cheminGroupe.isEmpty())
            QMessageBox::critical(zoneCentrale, "ERREUR !", "Erreur :\nVous devez choisir un groupe à modifier !");
        else
            erreur = true;
    }

    if (OS == 0)
        cheminGroupe.replace("/", "\\");
    QFile groupeRec(cheminGroupe);
    if (!groupeRec.open(QIODevice::Append | QIODevice::Text))
        fatalError("Impossible d'ouvrir le fichier de groupe sélectionné. Réessayez d'ajouter le personnage au groupe.");

    log("Ajout du personnage à un groupe !");

    QTextStream groupe(&groupeRec);

    QString cheminApp = QCoreApplication::applicationDirPath();
        cheminApp.remove("/debug");
        cheminApp.remove("/release");
        if (OS == 0)
            cheminApp.replace("/", "\\");
    cheminPerso = cheminPerso.remove(cheminApp);
    groupe << cheminPerso + "\n";

    progressBar_status->setValue(100);

// On ferme le dialogue d'ouverture
    ajouter_fenetre->close();

// On l'affiche
    if (compteurOnglets != 0)
    {
        QTabWidget *ajouterWidget = tableauDePersonnages[ajouter_nom->text()].afficher();
        QString ajouterNom = tableauDePersonnages[ajouter_nom->text()].getNom();

        MdiSubWindow *sousFenetre = new MdiSubWindow();
        sousFenetre->setWidget(ajouterWidget);
        sousFenetre->setWindowTitle(ajouterNom);
        sousFenetre->setAttribute(Qt::WA_DeleteOnClose);
        zoneCentrale->addSubWindow(sousFenetre)->show();

        ordreMarche->setNomPersos(nomPersoOuverts);
        ordreMarche->setEnabled(true);
    }

    if (compteurOnglets == 0)
    {
        for (QList<QString>::iterator it = fichiersOuverts.begin(); it < fichiersOuverts.end(); it++)
        {
            if (*it == cheminPerso)
            {
                fichiersOuverts.erase(it);
            }
        }
        for (QStringList::iterator it = nomPersoOuverts.begin(); it < nomPersoOuverts.end(); it++)
        {
            if (*it == ajouter_nom->text())
            {
                nomPersoOuverts.erase(it);
            }
        }
    }

    statusBar->removeWidget(progressBar_status);
    delete progressBar_status;
    progressBar_status = 0;
    statusBar->showMessage("Personnage créé et ajouté au groupe", 2000);
}

// Ouvrir
void FenPrincipale::ouvrir()
{
    if (groupeAdresse != "")
    {
        QMessageBox::information(zoneCentrale, "Attention",
                                 "Attention :\nVous ne pouves pas ouvrir 2 groupes de clampins !");
        return;
    }

// On demande à l'utilisateur de choisir le fichier contenant le groupe
    groupeAdresse = QFileDialog::getOpenFileName(zoneCentrale,
                                          "Ouvrir un groupe",
                                          "enregistrements",
                                          "Groupes de personnages (*.nbh)");

    // Si l'utilisateur annule
    if (groupeAdresse.isEmpty())
        return;

    QFile groupeOuverture(groupeAdresse);
    if (!groupeOuverture.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur lors de l'ouverture du groupe !",
                              "Impossible d'ouvrir le fichier de groupe.\n"
                              "Veuillez réessayer !");
        log("Erreur lors de l'ouverture du groupe : '" + groupeAdresse + "'\n"
            "Annulation du chargement du groupe.");
        groupeAdresse = "";
        return;
    }

    log("Ouverture du groupe : '" + groupeAdresse + "'");

    QTextStream groupeTxt(&groupeOuverture);

    QStringList chemins;
    QString ligne = groupeTxt.readLine();
    while (ligne != "")
    {
        QString cheminApp = QCoreApplication::applicationDirPath();
        cheminApp.remove("/debug");
        cheminApp.remove("/release");
        if (OS == 0)
            cheminApp.replace("/", "\\");
        chemins << cheminApp + ligne;
        ligne = groupeTxt.readLine();
    }

    QStringList::Iterator cheminPersoOuverture = chemins.begin();

    // On ouvre le fichier "notes"
    noteAdresse = *cheminPersoOuverture;
    QFile notes_fichier(noteAdresse);
    if (!notes_fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur lors de l'ouverture de notes !",
                              "Impossible d'ouvrir le fichier de notes.\n"
                              "Veuillez réessayer !");
        log("Erreur lors de l'ouverture du fichier de note : '" + noteAdresse + "'\n"
            "Annulation du chargement du groupe.");
        groupeAdresse = "";
        noteAdresse = "";
        return;
    }

    log("Ouverture du fichier de notes : '" + noteAdresse + "'");

    QTextStream notes_flux(&notes_fichier);
    QString notes_string = notes_flux.readAll();

    notes_txt->setText(notes_string);
    notes_txt->setEnabled(true);
    notes_txt->setUndoRedoEnabled(true);
// On ajoute 1 à l'itérateur
    cheminPersoOuverture++;

    progressBar_status = new QProgressBar();
    progressBar_status->setValue(0);
    statusBar->addWidget(progressBar_status);
    int valeurProgression = static_cast<int>(100 / chemins.size());
    while(cheminPersoOuverture != chemins.end())
    {
        if (progressBar_status->value() + valeurProgression >= 100)
            progressBar_status->setValue(100);
        else
            progressBar_status->setValue(progressBar_status->value() + valeurProgression);
// renvoie un personnage
        Personnage temp = chargerPerso(*cheminPersoOuverture);
        QString nom = temp.getNom();
        tableauDePersonnages.insert(nom, temp);

        QTabWidget *ouvrirWidget = tableauDePersonnages[nom].afficher();
        QString ouvrirNom = tableauDePersonnages[nom].getNom();

        MdiSubWindow *sousFenetre = new MdiSubWindow();
        sousFenetre->setWidget(ouvrirWidget);
        sousFenetre->setWindowTitle(ouvrirNom);
        sousFenetre->setAttribute(Qt::WA_DeleteOnClose);
        zoneCentrale->addSubWindow(sousFenetre)->show();

        cheminPersoOuverture++;
        compteurOnglets++;
    }

    statusBar->removeWidget(progressBar_status);
    delete progressBar_status;
    progressBar_status = 0;

    statusBar->showMessage("Groupe ouvert avec succèes", 2000);
    log("Groupe ouvert avec succès !");


// On "enable" l'ordre de marche et la gestion de l'attaque
    ordreMarche->setNomPersos(nomPersoOuverts);
    ordreMarche->setEnabled(true);

    attaque_fen->setNomPersos(nomPersoOuverts);
    attaque_fen->setEnabled(true);

// On "enable" les boutons
    enregistrer->setEnabled(true);
    quitterGroupe->setEnabled(true);

    attaque->setEnabled(true);
    passif->setEnabled(true);

    xpGroupe->setEnabled(true);
    POGroupe->setEnabled(true);
    PAGroupe->setEnabled(true);
    PCGroupe->setEnabled(true);
    poGroupe->setEnabled(true);
    paGroupe->setEnabled(true);
    pcGroupe->setEnabled(true);

    achatATPRD->setEnabled(true);
    achatINT->setEnabled(true);
    achatCHA->setEnabled(true);
    achatFO->setEnabled(true);
    achatCOU->setEnabled(true);
    achatEV->setEnabled(true);
    achatEA->setEnabled(true);

// Activation de l'enregistrement auto
    QTimer *auto_save = new QTimer(this);
    QObject::connect(auto_save, SIGNAL(timeout()), this, SLOT(enregistrerTout()));
    auto_save->start(600000);

// Synchronisation des onglets de chaque personnage
    for (QStringList::iterator iterateurSignal = nomPersoOuverts.begin();
         iterateurSignal != nomPersoOuverts.end();
         iterateurSignal++)
    {
        for (QStringList::iterator iterateurSlot = nomPersoOuverts.begin();
             iterateurSlot != nomPersoOuverts.end();
             iterateurSlot++)
        {
            if (*iterateurSignal != *iterateurSlot)
                QObject::connect(tableauDePersonnages[*iterateurSignal].getAffichage(), SIGNAL(currentChanged(int)),
                                 tableauDePersonnages[*iterateurSlot].getAffichage(), SLOT(setCurrentIndex(int)));
        }
    }
}

// Enregistrer tout
void FenPrincipale::enregistrerTout()
{
// Enregistrement des notes
    if (!noteAdresse.isEmpty())
    {
        QFile notesRec(noteAdresse);
        if (!notesRec.open(QIODevice::WriteOnly | QIODevice::Text))
            fatalError("Impossible d'enregistrer le fichier de note. Réessayez d'enregistrer le groupe.");

        QTextStream sortie(&notesRec);
        sortie << notes_txt->toHtml();

        notesRec.close();
    }

// Enregistrement des personnages
    for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
    {
        QString adresse = tableauDePersonnages[*it].getAdresse();

        QFile persoRec(adresse);
        if (!persoRec.open(QIODevice::WriteOnly | QIODevice::Text))
            fatalError("Impossible d'enregistrer le fichier de personnage sélectionné. Réessayez d'enregistrer le groupe.");

        QTextStream sortie(&persoRec);

        // On enregistre
        sortie << tableauDePersonnages[*it].getPersoEntier();

        persoRec.close();
    }

    log("Enregistrement effectué !");
    statusBar->showMessage("Enregistrement effectué", 2000);
}

// Fermer le groupe en cours
void FenPrincipale::fermerGroupe()
{
    enregistrerTout();

// On relance NBH
    QString nbh("NBH");
    if (OS == 0)
        nbh += ".exe";
    QProcess::startDetached(nbh, QStringList("-fermer_gr"));

    qApp->quit();
}
void FenPrincipale::fermerOnglets()
{
// On relance NBH
    QString nbh("NBH");
    if (OS == 0)
        nbh += ".exe";
    QProcess::startDetached(nbh, QStringList("-fermer_onglets"));

    qApp->quit();
}

// Quitter NBH
void FenPrincipale::quitterNBH()
{
    close();
}
void FenPrincipale::closeEvent(QCloseEvent *e)
{
// On vérifie que l'utilisateur veut vraiment fermer
    int reponse = QMessageBox::question(zoneCentrale, "Quitter NaheulBeuk Helper ?",
                                        "Êtes-vous sûr(e) de vouloir quitter NaheulBeuk Helper ?",
                                        QMessageBox::Yes | QMessageBox::No);

// Si "oui", on enregistre puis on ferme
    if (reponse == QMessageBox::Yes)
    {
    // On enregistre tout
        enregistrerTout();

    // Enregistrement des options/positions
        QSettings *settings = new QSettings("config.ini", QSettings::IniFormat, this);
            settings->beginGroup("FenPrincipale");
                settings->setValue("geometry", saveGeometry());
                settings->setValue("windowState", saveState());

                settings->beginGroup("toolBar");
                    settings->setValue("Fichier", afficher_fichier->isChecked());
                    settings->setValue("Action", afficher_action->isChecked());
                    settings->setValue("Achat", afficher_achat->isChecked());
                settings->endGroup();
            settings->endGroup();
        log("Enregistrement des préférences !");
        log("Fermeture de NBH.");

    // On ferme NBH (fen)
        e->accept();
    }
// Sinon, on ignore la fermeture
    else
        e->ignore();
}

// Mode d'attaque
void FenPrincipale::modeAttaque()
{
// Si l'utilisateur à décoché la case attaque sans toucher à la case passive
    if (!attaque->isChecked())
    {
        attaque->setChecked(true);
        return;
    }

    passif->setChecked(false);
    attaque_dock->setVisible(true);

    log("Passage en mode Attaque !");
}
// Mode passif
void FenPrincipale::modePassif()
{
// Si l'utilisateur à décoché la case passive sans toucher à la case attaque
    if (!passif->isChecked())
    {
        passif->setChecked(true);
        return;
    }

    attaque->setChecked(false);
    attaque_dock->setVisible(false);

    log("Passage en mode Passif !");
}

// Attaque
void FenPrincipale::attaquer()
{
    QMessageBox::information(this, "En dévelopemment",
                             "Cette fonction est encore en développement.");
}

// XP de groupe
void FenPrincipale::xp()
{
    bool ok(false);
    int xpPlus = QInputDialog::getInteger(zoneCentrale, "Ajout d'expérience de groupe",
                                          "Veuillez rentrer l'XP à ajouter à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].plus_xp(xpPlus);

        log("Ajout d'expérience de groupe : " + QString::number(xpPlus));
    }
}

// PO+ de goupe
void FenPrincipale::PO()
{
    bool ok(false);
    int poPlus = QInputDialog::getInteger(zoneCentrale, "Ajout de PO de groupe",
                                          "Veuillez rentrer le nombre de PO à ajouter à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].plus_po(poPlus);

        log("Ajout de PO de groupe : " + QString::number(poPlus));
    }
}
// PA+ de goupe
void FenPrincipale::PA()
{
    bool ok(false);
    int paPlus = QInputDialog::getInteger(zoneCentrale, "Ajout de PA de groupe",
                                          "Veuillez rentrer le nombre de PO à ajouter à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].plus_pa(paPlus);

        log("Ajout de PA de groupe : " + QString::number(paPlus));
    }
}
// PC+ de goupe
void FenPrincipale::PC()
{
    bool ok(false);
    int pcPlus = QInputDialog::getInteger(zoneCentrale, "Ajout de PC de groupe",
                                          "Veuillez rentrer le nombre de PO à ajouter à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].plus_pc(pcPlus);

        log("Ajout de PC de groupe : " + QString::number(pcPlus));
    }
}

// PO- de goupe
void FenPrincipale::po()
{
    bool ok(false);
    int poMoins = QInputDialog::getInteger(zoneCentrale, "Retrait de PO de groupe",
                                          "Veuillez rentrer le nombre de PO à retirer à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].moins_po(poMoins);

        log("Retrait de PO de groupe : " + QString::number(poMoins));
    }
}
// PA- de goupe
void FenPrincipale::pa()
{
    bool ok(false);
    int paMoins = QInputDialog::getInteger(zoneCentrale, "Retrait de PA de groupe",
                                          "Veuillez rentrer le nombre de PO à retirer à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].moins_pa(paMoins);

        log("Retrait de PA de groupe : " + QString::number(paMoins));
    }
}
// PC- de goupe
void FenPrincipale::pc()
{
    bool ok(false);
    int pcMoins = QInputDialog::getInteger(zoneCentrale, "Retrait de PC de groupe",
                                          "Veuillez rentrer le nombre de PO à retirer à chaque personnage du groupe :",
                                          1, 1, 100000, 1, &ok);

    if (ok)
    {
        for (QStringList::iterator it = nomPersoOuverts.begin(); it != nomPersoOuverts.end(); it++)
            tableauDePersonnages[*it].moins_pc(pcMoins);

        log("Retrait de PC de groupe : " + QString::number(pcMoins));
    }
}

// Achat
void FenPrincipale::ATPRD()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatATPRD();
}
void FenPrincipale::INT()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatINT();
}
void FenPrincipale::CHA()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatCHA();
}
void FenPrincipale::FO()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatFO();
}
void FenPrincipale::COU()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatCOU();
}
void FenPrincipale::EV()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatEV();
}
void FenPrincipale::EA()
{
    tableauDePersonnages[zoneCentrale->currentSubWindow()->windowTitle()].achatEA();
}

// Afficher les barres d'outils
void FenPrincipale::afficherFichier(bool affiche)
{
    if (!affiche)
        fichierToolBar->setVisible(false);
    else
        fichierToolBar->setVisible(true);
}
void FenPrincipale::afficherAction(bool affiche)
{
    if (!affiche)
        actionsToolBar->setVisible(false);
    else
        actionsToolBar->setVisible(true);
}
void FenPrincipale::afficherAchat(bool affiche)
{
    if (!affiche)
        achatToolBar->setVisible(false);
    else
        achatToolBar->setVisible(true);
}

// A propos
void FenPrincipale::aProposDeNBH()
{
// On affiche le message d'à propos
    QMessageBox::about(zoneCentrale, "A propos de NaheulBeuk Helper",
                       "NaheulBeuk Helper est un programme destiné aux maîtres du jeu qui jouent au jeu de rôle de Naheulbeuk...\n"
                       "Ce programme facilitera leur tâche... qui est assez difficile !\n\n\n"
                       "Vous utilisez la version " VERSION ".\n\n"
                       "Ce programme est développé en C++, avec QtCreator et utilise la bibliothèque graphique open source Qt.");
}

// Affichage de la licence
void FenPrincipale::licence()
{
// On ouvre le fichier contenant la licence
    QFile licence(":/prog-data/LICENCE");
    if (!licence.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Licence -> erreur d'ouverture",
                              "Impossible de charger le fichier contenant la licence de NBH.\n"
                              "Cette fenêtre va se fermer !");
        log("Impossible de charger le fichier contenant la licence");
        return;
    }

    QTextStream licenceTxt(&licence);

// On affiche la licence
    QDialog *licenceDialog = new QDialog(this, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
        licenceDialog->setWindowTitle("Licence de NaheulBeuk Helper");
        licenceDialog->setModal(true);
        licenceDialog->setWindowIcon(QIcon(":prog-data/img/licence.png"));
        licenceDialog->setMinimumSize(450, 500);

    QVBoxLayout *layout = new QVBoxLayout();
        QTextEdit *txt = new QTextEdit();
        txt->setPlainText(licenceTxt.readAll());
        txt->setReadOnly(true);
    layout->addWidget(txt);

        QDialogButtonBox *bouton = new QDialogButtonBox(QDialogButtonBox::Ok);
        QObject::connect(bouton, SIGNAL(accepted()), licenceDialog, SLOT(close()));
    layout->addWidget(bouton);

    licenceDialog->setLayout(layout);
    licenceDialog->show();
}

// Vérification de MAJ
void FenPrincipale::MAJ()
{
    enregistrerTout();

// On crée la fenêtre
    FenMAJ *maj = new FenMAJ(this);

// On affiche la fenêtre
    maj->show();
}

// Help
void FenPrincipale::help()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath().replace("\\", "/").remove("/debug").remove("/release") + "/aide/index.html"));
}

// Test pour l'ouverture
bool FenPrincipale::testOuverture(QString const& cheminFichier)
{
    bool ouvert = false;

    for (int lecteurListe = 0; lecteurListe < fichiersOuverts.size(); lecteurListe++)
    {
        if (fichiersOuverts.at(lecteurListe) == cheminFichier)
        {
            ouvert = true;
            return ouvert;
        }
    }

    if (!ouvert)
        fichiersOuverts << cheminFichier;

    return ouvert;
}

// MdiSubWindow modifiée
MdiSubWindow::MdiSubWindow()
{

}

// Fermeture d'un onglet
void MdiSubWindow::closeEvent(QCloseEvent *e)
{
    e->ignore();
}
