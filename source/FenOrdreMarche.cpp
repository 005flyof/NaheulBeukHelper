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

#include "FenOrdreMarche.h"

FenOrdreMarche::FenOrdreMarche(QStringList const& nomPersos)
    : QWidget(), nomPersonnages(nomPersos)
{
// Boutons
    haut = new QPushButton();
        haut->setIcon(QIcon(":prog-data/img/fleche_haut.png"));
        haut->setEnabled(false);
    haut1 = new QPushButton();
        haut1->setIcon(QIcon(":prog-data/img/fleche_haut-1.png"));
        haut1->setEnabled(false);
    bas1 = new QPushButton();
        bas1->setIcon(QIcon(":prog-data/img/fleche_bas-1.png"));
        bas1->setEnabled(false);
    bas = new QPushButton();
        bas->setIcon(QIcon(":prog-data/img/fleche_bas.png"));
        bas->setEnabled(false);

    QVBoxLayout *layout_boutons = new QVBoxLayout();
        layout_boutons->addWidget(haut);
        layout_boutons->addWidget(haut1);
        layout_boutons->addWidget(bas1);
        layout_boutons->addWidget(bas);

    QObject::connect(haut, SIGNAL(clicked()), this, SLOT(monter()));
    QObject::connect(haut1, SIGNAL(clicked()), this, SLOT(monter1()));
    QObject::connect(bas1, SIGNAL(clicked()), this, SLOT(descendre1()));
    QObject::connect(bas, SIGNAL(clicked()), this, SLOT(descendre()));

// Modèle
    modele = new QStringListModel(nomPersonnages);
        QObject::connect(modele, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(recharger()));

// Vue
    vue = new QListView();
    vue->setModel(modele);

    QObject::connect(vue, SIGNAL(clicked(QModelIndex)), this, SLOT(select(QModelIndex)));
    QObject::connect(this, SIGNAL(verrouiller()), this, SLOT(verrouillerBoutons()));

    QHBoxLayout *layout_hor = new QHBoxLayout();
        layout_hor->addWidget(vue);
        layout_hor->addLayout(layout_boutons);

    setLayout(layout_hor);
}

void FenOrdreMarche::select(QModelIndex index)
{
    if (!index.isValid())
    {
        haut->setEnabled(false);
        haut1->setEnabled(false);
        bas1->setEnabled(false);
        bas->setEnabled(false);
    }
    else
    {
        if (vue->currentIndex().row() == 0)
        {
            haut->setEnabled(false);
            haut1->setEnabled(false);
            bas1->setEnabled(true);
            bas->setEnabled(true);
        }
        else if (vue->currentIndex().row() == (nomPersonnages.count() - 1))
        {
            haut->setEnabled(true);
            haut1->setEnabled(true);
            bas1->setEnabled(false);
            bas->setEnabled(false);
        }
        else
        {
            haut->setEnabled(true);
            haut1->setEnabled(true);
            bas1->setEnabled(true);
            bas->setEnabled(true);
        }
    }
}
void FenOrdreMarche::verrouillerBoutons()
{
    haut->setEnabled(false);
    haut1->setEnabled(false);
    bas1->setEnabled(false);
    bas->setEnabled(false);
}

void FenOrdreMarche::monter()
{
    if (vue->currentIndex().isValid())
        nomPersonnages.move(vue->currentIndex().row(), 0);

    modele->setStringList(nomPersonnages);

    emit verrouiller();
}
void FenOrdreMarche::monter1()
{
    if (vue->currentIndex().isValid() && vue->currentIndex().row() != 0)
        nomPersonnages.move(vue->currentIndex().row(), (vue->currentIndex().row() - 1));

    modele->setStringList(nomPersonnages);

    emit verrouiller();
}
void FenOrdreMarche::descendre1()
{
    if (vue->currentIndex().isValid() && vue->currentIndex().row() < (nomPersonnages.count() - 1))
        nomPersonnages.move(vue->currentIndex().row(), (vue->currentIndex().row() + 1));

    modele->setStringList(nomPersonnages);

    emit verrouiller();
}
void FenOrdreMarche::descendre()
{
    if (vue->currentIndex().isValid())
        nomPersonnages.move(vue->currentIndex().row(), nomPersonnages.count() - 1);

    modele->setStringList(nomPersonnages);

    emit verrouiller();
}

void FenOrdreMarche::setNomPersos(QStringList const& nomPersos)
{
    nomPersonnages = nomPersos;
    modele->setStringList(nomPersonnages);

    emit verrouiller();
}

void FenOrdreMarche::recharger()
{
    modele->setStringList(nomPersonnages);
}
