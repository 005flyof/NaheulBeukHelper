#ifndef PERSONNAGE_H
    #define PERSONNAGE_H

    #include <QScrollArea>
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class Personnage;
    }

    #define MAX_PROTECTION 6
    #define MAX_ARME 4
    #define MAX_FLECHE 5
    #define MAX_VETEMENT 5
    #define MAX_EQUIPEMENT 10


    class Personnage : public QScrollArea
    {
        Q_OBJECT

    public:
        explicit Personnage(QString fichier);
        ~Personnage();

        bool chargerPerso();
        void enregistrerPerso();

        // Accesseurs
        QString getNom() const;
        bool getModif() const;

    signals:
        void persoModifie();

    public slots:
        void ajouterXP(int value = 0);
        void ajouterPO(int value = 0);
        void retirerPO(int value = 0);
        void ajouterPA(int value = 0);
        void retirerPA(int value = 0);
        void ajouterPC(int value = 0);
        void retirerPC(int value = 0);

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

        // Caractéristiques
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

    private:
        Ui::Personnage *ui;

    // Fonctions
        Caracteristiques chargerCarac(bool *erreur, QString ligne, bool AT_PRD, int numLigne);

        bool setNiveau();
        void setAffichage();
        void viderVariables();

        void rafraichirRichesses();

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
        Fleche *m_fleches[MAX_FLECHE];

        QVector<Competence*> m_competences;
    };

#endif // PERSONNAGE_H
