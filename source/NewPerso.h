#ifndef NEWPERSO_H
    #define NEWPERSO_H

    #include <QWizard>
    #include <QFile>

    #include "FenMAJ.h"
    #include "fonctions_diverses.h"
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class NewPerso;
    }

    class NewPerso : public QWizard
    {
        Q_OBJECT

    public:
        explicit NewPerso(QVector<Origine *> const& origines, QVector<Metier *> const& metiers);
        ~NewPerso();

    public slots:
        void accept();

    private slots:
        void changerPage(int id);

    private:
        Ui::NewPerso *ui;

        // Fonctions
        void testOrigines();
        void testMetiers();

        void setOrigine();
        void setMetier();

        // Variables
        QVector<Origine*> m_origines;
            QVector<QRadioButton*> m_originesBouttons;
        QVector<Metier*> m_metiers;
            QVector<QRadioButton*> m_metiersBouttons;

        // Pour le personnage
        QString m_nom;
        QString m_sexe;
        QString m_origine;
        QString m_metier;

        int m_EV;

        bool m_presenceEA;
        int m_EA;
        QString m_typeEA;

        Caracteristiques *m_carac;

        int m_ptsDestin;
        int m_niveau;
        int m_experience;

        Richesses *m_richesses;

        QVector<Competence*> m_competences;
    };

#endif // NEWPERSO_H
