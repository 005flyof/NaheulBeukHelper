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
                      "* créez un groupe\n" \
                      "* créez / ajouter un personnage au groupe créé\n" \
                      "* ouvrez le groupe\n" \
                      "* enjoy the features of this program !!!\n\n" \
                   "	------------\n\n" \
                   "Vous utilisez la version " VERSION " de ce programme.\n" \
                   "Ce programme est développé en C++ avec QtCreator, par Florent Fayollas.\n" \
                   "NaheulBeuk Helper utilise la bibliothèque Qt développée par Nokia."

using namespace std;

// Fenêtre principale
FenPrincipale::FenPrincipale() :
    QMainWindow(),
    m_fichierGroupe(0), m_fichierNotes(0)
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
        enregistrer->setStatusTip("Enregistrer les modifications apportées au groupe ouvert.");
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
    QMenu *groupe = barreDeMenu->addMenu("Modifications sur le &groupe");

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

    achatCOU = perso->addAction("Achat de point de COU");
        achatCOU->setIcon(QIcon(":prog-data/img/cou+.png"));
        achatCOU->setStatusTip("Achat d'un point de COU (400 PO -> 1 mois de stage)");
        achatCOU->setEnabled(false);
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
    achatATPRD = perso->addAction("Achat de point d'AT / PRD");
        achatATPRD->setIcon(QIcon(":prog-data/img/at_prd+.png"));
        achatATPRD->setStatusTip("Achat d'un point d'AT ou de PRD (500 PO -> 1 mois de stage)");
        achatATPRD->setEnabled(false);
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
    QObject::connect(enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerGroupe()));
    QObject::connect(quitterGroupe, SIGNAL(triggered()), this, SLOT(fermerGroupe()));
    QObject::connect(quitter, SIGNAL(triggered()), this, SLOT(close()));

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

        achatToolBar->addAction(achatCOU);
        achatToolBar->addAction(achatINT);
        achatToolBar->addAction(achatCHA);
        achatToolBar->addAction(achatFO);
        achatToolBar->addAction(achatATPRD);
        achatToolBar->addSeparator();

        achatToolBar->addAction(achatEV);
        achatToolBar->addAction(achatEA);
}
void FenPrincipale::initWidget()
{
// Création du widget central
    zoneCentrale = new QMdiArea(this);
    zoneCentrale->setViewMode(QMdiArea::TabbedView);
    zoneCentrale->setTabsMovable(false);

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
}


FenPrincipale::~FenPrincipale()
{}


// Fenêtre de création des personnages
void FenPrincipale::creerNouveauPersonnage()
{}
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


// Modification des chemins pour que ça marche sous linux
    if (OS == 1)
    {
        cheminGroupe += ".nbh";
        cheminNotes += ".notes";
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

    QString cheminApp = QApplication::applicationDirPath();
    if (OS == 0)
    {
        cheminNotes.replace("/", "\\");
        cheminApp.replace("/", "\\");
    }
    cheminNotes = cheminNotes.remove(cheminApp);
    sortie << cheminNotes + "\n";

    log("Groupe bien crée !");
    statusBar->showMessage("Groupe bien créé", 2000);
}
// Ajouter un personnage
void FenPrincipale::ajouterPersonnage()
{}

