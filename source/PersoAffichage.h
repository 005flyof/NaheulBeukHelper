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

#ifndef PERSOAFFICHAGE_H
    #define PERSOAFFICHAGE_H

    #include <QtGui>
    #include "ClassePourPersonnage.h"
    #include "CheckBox.h"

    #define MAX_VETEMENT 5
    #define MAX_EQUIPEMENT 10
    #define MAX_PROTECTION 6
    #define MAX_ARME 4
    #define MAX_FLECHE 5
    #define NB_SPACER 2

    #define PAS_ARME "A mains nues"
    #define PAS_PROTECTION "Pas de protection"
    #define PAS_VETEMENT "Nu"
    #define PAS_FLECHE "Pas de flèche"
    #define PAS_EQUIPEMENTS "Pas d'équipement"

    class Personnage : private QTabWidget
    {
        Q_OBJECT
    public:
        Personnage(Personnage const& b);
        Personnage(QString nom = "Sans nom !", QString sexe = "Sexe non défini !",
                   QString nomOrigine = "Sans Origine ?", QString nomMetier = "Sans métier ?",
                   int cou = 8, int intel = 8, int cha = 8, int ad = 8, int fo = 8, int at = 0, int prd = 0,
                   int cou_modif = 8, int intel_modif = 8, int cha_modif = 8, int ad_modif = 8, int fo_modif = 8,
                   int at_modif = 0, int prd_modif = 0,
                   int ptsDestin = 0, int xp = 0, int ev = 0,
                   int OR = 0, int ARGENT = 0, int CUIVRE = 0);
        ~Personnage();
        Personnage& operator=(Personnage const& b);

        // Appliquer origine / métier
        void setOrigine(Origine& a);
        void setMetier(Metier& a);

        // Calculer niveau
        bool setNiveau();

        // Initialiser valeurs d'EA
        void setEA(int EA, QString typeEA);

        // Appliquer une adresse de fichier
        void setAdresse(QString const& adresse);

        // Appliquer des équipements lors de l'ouverture
        void addProtection(Protection *protectionAAjouter, int num);
        void addArme(Arme *armeAAjouter, int num);
        void addVetement(Vetement *VetementAAjouter, int num);
        void addFleche(Fleche *flecheAAjouter, int num);
        void addEquipement(QString nom, int num);

        // Pour afficher
        QTabWidget* afficher();
        QTabWidget* getAffichage();
        QString getNom() const;
        void rafraichir();

        // !!
        void setBonus_Malus_caracSup_Inf_moyenne(int degatsBonus = 0, int bonusAttaque = 0, int bonusParade = 0, int degatsBonusSorts = 0);

        // Achat
        void achatATPRD();
        void achatINT();
        void achatCHA();
        void achatFO();
        void achatCOU();
        void achatEV();
        void achatEA();

        // Récupérer adresse du fichier
        QString getAdresse() const;

        // Enregistrer
        QString getPersoEntier() const;

        // Tester origine / métier
        bool testOrigine(Origine const& a);
        bool testMetier(Metier const& a);

    public slots:
        void plus_xp(int value = 0);
        void moins_destin();

        void plus_cou();
        void plus_int();
        void plus_cha();
        void plus_ad();
        void plus_fo();
        void plus_at();
        void plus_prd();

        void plus_ev();
        void plus_ea();

        void plus_po(int value = 0);
        void plus_pa(int value = 0);
        void plus_pc(int value = 0);

        void moins_cou();
        void moins_int();
        void moins_cha();
        void moins_ad();
        void moins_fo();
        void moins_at();
        void moins_prd();

        void moins_ev();
        void moins_ea();

        void moins_po(int value = 0);
        void moins_pa(int value = 0);
        void moins_pc(int value = 0);

        void setCaracModif_Affichage();

        void conversionPAPC_PO();
        void conversionPO_PA();
        void conversionPO_PC();
        void conversionPA_PC();

        void addCompetence(QString nom = "", QString description = "");
        void addCompetence2();

        void attaquer();

    private:
        // Fonctions
        void afficherCompetences(bool nouvelleCompetence = false);

        void ongletsEquip();
        void ongletsCarac();

        // bonus
        int m_degatsBonus;
        int m_attaqueBonus;
        int m_paradeBonus;
        int m_degatsBonusSorts;

        QLineEdit *carac_degatsBonus;
        QLineEdit *carac_attaqueBonus;
        QLineEdit *carac_paradeBonus;
        QLineEdit *carac_degatsBonusSorts;

        // Le reste
        QSpacerItem *spacer[NB_SPACER];
        QGroupBox *armement, *fleche;

        // Boutons
        QPushButton *XP_plus;
        QPushButton *ptsDeDestin_moins;
        QPushButton *EV_plus, *EV_moins;
        QPushButton *COU_plus, *COU_moins;
        QPushButton *INT_plus, *INT_moins;
        QPushButton *CHA_plus, *CHA_moins;
        QPushButton *AD_plus, *AD_moins;
        QPushButton *FO_plus, *FO_moins;
        QPushButton *AT_plus, *AT_moins;
        QPushButton *PRD_plus, *PRD_moins;
        QPushButton *PO_plus, *PO_moins;
        QPushButton *PA_plus, *PA_moins;
        QPushButton *PC_plus, *PC_moins;
        QPushButton *EA_plus, *EA_moins;

        QPushButton *erreur;

        // Lignes d'édition
        QLineEdit *XP;
        QLineEdit *level;
        QLineEdit *ptsDeDestin;
        QLineEdit *EV, *EV_modif;
        QLineEdit *magieResist, *magiePhys, *magiePsy;
        QLineEdit *COU, *COU_modif;
        QLineEdit *INT, *INT_modif;
        QLineEdit *CHA, *CHA_modif;
        QLineEdit *AD, *AD_modif;
        QLineEdit *FO, *FO_modif;
        QLineEdit *AT, *AT_modif;
        QLineEdit *PRD, *PRD_modif;
        QLineEdit *EA, *EA_modif;
        QLineEdit *typeEA;
        QLineEdit *PO, *PA, *PC;

        // CheckBox pour savoir si équipement
        CheckBox *vetement_check[MAX_VETEMENT];
        QLabel *vetement_type[MAX_VETEMENT];
        QLabel *vetement_nom[MAX_VETEMENT];
        QLabel *vetement_bonus[MAX_VETEMENT];
        QLabel *vetement_malus[MAX_VETEMENT];
        QPushButton *vetement_modif[MAX_VETEMENT];

        int m_totalProtection;
        QLabel *prTotale;

        CheckBox *protection_check[MAX_PROTECTION];
        QLabel *protection_nom[MAX_PROTECTION];
        QLabel *protection_PR[MAX_PROTECTION];
        QLabel *protection_bonus[MAX_PROTECTION];
        QLabel *protection_malus[MAX_PROTECTION];
        QPushButton *protection_modif[MAX_PROTECTION];

        CheckBox *arme_check[MAX_ARME];
        QLabel *armement_num[MAX_ARME];
        QLabel *armement_nom[MAX_ARME];
        QLabel *armement_degats[MAX_ARME];
        QLabel *armement_bonus[MAX_ARME];
        QLabel *armement_malus[MAX_ARME];
        QPushButton *armement_modif[MAX_ARME];

        CheckBox *fleche_check[MAX_FLECHE];
        QLineEdit *fleche_nombre[MAX_FLECHE];
        QPushButton *fleche_plus[MAX_FLECHE], *fleche_moins[MAX_FLECHE];
        QLabel *fleche_nom[MAX_FLECHE];
        QLabel *fleche_bonus[MAX_FLECHE];
        QPushButton *fleche_modif[MAX_FLECHE];

        CheckBox *equipement_check[MAX_EQUIPEMENT];
        QLabel *equipement_num[MAX_EQUIPEMENT];
        QTextEdit *equipement_nom[MAX_EQUIPEMENT];
        QPushButton *equipement_modif[MAX_EQUIPEMENT];
    };

#endif // PERSOAFFICHAGE_H
