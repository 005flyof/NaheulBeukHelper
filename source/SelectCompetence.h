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

#ifndef SELECTCOMPETENCE_H
    #define SELECTCOMPETENCE_H

    #include <QDialog>
    #include <QtGui>
    #include "ClassesPourPersonnage.h"

    namespace Ui {
        class SelectCompetence;
    }

    class SelectCompetence : public QDialog
    {
        Q_OBJECT

    public:
        explicit SelectCompetence(QVector<Competence*> value, QWidget *parent = 0);
        explicit SelectCompetence(QVector<Competence*> value, bool plsChoix, QWidget *parent = 0);
        ~SelectCompetence();

        QString getChoix();
        QStringList getChoix(bool plsChoix);

    private:
        Ui::SelectCompetence *ui;

        bool m_plsChoix;

        QVector<Competence*> competences;
        QVector<QAbstractButton*> tableauBouttons;
    };

#endif // SELECTCOMPETENCE_H
