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

#ifndef FENATTAQUE_H
    #define FENATTAQUE_H

    #include <QtGui>

    class FenAttaque : public QWidget
    {
        Q_OBJECT

    public:
        FenAttaque(QStringList const& nomPersos, QMainWindow *parent = 0);
        QString getNomActivePerso();
        void setNomPersos(QStringList const& nomPersos);

    signals:
        void attaque();
        void parade();
        void esquive();

    public slots:
        void attaquer();
        void parer();
        void esquiver();

        void select(QModelIndex index);
        void verrouillerBouton();
        void recharger();

    private:
        QMainWindow *m_parent;
        QStringList m_nomPersos;

        QStringListModel *modele;
        QListView *vue;

        QPushButton *m_attaquer;
        QPushButton *m_esquiver;
        QPushButton *m_parer;
    };

#endif // FENATTAQUE_H
