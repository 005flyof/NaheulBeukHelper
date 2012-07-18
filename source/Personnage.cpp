#include "Personnage.h"
#include "ui_Personnage.h"

Personnage::Personnage(QString nom)
    : QScrollArea(), ui(new Ui::Personnage),
      m_cheminEnregistrement(), m_nom(nom)
{
    ui->setupUi(this);
    setAffichage();
}
Personnage::~Personnage()
{
    delete ui;
}

void Personnage::setAffichage()
{
    ui->nom->setText(m_nom);
    ui->sexe->setText(m_sexe);
}

void Personnage::on_nomEdit_clicked(bool checked)
{
    if (!checked)
        m_nom = ui->nom->text();
    else
        ui->nom->setText(m_nom);

    ui->nom->setEnabled(checked);
}
void Personnage::on_sexeEdit_clicked(bool checked)
{
    if (!checked)
        m_sexe = ui->sexe->text();
    else
        ui->sexe->setText(m_sexe);

    ui->sexe->setEnabled(checked);
}
