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

#ifndef ADDPERSO_H
    #define ADDPERSO_H

    #include <QDialog>
    #include <QFile>

    #include "FenMAJ.h"
    #include "fonctions_diverses.h"
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class AddPerso;
    }

    class AddPerso : public QDialog
    {
        Q_OBJECT

    public:
        explicit AddPerso(QWidget *parent = 0);
        ~AddPerso();

    private slots:
        void on_buttonBox_accepted();

    private:
        Ui::AddPerso *ui;
    };

#endif // ADDPERSO_H
