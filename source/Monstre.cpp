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

#include "Monstre.h"

Monstre::Monstre(QString nom, int COU, int AT, int PRD, int EV,
				 int PR, int nbDes, int degats, int XP,
				 QString notes)
	: QWidget()
{
	m_nom = nom;

	m_COU = COU;
	m_AT = AT;
	m_PRD = PRD;
	m_EV = EV;

	m_PR = PR;
	m_nbDes = nbDes;
	m_degatsEnPlus = degats;
	m_XP = XP;

	m_notes = notes;
}

QWidget* Monstre::afficher()
{
	QLineEdit *nom_Label = new QLineEdit(m_nom);
		nom_Label->setEnabled(false);
		nom_Label->setAlignment(Qt::AlignCenter);
	QLabel *COU_Label = new QLabel("COU :	" + QString::number(m_COU));
	QLabel *AT_Label = new QLabel("AT :	" + QString::number(m_AT));
	QLabel *PRD_Label = new QLabel("PRD :	" + QString::number(m_PRD));

	EV_Label = new QLabel("EV :	" + QString::number(m_EV));

	QLabel *PR_Label = new QLabel("PR :	" + QString::number(m_PR));
	QLabel *degats_Label = new QLabel();
		if (m_nbDes != 0 && m_degatsEnPlus > 0)
			degats_Label->setText("Dégâts :	" + QString::number(m_nbDes) + "D + " + QString::number(m_degatsEnPlus));
		else if (m_nbDes != 0 && m_degatsEnPlus < 0)
			degats_Label->setText("Dégâts :	" + QString::number(m_nbDes) + "D " + QString::number(m_degatsEnPlus));
		else if (m_nbDes != 0 && m_degatsEnPlus == 0)
			degats_Label->setText("Dégâts :	" + QString::number(m_nbDes) + "D");
		else
			degats_Label->setText("Dégâts :	" + QString::number(m_degatsEnPlus));

	QLabel *XP_Label = new QLabel("XP :	" + QString::number(m_XP));

	QLabel *notes_Label = new QLabel("Notes :");
	QTextEdit *notes = new QTextEdit();
		notes->setPlainText(m_notes);
		notes->setReadOnly(true);

	QSpacerItem *spacing1 = new QSpacerItem(10, 10);
	QSpacerItem *spacing2 = new QSpacerItem(10, 10);
	QSpacerItem *spacing3 = new QSpacerItem(10, 10);
	QSpacerItem *spacing4 = new QSpacerItem(10, 10);

	QVBoxLayout *layout = new QVBoxLayout();
		layout->addWidget(nom_Label);
		layout->addWidget(COU_Label);
		layout->addWidget(AT_Label);
		layout->addWidget(PRD_Label);
		layout->addItem(spacing1);

		layout->addWidget(EV_Label);
		layout->addItem(spacing2);

		layout->addWidget(PR_Label);
		layout->addWidget(degats_Label);
		layout->addItem(spacing3);

		layout->addWidget(XP_Label);
		layout->addItem(spacing4);

		layout->addWidget(notes_Label);
		layout->addWidget(notes);

	setLayout(layout);
	return this;
}

QString Monstre::nom() const
{
	return m_nom;
}
