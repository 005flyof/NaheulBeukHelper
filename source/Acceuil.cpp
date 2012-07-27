#include "Acceuil.h"
#include "ui_Acceuil.h"

Acceuil::Acceuil(QString const& version)
    : QScrollArea(),
      ui(new Ui::Acceuil)
{
    ui->setupUi(this);
    ui->version->setText(version);
}

Acceuil::~Acceuil()
{
    delete ui;
}
