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

#ifndef FENPRINCIPALE_H
    #define FENPRINCIPALE_H
    #define NOMBRE_PERSO_MAX 15
    #define NB_SPACER_FENPRINCIPALE 11

    #include <QtGui>
    #include "Personnage.h"
    #include "FenMAJ.h"
    #include "FenOrdreMarche.h"
    #include "FenAttaque.h"
    #include "Acceuil.h"

    class FenPrincipale : public QMainWindow
    {
        Q_OBJECT
    public:
        FenPrincipale();
        ~FenPrincipale();

    public slots:
        void attaquer();

    private slots:
        void persoModifie();

    // Menu : Fichier
        void creerNouveauPersonnage();
        void creerNouveauGroupe();
        void ajouterPersonnage();
        void ouvrir();
        void enregistrerGroupe();
        void fermerGroupe();

    // Menu : Mode
        void modeAttaque();
        void modePassif();

    // Menu : Modifications sur le groupe
        void xp();
        void PO();
        void PA();
        void PC();
        void po();
        void pa();
        void pc();

    // Menu : Personnage en cours
        void COU();
        void INT();
        void CHA();
        void FO();
        void ATPRD();
        void EV();
        void EA();

    // Menu : Affichage
        void afficherFichier(bool affiche);
        void afficherAction(bool affiche);
        void afficherAchat(bool affiche);
        void afficherNotes(bool affiche);
        void afficherOrdreMarche(bool affiche);

    // Menu : ?
        void aProposDeNBH();
        void licence();
        void MAJ();
        void help();

    protected:
        void closeEvent(QCloseEvent *e);

    private:
        void initMenus_ToolBars();
        void initWidget();

        void enregistrerNotes();
        void enregistrerTout();
        void enregistrerPref();

    // Pour le programme
        QVector<Personnage*> m_personnages;
        QStringList m_nomPersos;

        // Pour le groupe
        QFile *m_fichierGroupe;

        // Pour les notes
        QFile *m_fichierNotes;
        QTextEdit *notes_txt;

        // Affichage
        QMdiArea *zoneCentrale;
            Acceuil *widgetParDefaut;
        QStatusBar *statusBar;
            QProgressBar *progressBar_status;

            // ToolBars
        QToolBar *fichierToolBar;
        QToolBar *actionsToolBar;
        QToolBar *achatToolBar;

            // Docks
        QDockWidget *notes_dock;
        QDockWidget *ordreMarche_dock;
            FenOrdreMarche *ordreMarche;
        QDockWidget *attaque_dock;
            FenAttaque *attaque_fen;

            // Boutons
        QAction *enregistrer;
        QAction *quitterGroupe;

        QAction *attaque;
        QAction *passif;

        QAction *xpGroupe;
        QAction *POGroupe;
        QAction *PAGroupe;
        QAction *PCGroupe;
        QAction *poGroupe;
        QAction *paGroupe;
        QAction *pcGroupe;

        QAction *achatATPRD;
        QAction *achatINT;
        QAction *achatCHA;
        QAction *achatFO;
        QAction *achatCOU;
        QAction *achatEV;
        QAction *achatEA;

        QAction *afficher_fichier;
        QAction *afficher_action;
        QAction *afficher_achat;
        QAction *afficher_notes;
        QAction *afficher_ordreMarche;
    };

    class MdiSubWindow : public QMdiSubWindow
    {
        Q_OBJECT

    public:
        MdiSubWindow();

    protected:
        void closeEvent(QCloseEvent *e);
    };

#endif // FENPRINCIPALE_H
