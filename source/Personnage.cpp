#include "Personnage.h"
#include "ui_Personnage.h"

Personnage::Personnage(QString fichier)
    : QScrollArea(), ui(new Ui::Personnage),
      m_fichierPerso(0),
      m_cheminEnregistrement(fichier)
{
    ui->setupUi(this);
    chargerPerso();
    setNiveau();
    setAffichage();
}
Personnage::~Personnage()
{
    delete ui;
}

void Personnage::setAffichage()
{
// Informations générales
    ui->nom->setText(m_nom);
    ui->sexe->setText(m_sexe);
    ui->origine->setText(m_origine);
    ui->metier->setText(m_metier);

    ui->lvl->setText(QString::number(m_niveau));
    ui->xp->setText(QString::number(m_experience));
    ui->destin->setText(QString::number(m_ptsDestin));

// Richesses
    rafraichirRichesses();

// Caractéristiques
    ui->ev->setText(QString::number(m_EV));
    ui->evModif->setText(QString::number(m_EV_modif));

    if (m_presenceEA)
    {
        ui->ea->setText(QString::number(m_EA));
        ui->eaModif->setText(QString::number(m_EA_modif));
        ui->typeEa->setText(m_typeEA);
        ui->magiePhys->setText(QString::number((m_carac_modif->getIntelligence() + m_carac_modif->getAdresse() ) / 2));
        ui->magiePsy->setText(QString::number((m_carac_modif->getIntelligence() + m_carac_modif->getCharisme() ) / 2));
    }
    else
    {
        ui->eaModif->setEnabled(false);
        ui->eaPlus->setEnabled(false);
        ui->eaMoins->setEnabled(false);

        ui->ea->setText("-");
        ui->eaModif->setText("-");
        ui->typeEa->setText("-");
        ui->magiePhys->setText("-");
        ui->magiePsy->setText("-");
    }
    ui->resistMagie->setText(QString::number((m_carac_modif->getIntelligence() + m_carac_modif->getCourage() + m_carac_modif->getForce() ) / 3));

    ui->cou->setText(QString::number(m_carac->getCourage()));
    ui->couModif->setText(QString::number(m_carac_modif->getCourage()));
    ui->intel->setText(QString::number(m_carac->getIntelligence()));
    ui->intelModif->setText(QString::number(m_carac_modif->getIntelligence()));
    ui->cha->setText(QString::number(m_carac->getCharisme()));
    ui->chaModif->setText(QString::number(m_carac_modif->getCharisme()));
    ui->ad->setText(QString::number(m_carac->getAdresse()));
    ui->adModif->setText(QString::number(m_carac_modif->getAdresse()));
    ui->fo->setText(QString::number(m_carac->getForce()));
    ui->foModif->setText(QString::number(m_carac_modif->getForce()));
    ui->at->setText(QString::number(m_carac->getAttaque()));
    ui->atModif->setText(QString::number(m_carac_modif->getAttaque()));
    ui->prd->setText(QString::number(m_carac->getParade()));
    ui->prdModif->setText(QString::number(m_carac_modif->getParade()));

// Protections
    ui->prNom_1->setText(m_protections[0]->getNom());
    ui->prBonus_1->setText(m_protections[0]->getBonusAffichage());
    ui->prMalus_1->setText(m_protections[0]->getMalusAffichage());
    ui->prPr_1->setText(QString::number(m_protections[0]->getNbPR()));
    ui->prRupt_1->setText("A faire !!");

    ui->prNom_2->setText(m_protections[1]->getNom());
    ui->prBonus_2->setText(m_protections[1]->getBonusAffichage());
    ui->prMalus_2->setText(m_protections[1]->getMalusAffichage());
    ui->prPr_2->setText(QString::number(m_protections[1]->getNbPR()));
    ui->prRupt_2->setText("A faire !!");

    ui->prNom_3->setText(m_protections[2]->getNom());
    ui->prBonus_3->setText(m_protections[2]->getBonusAffichage());
    ui->prMalus_3->setText(m_protections[2]->getMalusAffichage());
    ui->prPr_3->setText(QString::number(m_protections[2]->getNbPR()));
    ui->prRupt_3->setText("A faire !!");

    ui->prNom_4->setText(m_protections[3]->getNom());
    ui->prBonus_4->setText(m_protections[3]->getBonusAffichage());
    ui->prMalus_4->setText(m_protections[3]->getMalusAffichage());
    ui->prPr_4->setText(QString::number(m_protections[3]->getNbPR()));
    ui->prRupt_4->setText("A faire !!");

    ui->prNom_5->setText(m_protections[4]->getNom());
    ui->prBonus_5->setText(m_protections[4]->getBonusAffichage());
    ui->prMalus_5->setText(m_protections[4]->getMalusAffichage());
    ui->prPr_5->setText(QString::number(m_protections[4]->getNbPR()));
    ui->prRupt_5->setText("A faire !!");

    ui->prNom_6->setText(m_protections[5]->getNom());
    ui->prBonus_6->setText(m_protections[5]->getBonusAffichage());
    ui->prMalus_6->setText(m_protections[5]->getMalusAffichage());
    ui->prPr_6->setText(QString::number(m_protections[5]->getNbPR()));
    ui->prRupt_6->setText("A faire !!");

    ui->prTotale->setText(QString::number(m_prTotale));

// Armes
    ui->armesNom_1->setText(m_armes[0]->getNom());
    ui->armesBonus_1->setText(m_armes[0]->getBonusAffichage());
    ui->armesMalus_1->setText(m_armes[0]->getMalusAffichage());
    ui->armesPi_1->setText(m_armes[0]->getDegatsAffichage());
    ui->armesRupt_1->setText("A faire !!");

    ui->armesNom_2->setText(m_armes[1]->getNom());
    ui->armesBonus_2->setText(m_armes[1]->getBonusAffichage());
    ui->armesMalus_2->setText(m_armes[1]->getMalusAffichage());
    ui->armesPi_2->setText(m_armes[1]->getDegatsAffichage());
    ui->armesRupt_2->setText("A faire !!");

    ui->armesNom_3->setText(m_armes[2]->getNom());
    ui->armesBonus_3->setText(m_armes[2]->getBonusAffichage());
    ui->armesMalus_3->setText(m_armes[2]->getMalusAffichage());
    ui->armesPi_3->setText(m_armes[2]->getDegatsAffichage());
    ui->armesRupt_3->setText("A faire !!");

    ui->armesNom_4->setText(m_armes[3]->getNom());
    ui->armesBonus_4->setText(m_armes[3]->getBonusAffichage());
    ui->armesMalus_4->setText(m_armes[3]->getMalusAffichage());
    ui->armesPi_4->setText(m_armes[3]->getDegatsAffichage());
    ui->armesRupt_4->setText("A faire !!");

// Flèches
    ui->flechesNom_1->setText(m_fleches[0]->getNom());
    ui->flechesBonus_1->setText(m_fleches[0]->getBonusAffichage());
    ui->flechesNb_1->setText(QString::number(m_fleches[0]->getNombre()));
    if (m_fleches[0]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_1->setEnabled(false);
        ui->flechesPlus_1->setEnabled(false);
        ui->flechesMoins_1->setEnabled(false);
    }
    else if (m_fleches[0]->getNombre() == 0)
    {
        ui->flechesNb_1->setEnabled(true);
        ui->flechesPlus_1->setEnabled(true);
        ui->flechesMoins_1->setEnabled(false);
    }
    else
    {
        ui->flechesNb_1->setEnabled(true);
        ui->flechesPlus_1->setEnabled(true);
        ui->flechesMoins_1->setEnabled(true);
    }

    ui->flechesNom_2->setText(m_fleches[1]->getNom());
    ui->flechesBonus_2->setText(m_fleches[1]->getBonusAffichage());
    ui->flechesNb_2->setText(QString::number(m_fleches[1]->getNombre()));
    if (m_fleches[1]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_2->setEnabled(false);
        ui->flechesPlus_2->setEnabled(false);
        ui->flechesMoins_2->setEnabled(false);
    }
    else if (m_fleches[1]->getNombre() == 0)
    {
        ui->flechesNb_2->setEnabled(true);
        ui->flechesPlus_2->setEnabled(true);
        ui->flechesMoins_2->setEnabled(false);
    }
    else
    {
        ui->flechesNb_2->setEnabled(true);
        ui->flechesPlus_2->setEnabled(true);
        ui->flechesMoins_2->setEnabled(true);
    }

    ui->flechesNom_3->setText(m_fleches[2]->getNom());
    ui->flechesBonus_3->setText(m_fleches[2]->getBonusAffichage());
    ui->flechesNb_3->setText(QString::number(m_fleches[2]->getNombre()));
    if (m_fleches[2]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_3->setEnabled(false);
        ui->flechesPlus_3->setEnabled(false);
        ui->flechesMoins_3->setEnabled(false);
    }
    else if (m_fleches[2]->getNombre() == 0)
    {
        ui->flechesNb_3->setEnabled(true);
        ui->flechesPlus_3->setEnabled(true);
        ui->flechesMoins_3->setEnabled(false);
    }
    else
    {
        ui->flechesNb_3->setEnabled(true);
        ui->flechesPlus_3->setEnabled(true);
        ui->flechesMoins_3->setEnabled(true);
    }

    ui->flechesNom_4->setText(m_fleches[3]->getNom());
    ui->flechesBonus_4->setText(m_fleches[3]->getBonusAffichage());
    ui->flechesNb_4->setText(QString::number(m_fleches[3]->getNombre()));
    if (m_fleches[3]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_4->setEnabled(false);
        ui->flechesPlus_4->setEnabled(false);
        ui->flechesMoins_4->setEnabled(false);
    }
    else if (m_fleches[3]->getNombre() == 0)
    {
        ui->flechesNb_4->setEnabled(true);
        ui->flechesPlus_4->setEnabled(true);
        ui->flechesMoins_4->setEnabled(false);
    }
    else
    {
        ui->flechesNb_4->setEnabled(true);
        ui->flechesPlus_4->setEnabled(true);
        ui->flechesMoins_4->setEnabled(true);
    }

    ui->flechesNom_5->setText(m_fleches[4]->getNom());
    ui->flechesBonus_5->setText(m_fleches[4]->getBonusAffichage());
    ui->flechesNb_5->setText(QString::number(m_fleches[4]->getNombre()));
    if (m_fleches[4]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_5->setEnabled(false);
        ui->flechesPlus_5->setEnabled(false);
        ui->flechesMoins_5->setEnabled(false);
    }
    else if (m_fleches[4]->getNombre() == 0)
    {
        ui->flechesNb_5->setEnabled(true);
        ui->flechesPlus_5->setEnabled(true);
        ui->flechesMoins_5->setEnabled(false);
    }
    else
    {
        ui->flechesNb_5->setEnabled(true);
        ui->flechesPlus_5->setEnabled(true);
        ui->flechesMoins_5->setEnabled(true);
    }

// Vêtements
    ui->vetNom_1->setText(m_vetements[0]->getNom());
    ui->vetBonus_1->setText(m_vetements[0]->getBonusAffichage());
    ui->vetMalus_1->setText(m_vetements[0]->getMalusAffichage());
    ui->vetVisible_1->setChecked(true);

    ui->vetNom_2->setText(m_vetements[1]->getNom());
    ui->vetBonus_2->setText(m_vetements[1]->getBonusAffichage());
    ui->vetMalus_2->setText(m_vetements[1]->getMalusAffichage());
    ui->vetVisible_2->setChecked(true);

    ui->vetNom_3->setText(m_vetements[2]->getNom());
    ui->vetBonus_3->setText(m_vetements[2]->getBonusAffichage());
    ui->vetMalus_3->setText(m_vetements[2]->getMalusAffichage());
    ui->vetVisible_3->setChecked(true);

    ui->vetNom_4->setText(m_vetements[3]->getNom());
    ui->vetBonus_4->setText(m_vetements[3]->getBonusAffichage());
    ui->vetMalus_4->setText(m_vetements[3]->getMalusAffichage());
    ui->vetVisible_4->setChecked(true);

    ui->vetNom_5->setText(m_vetements[4]->getNom());
    ui->vetBonus_5->setText(m_vetements[4]->getBonusAffichage());
    ui->vetMalus_5->setText(m_vetements[4]->getMalusAffichage());
    ui->vetVisible_5->setChecked(true);

// Equipements
    ui->equips_1->setText(m_equipements[0]);
    ui->equips_2->setText(m_equipements[1]);
    ui->equips_3->setText(m_equipements[2]);
    ui->equips_4->setText(m_equipements[3]);
    ui->equips_5->setText(m_equipements[4]);
    ui->equips_6->setText(m_equipements[5]);
    ui->equips_7->setText(m_equipements[6]);
    ui->equips_8->setText(m_equipements[7]);
    ui->equips_9->setText(m_equipements[8]);
    ui->equips_10->setText(m_equipements[9]);
}
void Personnage::viderVariables()
{
    m_nom = "";
    m_sexe = "";
    m_origine = "";
    m_metier = "";

    m_EV = 0;
    m_EV_modif = 0;

    m_presenceEA = false;
    m_EA = 0;
    m_EA_modif = 0;
    m_typeEA = "";

    m_carac = 0;
    m_carac_modif = 0;

    m_ptsDestin = 0;
    m_niveau = 0;
    m_experience = 0;

    m_richesses = 0;

    for (int lecteur = 0; lecteur < MAX_VETEMENT; lecteur++)
        m_vetements[lecteur] = 0;

    for (int lecteur = 0; lecteur < MAX_EQUIPEMENT; lecteur++)
        m_equipements[lecteur] = "";

    for (int lecteur = 0; lecteur < MAX_PROTECTION; lecteur++)
        m_protections[lecteur] = 0;
    m_prTotale = 0;

    for (int lecteur = 0; lecteur < MAX_ARME; lecteur++)
        m_armes[lecteur] = 0;

    for (int lecteur = 0; lecteur < MAX_FLECHE; lecteur++)
        m_fleches[lecteur] = 0;
}
void Personnage::rafraichirRichesses()
{
// PO
    ui->po->setText(QString::number(m_richesses->getOr()));
    if (m_richesses->getOr() == -999999)
    {
        ui->poMoins->setEnabled(false);
        ui->poPlus->setEnabled(true);
    }
    else if (m_richesses->getOr() == 999999)
    {
        ui->poMoins->setEnabled(true);
        ui->poPlus->setEnabled(false);
    }
    else
    {
        ui->poMoins->setEnabled(true);
        ui->poPlus->setEnabled(true);
    }

// PA
    ui->pa->setText(QString::number(m_richesses->getArgent()));
    if (m_richesses->getArgent() == -999999)
    {
        ui->paMoins->setEnabled(false);
        ui->paPlus->setEnabled(true);
    }
    else if (m_richesses->getArgent() == 999999)
    {
        ui->paMoins->setEnabled(true);
        ui->paPlus->setEnabled(false);
    }
    else
    {
        ui->paMoins->setEnabled(true);
        ui->paPlus->setEnabled(true);
    }

// PC
    ui->pc->setText(QString::number(m_richesses->getCuivre()));
    if (m_richesses->getCuivre() == -999999)
    {
        ui->pcMoins->setEnabled(false);
        ui->pcPlus->setEnabled(true);
    }
    else if (m_richesses->getCuivre() == 999999)
    {
        ui->pcMoins->setEnabled(true);
        ui->pcPlus->setEnabled(false);
    }
    else
    {
        ui->pcMoins->setEnabled(true);
        ui->pcPlus->setEnabled(true);
    }
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
            carac += ligne.at(lecteur);
            carac += ligne.at(lecteur + 1);
            switch (lecteur)
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
            lecteur += 3;
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
            carac += ligne.at(lecteur);
            carac += ligne.at(lecteur + 1);
            switch (lecteur)
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
            lecteur += 3;
        }

        return renvoyer;
    }
}

