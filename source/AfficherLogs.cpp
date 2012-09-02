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

#include "AfficherLogs.h"
#include "ui_AfficherLogs.h"

AfficherLogs::AfficherLogs(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AfficherLogs)
{
    ui->setupUi(this);

    QFile fichierLog("nbh.log");
    if (!fichierLog.open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Erreur lors de l'ouverture du fichier log");

    QTextStream entree(&fichierLog);

    ui->logs->setText(entree.readAll());
}

AfficherLogs::~AfficherLogs()
{
    delete ui;
}
