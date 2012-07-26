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

    class FenPrincipale : public QMainWindow
    {
        Q_OBJECT
    public:
        FenPrincipale();
        ~FenPrincipale();

    public slots:
        void creerNouveauPersonnage();
        void creerNouveauGroupe();
        void ajouterPersonnage();
        void ouvrir();
        void enregistrerGroupe();
        void fermerGroupe();

        void modeAttaque();
        void modePassif();

        void attaquer();

        void xp();
        void PO();
        void PA();
        void PC();
        void po();
        void pa();
        void pc();

        /*void ATPRD();
        void INT();
        void CHA();
        void FO();
        void COU();
        void EV();
        void EA();*/

        void afficherFichier(bool affiche);
        void afficherAction(bool affiche);
        void afficherAchat(bool affiche);

        void aProposDeNBH();
        void licence();
        void MAJ();
        void help();

    private slots:
        void persoModifie();

    protected:
        void closeEvent(QCloseEvent *e);

    private:
        void initMenus_ToolBars();
        void initWidget();

        void enregistrerNotes();
        void enregistrerTout();

        // ToolBars
        QToolBar *fichierToolBar;
        QToolBar *actionsToolBar;
        QToolBar *achatToolBar;

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
        QStatusBar *statusBar;
            QProgressBar *progressBar_status;

            // Docks
            FenOrdreMarche *ordreMarche;
            FenAttaque *attaque_fen;
            QDockWidget *attaque_dock;
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
