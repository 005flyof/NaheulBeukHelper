#include "Personnage.h"
#include "ui_Personnage.h"

Personnage::Personnage(QString fichier)
    : QScrollArea(), ui(new Ui::Personnage),
      m_fichierPerso(0),
      m_cheminEnregistrement(fichier)
{
    ui->setupUi(this);
    chargerPerso();
    setAffichage();
}
Personnage::~Personnage()
{
    delete ui;
}

void Personnage::setAffichage()
{
    ui->nom->setText(m_nom);
    ui->sexe->setText(m_sexe);
}
Caracteristiques Personnage::chargerCarac(QString ligne, bool AT_PRD, int numLigne)
{
    if (AT_PRD)
    {
        Caracteristiques renvoyer(0, 0, 0, 0, 0, 0, 0);
        int lecteur(0);
        while (lecteur < ligne.size())
        {
            QString carac("");
            carac += ligne[lecteur];
            carac += ligne[lecteur++];
            switch (lecteur - 1)
            {
            case 0:
                renvoyer.setCourage(carac.toInt());
                break;
            case 3:
                renvoyer.setIntelligence(carac.toInt());
                break;
            case 6:
                renvoyer.setCharisme(carac.toInt());
                break;
            case 9:
                renvoyer.setAdresse(carac.toInt());
                break;
            case 12:
                renvoyer.setForce(carac.toInt());
                break;
            case 15:
                renvoyer.setAttaque(carac.toInt());
                break;
            case 18:
                renvoyer.setParade(carac.toInt());
                break;
            default:
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Caractéristiques non valides !\n"
                                      "Pour plus d'informations : regardez le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a des caractéristiques invalides à la ligne " + QString::number(numLigne) + " !");
                log("Annulation du chargement du groupe !");
                return renvoyer;
                break;
            }
            lecteur += 2;
        }

        return renvoyer;
    }
    else
    {
        Caracteristiques renvoyer(0, 0, 0, 0, 0);
        int lecteur(0);
        while (lecteur < ligne.size())
        {
            QString carac("");
            carac += ligne[lecteur];
            carac += ligne[lecteur++];
            switch (lecteur - 1)
            {
            case 0:
                renvoyer.setCourage(carac.toInt());
                break;
            case 3:
                renvoyer.setIntelligence(carac.toInt());
                break;
            case 6:
                renvoyer.setCharisme(carac.toInt());
                break;
            case 9:
                renvoyer.setAdresse(carac.toInt());
                break;
            case 12:
                renvoyer.setForce(carac.toInt());
                break;
            default:
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Caractéristiques initiales non valides !\n"
                                      "Pour plus d'informations : regardez le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a des caractéristiques invalides à la ligne " + QString::number(numLigne) + " !");
                log("Annulation du chargement du groupe !");
                return renvoyer;
                break;
            }
            lecteur += 2;
        }

        return renvoyer;
    }
}

