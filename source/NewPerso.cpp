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

#include "NewPerso.h"
#include "ui_NewPerso.h"

NewPerso::NewPerso(QVector<Origine *> const& origines, QVector<Metier *> const& metiers)
    : QWizard(),
      ui(new Ui::NewPerso)
{
    ui->setupUi(this);

    m_origines = origines;
    m_metiers = metiers;

    QObject::connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(changerPage(int)));
}
NewPerso::~NewPerso()
{
    delete ui;
}


void NewPerso::accept()
{
// On vérifie que l'utilisateur a bien coché !
    bool origChoix(false), metierChoix(false);
    for (int i = 0; i < m_originesBouttons.count(); i++)
        if (m_originesBouttons.at(i)->isChecked())
        {
            origChoix = true;
            m_origine = m_originesBouttons.at(i)->text();
        }
    for (int i = 0; i < m_metiersBouttons.count(); i++)
        if (m_metiersBouttons.at(i)->isChecked())
        {
            metierChoix = true;
            m_metier = m_metiersBouttons.at(i)->text();
        }

    if (!origChoix)
    {
        QMessageBox::critical(this, "Pas d'origine choisie !",
                              "Vous n'avez pas choisi d'origine, veuillez en choisir une !");
        return;
    }
    if (!metierChoix)
    {
        QMessageBox::critical(this, "Pas de métier choisi !",
                              "Vous n'avez pas choisi de métier, veuillez en choisir un !");
        return;
    }

// On valide l'origine et le métier
    setOrigine();
    setMetier();

// On valide toutes les variables
    m_nom = ui->nom->text();
    m_sexe = ui->sexe->text();

    m_ptsDestin = ui->ptsDestin->value();
    m_experience = 0;

    m_richesses = new Richesses(ui->po->value(), 0, 0);

// On valide les compétences au choix
    bool continuer(choixCompetences());
    if (!continuer)
        return;

// On enregistre
    QString total = "~!NewPerso!~\n";

    total += m_nom + "\n";
    total += m_sexe + "\n";
    total += m_origine + "\n";
    total += m_metier + "\n";
    total += QString::number(m_EV) + "\n";
    total += QString::number(m_ptsDestin) + "\n";
    total += QString::number(m_experience) + "\n";
    total += m_carac->caracEnregistrement() + "\n";
    total += m_carac->caracEnregistrement() + "\n";

    total += m_richesses->richessesEnregistrement() + "\n";

    if (m_presenceEA)
        total += "~!magie!~\n" + QString::number(m_EA) + "\n" + m_typeEA + "\n";

    for (int lecteur = 0; lecteur < m_competences.count(); lecteur++)
    {
        total += "~!competence!~\n";
        total += m_competences.at(lecteur)->getNom() + "\n";
        total += m_competences.at(lecteur)->getDescription() + "\n";
    }

    total += "~!FIN_ENREGISTREMENT!~";

    // Eregistrement
    QString chemin = QFileDialog::getSaveFileName(this, "Enregistrer un personnage",
                                                  QString("enregistrements"), "Personnages (*.perso)");
    if (chemin.isEmpty())
        return;

    if (OS == 0)
        chemin.replace("/", "\\");

    QFile *m_fichierPerso = new QFile(chemin);
    if (!m_fichierPerso->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        error("Impossible d'enregistrer le fichier de personnage sélectionné.\n"
              "Ceci peut être dû aux permissions du fichier : il n'est pas accessible.");
        return;
    }

    QTextStream sortie(m_fichierPerso);

    sortie << total;

    m_fichierPerso->close();

// On modifie le groupe
    bool erreur(false);
    QString cheminGroupe;
    while (!erreur)
    {
        cheminGroupe = QFileDialog::getOpenFileName(this, "Modifier un groupe",
                                                    QString("enregistrements"), "Groupes de personnages (*.nbh)");

        if (cheminGroupe.isEmpty())
            QMessageBox::critical(this, "ERREUR !", "Erreur :\nVous devez choisir un groupe à modifier !");
        else
            erreur = true;
    }

    if (OS == 0)
        cheminGroupe.replace("/", "\\");

    QFile groupeRec(cheminGroupe);
    if (!groupeRec.open(QIODevice::Append | QIODevice::Text))
    {
        error("Impossible d'ouvrir le fichier de groupe sélectionné. Réessayez d'ajouter le personnage au groupe.\n"
              "Ceci peut être dû aux permissions du fichier : il n'est pas accessible.");
        return;
    }

    QTextStream groupe(&groupeRec);

    groupe << chemin.remove(QCoreApplication::applicationDirPath()) + "\n";

    log("'" + ui->nom->text() + "' a été ajouté à un groupe !");

// On ferme la fenêtre
    QDialog::accept();
    QMessageBox::information(this, "Chargement du personnage",
                             "Vous venez de créer un personnage lisible par NaheulBeuk Helper.\n\n"
                             "Si vous avez déjà ouvert le groupe modifié,"
                             "pour que les modifications soient appliquées, il faut recharger le groupe !");
}


