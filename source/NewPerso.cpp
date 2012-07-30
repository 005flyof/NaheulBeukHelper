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

// On valide l'origine
    setOrigine();
    setMetier();

// On valide toutes les variables
    m_nom = ui->nom->text();
    m_sexe = ui->sexe->text();

    m_ptsDestin = ui->ptsDestin->value();
    m_experience = 0;

    m_richesses = new Richesses(ui->po->value(), 0, 0);

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
        fatalError("Impossible d'enregistrer le fichier de personnage sélectionné.");

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
        fatalError("Impossible d'ouvrir le fichier de groupe sélectionné. Réessayez d'ajouter le personnage au groupe.");

    QTextStream groupe(&groupeRec);

    groupe << chemin.remove(QCoreApplication::applicationDirPath()) + "\n";

    log("'" + ui->nom->text() + "' a été ajouté à un groupe !");

// On ferme la fenêtre
    QDialog::accept();
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
    {
        if (m_origines.at(i)->getNom() == m_origine)
        {
            m_EV = m_origines.at(i)->getEV();

            if (m_origines.at(i)->getAT() != 0)
                m_carac->setAttaque(m_origines.at(i)->getAT());

            for (int j(0); j < m_origines.at(i)->getCompetences().count(); j++)
                m_competences.append(m_origines.at(i)->getCompetences().at(i));
        }
    }
}
void NewPerso::setMetier()
{
    for (int i(0); i < m_metiers.count(); i++)
    {
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

                for(int i = 0; i < m_metiers.at(i)->getClassesModifiees_EV().size(); i++)
                {
                    if (m_metiers.at(i)->getClassesModifiees_EV().at(i) == m_origine)
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
            for (int i(0); i < m_metiers.at(i)->getCompetences().count(); i++)
                m_competences.append(m_metiers.at(i)->getCompetences().at(i));
        }
    }
}
