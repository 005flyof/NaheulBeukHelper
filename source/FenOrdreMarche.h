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

#ifndef FENORDREMARCHE_H
    #define FENORDREMARCHE_H

    #include <QtGui>
    #include "Arme.h"

    class FenOrdreMarche : public QWidget
    {
        Q_OBJECT
    public:
        FenOrdreMarche(QStringList const& nomPersos);

        void setNomPersos(QStringList const& nomPersos);

    public slots:
        void select(QModelIndex index);
        void verrouillerBoutons();

        void monter();
        void monter1();
        void descendre1();
        void descendre();

        void recharger();

    signals:
        void verrouiller();

    private:
        QMdiArea* affichagePersos;

        QListView *vue;
        QStringList nomPersonnages;
        QStringListModel *modele;

        QPushButton *haut;
        QPushButton *haut1;
        QPushButton *bas;
        QPushButton *bas1;
    };

#endif // FENORDREMARCHE_H
