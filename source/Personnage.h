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

#ifndef PERSONNAGE_H
    #define PERSONNAGE_H

    #include "ClassePourPersonnage.h"

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

    class Personnage
    {
    public:
        Personnage(QString nom = "Sans nom !", QString sexe = "Sexe non défini !",
                   QString nomOrigine = "Sans Origine ?", QString nomMetier = "Sans métier ?",
                   int cou = 8, int intel = 8, int cha = 8, int ad = 8, int fo = 8, int at = 0, int prd = 0,
                   int cou_modif = 8, int intel_modif = 8, int cha_modif = 8, int ad_modif = 8, int fo_modif = 8, int at_modif = 0, int prd_modif = 0,
                   int ptsDestin = 0, int xp = 0, int ev = 0,
                   int OR = 0, int ARGENT = 0, int CUIVRE = 0);

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
        int m_totalProtection;

        QString m_adresseFichierPerso;

        QString m_nomPerso;
        QString m_sexePerso;

        QString m_originePersonnage;
        QString m_metierPersonnage;

        int m_energieVitale, m_energieVitale_modif;
        int m_energieAstrale, m_energieAstrale_modif;
        QString typeEnergieAstrale;
        bool presenceEnergieAstrale;

        Caracteristiques m_caracInitiales;
        Caracteristiques m_caracModifiees;

        int m_pointsDestin;
        int m_niveau;
        int m_experience;
        Richesses *m_pieces;

        Vetement *m_vetements[MAX_VETEMENT];
        QString *m_equipements[MAX_EQUIPEMENT];

        Protection *m_protections[MAX_PROTECTION];

        Arme *m_armes[MAX_ARME];
        Fleche *m_fleches[MAX_FLECHE];

        QVector<Competence *> m_competences;


        // Pas besoin pour le MJ ????
//      std::vector<QString> machinPrecieux;
//		std::vector<QString> bouffeEtBoisson;
//		std::vector<QString> butin;
//		Potions_Poisons *potions[5];
//		Potions_Poisons *poisons[5];
//		ObjetSpecial *objetsSpeciaux[10];
    };

#endif // PERSONNAGE_H
