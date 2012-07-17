#include "FenChargement.h"
#include "ui_FenChargement.h"

FenChargement::FenChargement(char *argv[])
    : QDialog(), ui(new Ui::FenChargement)
{
    ui->setupUi(this);
    ui->progression->setValue(0);

    show();
    setModal(true);

// Suppression du fichier temporaire de la MAJ
    ui->label->setText("Suppression du fichier temporaire de mise à jour : 'tmp.zip'...");
    remove("tmp.zip");
    ui->progression->setValue(10);
    ui->label->setText("Fichier temporaire de Mise à Jour supprimé !");

// Suppression du fichier d'erreur
    ui->label->setText("Suppression du fichier d'erreurs : 'error.log'...");
    remove("error.log");
    ui->progression->setValue(20);
    ui->label->setText("Fichier d'erreur supprimé !");

// Chargement des origines
    ui->label->setText("Chargement des origines...");
    //ouvrirOrigines();
    ui->progression->setValue(50);
    ui->label->setText("Origines chargées !");

// Chargement des métiers
    ui->label->setText("Chargement des métiers...");
    //ouvrirMetiers();
    ui->progression->setValue(80);
    ui->label->setText("Métiers chargés !");

// Création de l'interface graphique
    ui->label->setText("Création de l'interface graphique...");

    if (QString(argv[1]) == "-fermer_gr")
        log("Fermeture du groupe");
    else if (QString(argv[1]) == "-fermer_onglets")
        log("Fermeture du groupe dûe à une erreur dans un des fichiers.");
    else
        log("Lancement de NBH", true);

    //fenetrePrincipale = new FenPrincipale;
    Personnage *perso = new Personnage("Babar");

    ui->progression->setValue(100);
    ui->label->setText("Interface chargée ! Fermeture de la fenêtre de chargement...");

    close();
    //fenetrePrincipale->show();
    perso->show();
}

