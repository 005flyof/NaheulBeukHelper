#ifndef FENCHARGEMENT_H
    #define FENCHARGEMENT_H

    #include <QtGui>
    #include "FenPrincipale.h"

    namespace Ui {
        class FenChargement;
    }

    class FenChargement : public QDialog
    {
        Q_OBJECT

    public:
        explicit FenChargement(char *argv[]);
        ~FenChargement();

        void ouvrirOrigines();
        void ouvrirMetiers();

    private:
        Ui::FenChargement *ui;

        FenPrincipale *fenetrePrincipale;

        // Variables
        QVector<Metier*> metiers;
        QVector<Origine*> origines;
    };

#endif // FENCHARGEMENT_H
