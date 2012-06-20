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

#include "fonctions_diverses.h"
#include "FenMAJ.h"
#include <QtGui>
#include <QtNetwork>

FenMAJ::FenMAJ(QWidget* parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint), erreurTrouvee(false)
{
    setModal(true);
//    setIcone(this);
    this->setWindowIcon(QIcon(":prog-data/img/maj.png"));
//On donne une taille par d�faut � la fen�tre
    resize(228, 112);
    setWindowTitle("NBH Updater");

//On d�finit les layouts
    verticalLayout = new QVBoxLayout(this);

    label = new QLabel("Bienvenue dans le gestionnaire de MAJ de NBH.");
        verticalLayout->addWidget(label);

    verifier = new QPushButton("V�rifier les MAJ(s)...");
        verticalLayout->addWidget(verifier);

    demarrerTelechargement = new QPushButton("T�l�charger et installer\n(lance 'NBH-updater')");
        demarrerTelechargement->setEnabled(false);
        verticalLayout->addWidget(demarrerTelechargement);

    progression = new QProgressBar(this);
        progression->setValue(0);
        verticalLayout->addWidget(progression);

    QPushButton *fermer = new QPushButton("Fermer cette fen�tre");
        verticalLayout->addWidget(fermer);

    connect(verifier, SIGNAL(clicked()), this, SLOT(verifierMAJ()));
    connect(demarrerTelechargement, SIGNAL(clicked()), this, SLOT(telechargement()));
    connect(fermer, SIGNAL(clicked()), this, SLOT(close()));

    log("Recherche de Mises � Jour.");
}

void FenMAJ::verifierMAJ()
{
    log("Recherche de Mises � Jour.");

    verifier->setEnabled(false);
    label->setText("V�rification de la disponibilit� de Mise � Jour.");

//On r�cup�re l'URL entr�e par l'utilisateur.
    const QUrl url = QUrl("http://005flyof.free-h.fr/download/index.php?fichier=VERSION&dossier=nbh");
//On cr�e notre requ�te
    const QNetworkRequest requete(url);

//On cr�e le QNetworkAccessManager qui va traiter la requ�te
    QNetworkAccessManager *m = new QNetworkAccessManager;


// Ensuite, on utilise la m�thode get() pour t�l�charger le contenu de notre requ�te.
// On r�cup�re un pointeur de QNetworkReply.
    QNetworkReply *r = m->get(requete);

    connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
    connect(r, SIGNAL(finished()), this, SLOT(verifierMAJ_2()));
    connect(r, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressionTelechargement(qint64, qint64)));
}
void FenMAJ::verifierMAJ_2()
{
    //On v�rifie qu'il n'y a pas eu d'erreur.
    if(!erreurTrouvee)
    {
        QNetworkReply *r = qobject_cast<QNetworkReply*>(sender()); //On r�cup�re la r�ponse du serveur
        QFile f(":/prog-data/VERSION"); //On ouvre le fichier

        if ( f.open(QIODevice::ReadOnly) )
        {
            // Si c'est � jour
            if (f.readLine() == r->readLine())
            {
                f.close(); //On ferme le fichier
                label->setText("NBH est � jour");
                QMessageBox::information(this, "NBH d�j� � jour", "NBH est d�j� � jour...");

                log("NBH est � jour !");

                close();
                return;
            }

            // Sinon
            demarrerTelechargement->setEnabled(true);
            label->setText("NBH n'est pas � jour !");
            log("NBH n'est pas � jour !");

            //On indique que tout s'est bien pass�
            QMessageBox::information(this, "Fin de v�rification", "V�rification termin� !\nVotre version n'est pas � jour.");
        }
    }
}

void FenMAJ::telechargement()
{
    label->setText("Installation de la Mise � Jour !");

    QMessageBox::information(this, "NBH va se mettre � jour !",
                             "NBH va se mettre � jour ; pour cela, il va se fermer automatiquement puis red�marrer.\n"
                             "N'ayez pas peur, vos modifications ont �t�s enregistr�es !");
    log("Lancement de l'updater !");

    if (OS == 0)
        QProcess::startDetached("nbh-updater.exe");
    else
        QProcess::startDetached("nbh-updater");
    qApp->quit();
}

void FenMAJ::progressionTelechargement(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal != -1)
    {
        progression->setRange(0, bytesTotal);
        progression->setValue(bytesReceived);
    }
}

void FenMAJ::messageErreur(QNetworkReply::NetworkError)
{
    label->setText("Erreur !");

    erreurTrouvee = true; //On indique qu'il y a eu une erreur au slot enregistrer
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, "Erreur",
                          "Erreur lors du chargement."
                          "V�rifiez votre connexion internet ou r�essayez plus tard.<br /><br />"
                          "Code de l'erreur : <br /><em>" + r->errorString() + "</em>");

    verifier->setEnabled(true);
}
