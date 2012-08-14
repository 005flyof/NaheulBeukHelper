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

#include "FenChargement.h"
#include "ui_FenChargement.h"

FenChargement::FenChargement(char *argv[])
    : QDialog(),
      ui(new Ui::FenChargement)
{
    ui->setupUi(this);
    ui->progression->setValue(0);

    show();

    log("Lancement de NBH :", true);

// Suppression du fichier temporaire de la MAJ
    ui->label->setText("Suppression du fichier temporaire de mise à jour : 'tmp.zip'...");
    log("Suppression du fichier temporaire de mise à jour : 'tmp.zip'...", 1);
    remove("tmp.zip");
    ui->progression->setValue(5);
    pause(800);

// Suppression du fichier d'erreur
    ui->label->setText("Suppression du fichier d'erreurs : 'error.log'...");
    log("Suppression du fichier d'erreurs : 'error.log'...", 1);
    remove("error.log");
    ui->progression->setValue(10);
    pause(800);

// Vérification des MAJ
    ui->label->setText("Lancement de la vérification des mises à jour...");
    log("Vérification des mises à jour...", 1);
    FenMAJ *test = new FenMAJ(this, true);
        test->verifierMAJ();
    ui->progression->setValue(15);
    pause(1000);

// Chargement des origines
    ui->label->setText("Chargement des origines...");
    log("Chargement des origines...", 1);
    ouvrirOrigines();
    ui->progression->setValue(35);
    pause(1000);

// Chargement des métiers
    ui->label->setText("Chargement des métiers...");
    log("Chargement des métiers...", 1);
    ouvrirMetiers();
    ui->progression->setValue(65);
    pause(1000);

// Chargement des compétences
    ui->label->setText("Chargement des compétences...");
    log("Chargement des compétences...", 1);
    ouvrirCompetences();
    ui->progression->setValue(95);
    pause(1000);

// Création de l'interface graphique
    ui->label->setText("Création de l'interface graphique...");
    log("Création de l'interface graphique...", 1);

    fenetrePrincipale = new FenPrincipale;
        fenetrePrincipale->setOrigines(origines);
        fenetrePrincipale->setMetiers(metiers);
        fenetrePrincipale->setCompetencesPossibles(competences);

    ui->progression->setValue(100);
    pause(1000);

    close();
    fenetrePrincipale->showMaximized();
}

FenChargement::~FenChargement()
{
    delete ui;
}


