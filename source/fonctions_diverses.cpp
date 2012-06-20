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

#include <QtGui>
#include "fonctions_diverses.h"

using namespace std;

void setIcone(QWidget* widget)
{
    widget->setWindowIcon(QIcon(":prog-data/img/icone.png"));
}

void fatalError(QString const& message, bool const& logErreur)
{
    QFile error("error.log");

    if (error.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream entree(&error);

        entree << "NBH -> Erreur : " + message << "\n";

        QWidget *a = new QWidget();
        QMessageBox::critical(a, "Erreur fatale",
                              "NBH va �tre ferm� car une erreur fatale a �t� d�cel�e :\n\n" + message);
        if (!logErreur)
            log("Erreur fatale : NBH va �tre ferm� car une erreur fatale a �t� d�cel�e :\n\n" + message);
    }

    exit(2);
}

void log(QString const& message, bool vider)
{
    QFile log("nbh.log");

    if (vider)
    {
        if (!log.open(QIODevice::WriteOnly | QIODevice::Text))
            fatalError("Erreur lors de l'ouverture du fichier log");
    }
    else
    {
        if (!log.open(QIODevice::Append | QIODevice::Text))
            fatalError("Erreur lors de l'ouverture du fichier log");
    }

    QTextStream entree(&log);
    entree << QDate::currentDate().day() << "/" << QDate::currentDate().month() << "/" << QDate::currentDate().year() << " ";
    entree << QTime::currentTime().hour() << ":" << QTime::currentTime().minute() << " -> " << message << "\n";
}