// Ouvrir
void FenPrincipale::ouvrir()
{
// Si un groupe est déjà ouvert
    if (m_fichierGroupe != 0)
    {
        QMessageBox::information(zoneCentrale, "Attention",
                                 "Attention :\nVous ne pouves pas ouvrir 2 groupes de clampins !");
        return;
    }

// On demande à l'utilisateur de choisir le fichier contenant le groupe
    QString groupeAdresse = QFileDialog::getOpenFileName(zoneCentrale,
                                                         "Ouvrir un groupe",
                                                         "enregistrements",
                                                         "Groupes de personnages (*.nbh)");

    // Si l'utilisateur annule, on annule le chargement du groupe
    if (groupeAdresse.isEmpty())
        return;

    m_fichierGroupe = new QFile(groupeAdresse);
    if (!m_fichierGroupe->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur lors de l'ouverture du groupe !",
                              "Impossible d'ouvrir le fichier de groupe.\n"
                              "Veuillez réessayer !");
        log("Erreur lors de l'ouverture du groupe : '" + groupeAdresse + "'\n"
            "Annulation du chargement du groupe.");

        m_fichierGroupe->close();
        delete m_fichierGroupe;
        m_fichierGroupe = 0;
        return;
    }

    log("Ouverture du groupe : '" + groupeAdresse + "'");

    QTextStream groupeTxt(m_fichierGroupe);

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
    m_fichierNotes = new QFile(*cheminPersoOuverture);
    if (!m_fichierNotes->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur lors de l'ouverture de notes !",
                              "Impossible d'ouvrir le fichier de notes.\n"
                              "Veuillez réessayer !");
        log("Erreur lors de l'ouverture du fichier de note : '" + m_fichierNotes->fileName() + "'\n"
            "Annulation du chargement du groupe.");

        m_fichierGroupe->close();
        delete m_fichierGroupe;
        m_fichierGroupe = 0;

        m_fichierNotes->close();
        delete m_fichierNotes;
        m_fichierNotes = 0;

        return;
    }

    log("Ouverture du fichier de notes : '" + m_fichierNotes->fileName() + "'", 1);

    QTextStream notes_flux(m_fichierNotes);
    QString notes = notes_flux.readAll();
    m_fichierNotes->close();

    notes_txt->setText(notes);
    notes_txt->setEnabled(true);
    notes_txt->setUndoRedoEnabled(true);
// On ajoute 1 à l'itérateur
    cheminPersoOuverture++;

    progressBar_status = new QProgressBar();
    progressBar_status->setValue(0);
    statusBar->addWidget(progressBar_status);
    int valeurProgression = static_cast<int>(100 / chemins.size());

    int compteurOnglets(0);
    while(cheminPersoOuverture != chemins.end())
    {
        if (progressBar_status->value() + valeurProgression >= 100)
            progressBar_status->setValue(100);
        else
            progressBar_status->setValue(progressBar_status->value() + valeurProgression);

        // On crée le personnage
        m_personnages.push_back(new Personnage(*cheminPersoOuverture));

        // On charge le personnage
        bool erreur = m_personnages.at(compteurOnglets)->chargerPerso();
            // si erreur, on ferme tout
        if (erreur)
        {
            for (int i = 0; i < m_personnages.count(); i++)
                zoneCentrale->removeSubWindow(m_personnages.at(i));
            m_personnages.clear();
            m_nomPersos.clear();

            zoneCentrale->deleteLater();
            zoneCentrale = new QMdiArea(this);
            zoneCentrale->setViewMode(QMdiArea::TabbedView);
            zoneCentrale->setTabsMovable(true);
            setCentralWidget(zoneCentrale);

            m_fichierGroupe->close();
            delete m_fichierGroupe;
            m_fichierGroupe = 0;
            m_fichierNotes->close();
            delete m_fichierNotes;
            m_fichierNotes = 0;

            notes_txt->setPlainText(NOTES_BASE);
            notes_txt->setEnabled(false);
            notes_txt->setUndoRedoEnabled(true);

            ordreMarche->setNomPersos(QStringList("Pas de groupe ouvert"));
            ordreMarche->setEnabled(false);

            attaque_fen->setNomPersos(QStringList("Pas de groupe ouvert"));
            attaque_fen->setEnabled(false);

            quitterGroupe->setEnabled(false);

            attaque->setEnabled(false);
            passif->setEnabled(false);

            xpGroupe->setEnabled(false);
            POGroupe->setEnabled(false);
            PAGroupe->setEnabled(false);
            PCGroupe->setEnabled(false);
            poGroupe->setEnabled(false);
            paGroupe->setEnabled(false);
            pcGroupe->setEnabled(false);

            achatATPRD->setEnabled(false);
            achatINT->setEnabled(false);
            achatCHA->setEnabled(false);
            achatFO->setEnabled(false);
            achatCOU->setEnabled(false);
            achatEV->setEnabled(false);
            achatEA->setEnabled(false);

            statusBar->removeWidget(progressBar_status);
            delete progressBar_status;
            progressBar_status = 0;

            return;
        }


        // On ajoute le nom du personnage à la liste
        m_nomPersos << m_personnages.at(compteurOnglets)->getNom();

        // On crée l'affichage
        MdiSubWindow *sousFen = new MdiSubWindow();
        sousFen->setWidget(m_personnages.at(compteurOnglets));
        sousFen->setWindowTitle(m_personnages.at(compteurOnglets)->getNom());
        zoneCentrale->addSubWindow(sousFen)->show();

        // On connecte le changement de nom des onglets
        QObject::connect(m_personnages.at(compteurOnglets), SIGNAL(persoModifie()), this, SLOT(persoModifie()));

        cheminPersoOuverture++;
        compteurOnglets++;
    }

    statusBar->removeWidget(progressBar_status);
    delete progressBar_status;
    progressBar_status = 0;

    statusBar->showMessage("Groupe ouvert avec succès", 2000);
    log("Groupe ouvert avec succès !", 1);


