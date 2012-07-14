#include "FenChargement.h"
#include "ui_FenChargement.h"

FenChargement::FenChargement(char *argv[])
    : QDialog(), ui(new Ui::FenChargement)
{
    ui->setupUi(this);
    ui->progression->setValue(0);

    show();
// Suppression des fichiers de MAJ et d'erreur si ils sont là
    ui->label->setText("Suppression du fichier temporaire de mise à jour...");
    ui->progression->setValue(20);
    remove("tmp.zip");
    ui->label->setText("Suppression du fichier contenant les erreurs...");
    ui->progression->setValue(40);
    remove("error.log");

// Ecriture du log
    ui->label->setText("Création de l'interface graphique...");
    ui->progression->setValue(60);
    if (QString(argv[1]) == "-fermer_gr")
        log("Fermeture du groupe");
    else if (QString(argv[1]) == "-fermer_onglets")
        log("Fermeture du groupe dûe à une erreur dans un des fichiers.");
    else
        log("Lancement de NBH", true);

// On crée la fenêtre
    FenPrincipale fenetre;

// On affiche la fenêtre
    fenetre.show();

    hide();
}

FenChargement::~FenChargement()
{
    delete ui;
}

