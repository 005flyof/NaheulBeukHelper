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

#ifndef COMPETENCE_H
    #define COMPETENCE_H

    #include <QtGui>

    class Competence : private QWidget
    {
        Q_OBJECT

    public:
        Competence(QString const& nom, QString const& description);
        Competence(Competence const& aCopier);
        Competence& operator=(Competence const& b);
        ~Competence();

        QString getNom() const;
        QString getDescription() const;

        QWidget* getWidget();

    public slots:
        void modifier();
        void modifier2();

    private:
        void initAffichage();

        QString m_nom;
        QString m_description;

        QGroupBox *nom_label;
        QTextEdit *description_label;
        QPushButton *modif;

        QDialog *fen;
        QLineEdit *nom_edit;
        QTextEdit *description_edit;
    };

#endif // COMPETENCE_H
