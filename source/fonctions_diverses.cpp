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

        QWidget *a = new QWidget();
        QMessageBox::critical(a, "Erreur fatale",
                              "NBH va être fermé car une erreur fatale a été décelée :\n\n" + message);
        if (!logErreur)
            log("Erreur fatale : NBH va être fermé car une erreur fatale a été décelée :\n\n" + message);
    }

    exit(2);
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
    entree << QDate::currentDate().day() << "/" << QDate::currentDate().month() << "/" << QDate::currentDate().year() << " ";
    entree << QTime::currentTime().hour() << ":" << QTime::currentTime().minute() << " -> " << message << "\n";
}

Personnage chargerPerso(QString chemin)
{
    QFile persoOuverture(*cheminPersoOuverture);
    if (!persoOuverture.open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Impossible d'ouvrir le fichier personnage suivant : " + *cheminPersoOuverture);

    log("Ouverture du personnage : '" + *cheminPersoOuverture + "'");

    QTextStream entree(&persoOuverture);
// Création des variables
    QString groupeAdresse;
    int lecteurLigne;
    int lecteurTableauProtection, lecteurTableauArme, lecteurTableauFleche, lecteurTableauEquipement;

    int ouvertureEV, ouverturePtsDestin, ouvertureXP;
    int ouverturePO, ouverturePA, ouverturePC;
    int ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO, ouverture_AT, ouverture_PRD;
    int ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo, ouverture_at, ouverture_prd;

    QString ouvertureNom, ouvertureSexe, ouvertureNomOrigine, ouvertureNomMetier;
    Vetement *ouverture_VETEMENT;
    Protection *ouverture_PROTECTION;
    Arme *ouverture_ARME;
    Fleche *ouverture_FLECHE;
    QString ouverture_EQUIPEMENT;

// Ouverture du nom, etc
    ouvertureNom = entree.readLine();
    ouvertureSexe = entree.readLine();
    ouvertureNomOrigine = entree.readLine();
    ouvertureNomMetier = entree.readLine();

    QString ouvertureEV_string = entree.readLine();
    ouvertureEV = ouvertureEV_string.toInt();

    QString ouverturePtsDestin_string = entree.readLine();
    ouverturePtsDestin = ouverturePtsDestin_string.toInt();

    QString ouvertureXP_string = entree.readLine();
    ouvertureXP = ouvertureXP_string.toInt();

// Ouverture pour les caractéristiques
        // Initiales
    QString ouvertureCarac_ligne = entree.readLine();
    lecteurLigne = 0;
    CARAC_A_ZERO;
    while (lecteurLigne < ouvertureCarac_ligne.size())
    {
        if (ouvertureCarac_ligne[lecteurLigne] == '_')
            lecteurLigne++;

        else
        {
            QString ouvertureCarac_string("");
            QChar a(ouvertureCarac_ligne[lecteurLigne]);
            ouvertureCarac_string = a + ouvertureCarac_ligne[lecteurLigne+1];

            switch (lecteurLigne)
            {
            case 0:
                ouverture_COU = ouvertureCarac_string.toInt();
                break;
            case 3:
                ouverture_INT = ouvertureCarac_string.toInt();
                break;
            case 6:
                ouverture_CHA = ouvertureCarac_string.toInt();
                break;
            case 9:
                ouverture_AD = ouvertureCarac_string.toInt();
                break;
            case 12:
                ouverture_FO = ouvertureCarac_string.toInt();
                break;
            case 15:
                ouverture_AT = ouvertureCarac_string.toInt();
                break;
            case 18:
                ouverture_PRD = ouvertureCarac_string.toInt();
                break;
            default:
                QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                      "Caractéristiques initiales non valides !\n");
                fermerOnglets();
                log("Personnage non ouvert : caractéristiques initiales invalides !");
                log("Annulation du chargement du groupe !");
                statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                return;
                break;
            }
            lecteurLigne += 2;
        }
    }

        // Modifiées
    ouvertureCarac_ligne = entree.readLine();
    lecteurLigne = 0;
    while (lecteurLigne < ouvertureCarac_ligne.size())
    {
        if (ouvertureCarac_ligne[lecteurLigne] == '_')
            lecteurLigne++;

        else
        {
            QString ouvertureCarac_string("");
            QChar a(ouvertureCarac_ligne[lecteurLigne]);
            ouvertureCarac_string = a + ouvertureCarac_ligne[lecteurLigne+1];

            switch (lecteurLigne)
            {
            case 0:
                ouverture_cou = ouvertureCarac_string.toInt();
                break;
            case 3:
                ouverture_int = ouvertureCarac_string.toInt();
                break;
            case 6:
                ouverture_cha = ouvertureCarac_string.toInt();
                break;
            case 9:
                ouverture_ad = ouvertureCarac_string.toInt();
                break;
            case 12:
                ouverture_fo = ouvertureCarac_string.toInt();
                break;
            case 15:
                ouverture_at = ouvertureCarac_string.toInt();
                break;
            case 18:
                ouverture_prd = ouvertureCarac_string.toInt();
                break;
            default:
                QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                      "Caractéristiques modifiées non valides !\n");
                fermerOnglets();
                log("Personnage non ouvert : caractéristiques modifiées invalides !");
                log("Annulation du chargement du groupe !");
                statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                return;
                break;
            }
            lecteurLigne += 2;
        }
    }