// On "enable" l'ordre de marche et la gestion de l'attaque
    ordreMarche->setNomPersos(m_nomPersos);
    ordreMarche->setEnabled(true);

    attaque_fen->setNomPersos(m_nomPersos);
    attaque_fen->setEnabled(true);

// On "enable" les boutons
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
}

// Enregistrement
void FenPrincipale::enregistrerGroupe() // Pour le bouton
{
    log("Enregistrement du groupe :");
    enregistrerTout();
    enregistrer->setEnabled(false);
}
void FenPrincipale::enregistrerTout()   // Pour la fermeture
{
    if (m_fichierGroupe != 0)
    {
    // Enregistrement des notes
        if (m_fichierNotes != 0)
        {
            if (!m_fichierNotes->open(QIODevice::WriteOnly | QIODevice::Text))
                fatalError("Impossible d'enregistrer le fichier de note. Réessayez d'enregistrer le groupe.");

            QTextStream sortie(m_fichierNotes);
            sortie << notes_txt->toHtml();

            m_fichierNotes->close();

            log("Enregistrement des notes !", 2);
        }
        else
            fatalError("Impossible d'accéder à la variable de fichier de notes !");

    // Enregistrement des personnages
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->enregistrerPerso();

    // Réinitialisation des noms des onglets
        for (int i = 0; i < zoneCentrale->subWindowList().count(); i++)
            zoneCentrale->subWindowList().at(i)->setWindowTitle(m_personnages.at(i)->getNom());


        log("Enregistrement effectué !", 2);
        statusBar->showMessage("Enregistrement effectué", 2000);
    }
}
void FenPrincipale::enregistrerNotes()  // Pour juste les notes
{
    if (m_fichierGroupe != 0)
    {
    // Enregistrement des notes
        if (m_fichierNotes != 0)
        {
            if (!m_fichierNotes->open(QIODevice::WriteOnly | QIODevice::Text))
                fatalError("Impossible d'enregistrer le fichier de note. Réessayez d'enregistrer le groupe.");

            QTextStream sortie(m_fichierNotes);
            sortie << notes_txt->toHtml();

            m_fichierNotes->close();

            log("Enregistrement des notes !", 2);
        }
        else
            fatalError("Impossible d'accéder à la variable de fichier de notes !");
    }
}