void Personnage::chargerPerso()
{
    viderVariables();

    m_fichierPerso = new QFile(m_cheminEnregistrement);
    if (!m_fichierPerso->open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Impossible d'ouvrir le fichier personnage suivant : " + m_cheminEnregistrement);

    log("Ouverture du personnage : '" + m_cheminEnregistrement + "'");

    QTextStream entree(m_fichierPerso);
    int numLigne(1);

// Informations générales
    m_nom = entree.readLine();
    numLigne++;
    m_sexe = entree.readLine();
    numLigne++;
    m_origine = entree.readLine();
    numLigne++;
    m_metier = entree.readLine();
    numLigne++;

// Energie Vitale
    m_EV = entree.readLine().toInt();
    numLigne++;

// Informations générales (suite)
    m_ptsDestin = entree.readLine().toInt();
    numLigne++;
    m_experience = entree.readLine().toInt();
    numLigne++;

// Caractéristiques
    m_carac = new Caracteristiques(chargerCarac(entree.readLine(), true, numLigne++));
    m_carac_modif = new Caracteristiques(chargerCarac(entree.readLine(), true, numLigne++));

// Richesses
    m_richesses = new Richesses(0, 0, 0);
    QString piecesLigne = entree.readLine();
    int lecteur = 0;
    while (lecteur < piecesLigne.size())
    {
        QString piecesString("");
        piecesString += piecesLigne.at(lecteur);
        piecesString += piecesLigne.at(lecteur + 1);
        piecesString += piecesLigne.at(lecteur + 2);
        piecesString += piecesLigne.at(lecteur + 3);
        piecesString += piecesLigne.at(lecteur + 4);
        piecesString += piecesLigne.at(lecteur + 5);

        switch (lecteur)
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
        lecteur += 7;
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
        total += m_vetements[lecteur]->vetementEnregistrement() + "\n";

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

bool Personnage::setNiveau()
{
    int niveauAncien = m_niveau;

    if (m_experience == 0 || m_experience < 100)
    {
        m_niveau = 1;
    }
    else if (m_experience == 100 || m_experience < 300)
    {
        m_niveau = 2;
    }
    else if (m_experience == 300 || m_experience < 600)
    {
        m_niveau = 3;
    }
    else if (m_experience == 600 || m_experience < 1000)
    {
        m_niveau = 4;
    }
    else if (m_experience == 1000 || m_experience < 1500)
    {
        m_niveau = 5;
    }
    else if (m_experience == 1500 || m_experience < 2100)
    {
        m_niveau = 6;
    }
    else if (m_experience == 2100 || m_experience < 2800)
    {
        m_niveau = 7;
    }
    else if (m_experience == 2800 || m_experience < 3600)
    {
        m_niveau = 8;
    }
    else if (m_experience == 3600 || m_experience < 4500)
    {
        m_niveau = 9;
    }
    else if (m_experience == 4500 || m_experience < 5500)
    {
        m_niveau = 10;
    }
    else if (m_experience == 5500 || m_experience < 6600)
    {
        m_niveau = 11;
    }
    else if (m_experience == 6600 || m_experience < 7800)
    {
        m_niveau = 12;
    }
    else if (m_experience == 7800 || m_experience < 9100)
    {
        m_niveau = 13;
    }
    else if (m_experience == 9100 || m_experience < 10500)
    {
        m_niveau = 14;
    }
    else if (m_experience == 10500 || m_experience < 12000)
    {
        m_niveau = 15;
    }
    else if (m_experience == 12000 || m_experience < 13600)
    {
        m_niveau = 16;
    }
    else if (m_experience == 13600 || m_experience < 15300)
    {
        m_niveau = 17;
    }
    else if (m_experience == 15300 || m_experience < 17100)
    {
        m_niveau = 18;
    }
    else if (m_experience == 17100 || m_experience < 19000)
    {
        m_niveau = 19;
    }
    else if (m_experience == 19000 || m_experience < 21000)
    {
        m_niveau = 20;
    }
    else if (m_experience == 21000 || m_experience < 24000)
    {
        m_niveau = 21;
    }
    else if (m_experience == 24000 || m_experience < 29000)
    {
        m_niveau = 22;
    }
    else if (m_experience == 29000 || m_experience < 35000)
    {
        m_niveau = 23;
    }
    else if (m_experience == 35000 || m_experience < 45000)
    {
        m_niveau = 24;
    }
    else if (m_experience == 45000 || m_experience < 60000)
    {
        m_niveau = 25;
    }
    else if (m_experience >= 6000)
    {
        m_niveau = 26;
    }

    ui->lvl->setText(QString::number(m_niveau));

    // Si le niveau est modifié, on renvoie 'true'
    if (niveauAncien != m_niveau)
        return true;
    else
        return false;
}

// Slots perso
void Personnage::ajouterXP(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int XP_EnPlus = QInputDialog::getInteger(ui->nom, "Ajouter de l'expérience", "Ajouter de l'expérience à " + m_nom, 1, 1, 999999, 1, &ok);

        if (ok)
        {
            m_experience += XP_EnPlus;

            log(m_nom + " gagne de l'expérience : " + QString::number(XP_EnPlus) + " point(s) !");
        }
    }
    else
    {
        m_experience += value;

        log(m_nom + " gagne de l'expérience : " + QString::number(value) + " point(s) !");
    }

    if (setNiveau())
    {
    // On informe le MJ que le perso a gagné un niveau
        QString D;
        QMessageBox::information(this, "Niveau", m_nom + " a gagné un niveau, nous allons voir les modifications...");
        log(m_nom + "a gagné un niveau ! Les modifications faites en raison de ce nouveau niveau sont citées en dessous...");


    // On demande de quelle type est l'origine pour l'ajout d'EV
        QStringList D6_D4;
        D6_D4 << "D6" << "D4";
        D = QInputDialog::getItem(this, m_nom + " -> Passage d'un niveau -> EV",
                                  "De quel type de dé l'origine de ce personnage a besoin pour l'ajout d'EV ?",
                                  D6_D4);
        int ev;
        if (D == "D6")
        {
            ev = QInputDialog::getInt(this, m_nom + " -> Passage d'un niveau -> EV",
                                      "Quel score le D6 indique-t-il ?", 1, 1, 6);
            m_EV += ev;
            QMessageBox::information(this, "Information sur l'EV de " + m_nom,
                                     "Ce personnage gagne " + QString::number(ev) + " point(s) d'EV en plus");
            log(m_nom + " gagne " + QString::number(ev) + " point(s) d'EV en plus à cause de son nouveau niveau.");
        }
        else if (D == "D4")
        {
            ev = QInputDialog::getInt(this, m_nom + " -> Passage d'un niveau -> EV",
                                      "Quel score le D4 indique-t-il ?", 1, 1, 4);
            m_EV += ev;
            QMessageBox::information(this, "Information sur l'EV de " + m_nom,
                                     "Ce personnage gagne " + QString::number(ev) + " point(s) d'EV en plus");
            log(m_nom + " gagne " + QString::number(ev) + " point(s) d'EV en plus à cause de son nouveau niveau.");
        }


    // Si le perso est un sorcier il peut recevoir de l'EA en plus
        if (m_presenceEA)
        {
            int ea = QInputDialog::getInt(this, m_nom + " -> Passage d'un niveau -> EA",
                                          "EA -> Quel score le D6 indique-t-il ?", 1, 1, 6);
            m_EA += ea;
            QMessageBox::information(this, "Information sur l'EA de " + m_nom,
                                     "Ce personnage gagne " + QString::number(ea) + " point(s) d'EA en plus");

            log(m_nom + " gagne " + QString::number(ea) + " point(s) d'EA en plus à cause de son nouveau niveau.");
        }


    // Ajout de  pt sur une carac au choix du joueur
        QStringList carac;
        if (m_carac->getCourage() < 18)
            carac << "COU (" + QString::number(m_carac->getCourage()) + ")";
        if (m_carac->getIntelligence() < 18)
            carac << "INT (" + QString::number(m_carac->getIntelligence()) + ")";
        if (m_carac->getAdresse() < 18)
            carac << "AD (" + QString::number(m_carac->getAdresse()) + ")";
        if (m_carac->getForce() < 18)
            carac << "FO (" + QString::number(m_carac->getForce()) + ")";
        D = QInputDialog::getItem(this, m_nom + " -> Passage d'un niveau -> Caractéristiques",
                                  "Ce personnage a droit à un point en plus sur les caractéristiques suivantes.\n"
                                  "Choisissez en une !",
                                  carac);
        if (D == "COU (" + QString::number(m_carac->getCourage()) + ")")
        {
            if (m_carac->getCourage() <= 18)
            {
                QMessageBox::information(this, "Information sur le COU de " + m_nom,
                                         "Ce personnage gagne 1 point de COU en plus, en raison de son nouveau niveau");
                m_carac->setCourage(m_carac->getCourage() + 1);
                log(m_nom + " gagne 1 point de COU à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur le COU de " + m_nom,
                                         m_nom + " était censé gagner un point de COU en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }
        else if (D == "INT (" + QString::number(m_carac->getIntelligence()) + ")")
        {
            if (m_carac->getIntelligence() <= 18)
            {
                QMessageBox::information(this, "Information sur l'INT de " + m_nom,
                                         "Ce personnage gagne 1 point d'INT en plus en raison de son nouveau niveau.");
                m_carac->setIntelligence(m_carac->getIntelligence() + 1);
                log(m_nom + " gagne 1 point d'INT à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur l'INT de " + m_nom,
                                         m_nom + " était censé gagner un point d'INT en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }
        else if (D == "AD (" + QString::number(m_carac->getAdresse()) + ")")
        {
            if (m_carac->getAdresse() <= 18)
            {
                QMessageBox::information(this, "Information sur l'AD de " + m_nom,
                                         "Ce personnage gagne 1 point d'AD en plus en raison de son nouveau niveau.");
                m_carac->setAdresse(m_carac->getAdresse() + 1);
                log(m_nom + " gagne 1 point d'AD à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur l'AD de " + m_nom,
                                         m_nom + " était censé gagner un point d'AD en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }
        else if (D == "FO (" + QString::number(m_carac->getForce()) + ")")
        {
            if (m_carac->getForce() <= 18)
            {
                QMessageBox::information(this, "Information sur la FO de " + m_nom,
                                         "Ce personnage gagne 1 point de FO en plus, en raison de son nouveau niveau");
                m_carac->setForce(m_carac->getForce() + 1);
                log(m_nom + " gagne 1 point de FO à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur la FO de " + m_nom,
                                         m_nom + " était censé gagner un point de FO en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }


    // si le joueur peut gagner un point de CHA
        if (m_origine == "Elfe Sylvain" || m_origine == "Haut-elfe")
        {
            if (m_carac->getCharisme() <= 18)
            {
                QMessageBox::information(this, "Information sur le CHA de " + m_nom,
                                         "Ce personnage gagne 1 point de CHA en plus, en raison de son origine et de son nouveau niveau");
                m_carac->setCharisme(m_carac->getCharisme() + 1);
                log(m_nom + " gagne 1 point de CHA à cause de son nouveau niveau et de son origine.");
            }
            else
                QMessageBox::information(this, "Information sur le CHA de " + m_nom,
                                         m_nom + " était censé gagner un point de CHA en raison de son origine et de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }


    // Ajout de points sur l'attaque ou la parade
        if (m_carac->getAttaque() < 18 && m_carac->getParade() < 17)
        {
            QStringList At_Prd;
            At_Prd << "AT (" + QString::number(m_carac->getAttaque()) + ")"
                   << "PRD (" + QString::number(m_carac->getParade()) + ")";
            D = QInputDialog::getItem(this, m_nom + " -> Passage d'un niveau -> AT / PRD",
                                      "Ce personnage a droit à un point en plus sur les caractéristiques suivantes.\n"
                                      "Choisissez en une !",
                                      At_Prd);
            if (D == "AT (" + QString::number(m_carac->getAttaque()) + ")")
            {
                QMessageBox::information(this, "Gain d'un point d'AT",
                                         m_nom + " gagne un point d'AT en raison de son nouveau niveau.");
                log(m_nom + "gagne un point d'AT en raison de son nouveau niveau");
                m_carac->setAttaque(m_carac->getAttaque() + 1);
            }
            else if (D == "PRD (" + QString::number(m_carac->getParade()) + ")")
            {
                QMessageBox::information(this, "Gain d'un point de PRD",
                                         m_nom + " gagne un point de PRD en raison de son nouveau niveau.");
                log(m_nom + "gagne un point de PRD en raison de son nouveau niveau");
                m_carac->setParade(m_carac->getParade() + 1);
            }
        }
        else if (m_carac->getAttaque() < 18 && m_carac->getParade() == 17)
        {
            QMessageBox::information(this, "Gain d'un point d'AT",
                                     m_nom + " gagne un point d'AT car il passe un niveau !");
            log(m_nom + "gagne un point d'AT en raison de son nouveau niveau");
            m_carac->setAttaque(m_carac->getAttaque() + 1);
        }
        else if (m_carac->getAttaque() == 18 && m_carac->getParade() < 17)
        {
            QMessageBox::information(this, "Gain d'un point de PRD",
                                     m_nom + " gagne un point de PRD car il passe un niveau !");
            log(m_nom + "gagne un point de PRD en raison de son nouveau niveau");
            m_carac->setParade(m_carac->getParade() + 1);
        }

    // Autres modifications
        if (m_niveau == 3)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nom + " doit choisir une compétence supplémentaire.");
        }
        else if (m_niveau == 5 && m_presenceEA)
        {
            QMessageBox::information(this, "Choix d'une spécialisation supplémentaire",
                                     m_nom + " doit choisir une spécialisation supplémentaire");
        }
        else if (m_niveau == 6)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nom + " doit choisir une compétence supplémentaire.");
        }
        else if (m_niveau == 10)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nom + " doit choisir une compétence supplémentaire.");
        }
        else if (m_niveau == 15 && m_presenceEA)
        {
            QMessageBox::information(this, "Choix d'une spécialisation supplémentaire",
                                     m_nom + " doit choisir une spécialisation supplémentaire");
        }
    }
}

void Personnage::ajouterPO(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Ajouter des PO",
                                             "Ajouter des Pièces d'Or à " + m_nom,
                                             1, 0, 999999 - m_richesses->getOr(), 1, &ok);

        if (ok)
        {
            m_richesses->setOr(m_richesses->getOr() + value);
            log(m_nom + " gagne " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
        }
    }
    else
    {
        m_richesses->setOr(m_richesses->getOr() + value);
        log(m_nom + " gagne " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
    }

    rafraichirRichesses();
}
void Personnage::retirerPO(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Retirer des PO",
                                             "Retirer des Pièces d'Or à " + m_nom,
                                             1, 0, 1999998 - m_richesses->getOr(), 1, &ok);

        if (ok)
        {
            m_richesses->setOr(m_richesses->getOr() - value);
            log(m_nom + " perd " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
        }
    }
    else
    {
        m_richesses->setOr(m_richesses->getOr() - value);
        log(m_nom + " perd " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
    }

    rafraichirRichesses();
}
void Personnage::ajouterPA(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Ajouter des PA",
                                             "Ajouter des Pièces d'Argent à " + m_nom,
                                             1, 0, 999999 - m_richesses->getArgent(), 1, &ok);

        if (ok)
        {
            m_richesses->setArgent(m_richesses->getArgent() - value);
            log(m_nom + " gagne " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
        }
    }
    else
    {
        m_richesses->setArgent(m_richesses->getArgent() - value);
        log(m_nom + " gagne " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
    }

    rafraichirRichesses();
}
void Personnage::retirerPA(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Retirer des PA",
                                             "Retirer des Pièces d'Argent à " + m_nom,
                                             1, 0, 1999998 - m_richesses->getArgent(), 1, &ok);

        if (ok)
        {
            m_richesses->setArgent(m_richesses->getArgent() - value);
            log(m_nom + " perd " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
        }
    }
    else
    {
        m_richesses->setArgent(m_richesses->getArgent() - value);
        log(m_nom + " perd " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
    }

    rafraichirRichesses();
}
void Personnage::ajouterPC(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Ajouter des PC",
                                             "Ajouter des Pièces de Cuivre à " + m_nom,
                                             1, 0, 999999 - m_richesses->getCuivre(), 1, &ok);

        if (ok)
        {
            m_richesses->setCuivre(m_richesses->getCuivre() + value);
            log(m_nom + " gagne " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
        }
    }
    else
    {
        m_richesses->setCuivre(m_richesses->getCuivre() + value);
        log(m_nom + " gagne " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
    }

    rafraichirRichesses();
}
void Personnage::retirerPC(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Retirer des PC",
                                             "Retirer des Pièces de Cuivre à " + m_nom,
                                             1, 1, 1999998 - m_richesses->getCuivre(), 1, &ok);

        if (ok)
        {
            m_richesses->setCuivre(m_richesses->getCuivre() - value);
            log(m_nom + " perd " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
        }
    }
    else
    {
        m_richesses->setCuivre(m_richesses->getCuivre() - value);
        log(m_nom + " perd " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
    }

    rafraichirRichesses();
}


// Slots automatiques de Qt
// Informations générales
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
void Personnage::on_xpPlus_clicked()
{
    ajouterXP();
}
void Personnage::on_destinMoins_clicked()
{
    if (m_ptsDestin > 1)
    {
        m_ptsDestin--;
        ui->destin->setText(QString::number(m_ptsDestin));

        log(m_nom + " perd 1 point de destin");
    }
    else if (m_ptsDestin == 1)
    {
        m_ptsDestin--;
        ui->destin->setText(QString::number(m_ptsDestin));
        ui->destinMoins->setEnabled(false);

        log(m_nom + " perd 1 point de destin");
    }
    else
        QMessageBox::information(this, "Erreur !",
                                 m_nom + " ne peut pas perdre de points de destin : il n'en a déjà plus !");
}

// Richesses
void Personnage::on_poPlus_clicked()
{
    ajouterPO();
}
void Personnage::on_poMoins_clicked()
{
    retirerPO();
}
void Personnage::on_paPlus_clicked()
{
    ajouterPA();
}
void Personnage::on_paMoins_clicked()
{
    retirerPA();
}
void Personnage::on_pcPlus_clicked()
{
    ajouterPC();
}
void Personnage::on_pcMoins_clicked()
{
    retirerPC();
}

void Personnage::on_conversionPA_et_PC_en_PO_clicked()
{
    m_richesses->convertir(Richesses::PA_PC_en_PO);
    rafraichirRichesses();
}
void Personnage::on_conversionPO_en_PA_clicked()
{
    m_richesses->convertir(Richesses::PO_en_PA);
    rafraichirRichesses();
}
void Personnage::on_conversionPO_en_PC_clicked()
{
    m_richesses->convertir(Richesses::PO_en_PC);
    rafraichirRichesses();
}
void Personnage::on_conversionPA_en_PC_clicked()
{
    m_richesses->convertir(Richesses::PA_en_PC);
    rafraichirRichesses();
}

// Equipements
void Personnage::on_equipsEdit_1_clicked(bool checked)
{
    if (!checked)
        m_equipements[0] = ui->equips_1->toPlainText();
    else
        ui->equips_1->setPlainText(m_equipements[0]);

    ui->equips_1->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_2_clicked(bool checked)
{
    if (!checked)
        m_equipements[1] = ui->equips_2->toPlainText();
    else
        ui->equips_2->setPlainText(m_equipements[1]);

    ui->equips_2->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_3_clicked(bool checked)
{
    if (!checked)
        m_equipements[2] = ui->equips_3->toPlainText();
    else
        ui->equips_3->setPlainText(m_equipements[2]);

    ui->equips_3->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_4_clicked(bool checked)
{
    if (!checked)
        m_equipements[3] = ui->equips_4->toPlainText();
    else
        ui->equips_4->setPlainText(m_equipements[3]);

    ui->equips_4->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_5_clicked(bool checked)
{
    if (!checked)
        m_equipements[4] = ui->equips_5->toPlainText();
    else
        ui->equips_5->setPlainText(m_equipements[4]);

    ui->equips_5->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_6_clicked(bool checked)
{
    if (!checked)
        m_equipements[5] = ui->equips_6->toPlainText();
    else
        ui->equips_6->setPlainText(m_equipements[5]);

    ui->equips_6->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_7_clicked(bool checked)
{
    if (!checked)
        m_equipements[6] = ui->equips_7->toPlainText();
    else
        ui->equips_7->setPlainText(m_equipements[6]);

    ui->equips_7->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_8_clicked(bool checked)
{
    if (!checked)
        m_equipements[7] = ui->equips_8->toPlainText();
    else
        ui->equips_8->setPlainText(m_equipements[7]);

    ui->equips_8->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_9_clicked(bool checked)
{
    if (!checked)
        m_equipements[8] = ui->equips_9->toPlainText();
    else
        ui->equips_9->setPlainText(m_equipements[8]);

    ui->equips_9->setReadOnly(!checked);
}
void Personnage::on_equipsEdit_10_clicked(bool checked)
{
    if (!checked)
        m_equipements[9] = ui->equips_10->toPlainText();
    else
        ui->equips_10->setPlainText(m_equipements[9]);

    ui->equips_10->setReadOnly(!checked);
}
