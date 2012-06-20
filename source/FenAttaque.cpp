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

#include "FenAttaque.h"

FenAttaque::FenAttaque(QStringList const& nomPersos, QMainWindow *parent)
    : QWidget(), m_parent(parent), m_nomPersos(nomPersos)
{
// Modèle
    modele = new QStringListModel(m_nomPersos);
        QObject::connect(modele, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(recharger()));

// Vue
    vue = new QListView();
    vue->setModel(modele);

    m_attaquer = new QPushButton("Attaquer !");
        m_attaquer->setEnabled(false);
        QObject::connect(m_attaquer, SIGNAL(clicked()), this, SLOT(attaquer()));

    QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(vue);
        layout->addWidget(m_attaquer);

    setLayout(layout);

// Verrou des boutons
    QObject::connect(vue, SIGNAL(clicked(QModelIndex)), this, SLOT(select(QModelIndex)));
    QObject::connect(m_attaquer, SIGNAL(clicked()), this, SLOT(verrouillerBouton()));
}

void FenAttaque::attaquer()
{
    emit attaque();
}
QString FenAttaque::getNomActivePerso()
{
    return m_nomPersos.at(vue->currentIndex().row());
}

void FenAttaque::setNomPersos(QStringList const& nomPersos)
{
    m_nomPersos = nomPersos;
    modele->setStringList(m_nomPersos);
}

void FenAttaque::select(QModelIndex index)
{
    if (!index.isValid())
        m_attaquer->setEnabled(false);
    else
        m_attaquer->setEnabled(true);
}
void FenAttaque::verrouillerBouton()
{
    m_attaquer->setEnabled(false);
}

void FenAttaque::recharger()
{
    modele->setStringList(m_nomPersos);
}
