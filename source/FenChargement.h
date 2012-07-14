#ifndef FENCHARGEMENT_H
    #define FENCHARGEMENT_H

    #include <QtGui>

    namespace Ui {
    class FenChargement;
    }

    class FenChargement : public QDialog
    {
        Q_OBJECT

    public:
        explicit FenChargement(char *argv[]);
        ~FenChargement();

    private:
        Ui::FenChargement *ui;
    };

#endif // FENCHARGEMENT_H
