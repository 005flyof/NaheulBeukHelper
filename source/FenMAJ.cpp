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
//On donne une taille par défaut à la fenêtre
	resize(228, 112);
	setWindowTitle("NBH Updater");

//On définit les layouts
	verticalLayout = new QVBoxLayout(this);

	label = new QLabel("Bienvenue dans le gestionnaire de MAJ de NBH.");
		verticalLayout->addWidget(label);

	verifier = new QPushButton("Vérifier les MAJ(s)...");
		verticalLayout->addWidget(verifier);

	demarrerTelechargement = new QPushButton("Télécharger et installer\n(lance 'NBH-updater')");
		demarrerTelechargement->setEnabled(false);
		verticalLayout->addWidget(demarrerTelechargement);

	progression = new QProgressBar(this);
		progression->setValue(0);
		verticalLayout->addWidget(progression);

	QPushButton *fermer = new QPushButton("Fermer cette fenêtre");
		verticalLayout->addWidget(fermer);

	connect(verifier, SIGNAL(clicked()), this, SLOT(verifierMAJ()));
	connect(demarrerTelechargement, SIGNAL(clicked()), this, SLOT(telechargement()));
	connect(fermer, SIGNAL(clicked()), this, SLOT(close()));
}

void FenMAJ::verifierMAJ()
{
	log("Recherche de Mises à Jour.");

	verifier->setEnabled(false);
	label->setText("Vérification de la disponibilité de Mise à Jour.");

//On récupère l'URL entrée par l'utilisateur.
	const QUrl url = QUrl("http://naheulbeuk-help.sourceforge.net/release/VERSION");
//On crée notre requête
	const QNetworkRequest requete(url);

//On crée le QNetworkAccessManager qui va traiter la requête
	QNetworkAccessManager *m = new QNetworkAccessManager;


// Ensuite, on utilise la méthode get() pour télécharger le contenu de notre requête.
// On récupère un pointeur de QNetworkReply.
	QNetworkReply *r = m->get(requete);

	connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
	connect(r, SIGNAL(finished()), this, SLOT(verifierMAJ_2()));
	connect(r, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressionTelechargement(qint64, qint64)));
}
void FenMAJ::verifierMAJ_2()
{
	//On vérifie qu'il n'y a pas eu d'erreur.
	if(!erreurTrouvee)
	{
		QNetworkReply *r = qobject_cast<QNetworkReply*>(sender()); //On récupère la réponse du serveur

		// Si c'est à jour
		if (VERSION == r->readLine())
		{
			label->setText("NBH est à jour");
			QMessageBox::information(this, "NBH déjà à jour", "NBH est déjà à jour...");

			log("NBH est à jour !");

			close();
			return;
		}

		// Sinon
		demarrerTelechargement->setEnabled(true);
		label->setText("NBH n'est pas à jour !");
		log("NBH n'est pas à jour !");

		//On indique que tout s'est bien passé
		QMessageBox::information(this, "Fin de vérification", "Vérification terminé !\nVotre version n'est pas à jour.");
	}
}

void FenMAJ::telechargement()
{
	label->setText("Installation de la Mise à Jour !");

	QMessageBox::information(this, "NBH va se mettre à jour !",
							 "NBH va se mettre à jour ; pour cela, il va se fermer automatiquement puis redémarrer.\n"
							 "N'ayez pas peur, vos modifications ont étés enregistrées !");
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
						  "Vérifiez votre connexion internet ou réessayez plus tard.<br /><br />"
						  "Code de l'erreur : <br /><em>" + r->errorString() + "</em>");

	verifier->setEnabled(true);
}