// Ouverture pour les pièces
    QString ouverturePieces_ligne = entree.readLine();
    lecteurLigne = 0;
    while (lecteurLigne < ouverturePieces_ligne.size())
    {
        if (ouverturePieces_ligne[lecteurLigne] == '_')
            lecteurLigne++;
        else
        {
            QString ouverturePieces_string("");
            ouverturePieces_string = ouverturePieces_ligne[lecteurLigne];
            ouverturePieces_string += ouverturePieces_ligne[lecteurLigne+1];
            ouverturePieces_string += ouverturePieces_ligne[lecteurLigne+2];
            ouverturePieces_string += ouverturePieces_ligne[lecteurLigne+3];
            ouverturePieces_string += ouverturePieces_ligne[lecteurLigne+4];
            ouverturePieces_string += ouverturePieces_ligne[lecteurLigne+5];

            switch (lecteurLigne)
            {
            case 0:
                ouverturePO = ouverturePieces_string.toInt();
                break;
            case 7:
                ouverturePA = ouverturePieces_string.toInt();
                break;
            case 14:
                ouverturePC = ouverturePieces_string.toInt();
                break;
            default:
                QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                      "Richesses non valides !\n");
                fermerOnglets();
                log("Personnage non ouvert : richesses invalides !");
                log("Annulation du chargement du groupe !");
                statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                return;
                break;
            }
            lecteurLigne += 6;
        }
    }

// Création du personnage
    tableauDePersonnages[ouvertureNom] = Personnage(ouvertureNom, ouvertureSexe, ouvertureNomOrigine, ouvertureNomMetier,
                                                    ouverture_COU, ouverture_INT, ouverture_CHA,
                                                    ouverture_AD, ouverture_FO, ouverture_AT, ouverture_PRD,
                                                    ouverture_cou, ouverture_int, ouverture_cha,
                                                    ouverture_ad, ouverture_fo, ouverture_at, ouverture_prd,
                                                    ouverturePtsDestin, ouvertureXP, ouvertureEV,
                                                    ouverturePO, ouverturePA, ouverturePC);
    tableauDePersonnages[ouvertureNom].setAdresse(*cheminPersoOuverture);

// Ajout du personnage aux personnages/fichiers ouverts
    fichiersOuverts << *cheminPersoOuverture;
    nomPersoOuverts << ouvertureNom;

// On augmente la barre de statut
    progressBar_status->setValue(25);

