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

        void chargerPerso();
        void enregistrerPerso();

    private slots:
        void on_nomEdit_clicked(bool checked);
        void on_sexeEdit_clicked(bool checked);

    private:
        Ui::Personnage *ui;

        // Fonctions
        void setAffichage();
        Caracteristiques chargerCarac(QString ligne, bool AT_PRD, int numLigne);
        void viderVariables();

        // Pour le programme
        QFile *m_fichierPerso;
        QString m_cheminEnregistrement;

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
