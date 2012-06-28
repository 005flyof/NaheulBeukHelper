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
#include "FenPrincipale.h"

int main(int argc, char *argv[])
{
// On crée l'application
	QApplication app(argc, argv);

// On indique l'UTF-8
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

// On traduit
	QString locale = QLocale::system().name().section('_', 0, 0);
	QTranslator translator;
	translator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&translator);

// On crée la fenêtre
	FenPrincipale fenetre;

// Suppression des fichiers de MAJ et d'erreur si ils sont là
	remove("tmp.zip");
	remove("error.log");

// Ecriture du log
	if (QString(argv[1]) == "-fermer_gr")
		log("Fermeture du groupe");
	else if (QString(argv[1]) == "-fermer_onglets")
		log("Fermeture du groupe dûe à une erreur dans un des fichiers.");
	else
		log("Lancement de NBH", true);

// On affiche la fenêtre
	fenetre.show();

	return app.exec();
}

/*
  Ce qui reste à faire :
	- monstres !!! -> ouverture du fichier quand début fenêtre

	1	- XP / PO / PA / PC de groupe								(1)		- fait
	2	- modificat° tout le temps (if fo >= 12) etc				(2)		- en cours
	3	- pouvoir attaquer, parer, esquiver => combat				(3)		- en cours -> branche git
	4	- augmentation d'un niveau									(4)		- fait
	5	- acheter puissance											(5)		- fait
	6	- mankdebol / débilibeuk									(6)		- NON
	7	- historique												(7)		-
	8	- compétences												(8)		- fait
	9	- gestionnaire de MAJ										(9)		- fait
	10	- pouvoir changer l'ordre des persos						(10)	- fait
	11	- ordre de marche dans un donjon							(11)	- fait
	12	- fen chargement											(12)	- NON
	13	- convertion des PC et PA en PO								(13)	- fait
	14	- synchronisation des onglets								(14)	- fait
	15	- faire le log                                              (15)    - fait
	16	- fonctions d'ouverture des fichiers, de chargement des obj (16)	- pas la peine
	17	- changement des erreurs pour les chargements de  carac     (17)    - fait
	18	- classe personnage à faire en 2 parties                    (18)    - en cours
	19	- changer l'encodage de tous les fichiers : iso -> utf-8	(19)	- fait
	20	- modififer les updates / updaters							(20)	- fait
	21	- faire la doc des sources									(21)	-
*/