void Personnage::chargerPerso()
{
    m_fichierPerso = new QFile(m_cheminEnregistrement);
    if (!m_fichierPerso->open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Impossible d'ouvrir le fichier personnage suivant : " + m_cheminEnregistrement);

    log("Ouverture du personnage : '" + m_cheminEnregistrement + "'");

    QTextStream entree(m_fichierPerso);
    int numLigne(0);

// Informations générales
    m_nom = entree.readLine();
    numLigne++;
    m_sexe = entree.readLine();
    numLigne++;
    m_origine = entree.readLine();
    numLigne++;
    m_metier = entree.readLine();
    numLigne++;

    m_ptsDestin = entree.readLine().toInt();
    numLigne++;
    m_experience = entree.readLine().toInt();
    numLigne++;

// Caractéristiques
    m_EV = entree.readLine().toInt();
    numLigne++;

    m_carac = new Caracteristiques(chargerCarac(entree.readLine(), true, numLigne++));
    m_carac_modif = new Caracteristiques(chargerCarac(entree.readLine(), true, numLigne++));

// Richesses
    m_richesses = new Richesses(0, 0, 0);
    QString piecesLigne = entree.readLine();
    int lecteur = 0;
    while (lecteur < piecesLigne.size())
    {
        QString piecesString("");
        piecesString += piecesLigne[lecteur];           // 1
        piecesString += piecesLigne[lecteur++];         // 2
        piecesString += piecesLigne[lecteur++];         // 3
        piecesString += piecesLigne[lecteur++];         // 4
        piecesString += piecesLigne[lecteur++];         // 5
        piecesString += piecesLigne[lecteur++];         // 6

        switch (lecteur - 5)
        {
        case 0:
            m_richesses->setOr(piecesString.toInt());
            break;
        case 7:
            m_richesses->setArgent(piecesString.toInt());
            break;
        case 14:
            m_richesses->setCuivre(piecesString.toInt());
            break;
        default:
            QMessageBox::critical(ui->nom, "Erreur réparable !",
                                  "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                  "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                  "Richesses non valides !\n");
            //////////////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
            log("Personnage non ouvert : richesses invalides à la ligne " + QString::number(numLigne++) + " !");
            log("Annulation du chargement du groupe !");
            return;
            break;
        }
        lecteur += 2;
    }

// Ouverture des autres choses
    bool ouvertureFichierTerminee(false);
    int lecteurTableauVetement(0),
            lecteurTableauProtection(0),
            lecteurTableauArme(0),
            lecteurTableauFleche(0),
            lecteurTableauEquipement(0);

    bool ligneDejaLue = false;
    QString ligne = "";

    while (!ouvertureFichierTerminee)
    {
        numLigne++;
        // On charge la ligne si elle n'a pas déjà été lue
        if (!ligneDejaLue)
            ligne = entree.readLine();

        // On remet au défaut la fait que la ligne est lue ou pas
        ligneDejaLue = false;

        // Bonus de caractéristiques
        if (ligne == "~!carac_sup_inf!~")
        {
            int ouvertureDegatsBonus = entree.readLine().toInt();
            numLigne++;
            int ouvertureAttaqueBonus = entree.readLine().toInt();
            numLigne++;
            int ouvertureParadeBonus = entree.readLine().toInt();
            numLigne++;
            int ouvertureDegatsBonusSorts = entree.readLine().toInt();
            numLigne++;
        }

        // Si le perso est magicien
        else if (ligne == "~!magie!~")
        {
            m_EA = entree.readLine().toInt();
            numLigne++;
            m_typeEA = entree.readLine();
            numLigne++;
        }

        // Pour les vêtements
        else if (ligne == "~!chapeau!~"
                 || ligne == "~!haut!~"
                 || ligne == "~!bas!~"
                 || ligne == "~!chaussures!~"
                 || ligne == "~!divers!~"
                 || ligne == "~!vetement!~")
        {
            if (lecteurTableauVetement >= MAX_VETEMENT)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop de vêtements\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a trop de vêtements pour ce personnage (nombre max de vêtements : " + QString::number(MAX_VETEMENT) + ") !");
                log("Annulation du chargement du groupe !");
            }
            else
            {
                m_vetements[lecteurTableauVetement] = new Vetement(entree.readLine(),
                                                                   0, 0, 0, 0, 0,
                                                                   0, 0, 0, 0, 0);
                numLigne++;
                m_vetements[lecteurTableauVetement]->setBonus(chargerCarac(entree.readLine(), false, numLigne));
                numLigne++;
                m_vetements[lecteurTableauVetement]->setMalus(chargerCarac(entree.readLine(), false, numLigne));
                numLigne++;

                lecteurTableauVetement++;
            }
        }

        // Pour les protections
        else if (ligne == "~!protection!~")
        {
            if (lecteurTableauProtection >= MAX_PROTECTION)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop de protections\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a trop de protections pour ce personnage (nombre max de protections : " + QString::number(MAX_PROTECTION) + ") !");
                log("Annulation du chargement du groupe !");
            }
            else
            {
                m_protections[lecteurTableauProtection] = new Protection(entree.readLine(), entree.readLine().toInt(),
                                                                         0, 0, 0, 0, 0, 0, 0,
                                                                         0, 0, 0, 0, 0, 0, 0);
                numLigne++;
                numLigne++;
                m_protections[lecteurTableauProtection]->setBonus(chargerCarac(entree.readLine(), true, numLigne));
                numLigne++;
                m_protections[lecteurTableauProtection]->setMalus(chargerCarac(entree.readLine(), true, numLigne));
                numLigne++;

                lecteurTableauProtection++;
            }
        }

        // Pour les protections
        else if (ligne == "~!arme!~")
        {
            if (lecteurTableauArme >= MAX_ARME)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop d'armes\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a trop d'armes pour ce personnage (nombre max d'armes : " + QString::number(MAX_ARME) + ") !");
                log("Annulation du chargement du groupe !");
            }
            else
            {
                m_armes[lecteurTableauArme] = new Arme(entree.readLine(),               // nom
                                                       entree.readLine().toInt(),       // nb des
                                                       entree.readLine().toInt(),       // degats
                                                       0, 0, 0, 0, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 0);
                numLigne++;
                numLigne++;
                numLigne++;
                m_armes[lecteurTableauArme]->setBonus(chargerCarac(entree.readLine(), true, numLigne));
                numLigne++;
                m_armes[lecteurTableauArme]->setMalus(chargerCarac(entree.readLine(), true, numLigne));
                numLigne++;
                int type = entree.readLine().toInt();
                numLigne++;
                switch (type)
                {
                case 0:
                    m_armes[lecteurTableauArme]->setType(Arme::MainNue);
                    break;
                case 1:
                    m_armes[lecteurTableauArme]->setType(Arme::Tranchante);
                    break;
                case 2:
                    m_armes[lecteurTableauArme]->setType(Arme::Contandante);
                    break;
                case 3:
                    m_armes[lecteurTableauArme]->setType(Arme::Projectile);
                    break;
                }
                m_armes[lecteurTableauArme]->setRupture(entree.readLine().toInt());
                numLigne++;

                lecteurTableauArme++;
            }
        }

        // Pour les flèches
        else if (ligne == "~!fleche!~")
        {
            if (lecteurTableauFleche >= MAX_FLECHE)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop de flèches"
                                      "Pour plus d'informations : regarder le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a trop de flèches pour ce personnage (nombre max de flèches : " + QString::number(MAX_FLECHE) + ") !");
                log("Annulation du chargement du groupe !");
            }
            else
            {
                m_fleches[lecteurTableauFleche] = new Fleche(entree.readLine(),             // nom
                                                             entree.readLine().toInt(),     // nb
                                                             entree.readLine().toInt(),     // PI
                                                             entree.readLine().toInt());    // bonus AD
                numLigne++;
                numLigne++;
                numLigne++;
                numLigne++;

                lecteurTableauFleche++;
            }
        }

        // Pour l'équipement
        else if (ligne == "~!equipement!~")
        {
            if (lecteurTableauEquipement >= MAX_EQUIPEMENT)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop d'équipements\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                //////////////////////////////////////////////////////////////////////////////////////////////fermerOnglets();
                log("Personnage non ouvert : il y a trop d'équipements pour ce personnage (nombre max d'équipements : " + QString::number(MAX_EQUIPEMENT) + ") !");
                log("Annulation du chargement du groupe !");
            }
            else
            {
                m_equipements[lecteurTableauEquipement] = entree.readLine();
                numLigne++;

                // On charge la ligne suivante pour vérifier que l'équipement n'est pas sur plusieurs lignes
                ligne = entree.readLine();

                bool fin(false);

                // On vérifier que c'est pas un autre objet qui commence
                if (ligne == "~!equipement!~")
                    fin = true;
                if (ligne == "~!competence!~")
                    fin = true;

                // On inscrit la ligne dans l'équipement tant que ce n'est pas un autre objet
                while (!fin)
                {
                    m_equipements[lecteurTableauEquipement] += "\n" + ligne;
                    numLigne++;
                    ligne = entree.readLine();

                    if (ligne == "~!equipement!~")
                        fin = true;
                    if (ligne == "~!competence!~")
                        fin = true;
                }

                // On dit au programme que la ligne est déjà lue
                ligneDejaLue = true;

                // On ajoute un équipement :)
                lecteurTableauEquipement++;
            }
        }

        // Pour les compétences
        else if (ligne == "~!competence!~")
        {
            QString nomCompetence = entree.readLine();
            numLigne++;
            QString descriptionCompetence = entree.readLine();
            numLigne++;

            // On vérifier que la ligne suivante n'est pas la suite de la compétence
            ligne = entree.readLine();

            bool fin(false);

            if (ligne == "~!competence!~")
                fin = true;
            if (ligne == "~!FIN_ENREGISTREMENT!~")
                fin = true;

            while (!fin)
            {
                descriptionCompetence += "\n" + ligne;
                numLigne++;
                ligne = entree.readLine();

                if (ligne == "~!competence!~")
                    fin = true;
                if (ligne == "~!FIN_ENREGISTREMENT!~")
                    fin = true;
            }

            // On ajoute la compétence
            m_competences.push_back(new Competence(nomCompetence, descriptionCompetence));

            // On indique au programme que la ligne est déjà lue
            ligneDejaLue = true;
        }

        // Pour finir
        else if (ligne == "~!FIN_ENREGISTREMENT!~")
            ouvertureFichierTerminee = true;

        // Dans les autres cas
        else
        {
            QMessageBox::critical(ui->nom, "Erreur inconnue !",
                                  "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                  "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                  "Elément inconnu !\n");
            log("Personnage non ouvert : élément inconnu à la ligne " + QString::number(numLigne) + " !");
            log("Annulation du chargement du groupe !");
            /////////////////////////////////////////////////////////////////////////fermerOnglets();
            return;
        }
    }

    log("Personnage chargé !");
    m_fichierPerso->close();
}
void Personnage::enregistrerPerso()
{
    QString total = "";

    total += m_nom + "\n";
    total += m_sexe + "\n";
    total += m_origine + "\n";
    total += m_metier + "\n";
    total += QString::number(m_EV) + "\n";
    total += QString::number(m_ptsDestin) + "\n";
    total += QString::number(m_experience) + "\n";
    total += m_carac->caracEnregistrement() + "\n";
    total += m_carac_modif->caracEnregistrement() + "\n";

    total += m_richesses->richessesEnregistrement() + "\n";

    /* Bonus de caractéristiques
    total += "~!carac_sup_inf!~\n";
    total += QString::number(m_degatsBonus) + "\n";
    total += QString::number(m_attaqueBonus) + "\n";
    total += QString::number(m_paradeBonus) + "\n";
    total += QString::number(m_degatsBonusSorts) + "\n";*/

    if (m_presenceEA)
        total += "~!magie!~\n" + QString::number(m_EA) + "\n" + m_typeEA + "\n";

    for (int lecteur = 0; lecteur < MAX_VETEMENT; lecteur++)
        total += "~!vetement!~\n" + m_vetements[lecteur]->vetementEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_PROTECTION; lecteur++)
        total += m_protections[lecteur]->protectionEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_ARME; lecteur++)
        total += m_armes[lecteur]->armeEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_FLECHE; lecteur++)
        total += m_fleches[lecteur]->flechesEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_EQUIPEMENT; lecteur++)
        total += "~!equipement!~\n" + m_equipements[lecteur] + "\n";

    for (int lecteur = 0; lecteur < m_competences.count(); lecteur++)
    {
        total += "~!competence!~\n";
        total += m_competences.at(lecteur)->getNom() + "\n";
        total += m_competences.at(lecteur)->getDescription() + "\n";
    }

    total += "~!FIN_ENREGISTREMENT!~";

// Eregistrement
    if (m_fichierPerso == 0)
        fatalError("Impossible d'enregistrer le personnage : il n'a pas été chargé.\n\n"
                   "Le programme va être arrêter car c'est une erreur de programmation.\n"
                   "Veuillez signaler ce bug sur : " SITE_BUGS);
    if (!m_fichierPerso->open(QIODevice::WriteOnly | QIODevice::Text))
        fatalError("Impossible d'enregistrer le fichier de personnage sélectionné.");

    QTextStream sortie(m_fichierPerso);

    sortie << total;

    log("'" + m_nom + "' a été enregistré !");
    m_fichierPerso->close();
}

void Personnage::on_nomEdit_clicked(bool checked)
{
    if (!checked)
        m_nom = ui->nom->text();
    else
        ui->nom->setText(m_nom);

    ui->nom->setEnabled(checked);
}
void Personnage::on_sexeEdit_clicked(bool checked)
{
    if (!checked)
        m_sexe = ui->sexe->text();
    else
        ui->sexe->setText(m_sexe);

    ui->sexe->setEnabled(checked);
}
