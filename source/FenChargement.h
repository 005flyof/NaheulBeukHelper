#ifndef FENCHARGEMENT_H
    #define FENCHARGEMENT_H

    #include <QtGui>

//#include "FenPrincipale.h"

    #include "Personnage.h"

    namespace Ui {
        class FenChargement;
    }

    class FenChargement : public QDialog
    {
        Q_OBJECT

    public:
        explicit FenChargement(char *argv[]);
        ~FenChargement();
/*
        void ouvrirOrigines();
        void ouvrirMetiers();*/

    private:
        Ui::FenChargement *ui;

        /*FenPrincipale *fenetrePrincipale;
        QMap<QString, Origine*> m_origines;
        QMap<QString, Metier*> m_metiers;*/
    };

#endif // FENCHARGEMENT_H