void NewPerso::changerPage(int id)
{
    switch (id)
    {
    case 1:
        m_carac = new Caracteristiques(ui->cou->value(),
                                       ui->intel->value(),
                                       ui->cha->value(),
                                       ui->ad->value(),
                                       ui->fo->value(),
                                       8, 10);
        testOrigines();
        break;

    case 2:
        testMetiers();
        break;
    }
}
void NewPerso::testMetiers()
{
    for (int i(0); i < m_metiersBouttons.count(); i++)
    {
        ui->origLayout->removeWidget(m_metiersBouttons.at(i));
        m_metiersBouttons.at(i)->hide();
    }
    m_metiersBouttons.clear();

    int nbMetiersPossibles(0);
    for (int i = 0; i < m_metiers.count(); i++)
    {
        if (m_metiers.at(i)->getCaracMini() <= *m_carac)
        {
            QRadioButton *temp = new QRadioButton(m_metiers.at(i)->getNom());
            m_metiersBouttons.push_back(temp);
            ui->metierLayout->addWidget(m_metiersBouttons.at(nbMetiersPossibles));
            nbMetiersPossibles++;
        }
    }
}
void NewPerso::testOrigines()
{
    for (int i(0); i < m_originesBouttons.count(); i++)
    {
        ui->origLayout->removeWidget(m_originesBouttons.at(i));
        m_originesBouttons.at(i)->hide();
    }
    m_originesBouttons.clear();

    int nbOrigPossibles(0);
    for (int i = 0; i < m_origines.count(); i++)
    {
        if (m_origines.at(i)->getCaracMini() <= *m_carac
            && m_origines.at(i)->getCaracMaxi() >= *m_carac)
        {
            QRadioButton *temp = new QRadioButton(m_origines.at(i)->getNom());
            m_originesBouttons.push_back(temp);
            ui->origLayout->addWidget(m_originesBouttons.at(nbOrigPossibles));
            nbOrigPossibles++;
        }
    }
}

void NewPerso::setOrigine()
{
    for (int i(0); i < m_origines.count(); i++)
        if (m_origines.at(i)->getNom() == m_origine)
        {
        // On valide l'EV
            m_EV = m_origines.at(i)->getEV();

        // On valide l'AT s'il le faut
            if (m_origines.at(i)->getAT() != 0)
                m_carac->setAttaque(m_origines.at(i)->getAT());

        // Copie des compétences
            for (int i3(0); i3 < m_origines.at(i)->getCompetences().count(); i3++)                                                   // On parcourt les compétences de l'origine courante
            {
                bool dejaInscrite = false;
                for (int competenceAcquises(0); competenceAcquises < m_competences.count(); competenceAcquises++)                   // On parcourt les compétences déjà inscrites pour éviter les doublons
                {
                    if (m_competences.at(competenceAcquises)->getNom() == m_origines.at(i)->getCompetences().at(i3)->getNom())
                        dejaInscrite = true;
                }

                if (!dejaInscrite)
                    m_competences.append(m_origines.at(i)->getCompetences().at(i3));
            }
        }
}
void NewPerso::setMetier()
{
    for (int i(0); i < m_metiers.count(); i++)
        if (m_metiers.at(i)->getNom() == m_metier)
        {
            if (m_metiers.at(i)->getAT() != 0)
                m_carac->setAttaque(m_metiers.at(i)->getAT());

            if (m_metiers.at(i)->getPRD() != 0)
                m_carac->setParade(m_metiers.at(i)->getPRD());

        // Modification pour certains métiers :
            if (m_metiers.at(i)->getEV_pourClassesModifiees() != 0)
            {
                bool persoEstClasseModifiee(false);

                for(int i2 = 0; i2 < m_metiers.at(i)->getClassesModifiees_EV().size(); i2++)
                {
                    if (m_metiers.at(i)->getClassesModifiees_EV().at(i2) == m_origine)
                        persoEstClasseModifiee = true;
                }

                if (persoEstClasseModifiee)
                    m_EV = m_metiers.at(i)->getEV_pourClassesModifiees();
                else
                {
                    if (m_metiers.at(i)->getEV_pourAutresClasses_pourcent()) // Si la modif est en pourcent
                    {
                        int modif = m_metiers.at(i)->getEV_pourAutresClasses();    // On demande combien de pourcent
                        // On calcule 1 pourcent de l'actuelle EV
                        double unPourcent_EV = static_cast<double>(m_EV) / static_cast<double>(100);
                        int ajout = unPourcent_EV * modif;          // On calcule le résultat à ajouter

                        m_EV += ajout;
                    }
                    else // Sinon
                        m_EV += m_metiers.at(i)->getEV_pourAutresClasses();
                }
            }

            if (m_metiers.at(i)->getPresenceEA())
            {
                m_presenceEA = true;
                m_EA = m_metiers.at(i)->getEA();
                m_typeEA = m_metiers.at(i)->getTypeEA();
            }

        // Copie des compétences
            for (int i3(0); i3 < m_metiers.at(i)->getCompetences().count(); i3++)                                                   // On parcourt les compétences du métier courant
            {
                bool dejaInscrite = false;
                for (int competenceAcquises(0); competenceAcquises < m_competences.count(); competenceAcquises++)                   // On parcourt les compétences déjà inscrites pour éviter les doublons
                {
                    if (m_competences.at(competenceAcquises)->getNom() == m_metiers.at(i)->getCompetences().at(i3)->getNom())
                        dejaInscrite = true;
                }

                if (!dejaInscrite)
                    m_competences.append(m_metiers.at(i)->getCompetences().at(i3));
            }
        }
}