// Fermer le groupe en cours
void FenPrincipale::fermerGroupe()
{
    bool modifNonRec(false);
    for (int i = 0; i < m_personnages.count(); i++)
        if (m_personnages.at(i)->getModif())
            modifNonRec = true;

// S'il y a des modifications non enregistrées, on demande que faire
    if (modifNonRec)
    {
        QMessageBox question;
        question.setWindowTitle("Fermer le groupe actuel ?");
        question.setText("Il y a des modifications non enregistrées");
        question.setInformativeText("Voulez-vous enregistrer les modifications ?");
        question.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        question.setDefaultButton(QMessageBox::Save);
        int reponse = question.exec();

        if (reponse == QMessageBox::Save)
        {
            log("Fermeture du groupe :");
            log("Enregistrement du groupe :", 1);
            enregistrerTout();

            for (int i = 0; i < m_personnages.count(); i++)
                zoneCentrale->removeSubWindow(m_personnages.at(i));
            m_personnages.clear();
            m_nomPersos.clear();

            zoneCentrale->deleteLater();
            zoneCentrale = new QMdiArea(this);
            zoneCentrale->setViewMode(QMdiArea::TabbedView);
            zoneCentrale->setTabsMovable(true);
            setCentralWidget(zoneCentrale);

            m_fichierGroupe->close();
            delete m_fichierGroupe;
            m_fichierGroupe = 0;
            m_fichierNotes->close();
            delete m_fichierNotes;
            m_fichierNotes = 0;

            notes_txt->setPlainText(NOTES_BASE);
            notes_txt->setEnabled(false);
            notes_txt->setUndoRedoEnabled(true);

            ordreMarche->setNomPersos(QStringList("Pas de groupe ouvert"));
            ordreMarche->setEnabled(false);

            attaque_fen->setNomPersos(QStringList("Pas de groupe ouvert"));
            attaque_fen->setEnabled(false);

            quitterGroupe->setEnabled(false);

            attaque->setEnabled(false);
            passif->setEnabled(false);

            xpGroupe->setEnabled(false);
            POGroupe->setEnabled(false);
            PAGroupe->setEnabled(false);
            PCGroupe->setEnabled(false);
            poGroupe->setEnabled(false);
            paGroupe->setEnabled(false);
            pcGroupe->setEnabled(false);

            achatATPRD->setEnabled(false);
            achatINT->setEnabled(false);
            achatCHA->setEnabled(false);
            achatFO->setEnabled(false);
            achatCOU->setEnabled(false);
            achatEV->setEnabled(false);
            achatEA->setEnabled(false);

            log("Groupe fermé !", 1);
        }
        else if (reponse == QMessageBox::Discard)
        {
            log("Fermeture du groupe !");

            for (int i = 0; i < m_personnages.count(); i++)
                zoneCentrale->removeSubWindow(m_personnages.at(i));
            m_personnages.clear();
            m_nomPersos.clear();

            zoneCentrale->deleteLater();
            zoneCentrale = new QMdiArea(this);
            zoneCentrale->setViewMode(QMdiArea::TabbedView);
            zoneCentrale->setTabsMovable(true);
            setCentralWidget(zoneCentrale);

            m_fichierGroupe->close();
            delete m_fichierGroupe;
            m_fichierGroupe = 0;
            m_fichierNotes->close();
            delete m_fichierNotes;
            m_fichierNotes = 0;

            notes_txt->setPlainText(NOTES_BASE);
            notes_txt->setEnabled(false);
            notes_txt->setUndoRedoEnabled(true);

            ordreMarche->setNomPersos(QStringList("Pas de groupe ouvert"));
            ordreMarche->setEnabled(false);

            attaque_fen->setNomPersos(QStringList("Pas de groupe ouvert"));
            attaque_fen->setEnabled(false);

            quitterGroupe->setEnabled(false);

            attaque->setEnabled(false);
            passif->setEnabled(false);

            xpGroupe->setEnabled(false);
            POGroupe->setEnabled(false);
            PAGroupe->setEnabled(false);
            PCGroupe->setEnabled(false);
            poGroupe->setEnabled(false);
            paGroupe->setEnabled(false);
            pcGroupe->setEnabled(false);

            achatATPRD->setEnabled(false);
            achatINT->setEnabled(false);
            achatCHA->setEnabled(false);
            achatFO->setEnabled(false);
            achatCOU->setEnabled(false);
            achatEV->setEnabled(false);
            achatEA->setEnabled(false);
        }
        else if (reponse == QMessageBox::Cancel)
            return;
    }
// Sinon, on ferme le groupe
    else
    {
        log("Fermeture du groupe !");

        for (int i = 0; i < m_personnages.count(); i++)
            zoneCentrale->removeSubWindow(m_personnages.at(i));
        m_personnages.clear();
        m_nomPersos.clear();

        zoneCentrale->deleteLater();
        zoneCentrale = new QMdiArea(this);
        zoneCentrale->setViewMode(QMdiArea::TabbedView);
        zoneCentrale->setTabsMovable(true);
        setCentralWidget(zoneCentrale);

        m_fichierGroupe->close();
        delete m_fichierGroupe;
        m_fichierGroupe = 0;
        m_fichierNotes->close();
        delete m_fichierNotes;
        m_fichierNotes = 0;

        notes_txt->setPlainText(NOTES_BASE);
        notes_txt->setEnabled(false);
        notes_txt->setUndoRedoEnabled(true);

        ordreMarche->setNomPersos(QStringList("Pas de groupe ouvert"));
        ordreMarche->setEnabled(false);

        attaque_fen->setNomPersos(QStringList("Pas de groupe ouvert"));
        attaque_fen->setEnabled(false);

        quitterGroupe->setEnabled(false);

        attaque->setEnabled(false);
        passif->setEnabled(false);

        xpGroupe->setEnabled(false);
        POGroupe->setEnabled(false);
        PAGroupe->setEnabled(false);
        PCGroupe->setEnabled(false);
        poGroupe->setEnabled(false);
        paGroupe->setEnabled(false);
        pcGroupe->setEnabled(false);

        achatATPRD->setEnabled(false);
        achatINT->setEnabled(false);
        achatCHA->setEnabled(false);
        achatFO->setEnabled(false);
        achatCOU->setEnabled(false);
        achatEV->setEnabled(false);
        achatEA->setEnabled(false);
    }
}
// Quitter NBH
void FenPrincipale::closeEvent(QCloseEvent *e)
{
    bool modifNonRec(false);
    for (int i = 0; i < m_personnages.count(); i++)
        if (m_personnages.at(i)->getModif())
            modifNonRec = true;

// S'il y a des modifications non enregistrées, on demande que faire
    if (modifNonRec)
    {
        QMessageBox question;
        question.setWindowTitle("Quitter NaheulBeuk Helper ?");
        question.setText("Il y a des modifications non enregistrées");
        question.setInformativeText("Voulez-vous enregistrer les modifications ?");
        question.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        question.setDefaultButton(QMessageBox::Save);
        int reponse = question.exec();

        if (reponse == QMessageBox::Save)
        {
            log("Fermeture de NBH :");
            log("Enregistrement du groupe :", 1);
            enregistrerTout();

            log("Enregistrement des préférences !", 1);

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

            // On ferme NBH
            e->accept();
        }
        else if (reponse == QMessageBox::Discard)
        {
            log("Fermeture de NBH !");
            log("Enregistrement des préférences !", 1);

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

            // On ferme NBH
            e->accept();
        }
        else if (reponse == QMessageBox::Cancel)
            e->ignore();
    }
// Sinon, on quitte normalement, sans enregistrer (pas de calculs process en plus)
    else
    {
        log("Fermeture de NBH :");
        log("Enregistrement du groupe :", 1);
        enregistrerNotes();

        log("Enregistrement des préférences !", 1);

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

        // On ferme NBH
        e->accept();
    }
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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->ajouterXP(xpPlus);

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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->ajouterPO(poPlus);

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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->ajouterPA(paPlus);

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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->ajouterPC(pcPlus);

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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->retirerPO(poMoins);

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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->retirerPA(paMoins);

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
        for (int i = 0; i < m_personnages.count(); i++)
            m_personnages.at(i)->retirerPC(pcMoins);

        log("Retrait de PC de groupe : " + QString::number(pcMoins));
    }
}


