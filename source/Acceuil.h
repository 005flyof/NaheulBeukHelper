#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <QScrollArea>

namespace Ui {
class Acceuil;
}

class Acceuil : public QScrollArea
{
    Q_OBJECT

public:
    explicit Acceuil(QString const& version);
    ~Acceuil();

private:
    Ui::Acceuil *ui;
};

#endif // ACCEUIL_H
