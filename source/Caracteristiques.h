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

#ifndef CARACTERISTIQUES_H
	#define CARACTERISTIQUES_H

	#include <QtGui>

	class Caracteristiques
	{
	public:
		Caracteristiques(bool at_prd_vrai = false,
						 int COU_recup = 0, int INT_recup = 0, int CHA_recup = 0, int AD_recup = 0, int FO_recup = 0,
						 int AT_recup = 0, int PRD_recup = 0);
		Caracteristiques(Caracteristiques const& b);

		bool estEgal(Caracteristiques const& b) const;
		bool estInfOuEgal(Caracteristiques const& b) const;
		bool estSupOuEgal(Caracteristiques const& b) const;
		Caracteristiques& operator=(Caracteristiques const& b);
		Caracteristiques& operator+=(Caracteristiques const& b);
		Caracteristiques& operator-=(Caracteristiques const& b);

		void remplir(int COU_recup, int INT_recup, int CHA_recup, int AD_recup, int FO_recup,
					 int AT_recup = 0, int PRD_recup = 0);

		QString getCarac(bool plus);
		QString getCaracteristiques() const;

		int getCOU();
		int getINT();
		int getCHA();
		int getAD();
		int getFO();
		int getAT();
		int getPRD();

		void setCOU(int nb);
		void setINT(int nb);
		void setCHA(int nb);
		void setAD(int nb);
		void setFO(int nb);
		void setAT(int nb);
		void setPRD(int nb);

		void COU_1(bool plus = true);
		void INT_1(bool plus = true);
		void CHA_1(bool plus = true);
		void AD_1(bool plus = true);
		void FO_1(bool plus = true);
		void AT_1(bool plus = true);
		void PRD_1(bool plus = true);

	private:
		bool AT_PRD_vrai;

		int COU;
		int INT;
		int CHA;
		int AD;
		int FO;
		int AT;
		int PRD;
	};

	bool operator==(Caracteristiques const& a, Caracteristiques const& b);
	bool operator<=(Caracteristiques const& a, Caracteristiques const& b);
	bool operator>=(Caracteristiques const& a, Caracteristiques const& b);


#endif // CARACTERISTIQUES_H