bool NewPerso::choixCompetences()
{
    QMessageBox::information(this, "Sélection des compétences ...",
                             "Veuillez sélectionner 2 compétences dans la liste suivante, elles seront ajoutées au personnage !");

    QVector<Competence*> selection;
    int metier(0), orig(0);

    for (int i(0); i < m_metiers.count(); i++)
        if (m_metiers.at(i)->getNom() == m_metier)
            metier = i;
    for (int i(0); i < m_origines.count(); i++)
        if (m_origines.at(i)->getNom() == m_origine)
            orig = i;

    for (int i(0); i < m_metiers.at(metier)->getCompetences(false).count(); i++)                                                   // On parcourt les compétences du métier courant
    {
        bool dejaInscrite = false;

        for (int competenceAcquises(0); competenceAcquises < selection.count(); competenceAcquises++)                   // On parcourt les compétences déjà inscrites pour éviter les doublons
        {
            if (selection.at(competenceAcquises)->getNom() == m_metiers.at(metier)->getCompetences(false).at(i)->getNom())
                dejaInscrite = true;
        }

        if (!dejaInscrite)
            selection.append(m_metiers.at(metier)->getCompetences(false).at(i));
    }
    for (int i(0); i < m_origines.at(orig)->getCompetences(false).count(); i++)                                                   // On parcourt les compétences du métier courant
    {
        bool dejaInscrite = false;

        for (int competenceAcquises(0); competenceAcquises < selection.count(); competenceAcquises++)                   // On parcourt les compétences déjà inscrites pour éviter les doublons
        {
            if (selection.at(competenceAcquises)->getNom() == m_origines.at(orig)->getCompetences(false).at(i)->getNom())
                dejaInscrite = true;
        }

        if (!dejaInscrite)
            selection.append(m_origines.at(orig)->getCompetences(false).at(i));
    }

    // On enlève les compétences déjà acquises !
    for (int i(0); i < selection.count(); i++)
        for (int j(0); j < m_competences.count(); j++)
            if (selection.at(i)->getNom() == m_competences.at(j)->getNom())
                selection.remove(i);

    bool erreur = true;
    while (erreur)
    {
        SelectCompetence *dialogue = new SelectCompetence(selection, true, this);
        int result = dialogue->exec();

        if (result == QDialog::Accepted)
        {
            QStringList noms = dialogue->getChoix(true);

            if (noms.count() != 2)
                QMessageBox::information(this, "Erreur !",
                                         "ERREUR :\n"
                                         "Vous avez sélectionné trop/pas assez de compétences !\n"
                                         "Veuillez en sélectionner 2 !");
            else
            {
            // On ajoute la compétence à la liste
                for (int i(0); i < selection.count(); i++)
                    if (selection.at(i)->getNom() == noms.at(0))
                        m_competences.push_back(selection.at(i));
                for (int i(0); i < selection.count(); i++)
                    if (selection.at(i)->getNom() == noms.at(1))
                        m_competences.push_back(selection.at(i));
                erreur = false;
            }
        }
        else
            return false;
    }

    return true;
}