// Achat
void FenPrincipale::COU()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatCOU();
    }
}
void FenPrincipale::INT()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatINT();
    }
}
void FenPrincipale::CHA()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatCHA();
    }
}
void FenPrincipale::FO()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatFO();
    }
}
void FenPrincipale::ATPRD()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatATPRD();
    }
}

void FenPrincipale::EV()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatEV();
    }
}
void FenPrincipale::EA()
{
    for (int i = 0; i < m_personnages.count(); i++)
    {
        if (m_personnages.at(i)->getNom() == zoneCentrale->currentSubWindow()->windowTitle()
            || ("* " + m_personnages.at(i)->getNom()) == zoneCentrale->currentSubWindow()->windowTitle())
            m_personnages.at(i)->achatEA();
    }
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
// Licence
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


// Modification d'un personnage
void FenPrincipale::persoModifie()
{
    for (int i = 0; i < zoneCentrale->subWindowList().count(); i++)
    {
        if (m_personnages.at(i)->getModif())
            zoneCentrale->subWindowList().at(i)->setWindowTitle("* " + m_personnages.at(i)->getNom());
    }
    enregistrer->setEnabled(true);
}




// MdiSubWindow modifiée
MdiSubWindow::MdiSubWindow()
{}

// Annulation de la fermeture d'un onglet
void MdiSubWindow::closeEvent(QCloseEvent *e)
{
    e->ignore();
}
