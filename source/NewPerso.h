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

#ifndef NEWPERSO_H
    #define NEWPERSO_H

    #include <QWizard>
    #include <QFile>

    #include "FenMAJ.h"
    #include "fonctions_diverses.h"
    #include "ClassesPourPersonnage.h"
    #include "SelectCompetence.h"

    namespace Ui {
        class NewPerso;
    }

    class NewPerso : public QWizard
    {
        Q_OBJECT

    public:
        explicit NewPerso(QVector<Origine *> const& origines, QVector<Metier *> const& metiers);
        ~NewPerso();

    public slots:
        void accept();

    private slots:
        void changerPage(int id);

    private:
        Ui::NewPerso *ui;

        // Fonctions
        void testOrigines();
        void testMetiers();

        void setOrigine();
        void setMetier();

        bool choixCompetences();

        // Variables
        QVector<Origine*> m_origines;
            QVector<QRadioButton*> m_originesBouttons;
        QVector<Metier*> m_metiers;
            QVector<QRadioButton*> m_metiersBouttons;

        // Pour le personnage
        QString m_nom;
        QString m_sexe;
        QString m_origine;
        QString m_metier;

        int m_EV;

        bool m_presenceEA;
        int m_EA;
        QString m_typeEA;

        Caracteristiques *m_carac;

        int m_ptsDestin;
        int m_niveau;
        int m_experience;

        Richesses *m_richesses;

        QVector<Competence*> m_competences;
    };

#endif // NEWPERSO_H
