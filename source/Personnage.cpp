#include "Personnage.h"
#include "ui_Personnage.h"

Personnage::Personnage(QString nom)
    : QScrollArea(), ui(new Ui::Personnage),
      m_nom(nom)
{
    ui->setupUi(this);
    ui->nom->setText(m_nom);
}

Personnage::~Personnage()
{
    delete ui;
}

void Personnage::on_nomEdit_clicked(bool checked)
{
    ui->nom->setEnabled(checked);
    if (!checked)
        m_nom = ui->nom->text();
    else
        ui->nom->setText(m_nom);
}
