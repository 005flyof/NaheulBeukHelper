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

    #include <QTabWidget>
    #include "ClassesPourPersonnage.h"
    #include "EquipModif.h"
    #include "SelectCompetence.h"

    namespace Ui {
        class Personnage;
    }

    #define MAX_PROTECTION 6
    #define MAX_ARME 4
    #define MAX_FLECHE 5
    #define MAX_VETEMENT 5
    #define MAX_EQUIPEMENT 10


    class Personnage : public QTabWidget
    {
        Q_OBJECT

    public:
        explicit Personnage(QString fichier);
        ~Personnage();

        bool chargerPerso();
        void enregistrerPerso();

        static Caracteristiques chargerCaracStatic(bool *erreur, QString ligne, bool AT_PRD, int numLigne);

        // Accesseurs
        QString getNom() const;
        bool getModif() const;

        void setCompetencesPossibles(QVector<Competence*> tab);


        // Modifications du perso
        void ajouterXP(int value = 0);

        void ajouterPO(int value = 0);
        void retirerPO(int value = 0);
        void ajouterPA(int value = 0);
        void retirerPA(int value = 0);
        void ajouterPC(int value = 0);
        void retirerPC(int value = 0);

        void achatCOU();
        void achatINT();
        void achatCHA();
        void achatFO();
        void achatATPRD();

        void achatEV();
        void achatEA();

    signals:
        void persoModifie();

    private slots:
        void modifierPerso();

        // Informations générales
        void on_nomEdit_clicked(bool checked);
        void on_sexeEdit_clicked(bool checked);

        void on_xpPlus_clicked();
        void on_destinMoins_clicked();

        // Richesses
        void on_poPlus_clicked();
        void on_poMoins_clicked();
        void on_paPlus_clicked();
        void on_paMoins_clicked();
        void on_pcPlus_clicked();
        void on_pcMoins_clicked();

        void on_conversionPA_et_PC_en_PO_clicked();
        void on_conversionPO_en_PA_clicked();
        void on_conversionPO_en_PC_clicked();
        void on_conversionPA_en_PC_clicked();

        // Protections
        void on_prEdit_1_clicked();
        void on_prEdit_2_clicked();
        void on_prEdit_3_clicked();
        void on_prEdit_4_clicked();
        void on_prEdit_5_clicked();
        void on_prEdit_6_clicked();

        // Armes
        void on_armesEdit_1_clicked();
        void on_armesEdit_2_clicked();
        void on_armesEdit_3_clicked();
        void on_armesEdit_4_clicked();

        // Flèches
        void on_flechesEdit_1_clicked();
        void on_flechesEdit_2_clicked();
        void on_flechesEdit_3_clicked();
        void on_flechesEdit_4_clicked();
        void on_flechesEdit_5_clicked();

        void on_flechesPlus_1_clicked();
        void on_flechesPlus_2_clicked();
        void on_flechesPlus_3_clicked();
        void on_flechesPlus_4_clicked();
        void on_flechesPlus_5_clicked();

        void on_flechesMoins_1_clicked();
        void on_flechesMoins_2_clicked();
        void on_flechesMoins_3_clicked();
        void on_flechesMoins_4_clicked();
        void on_flechesMoins_5_clicked();

        // Vêtements
        void on_vetEdit_1_clicked();
        void on_vetEdit_2_clicked();
        void on_vetEdit_3_clicked();
        void on_vetEdit_4_clicked();
        void on_vetEdit_5_clicked();

        void on_vetVisible_1_clicked(bool checked);
        void on_vetVisible_2_clicked(bool checked);
        void on_vetVisible_3_clicked(bool checked);
        void on_vetVisible_4_clicked(bool checked);
        void on_vetVisible_5_clicked(bool checked);

        // Equipements
        void on_equipsEdit_1_clicked(bool checked);
        void on_equipsEdit_2_clicked(bool checked);
        void on_equipsEdit_3_clicked(bool checked);
        void on_equipsEdit_4_clicked(bool checked);
        void on_equipsEdit_5_clicked(bool checked);
        void on_equipsEdit_6_clicked(bool checked);
        void on_equipsEdit_7_clicked(bool checked);
        void on_equipsEdit_8_clicked(bool checked);
        void on_equipsEdit_9_clicked(bool checked);
        void on_equipsEdit_10_clicked(bool checked);

        // Caractéristiques
        void on_evPlus_clicked();
        void on_evMoins_clicked();
        void on_eaPlus_clicked();
        void on_eaMoins_clicked();

        void on_couPlus_clicked();
        void on_couMoins_clicked();
        void on_intelPlus_clicked();
        void on_intelMoins_clicked();
        void on_chaPlus_clicked();
        void on_chaMoins_clicked();
        void on_adPlus_clicked();
        void on_adMoins_clicked();
        void on_foPlus_clicked();
        void on_foMoins_clicked();
        void on_atPlus_clicked();
        void on_atMoins_clicked();
        void on_prdPlus_clicked();
        void on_prdMoins_clicked();

        void on_remiseAZero_clicked(bool checked);

        void on_addCompetence_clicked();
        void on_addCompetencePerso_clicked();

    private:
        Ui::Personnage *ui;

    // Fonctions
        void viderVariables();
        void viderTousEquipements();
        Caracteristiques chargerCarac(bool *erreur, QString ligne, bool AT_PRD, int numLigne);
        bool setNiveau();

        void setAffichage();
        void rafraichirRichesses();
        void rafraichirCarac();
        void rafraichirProtections();
        void rafraichirArmes();
        void rafraichirFleches();
        void rafraichirVetements();

        void calculerCarac();
        void calculerCaracSupInfMoy();

        void ajouterCompetence();
        void ajouterCompetencePerso();

    // Variables
        // Pour le programme
        QFile *m_fichierPerso;
        QString m_cheminEnregistrement;

        bool modifNonRec;

        // Pour le jeu
        QString m_nom;
        QString m_sexe;
        QString m_origine;
        QString m_metier;

        int m_EV, m_EV_modif;

        bool m_presenceEA;
        int m_EA, m_EA_modif;
        QString m_typeEA;

        Caracteristiques *m_carac;
        Caracteristiques *m_carac_modif;

        int m_ptsDestin;
        int m_niveau;
        int m_experience;

        Richesses *m_richesses;

        Vetement *m_vetements[MAX_VETEMENT];
        QString m_equipements[MAX_EQUIPEMENT];
        Protection *m_protections[MAX_PROTECTION];
            int m_prTotale;
        Arme *m_armes[MAX_ARME];
            int m_AT_modif[MAX_ARME];
            int m_PRD_modif[MAX_ARME];
        Fleche *m_fleches[MAX_FLECHE];

        QVector<Competence*> m_competences;

            // Pour les caractéristiques supérieures et inférieures à la moyenne
        bool m_bonusMalus_carac_calcules;
        bool m_bonusMalus_ATPRD_calcules;

        int m_bonus_degats;
        int m_bonus_degatsMagiques;
        int m_bonus_attaque;
        int m_bonus_parade;

        // Compétences
        QVector<Competence*> competencesPossibles;
    };

#endif // PERSONNAGE_H
