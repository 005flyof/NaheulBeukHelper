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

#include "SearchCompetence.h"
#include "ui_SearchCompetence.h"

SearchCompetence::SearchCompetence(QVector<Personnage *> tab, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SearchCompetence),
      personnages(tab)
{
    ui->setupUi(this);
}

SearchCompetence::~SearchCompetence()
{
    delete ui;
}


void SearchCompetence::on_closeBoutton_clicked()
{
    accept();
}
void SearchCompetence::on_search_clicked()
{
// On cheche dans les noms et les descriptions
    if (ui->nomCheck->isChecked() && ui->descriptionCheck->isChecked()
            && ui->terme->text() != "")
        chercher(true, true);
// On cherche dans les noms
    else if (ui->nomCheck->isChecked() && !ui->descriptionCheck->isChecked()
             && ui->terme->text() != "")
        chercher(true, false);
// On cherche dans les descriptions
    else if (!ui->nomCheck->isChecked() && ui->descriptionCheck->isChecked()
             && ui->terme->text() != "")
        chercher(false, true);
// On ne peut pas chercher
    else
        QMessageBox::critical(this, "Impossible d'effectuer la recherche !",
                              "ERREUR :\n\n"
                              "Impossible d'effectuer la recherche :\n"
                              "Pas de mode de recherche sélectionné ou pas de terme à chercher !");
}

void SearchCompetence::chercher(bool nom, bool description)
{
    QMap<QString, Competence*> resultats;
    int compteurOccurences(0);

    if (nom)
        for (int i(0); i < personnages.count(); i++)
            for (int j(0); j < personnages.at(i)->getCompetence().count(); j++)
                if (personnages.at(i)->getCompetence().at(j)->getNom().contains(ui->terme->text().toLower())                // en minuscules
                        || personnages.at(i)->getCompetence().at(j)->getNom().contains(ui->terme->text().toUpper())         // en maj
                        || personnages.at(i)->getCompetence().at(j)->getNom().contains(ui->terme->text()))                  // ce qui est écrit
                {
                    resultats.insert(personnages.at(i)->getNom(), personnages.at(i)->getCompetence().at(j));
                    compteurOccurences++;
                }
    if (description)
        for (int i(0); i < personnages.count(); i++)
            for (int j(0); j < personnages.at(i)->getCompetence().count(); j++)
                if (personnages.at(i)->getCompetence().at(j)->getDescription().contains(ui->terme->text().toLower())                // en minuscules
                        || personnages.at(i)->getCompetence().at(j)->getDescription().contains(ui->terme->text().toUpper())         // en maj
                        || personnages.at(i)->getCompetence().at(j)->getDescription().contains(ui->terme->text()))                  // ce qui est écrit
                {
                    resultats.insert(personnages.at(i)->getNom(), personnages.at(i)->getCompetence().at(j));
                    compteurOccurences++;
                }

    // On affiche
    if (resultats.isEmpty())
    {
        QMessageBox::information(this, "Terme non trouvé",
                                 "Impossible de trouver le terme recherché dans les compétences des personnages du groupe ouvert !");
        return;
    }

    QStandardItemModel *modele = new QStandardItemModel(resultats.count(), 2);
    QStringList header, nomPersos;
    header << "Nom" << "Description";
    modele->setHorizontalHeaderLabels(header);

        int ligne = 0;
    for (QMap<QString, Competence*>::iterator it = resultats.begin();
         it != resultats.end();
         it++)
    {
        nomPersos << it.key();

        Competence *temp = it.value();
        modele->setItem(ligne, 0, new QStandardItem(temp->getNom()));
        modele->setItem(ligne, 1, new QStandardItem(temp->getDescription()));

        ligne++;
    }
    modele->setVerticalHeaderLabels(nomPersos);

    ui->results->setModel(modele);
    ui->results->horizontalHeader()->setStretchLastSection(true);

    ui->label->setText("\"" + ui->terme->text() + "\" -> " + QString::number(compteurOccurences) + " occurences trouvées dans les compétences.");
}
