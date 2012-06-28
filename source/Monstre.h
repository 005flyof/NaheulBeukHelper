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

#ifndef MONSTRE_H
	#define MONSTRE_H

	#include <QtGui>

	class Monstre : public QWidget
	{
		Q_OBJECT
	public:
		Monstre(QString nom, int COU, int AT, int PRD, int EV,
				int PR, int nbDes, int degats, int XP,
				QString notes = "");

		QWidget* afficher();
		QString nom() const;

	private:
	// Cractéristiques
		QString m_nom;

		int m_COU;
		int m_AT;
		int m_PRD;
		int m_EV;

		int m_PR;
		int m_nbDes;
		int m_degatsEnPlus;

		int m_XP;
		QString m_notes;

	// Affichage
		QLabel *EV_Label;
	};

#endif // MONSTRE_H
