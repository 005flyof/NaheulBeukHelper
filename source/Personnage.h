#ifndef PERSONNAGE_H
    #define PERSONNAGE_H

    #include <QScrollArea>
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class Personnage;
    }
    namespace Perso {
        class Arme;
        class Caracteristiques;
        class Fleche;
        class Metier;
        class Origine;
        class Protection;
        class Richesses;
        class Vetement;

        class Competence;
    }

    class Personnage : public QScrollArea
    {
        Q_OBJECT

    public:
        explicit Personnage(QString nom);
        ~Personnage();

    private slots:
        void on_nomEdit_clicked(bool checked);
        void on_sexeEdit_clicked(bool checked);

    private:
        Ui::Personnage *ui;

        // Fonctions
        void setAffichage();

        // Pour le programme
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

        Perso::Caracteristiques *m_carac;
        Perso::Caracteristiques *m_carac_modif;

        int m_ptsDestin;
        int m_niveau;
        int m_experience;

        Perso::Richesses *m_richesses;

        Perso::Vetement *m_vetements[5];
        QString m_equipements[10];
        Perso::Protection *m_protections[6];
        Perso::Arme *m_armes[4];
        Perso::Fleche *m_fleches[5];

        QVector<Perso::Competence*> m_competences;
    };

#endif // PERSONNAGE_H
