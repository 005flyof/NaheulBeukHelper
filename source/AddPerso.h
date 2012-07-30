#ifndef ADDPERSO_H
    #define ADDPERSO_H

    #include <QDialog>
    #include <QFile>

    #include "FenMAJ.h"
    #include "fonctions_diverses.h"
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class AddPerso;
    }

    class AddPerso : public QDialog
    {
        Q_OBJECT

    public:
        explicit AddPerso(QWidget *parent = 0);
        ~AddPerso();

    private slots:
        void on_buttonBox_accepted();

    private:
        Ui::AddPerso *ui;
    };

#endif // ADDPERSO_H
