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
    #include "Monstre.h"

    class FenPrincipale : public QMainWindow
    {
        Q_OBJECT
    public:
        FenPrincipale();
        ~FenPrincipale();

    public slots:
        void creerNouveauPersonnage();
        void creerNouveauPersonnage_close();
        void creerNouveauPersonnage_Origine();
        void creerNouveauPersonnage_Origine_close();
        void creerNouveauPersonnage_Metier();
        void creerNouveauPersonnage_Metier_close();
        void creerNouveauPersonnage_Set();
        void creerNouveauGroupe();
        void ajouterPersonnage();
        void ajouterPersonnage_Save();
        void ouvrir();
        void enregistrerTout();
        void fermerGroupe();
        void fermerOnglets();
        void quitterNBH();

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

        void ATPRD();
        void INT();
        void CHA();
        void FO();
        void COU();
        void EV();
        void EA();

        void afficherFichier(bool affiche);
        void afficherAction(bool affiche);
        void afficherAchat(bool affiche);

        void aProposDeNBH();
        void licence();
        void MAJ();
        void help();

        bool testOuverture(QString const& cheminFichier);

    protected:
        void closeEvent(QCloseEvent *e);

    private:
        void initMenus_ToolBars();
        void initWidget();

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

        // Pour les blagues
        QPushButton *merci, *ohNon;

        // Nécessaire partout
        QString noteAdresse;
        QTextEdit *notes_txt;
        QTabWidget *monstres;
        FenOrdreMarche *ordreMarche;
        FenAttaque *attaque_fen;
        QDockWidget *attaque_dock;

        int compteurOnglets;
        QMdiArea *zoneCentrale;
        QStatusBar *statusBar;
            QProgressBar *progressBar_status;

        QMap<QString, Personnage> tableauDePersonnages;
        QList<QString> fichiersOuverts;
        QStringList nomPersoOuverts;

        QSpacerItem *spacer[NB_SPACER_FENPRINCIPALE];

        // Pour la création d'un nouveau personnage
        QDialog *nouveau_fenetre, *nouveau_fenetre2, *nouveau_fenetre3;

        QMap<QString, Origine> tableauDOrigines;
        QVector<QRadioButton*> tableauDeRadioButton_Origine;

        QMap<QString, Metier> tableauDeMetiers;
        QVector<QRadioButton*> tableauDeRadioButton_Metier;

        QLineEdit *nouveau_nom;
        QLineEdit *nouveau_sexe;

        QSpinBox *nouveau_ptsDestin;
        QSpinBox *nouveau_PO;

        QSpinBox *nouveau_COU;
        QSpinBox *nouveau_INT;
        QSpinBox *nouveau_CHA;
        QSpinBox *nouveau_AD;
        QSpinBox *nouveau_FO;

        // Pour ajouter un personnage
        QDialog *ajouter_fenetre;

        QLineEdit *ajouter_nom;
        QLineEdit *ajouter_sexe;
        QLineEdit *ajouter_origineNom;
        QLineEdit *ajouter_metierNom;

        QSpinBox *ajouter_COU;
        QSpinBox *ajouter_INT;
        QSpinBox *ajouter_CHA;
        QSpinBox *ajouter_AD;
        QSpinBox *ajouter_FO;
        QSpinBox *ajouter_AT;
        QSpinBox *ajouter_PRD;

        QSpinBox *ajouter_XP;
        QSpinBox *ajouter_ptsDestin;

        QSpinBox *ajouter_EV;
        QSpinBox *ajouter_EA;
        QLineEdit *ajouter_EA_type;

        QSpinBox *ajouter_PO;
        QSpinBox *ajouter_PA;
        QSpinBox *ajouter_PC;

        // Pour ajouter un équipement
        QDialog *fen;
        QLineEdit *nom;
        QSpinBox *prix;
        QSpinBox *des;
        QSpinBox *degats;

        QSpinBox *COU_;
        QSpinBox *INT_;
        QSpinBox *CHA_;
        QSpinBox *AD_;
        QSpinBox *FO_;
        QSpinBox *AT_;
        QSpinBox *PRD_;

        QSpinBox *cou_;
        QSpinBox *intel_;
        QSpinBox *cha_;
        QSpinBox *ad_;
        QSpinBox *fo_;
        QSpinBox *at_;
        QSpinBox *prd_;
        QComboBox *type_;

        // Pour l'ouverture
        QString groupeAdresse;
        int lecteurLigne;
        int lecteurTableauProtection, lecteurTableauArme, lecteurTableauFleche, lecteurTableauEquipement;

        int ouvertureEV, ouverturePtsDestin, ouvertureXP;
        int ouverturePO, ouverturePA, ouverturePC;
        int ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO, ouverture_AT, ouverture_PRD;
        int ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo, ouverture_at, ouverture_prd;

        QString ouvertureNom, ouvertureSexe, ouvertureNomOrigine, ouvertureNomMetier;
        Vetement *ouverture_VETEMENT;
        Protection *ouverture_PROTECTION;
        Arme *ouverture_ARME;
        Fleche *ouverture_FLECHE;
        QString ouverture_EQUIPEMENT;
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