void FenChargement::ouvrirOrigines()
{
// On ouvre le fichier
    QFile fichierOrig(":prog-data/origines.txt");
    if (!fichierOrig.open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Fichier contenant les origines inaccessible !");

    QTextStream originesTexte(&fichierOrig);

// Définition des variables
    bool erreur(false);
    int nbOrigines(0);

// On commence à charger
    QString ligne = originesTexte.readLine();
    int compteurLigne(2);

    do
    {
    // Ouverture du nom
        QString nom = originesTexte.readLine();
        compteurLigne++;

    // Malus
        Caracteristiques mini = Personnage::chargerCaracStatic(&erreur, originesTexte.readLine(), false, compteurLigne);
        if (erreur)
            fatalError("Impossible de charger les caractéristiques à la ligne " + QString::number(compteurLigne) + " du fichier " + fichierOrig.fileName());
        compteurLigne++;

    // Bonus
        Caracteristiques maxi = Personnage::chargerCaracStatic(&erreur, originesTexte.readLine(), false, compteurLigne);
        if (erreur)
            fatalError("Impossible de charger les caractéristiques à la ligne " + QString::number(compteurLigne) + " du fichier " + fichierOrig.fileName());
        compteurLigne++;

    // EV et AT
        int EV(0), AT(0);

        ligne = originesTexte.readLine();
        EV = ligne.toInt();
        compteurLigne++;

        ligne = originesTexte.readLine();
        if (ligne == "x")
            AT = ligne.toInt();
        compteurLigne++;

    // On crée l'origine
        origines.push_back(new Origine(nom, EV, AT, mini, maxi));

    // On charge la ligne pour vérifier que le fichier n'est pas fini
        ligne = originesTexte.readLine();
        compteurLigne++;

        while (ligne == "~!competence-obligatoire!~")
        {
            QString competence_nom = originesTexte.readLine();
            compteurLigne++;
            QString competence_description = originesTexte.readLine();
            compteurLigne++;

            ligne = originesTexte.readLine();
            compteurLigne++;

            bool fin = false;
            while (!fin)
            {
                if (ligne == "~!competence-obligatoire!~")
                    fin = true;
                else if (ligne == "~!competence-choisir!~")
                    fin = true;
                else
                {
                    competence_description += "\n" + ligne;
                    ligne = originesTexte.readLine();
                    compteurLigne++;
                }
            }

            origines.at(nbOrigines)->addCompetence(competence_nom, competence_description);
        }
        while (ligne == "~!competence-choisir!~")
        {
            QString competence_nom = originesTexte.readLine();
            compteurLigne++;
            QString competence_description = originesTexte.readLine();
            compteurLigne++;

            ligne = originesTexte.readLine();
            compteurLigne++;

            bool fin = false;
            while (!fin)
            {
                if (ligne == "~!NOUVELLE_ORIGINE!~")
                    fin = true;
                else if (ligne == "~!FIN_ORIGINE!~")
                    fin = true;
                else if (ligne == "~!competence-choisir!~")
                    fin = true;
                else
                {
                    competence_description += "\n" + ligne;
                    ligne = originesTexte.readLine();
                    compteurLigne++;
                }
            }

            origines.at(nbOrigines)->addCompetence(competence_nom, competence_description, false);
        }

        nbOrigines++;
    } while (ligne != "~!FIN_ORIGINE!~");
}
void FenChargement::ouvrirMetiers()
{
// On ouvre le fichier
    QFile metiersFichier(":prog-data/metiers.txt");
    if (!metiersFichier.open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Impossible de charger le fichier contenant les métiers.");

    QTextStream metiersTexte(&metiersFichier);

// Définition des variables
    bool erreur(false);
    int nbMetiers(0);

// On commence à charger
    QString ligne = metiersTexte.readLine();
    int compteurLigne(2);

    do {
    // Ouverture du nom
        QString nom = metiersTexte.readLine();
        compteurLigne++;

    // Malus
        Caracteristiques malus = Personnage::chargerCaracStatic(&erreur, metiersTexte.readLine(), false, compteurLigne);
        if (erreur)
            fatalError("Impossible de charger les caractéristiques à la ligne " + QString::number(compteurLigne) + " du fichier " + metiersFichier.fileName());
        compteurLigne++;

    // AT & PRD
        int AT(0), PRD(0);
        ligne = metiersTexte.readLine();
        if (ligne != "x")
            AT = ligne.toInt();
        compteurLigne++;

        ligne = metiersTexte.readLine();
        if (ligne != "x")
            PRD = ligne.toInt();
        compteurLigne++;

        // On crée le métier
        metiers.push_back(new Metier(nom,
                                     AT, PRD,
                                     malus.getCourage(), malus.getIntelligence(), malus.getCharisme(), malus.getAdresse(), malus.getForce()));

        // EV
        ligne = metiersTexte.readLine();
        compteurLigne++;

        if (ligne == "~!EV_CLASSES!~")
        {
            QStringList liste_classes;
            int ev_pourClassesModifiees(0), evEnPlus_pourLesAutres(0);

            // On capte la ligne pour pas faire planter
            ligne = metiersTexte.readLine();
            compteurLigne++;

            do {
                // On remplit la liste de classes modifiées
                liste_classes << ligne;

                // On charge la ligne pour vérifier que la liste des classes modifiées n'est pas fini
                ligne = metiersTexte.readLine();
                compteurLigne++;
            } while (ligne != "~!EV_MODIF!~");

            ev_pourClassesModifiees = metiersTexte.readLine().toInt();
            compteurLigne++;

            evEnPlus_pourLesAutres = metiersTexte.readLine().toInt();
            compteurLigne++;

            QString ligne2 = metiersTexte.readLine();
            compteurLigne++;
            if (ligne2 == "pourcent")
            {
                // On ajoute tout cela au métier
                metiers.at(nbMetiers)->setEV(liste_classes, ev_pourClassesModifiees, evEnPlus_pourLesAutres, true);
                // On charge la ligne pour pouvoir vérifier que le fichier n'est pas fini
                ligne = metiersTexte.readLine();
                compteurLigne++;
            }
            else
            {
                ligne = ligne2;
                // On ajoute tout cela au métier
                metiers.at(nbMetiers)->setEV(liste_classes, ev_pourClassesModifiees, evEnPlus_pourLesAutres, false);
            }
        }

        if (ligne == "~!magie!~")
        {
            QString typeEA = metiersTexte.readLine();
            compteurLigne++;
            int EA = metiersTexte.readLine().toInt();
            compteurLigne++;

            // On ajoute l'EA au métier
            metiers.at(nbMetiers)->setEA(typeEA, EA);

            // On charge la ligne pour pouvoir vérifier que le fichier n'est pas fini
            ligne = metiersTexte.readLine();
            compteurLigne++;
        }

    // Conpétences
        while (ligne == "~!competence-obligatoire!~")
        {
            QString competence_nom = metiersTexte.readLine();
            compteurLigne++;
            QString competence_description = metiersTexte.readLine();
            compteurLigne++;

            ligne = metiersTexte.readLine();
            compteurLigne++;

            bool fin = false;
            while (!fin)
            {
                if (ligne == "~!competence-obligatoire!~")
                    fin = true;
                else if (ligne == "~!competence-choisir!~")
                    fin = true;
                else
                {
                    competence_description += "\n" + ligne;
                    ligne = metiersTexte.readLine();
                    compteurLigne++;
                }
            }

            metiers.at(nbMetiers)->addCompetence(competence_nom, competence_description);
        }
        while (ligne == "~!competence-choisir!~")
        {
            QString competence_nom = metiersTexte.readLine();
            compteurLigne++;
            QString competence_description = metiersTexte.readLine();
            compteurLigne++;

            ligne = metiersTexte.readLine();
            compteurLigne++;

            bool fin = false;
            while (!fin)
            {
                if (ligne == "~!NOUVEAU_METIER!~")
                    fin = true;
                else if (ligne == "~!FIN_METIER!~")
                    fin = true;
                else if (ligne == "~!competence-choisir!~")
                    fin = true;
                else
                {
                    competence_description += "\n" + ligne;
                    ligne = metiersTexte.readLine();
                    compteurLigne++;
                }
            }

            metiers.at(nbMetiers)->addCompetence(competence_nom, competence_description, false);
        }

        nbMetiers++;
    } while (ligne != "~!FIN_METIER!~");
}
void FenChargement::ouvrirCompetences()
{
// On ouvre le fichier
    QFile fichierCompetences(":prog-data/competences.txt");
    if (!fichierCompetences.open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Fichier contenant les compétences inaccessible !");

    QTextStream entree(&fichierCompetences);

    QString ligne(entree.readLine());

    while (ligne == "~!competence!~")
    {
        QString nom = entree.readLine();
        QString description = entree.readLine();


        // On vérifier que la ligne suivante n'est pas la suite de la compétence
        ligne = entree.readLine();

        bool fin(false);

        if (ligne == "~!competence!~")
            fin = true;
        if (ligne == "~!FIN_COMPETENCES!~")
            fin = true;

        while (!fin)
        {
            description += "\n" + ligne;
            ligne = entree.readLine();

            if (ligne == "~!competence!~")
                fin = true;
            if (ligne == "~!FIN_COMPETENCES!~")
                fin = true;
        }

        // On ajoute la compétence
        competences.push_back(new Competence(nom, description));
    }
}
