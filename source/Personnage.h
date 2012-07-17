#ifndef PERSONNAGE_H
    #define PERSONNAGE_H

    #include <QScrollArea>

    namespace Ui {
        class Personnage;
    }

    class Personnage : public QScrollArea
    {
        Q_OBJECT

    public:
        explicit Personnage(QString nom);
        ~Personnage();

    private slots:
        void on_nomEdit_clicked(bool checked);

    private:
        Ui::Personnage *ui;

        QString m_nom;
    };

#endif // PERSONNAGE_H