// Ouverture des autres choses
    bool ouvertureFichierTerminee(false);
    lecteurTableauProtection = 0;
    lecteurTableauArme = 0;
    lecteurTableauFleche = 0;
    lecteurTableauEquipement = 0;

    bool ligneDejaLue = false;
    QString ligne = "";

    while (!ouvertureFichierTerminee)
    {
        if (!ligneDejaLue)
            ligne = entree.readLine();

        ligneDejaLue = false;   // on resete le fait que la ligne est déjà lue ou pas
        lecteurLigne = 0;		// Pour sélectionner un caractère de la ligne

    // carac
        if (ligne == "~!carac_sup_inf!~")
        {
            int ouvertureDegatsBonus = entree.readLine().toInt();
            int ouvertureAttaqueBonus = entree.readLine().toInt();
            int ouvertureParadeBonus = entree.readLine().toInt();
            int ouvertureDegatsBonusSorts = entree.readLine().toInt();

        // On crée les bonus
            tableauDePersonnages[ouvertureNom].setBonus_Malus_caracSup_Inf_moyenne(ouvertureDegatsBonus,
                                                                                   ouvertureAttaqueBonus,
                                                                                   ouvertureParadeBonus,
                                                                                   ouvertureDegatsBonusSorts);
        }

    // Si le perso est magicien
        else if (ligne == "~!magie!~")
        {
            int ouvertureEA = entree.readLine().toInt();
            QString ouvertureTypeEA = entree.readLine();

        // On crée l'EA
            tableauDePersonnages[ouvertureNom].setEA(ouvertureEA, ouvertureTypeEA);
        }

    // Pour les vêtements
        // Châpeau
        else if (ligne == "~!chapeau!~")
        {
        // Châpeau
            // Nom
            QString ouvertureChapeau_nom = entree.readLine();

            CARAC_A_ZERO;

            // Bonus
            QString ouvertureChapeau_bonus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureChapeau_bonus_ligne.size())
            {
                if (ouvertureChapeau_bonus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureHaut_bonus_string("");
                    QChar a(ouvertureChapeau_bonus_ligne[lecteurLigne]);
                    ouvertureHaut_bonus_string = a + ouvertureChapeau_bonus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 12:
                        ouverture_FO= ouvertureHaut_bonus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Châpeau -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Châpeau -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Malus
            QString ouvertureChapeau_malus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureChapeau_malus_ligne.size())
            {
                if (ouvertureChapeau_malus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureHaut_malus_string("");
                    QChar a(ouvertureChapeau_malus_ligne[lecteurLigne]);
                    ouvertureHaut_malus_string = a + ouvertureChapeau_malus_ligne[lecteurLigne+1];
                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureHaut_malus_string.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureHaut_malus_string.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureHaut_malus_string.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureHaut_malus_string.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureHaut_malus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Châpeau -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Châpeau -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Création
            ouverture_VETEMENT = new Vetement(ouvertureChapeau_nom,
                                              ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo,
                                              ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO);
            tableauDePersonnages[ouvertureNom].addVetement(ouverture_VETEMENT, 0);
        }

        // Haut
        else if (ligne == "~!haut!~")
        {
        // Haut
            // Nom
            QString ouvertureHaut_nom = entree.readLine();

            CARAC_A_ZERO;

            // Bonus
            QString ouvertureChapeau_bonus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureChapeau_bonus_ligne.size())
            {
                if (ouvertureChapeau_bonus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureHaut_bonus_string("");
                    QChar a(ouvertureChapeau_bonus_ligne[lecteurLigne]);
                    ouvertureHaut_bonus_string = a + ouvertureChapeau_bonus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureHaut_bonus_string.toInt();
                        break;
                    case 12:
                        ouverture_FO= ouvertureHaut_bonus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Haut -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Haut -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Malus
            QString ouvertureChapeau_malus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureChapeau_malus_ligne.size())
            {
                if (ouvertureChapeau_malus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureHaut_malus_string("");
                    QChar a(ouvertureChapeau_malus_ligne[lecteurLigne]);
                    ouvertureHaut_malus_string = a + ouvertureChapeau_malus_ligne[lecteurLigne+1];
                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureHaut_malus_string.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureHaut_malus_string.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureHaut_malus_string.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureHaut_malus_string.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureHaut_malus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Haut -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Haut -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Création
            ouverture_VETEMENT = new Vetement(ouvertureHaut_nom,
                                              ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo,
                                              ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO);
            tableauDePersonnages[ouvertureNom].addVetement(ouverture_VETEMENT, 1);
        }

        // Bas
        else if (ligne == "~!bas!~")
        {
            // Nom
            QString ouvertureBas_nom = entree.readLine();

            delete ouverture_VETEMENT;
            CARAC_A_ZERO;

            // Bonus
            QString ouvertureBas_bonus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureBas_bonus_ligne.size())
            {
                if (ouvertureBas_bonus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureBas_bonus_string("");
                    QChar a(ouvertureBas_bonus_ligne[lecteurLigne]);
                    ouvertureBas_bonus_string = a + ouvertureBas_bonus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureBas_bonus_string.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureBas_bonus_string.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureBas_bonus_string.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureBas_bonus_string.toInt();
                        break;
                    case 12:
                        ouverture_FO= ouvertureBas_bonus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Bas -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Bas -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Malus
            QString ouvertureBas_malus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureBas_malus_ligne.size())
            {
                if (ouvertureBas_malus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureBas_malus_string("");
                    QChar a(ouvertureBas_malus_ligne[lecteurLigne]);
                    ouvertureBas_malus_string = a + ouvertureBas_malus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureBas_malus_string.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureBas_malus_string.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureBas_malus_string.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureBas_malus_string.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureBas_malus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Bas -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Bas -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Création
            ouverture_VETEMENT = new Vetement(ouvertureBas_nom,
                                              ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo,
                                              ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO);
            tableauDePersonnages[ouvertureNom].addVetement(ouverture_VETEMENT, 2);

        }

        // Chaussures
        else if (ligne == "~!chaussures!~")
        {
            // Nom
            QString ouvertureChaussures_nom = entree.readLine();

            delete ouverture_VETEMENT;
            CARAC_A_ZERO;

            // Bonus
            QString ouvertureChaussures_bonus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureChaussures_bonus_ligne.size())
            {
                if (ouvertureChaussures_bonus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureChaussures_bonus_string("");
                    QChar a(ouvertureChaussures_bonus_ligne[lecteurLigne]);
                    ouvertureChaussures_bonus_string = a + ouvertureChaussures_bonus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureChaussures_bonus_string.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureChaussures_bonus_string.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureChaussures_bonus_string.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureChaussures_bonus_string.toInt();
                        break;
                    case 12:
                        ouverture_FO= ouvertureChaussures_bonus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Chaussures -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Chaussures -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Malus
            QString ouvertureChaussures_malus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureChaussures_malus_ligne.size())
            {
                if (ouvertureChaussures_malus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureChaussures_malus_string("");
                    QChar a(ouvertureChaussures_malus_ligne[lecteurLigne]);
                    ouvertureChaussures_malus_string = a + ouvertureChaussures_malus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureChaussures_malus_string.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureChaussures_malus_string.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureChaussures_malus_string.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureChaussures_malus_string.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureChaussures_malus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Chaussures -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Chaussures -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Création
            ouverture_VETEMENT = new Vetement(ouvertureChaussures_nom,
                                              ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo,
                                              ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO);
            tableauDePersonnages[ouvertureNom].addVetement(ouverture_VETEMENT, 3);
        }

        // Divers
        else if (ligne == "~!divers!~")
        {
            // Nom
            QString ouvertureDivers_nom = entree.readLine();

            delete ouverture_VETEMENT;
            CARAC_A_ZERO;

            // Bonus
            QString ouvertureDivers_bonus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureDivers_bonus_ligne.size())
            {
                if (ouvertureDivers_bonus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureDivers_bonus_string("");
                    QChar a(ouvertureDivers_bonus_ligne[lecteurLigne]);
                    ouvertureDivers_bonus_string = a + ouvertureDivers_bonus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureDivers_bonus_string.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureDivers_bonus_string.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureDivers_bonus_string.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureDivers_bonus_string.toInt();
                        break;
                    case 12:
                        ouverture_FO= ouvertureDivers_bonus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Divers -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Divers -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Malus
            QString ouvertureDivers_malus_ligne = entree.readLine();
            lecteurLigne = 0;
            while (lecteurLigne < ouvertureDivers_malus_ligne.size())
            {
                if (ouvertureDivers_malus_ligne[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QString ouvertureDivers_malus_string("");
                    QChar a(ouvertureDivers_malus_ligne[lecteurLigne]);
                    ouvertureDivers_malus_string = a + ouvertureDivers_malus_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureDivers_malus_string.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureDivers_malus_string.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureDivers_malus_string.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureDivers_malus_string.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureDivers_malus_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Divers -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : Divers -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // Création
            ouverture_VETEMENT = new Vetement(ouvertureDivers_nom,
                                              ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo,
                                              ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO);
            tableauDePersonnages[ouvertureNom].addVetement(ouverture_VETEMENT, 4);

            progressBar_status->setValue(50);
        }

    // Pour les protections
        else if (ligne == "~!protection!~")
        {
            CARAC_A_ZERO;

            // Nom
            QString ouvertureProtection_nom = entree.readLine();

            // Protection
            QString PR_ligne = entree.readLine();
            int ouvertureProtection_PR = PR_ligne.toInt();

            // Bonus
            lecteurLigne = 0;
            QString ouvertureProtection_bonus_string = entree.readLine();
            while (lecteurLigne < ouvertureProtection_bonus_string.size())
            {
                if (ouvertureProtection_bonus_string[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QChar a = ouvertureProtection_bonus_string[lecteurLigne];
                    QString ouvertureProtection_bonus = a + ouvertureProtection_bonus_string[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureProtection_bonus.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureProtection_bonus.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureProtection_bonus.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureProtection_bonus.toInt();
                        break;
                    case 12:
                        ouverture_FO = ouvertureProtection_bonus.toInt();
                        break;
                    case 15:
                        ouverture_AT = ouvertureProtection_bonus.toInt();
                        break;
                    case 18:
                        ouverture_PRD = ouvertureProtection_bonus.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Protection -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : une des protections -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }

                    lecteurLigne += 2;
                }
            }

            // Malus
            lecteurLigne = 0;
            QString ouvertureProtection_malus_string = entree.readLine();
            while (lecteurLigne < ouvertureProtection_malus_string.size())
            {
                if (ouvertureProtection_malus_string[lecteurLigne] == '_')
                    lecteurLigne++;

                else
                {
                    QChar a = ouvertureProtection_malus_string[lecteurLigne];
                    QString ouvertureProtection_malus = a + ouvertureProtection_malus_string[lecteurLigne + 1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureProtection_malus.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureProtection_malus.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureProtection_malus.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureProtection_malus.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureProtection_malus.toInt();
                        break;
                    case 15:
                        ouverture_at = ouvertureProtection_malus.toInt();
                        break;
                    case 18:
                        ouverture_prd = ouvertureProtection_malus.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Protection -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : une des protections -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }

                    lecteurLigne += 2;
                }
            }

            ouverture_PROTECTION = new Protection(ouvertureProtection_nom, ouvertureProtection_PR,
                                                  ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo, ouverture_at, ouverture_prd,
                                                  ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO, ouverture_AT, ouverture_PRD);
            tableauDePersonnages[ouvertureNom].addProtection(ouverture_PROTECTION, lecteurTableauProtection);

            delete ouverture_PROTECTION;
            lecteurTableauProtection++;
            lecteurLigne = 0;
        }

    // Pour les armes
        else if (ligne == "~!arme!~")
        {
            CARAC_A_ZERO;

            // Nom
            QString ouvertureArme_nom = entree.readLine();

            // Nombre de dés
            int ouvertureArme_nbDes = entree.readLine().toInt();

            // Nombre de dégâts en plus
            int ouvertureArme_degats = entree.readLine().toInt();

            // Bonus
            QString ouvertureArme_bonus_string = entree.readLine();
            while (lecteurLigne < ouvertureArme_bonus_string.size())
            {
                if (ouvertureArme_bonus_string[lecteurLigne] == '_')
                    lecteurLigne++;

                else
                {
                    QChar a = ouvertureArme_bonus_string[lecteurLigne];
                    QString ouvertureArme_bonus = a + ouvertureArme_bonus_string[lecteurLigne + 1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_COU = ouvertureArme_bonus.toInt();
                        break;
                    case 3:
                        ouverture_INT = ouvertureArme_bonus.toInt();
                        break;
                    case 6:
                        ouverture_CHA = ouvertureArme_bonus.toInt();
                        break;
                    case 9:
                        ouverture_AD = ouvertureArme_bonus.toInt();
                        break;
                    case 12:
                        ouverture_FO = ouvertureArme_bonus.toInt();
                        break;
                    case 15:
                        ouverture_AT = ouvertureArme_bonus.toInt();
                        break;
                    case 18:
                        ouverture_PRD = ouvertureArme_bonus.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Arme -> Caractéristiques bonus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : une des armes -> caractéristiques bonus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }

                    lecteurLigne += 2;
                }
            }

            // Malus
            lecteurLigne = 0;
            QString ouvertureArme_malus_string = entree.readLine();
            while (lecteurLigne < ouvertureArme_malus_string.size())
            {
                if (ouvertureArme_malus_string[lecteurLigne] == '_')
                    lecteurLigne++;
                else
                {
                    QChar a = ouvertureArme_malus_string[lecteurLigne];
                    QString ouvertureArme_malus = a + ouvertureArme_malus_string[lecteurLigne + 1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        ouverture_cou = ouvertureArme_malus.toInt();
                        break;
                    case 3:
                        ouverture_int = ouvertureArme_malus.toInt();
                        break;
                    case 6:
                        ouverture_cha = ouvertureArme_malus.toInt();
                        break;
                    case 9:
                        ouverture_ad = ouvertureArme_malus.toInt();
                        break;
                    case 12:
                        ouverture_fo = ouvertureArme_malus.toInt();
                        break;
                    case 15:
                        ouverture_at = ouvertureArme_malus.toInt();
                        break;
                    case 18:
                        ouverture_prd = ouvertureArme_malus.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                              "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                              "Arme -> Caractéristiques malus non valides !\n");
                        fermerOnglets();
                        log("Personnage non ouvert : une des armes -> caractéristiques malus invalides !");
                        log("Annulation du chargement du groupe !");
                        statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
                        return;
                        break;
                    }

                    lecteurLigne += 2;
                }
            }

            // Type d'arme
            int ouvertureArme_type = entree.readLine().toInt();

            // Prix
            int ouvertureArme_rupture = entree.readLine().toInt();

            // Création
            ouverture_ARME = new Arme(ouvertureArme_nom, ouvertureArme_nbDes, ouvertureArme_degats,
                                      ouverture_cou, ouverture_int, ouverture_cha, ouverture_ad, ouverture_fo, ouverture_at, ouverture_prd,
                                      ouverture_COU, ouverture_INT, ouverture_CHA, ouverture_AD, ouverture_FO, ouverture_AT, ouverture_PRD);
            ouverture_ARME->setRupture(ouvertureArme_rupture);
            switch (ouvertureArme_type)
            {
            case 0:
                ouverture_ARME->setType(Arme::MainNue);
                break;
            case 1:
                ouverture_ARME->setType(Arme::Tranchante);
                break;
            case 2:
                ouverture_ARME->setType(Arme::Contandante);
                break;
            case 3:
                ouverture_ARME->setType(Arme::Projectile);
                break;
            }

            // On ajoute l'arme au personnage
            tableauDePersonnages[ouvertureNom].addArme(ouverture_ARME, lecteurTableauArme);

            delete ouverture_ARME;
            lecteurTableauArme++;
            lecteurLigne = 0;
        }

    // Pour les flèches
        else if (ligne == "~!fleche!~")
        {
            CARAC_A_ZERO;

            // Nom
            QString ouvertureFleche_nom = entree.readLine();

            // Nombre de flèches
            QString Fleche_ligne = entree.readLine();
            int ouvertureFleche_nb = Fleche_ligne.toInt();

            // PI en +
            Fleche_ligne = entree.readLine();
            int ouvertureFleche_PI = Fleche_ligne.toInt();

            // AD en +
            Fleche_ligne = entree.readLine();
            ouverture_AD = Fleche_ligne.toInt();

            // Création
            ouverture_FLECHE = new Fleche(ouvertureFleche_nom, ouvertureFleche_nb,
                                          ouvertureFleche_PI, ouverture_AD);
            tableauDePersonnages[ouvertureNom].addFleche(ouverture_FLECHE, lecteurTableauFleche);

            delete ouverture_FLECHE;
            lecteurTableauFleche++;
            lecteurLigne = 0;
        }

    // Pour l'équipement
        else if (ligne == "~!equipement!~")
        {
            ouverture_EQUIPEMENT = entree.readLine();

            ligne = entree.readLine();

            bool fin(false);

            if (ligne == "~!equipement!~")
                fin = true;
            if (ligne == "~!competence!~")
                fin = true;

            while (!fin)
            {
                ouverture_EQUIPEMENT += "\n" + ligne;
                ligne = entree.readLine();

                if (ligne == "~!equipement!~")
                    fin = true;
                if (ligne == "~!competence!~")
                    fin = true;
            }

            tableauDePersonnages[ouvertureNom].addEquipement(ouverture_EQUIPEMENT, lecteurTableauEquipement);
            ouverture_EQUIPEMENT.clear();
            lecteurTableauEquipement++;

            progressBar_status->setValue(70);

            ligneDejaLue = true;
        }

    // Pour les compétences
        else if (ligne == "~!competence!~")
        {
            QString ouvertureCompetence_nom = entree.readLine();
            QString ouvertureCompetence_description = entree.readLine();

            ligne = entree.readLine();

            bool fin(false);

            if (ligne == "~!competence!~")
                fin = true;
            if (ligne == "~!FIN_ENREGISTREMENT!~")
                fin = true;

            while (!fin)
            {
                ouvertureCompetence_description += "\n" + ligne;
                ligne = entree.readLine();

                if (ligne == "~!competence!~")
                    fin = true;
                if (ligne == "~!FIN_ENREGISTREMENT!~")
                    fin = true;
            }
            tableauDePersonnages[ouvertureNom].addCompetence(ouvertureCompetence_nom, ouvertureCompetence_description);
            progressBar_status->setValue(80);

            ligneDejaLue = true;
        }

    // Pour finir
        else if (ligne == "~!FIN_ENREGISTREMENT!~")
            ouvertureFichierTerminee = true;

    // Dans les autres cas
        else
        {
            QMessageBox::critical(zoneCentrale, "Erreur inconnue !",
                                  "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                  "     -> " + *cheminPersoOuverture + " (" + ouvertureNom + ") !\n\n"
                                  "Elément inconnu !\n");
            log("Personnage non ouvert : élément inconnu !");
            log("Annulation du chargement du groupe !");
            fermerOnglets();
            statusBar->showMessage("Groupe non ouvert -> Erreur lors de l'ouverture du fichier \"" + *cheminPersoOuverture + "\" !");
            return;
        }
    }
}
