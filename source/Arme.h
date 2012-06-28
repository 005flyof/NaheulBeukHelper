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

#ifndef ARME_H
	#define ARME_H

	#include <QtGui>
	#include "Caracteristiques.h"

	class Arme
	{
	public:
		Arme(QString nom,
			 int nbDes, int degatsEnPlus,
			 int cou, int intel, int cha, int ad, int fo, int at, int prd,
			 int COU, int INTEL, int CHA, int AD, int FO, int AT, int PRD);

		enum typeArme
		{
			MainNue, Tranchante, Contandante, Projectile
		};

		void setBonus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup, int AT_recup, int PRD_recup);
		void setMalus(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup, int AT_recup, int PRD_recup);
		void setNom(QString nom);
		void setDegats(int des, int degats);

		void setRupture(int maximum);
		void setType(Arme::typeArme type);

	// Récupérer pour afficher
		QString getNom() const;
		QString getBonusAffichage() const;
		QString getMalusAffichage() const;
		QString getDegatsAffichage() const;

		int getNbDes() const;
		int getDegatsEnPlus() const;

	// Récupérer pour enregistrer
		QString armeEnregistrement() const;

	// Récupérer les caractéristiques
		Caracteristiques getBonus() const;
		Caracteristiques getMalus() const;

	private:
		QString m_nomArme;

		int m_nombreDes;
		int m_degats;

		Caracteristiques m_bonus;
		Caracteristiques m_malus;

		Arme::typeArme m_type;

		int m_rupture_max;
	};

	/*! \class Arme
	 *  \brief Classe gérant l'arme
	 */

#endif // ARME_H
