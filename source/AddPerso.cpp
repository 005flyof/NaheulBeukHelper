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

#include "AddPerso.h"
#include "ui_AddPerso.h"

AddPerso::AddPerso(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddPerso)
{
    ui->setupUi(this);
}

AddPerso::~AddPerso()
{
    delete ui;
}

void AddPerso::on_buttonBox_accepted()
{
// On demande où enregistrer le fichier
    QString chemin = QFileDialog::getSaveFileName(this, "Enregistrer un personnage",
                                                       QString("enregistrements"), "Personnages (*.perso)");
    if (chemin.isEmpty())
        return;

    if (OS == 0)
        chemin.replace("/", "\\");

// On crée l'enregistrement
    QString total = "~!AddPerso!~\n";

    total += ui->nom->text() + "\n";
    total += ui->sexe->text() + "\n";
    total += ui->origine->text() + "\n";
    total += ui->metier->text() + "\n";
    total += QString::number(ui->ev->value()) + "\n";
    total += QString::number(ui->destin->value()) + "\n";
    total += QString::number(ui->xp->value()) + "\n";
    total += Caracteristiques(ui->courage->value(),
                              ui->intelligence->value(),
                              ui->charisme->value(),
                              ui->adresse->value(),
                              ui->force->value(),
                              ui->attaque->value(),
                              ui->parade->value()).caracEnregistrement() + "\n";
    total += Caracteristiques(ui->courage->value(),
                              ui->intelligence->value(),
                              ui->charisme->value(),
                              ui->adresse->value(),
                              ui->force->value(),
                              ui->attaque->value(),
                              ui->parade->value()).caracEnregistrement() + "\n";

    total += Richesses(ui->po->value(),
                       ui->pa->value(),
                       ui->pc->value()).richessesEnregistrement() + "\n";

    if (ui->magieGroup->isChecked())
        total += "~!magie!~\n" + QString::number(ui->EA->value()) + "\n" + ui->typeEA->text() + "\n";

    total += "~!FIN_ENREGISTREMENT!~";

// On enregistre
    QFile *m_fichierPerso = new QFile(chemin);
    if (!m_fichierPerso->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        error("Impossible d'enregistrer le fichier de personnage sélectionné.\n"
              "Ceci peut être dû aux permissions du fichier : il n'est pas accessible.");
        return;
    }

    QTextStream sortie(m_fichierPerso);

    sortie << total;

    m_fichierPerso->close();

// On modifie le groupe
    bool erreur(false);
    QString cheminGroupe;
    while (!erreur)
    {
        cheminGroupe = QFileDialog::getOpenFileName(this, "Modifier un groupe",
                                                    QString("enregistrements"), "Groupes de personnages (*.nbh)");

        if (cheminGroupe.isEmpty())
            QMessageBox::critical(this, "ERREUR !", "Erreur :\nVous devez choisir un groupe à modifier !");
        else
            erreur = true;
    }

    if (OS == 0)
        cheminGroupe.replace("/", "\\");

    QFile groupeRec(cheminGroupe);
    if (!groupeRec.open(QIODevice::Append | QIODevice::Text))
    {
        error("Impossible d'ouvrir le fichier de groupe sélectionné. Réessayez d'ajouter le personnage au groupe.\n"
              "Ceci peut être dû aux permissions du fichier : il n'est pas accessible.");
        return;
    }

    QTextStream groupe(&groupeRec);

    groupe << chemin.remove(QCoreApplication::applicationDirPath()) + "\n";

    log("'" + ui->nom->text() + "' a été ajouté à un groupe !");
    QMessageBox::information(this, "Chargement du personnage",
                             "Vous venez de créer un personnage lisible par NaheulBeuk Helper.\n\n"
                             "Si vous avez déjà ouvert le groupe modifié,"
                             "pour que les modifications soient appliquées, il faut recharger le groupe !");
}
