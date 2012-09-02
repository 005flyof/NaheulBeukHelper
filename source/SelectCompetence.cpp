/*
    Copyright (C) 2011 Florent FAYOLLAS

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "SelectCompetence.h"
#include "ui_SelectCompetence.h"

SelectCompetence::SelectCompetence(QVector<Competence *> value, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SelectCompetence)
{
    ui->setupUi(this);


    competences = value;

    QVBoxLayout *layout = new QVBoxLayout;

    for (int i(0); i < competences.count(); i++)
    {
        QRadioButton *temp = new QRadioButton(competences.at(i)->getNom());
        temp->setWhatsThis(competences.at(i)->getDescription());

        layout->addWidget(temp);

        tableauBouttons.push_back(temp);
    }

    ui->scrollWidgetContents->setLayout(layout);
}
SelectCompetence::SelectCompetence(QVector<Competence *> value, bool plsChoix, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SelectCompetence)
{
    ui->setupUi(this);


    competences = value;

    QVBoxLayout *layout = new QVBoxLayout;

    for (int i(0); i < competences.count(); i++)
    {
        QCheckBox *temp = new QCheckBox(competences.at(i)->getNom());
        temp->setWhatsThis(competences.at(i)->getDescription());

        layout->addWidget(temp);

        tableauBouttons.push_back(temp);
    }

    ui->scrollWidgetContents->setLayout(layout);
}
SelectCompetence::~SelectCompetence()
{
    delete ui;
}


QString SelectCompetence::getChoix()
{
    for (int i(0); i < tableauBouttons.count(); i++)
    {
        if (tableauBouttons.at(i)->isChecked())
            return tableauBouttons.at(i)->text();
    }
    return "";
}
QStringList SelectCompetence::getChoix(bool plsChoix)
{
    QStringList liste;
    for (int i(0); i < tableauBouttons.count(); i++)
    {
        if (tableauBouttons.at(i)->isChecked())
            liste << tableauBouttons.at(i)->text();
    }
    return liste;
}
