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
    }

    QWidget *a = new QWidget();
    QMessageBox::critical(a, "Erreur fatale",
                          "NBH va être fermé car une erreur fatale a été décelée :\n\n" + message);
    if (!logErreur)
        log("Erreur fatale : NBH va être fermé car une erreur fatale a été décelée :\n\n" + message);

    exit(2);
}
void error(QString const& message)
{
    QFile error("error.log");

    if (error.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream entree(&error);

        entree << "NBH -> Erreur : " + message << "\n";

        QWidget *a = new QWidget();
        QMessageBox::critical(a, "Erreur mineure",
                              "NBH a rencontré une erreur :\n\n" + message);
        log("Erreur mineure : NBH a rencontré une erreur :\n\n" + message);
    }
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
    // si le nombre de minute est inf à 10
    if (QTime::currentTime().minute() < 10)
    {
        if (QDate::currentDate().month() < 10)
            entree << QDate::currentDate().day() << "/0" << QDate::currentDate().month() << "/" << QDate::currentDate().year() << " ";
        else
            entree << QDate::currentDate().day() << "/" << QDate::currentDate().month() << "/" << QDate::currentDate().year() << " ";

        entree << QTime::currentTime().hour() << ":0" << QTime::currentTime().minute() << " -> " << message << "\n";
    }
    else
    {
        if (QDate::currentDate().month() < 10)
            entree << QDate::currentDate().day() << "/0" << QDate::currentDate().month() << "/" << QDate::currentDate().year() << " ";
        else
            entree << QDate::currentDate().day() << "/" << QDate::currentDate().month() << "/" << QDate::currentDate().year() << " ";

        entree << QTime::currentTime().hour() << ":" << QTime::currentTime().minute() << " -> " << message << "\n";
    }

    log.close();
}
void log(QString message, int niveau)
{
    QFile log("nbh.log");
    if (!log.open(QIODevice::Append | QIODevice::Text))
        fatalError("Erreur lors de l'ouverture du fichier log");

    QTextStream entree(&log);

    switch (niveau)
    {
    case 1:
        message.replace("\n", "\n                            ");
        entree << "                         -> " + message + "\n";
        break;

    case 2:
        message.replace("\n", "\n                                       ");
        entree << "                                     * " + message + "\n";
        break;

    default:
        fatalError("Niveau pour le log inconnu !");
    }

    log.close();
}

void pause(int msec)
{
    QTime tempo;
    tempo.start();
    while (tempo.elapsed() < msec);
}