FenChargement::~FenChargement()
{
    delete ui;
}
/*
void FenChargement::ouvrirOrigines()
{
    QFile nouveau_origine_conteneur(":prog-data/origines.txt");
    if (!nouveau_origine_conteneur.open(QIODevice::ReadOnly | QIODevice::Text))
        fatalError("Fichier contenant les origines inaccessible !");

    QTextStream nouveau_origineTexte(&nouveau_origine_conteneur);

    QString ligne = nouveau_origineTexte.readLine();
    int compteurLigne(0);

    do
    {
        // On travaille sur le fichier
        QString origine_nom = nouveau_origineTexte.readLine();
        compteurLigne++;

        lecteurLigne = 0;
        int origine_COU(0), origine_INT(0), origine_CHA(0), origine_FO(0), origine_AD(0);
        int origine_cou(0), origine_int(0), origine_cha(0), origine_fo(0), origine_ad(0);

        // Carac minimum
        QString origineCarac_ligne = nouveau_origineTexte.readLine();
        compteurLigne++;
        while (lecteurLigne < origineCarac_ligne.size())
        {
            if (origineCarac_ligne[lecteurLigne] == '_')
                lecteurLigne++;

            else
            {
                QString origineCarac_string("");
                QChar a(origineCarac_ligne[lecteurLigne]);
                origineCarac_string = a + origineCarac_ligne[lecteurLigne+1];

                switch (lecteurLigne)
                {
                case 0:
                    origine_cou = origineCarac_string.toInt();
                    break;
                case 3:
                    origine_int = origineCarac_string.toInt();
                    break;
                case 6:
                    origine_cha = origineCarac_string.toInt();
                    break;
                case 9:
                    origine_ad = origineCarac_string.toInt();
                    break;
                case 12:
                    origine_fo = origineCarac_string.toInt();
                    break;
                default:
                    QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                          "ERREUR : Erreur lors de l'ouverture du fichier contenant les origines :\n"
                                          "     ->  Origine : \"" + origine_nom + "\" invalide !\n\n"
                                          "Caractéristiques minimum non valides !\n");
                    statusBar->showMessage("Action annulée -> Erreur lors de l'ouverture du fichier contenant les origines !");
                    return;
                    break;
                }
                lecteurLigne += 2;
            }
        }

        // Carac maximum
        lecteurLigne = 0;
        origineCarac_ligne = nouveau_origineTexte.readLine();
        while (lecteurLigne < origineCarac_ligne.size())
        {
            if (origineCarac_ligne[lecteurLigne] == '_')
                lecteurLigne++;

            else
            {
                QString origineCarac_string("");
                QChar a(origineCarac_ligne[lecteurLigne]);
                origineCarac_string = a + origineCarac_ligne[lecteurLigne+1];

                switch (lecteurLigne)
                {
                case 0:
                    origine_COU = origineCarac_string.toInt();
                    break;
                case 3:
                    origine_INT = origineCarac_string.toInt();
                    break;
                case 6:
                    origine_CHA = origineCarac_string.toInt();
                    break;
                case 9:
                    origine_AD = origineCarac_string.toInt();
                    break;
                case 12:
                    origine_FO = origineCarac_string.toInt();
                    break;
                default:
                    QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                          "ERREUR : Erreur lors de l'ouverture du fichier contenant les origines :\n"
                                          "     ->  Origine : \"" + origine_nom + "\" invalide !\n\n"
                                          "Caractéristiques maximum non valides !\n");
                    statusBar->showMessage("Action annulée -> Erreur lors de l'ouverture du fichier contenant les origines !");
                    return;
                    break;
                }
                lecteurLigne += 2;
            }
        }

        // EV et AT
        int origine_EV(0), origine_AT(0);

        ligne = nouveau_origineTexte.readLine();
        origine_EV = ligne.toInt();

        ligne = nouveau_origineTexte.readLine();
        if (ligne == "x")
            origine_AT = ligne.toInt();

        m_origines[origine_nom] = new Origine(origine_nom, origine_EV, origine_AT,
                                                    origine_cou, origine_int, origine_cha, origine_ad, origine_fo,
                                                    origine_COU, origine_INT, origine_CHA, origine_AD, origine_FO);

        bool possible = tableauDePersonnages[nouveau_nom->text()].testOrigine(m_origines[origine_nom]);

        if (possible)
        {
            QRadioButton *temp = new QRadioButton(origine_nom);
            tableauDeRadioButton_Origine.push_back(temp);

            QVector<QRadioButton>::iterator it = tableauDeRadioButton_Origine.at(totalOrigine);
            layout->addWidget(&*it);
            totalOrigine++;
        }

        // On charge la ligne pour vérifier que le fichier n'est pas fini
        ligne = nouveau_origineTexte.readLine();

        while (ligne == "~!competence-obligatoire!~")
        {
            QString competence_nom = nouveau_origineTexte.readLine();
            QString competence_description = nouveau_origineTexte.readLine();

            m_origines[origine_nom]->addCompetence(competence_nom, competence_description);

            ligne = nouveau_origineTexte.readLine();
        }

        while (ligne == "~!competence-choisir!~")
        {
            QString competence_nom = nouveau_origineTexte.readLine();
            QString competence_description = nouveau_origineTexte.readLine();

            m_origines[origine_nom]->addCompetence(competence_nom, competence_description, false);

            ligne = nouveau_origineTexte.readLine();
        }
    } while (ligne != "~!FIN_ORIGINE!~");
}
void FenChargement::ouvrirMetiers()
{
    // On crée les métiers depuis le fichier conteneur
        QFile nouveau_metier_conteneur(":prog-data/metiers.txt");
        if (!nouveau_metier_conteneur.open(QIODevice::ReadOnly | QIODevice::Text))
            fatalError("Impossible de charger le fichier contenant les métiers.");

        QTextStream nouveau_metierTexte(&nouveau_metier_conteneur);

        QString ligne = nouveau_metierTexte.readLine();

        do {
        // On travaille sur le fichier
            QString metier_nom = nouveau_metierTexte.readLine();

            int lecteurLigne = 0;
            int metier_cou(0), metier_int(0), metier_cha(0), metier_fo(0), metier_ad(0), metier_at(0), metier_prd(0);

            // Carac minimum
            QString metierCarac_ligne = nouveau_metierTexte.readLine();
            while (lecteurLigne < metierCarac_ligne.size())
            {
                if (metierCarac_ligne[lecteurLigne] == '_')
                    lecteurLigne++;

                else
                {
                    QString metierCarac_string("");
                    QChar a(metierCarac_ligne[lecteurLigne]);
                    metierCarac_string = a + metierCarac_ligne[lecteurLigne+1];

                    switch (lecteurLigne)
                    {
                    case 0:
                        metier_cou = metierCarac_string.toInt();
                        break;
                    case 3:
                        metier_int = metierCarac_string.toInt();
                        break;
                    case 6:
                        metier_cha = metierCarac_string.toInt();
                        break;
                    case 9:
                        metier_ad = metierCarac_string.toInt();
                        break;
                    case 12:
                        metier_fo = metierCarac_string.toInt();
                        break;
                    default:
                        QMessageBox::critical(zoneCentrale, "Erreur réparable !",
                                              "ERREUR : Erreur lors de l'ouverture du fichier contenant les métiers :\n"
                                              "     ->  Métier : \"" + metier_nom + "\" invalide !\n\n"
                                              "Caractéristiques minimum non valides !\n");
                        statusBar->showMessage("Action annulée -> Erreur lors de l'ouverture du fichier contenant les métiers !");
                        return;
                        break;
                    }
                    lecteurLigne += 2;
                }
            }

            // AT & PRD
            ligne = nouveau_metierTexte.readLine();
            if (ligne != "x")
                metier_at = ligne.toInt();

            ligne = nouveau_metierTexte.readLine();
            if (ligne != "x")
                metier_prd = ligne.toInt();

        // On crée le métier
            m_metiers[metier_nom] = new Metier(metier_nom, metier_at, metier_prd,
                                               metier_cou, metier_int, metier_cha, metier_ad, metier_fo);

            // EV
            ligne = nouveau_metierTexte.readLine();

            if (ligne == "~!EV_CLASSES!~")
            {
                QStringList liste_classes;
                int ev_pourClassesModifiees(0), evEnPlus_pourLesAutres(0);

            // On capte la ligne pour pas faire planter
                ligne = nouveau_metierTexte.readLine();

                do {
                // On remplit la liste de classes modifiées
                    liste_classes << ligne;

                // On charge la ligne pour vérifier que la liste des classes modifiées n'est pas fini
                    ligne = nouveau_metierTexte.readLine();
                } while (ligne != "~!EV_MODIF!~");

                ligne = nouveau_metierTexte.readLine();
                ev_pourClassesModifiees = ligne.toInt();

                ligne = nouveau_metierTexte.readLine();
                evEnPlus_pourLesAutres = ligne.toInt();
                QString ligne2 = nouveau_metierTexte.readLine();
                if (ligne2 == "pourcent")
                {
                // On ajoute tout cela au métier
                    m_metiers[metier_nom]->setEV(liste_classes, ev_pourClassesModifiees, evEnPlus_pourLesAutres, true);
                // On charge la ligne pour pouvoir vérifier que le fichier n'est pas fini
                    ligne = nouveau_metierTexte.readLine();
                }
                else
                {
                    ligne = ligne2;
                // On ajoute tout cela au métier
                    m_metiers[metier_nom]->setEV(liste_classes, ev_pourClassesModifiees, evEnPlus_pourLesAutres, false);
                }
            }

            if (ligne == "~!magie!~")
            {
                QString typeEA = nouveau_metierTexte.readLine();
                int EA = nouveau_metierTexte.readLine().toInt();

            // On ajoute l'EA au métier
                m_metiers[metier_nom]->setEA(typeEA, EA);

            // On charge la ligne pour pouvoir vérifier que le fichier n'est pas fini
                ligne = nouveau_metierTexte.readLine();
            }

            while (ligne == "~!competence-obligatoire!~")
            {
                QString competence_nom = nouveau_metierTexte.readLine();
                QString competence_description = nouveau_metierTexte.readLine();

                m_metiers[metier_nom]->addCompetence(competence_nom, competence_description);

                ligne = nouveau_metierTexte.readLine();
            }

            while (ligne == "~!competence-choisir!~")
            {
                QString competence_nom = nouveau_metierTexte.readLine();
                QString competence_description = nouveau_metierTexte.readLine();

                m_metiers[metier_nom]->addCompetence(competence_nom, competence_description, false);

                ligne = nouveau_metierTexte.readLine();
            }
        } while (ligne != "~!FIN_METIER!~");
}
*/
