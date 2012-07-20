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

#include "ClassesPourPersonnage.h"

Richesses::Richesses(int OR, int ARGENT, int CUIVRE)
    : m_or(OR), m_argent(ARGENT), m_cuivre(CUIVRE)
{
    pb = new QWidget();
}

void Richesses::setOr(int value)
{
    if (value > 999999)
        QMessageBox::information(pb, "Information",
                                 "ATTENTION :\nLe nombre maximum de PO (= 999999) a été dépassé !\n\n"
                                 "Le nombre de PO n'a donc pas été modifié");
    else if (value < -999999)
        QMessageBox::information(pb, "Information",
                                 "ATTENTION :\nLe nombre minimal de PO (= -999999) a été dépassé !\n\n"
                                 "Le nombre de PO n'a donc pas été modifié");
    else
        m_or = value;

    // Pas de contrôle au cas où c'est inférieur à zéro, les joueurs peuvent être endettés ! :)
}
void Richesses::setArgent(int value)
{
    if (value > 999999)
        QMessageBox::information(pb, "Information",
                                 "ATTENTION :\nLe nombre maximum de PA (= 999999) a été dépassé !\n\n"
                                 "Le nombre de PA n'a donc pas été modifié");
    else if (value < -999999)
        QMessageBox::information(pb, "Information",
                                 "ATTENTION :\nLe nombre minimal de PA (= -999999) a été dépassé !\n\n"
                                 "Le nombre de PA n'a donc pas été modifié");
    else
        m_argent = value;

    // Pas de contrôle au cas où c'est inférieur à zéro, les joueurs peuvent être endettés ! :)
}
void Richesses::setCuivre(int value)
{
    if (value > 999999)
        QMessageBox::information(pb, "Information",
                                 "ATTENTION :\nLe nombre maximum de PC (= 999999) a été dépassé !\n\n"
                                 "Le nombre de PC n'a donc pas été modifié");
    else if (value < -999999)
        QMessageBox::information(pb, "Information",
                                 "ATTENTION :\nLe nombre minimal de PC (= -999999) a été dépassé !\n\n"
                                 "Le nombre de PC n'a donc pas été modifié");
    else
        m_cuivre = value;

    // Pas de contrôle au cas où c'est inférieur à zéro, les joueurs peuvent être endettés ! :)
}

int Richesses::getOr() const
{
    return m_or;
}
int Richesses::getArgent() const
{
    return m_argent;
}
int Richesses::getCuivre() const
{
    return m_cuivre;
}

void Richesses::convertir(conversion convert)
{
    switch (convert)
    {
    // Convertir les PO en PA
    case PO_en_PA:
        if (m_or >= 1)
        {
            m_or--;
            m_argent += 10;
        }
        break;

    // Convertir les PO en PC
    case PO_en_PC:
        if (m_or >= 1)
        {
            m_or--;
            m_cuivre += 100;
        }
        break;

    // Convertir les PA en PC
    case PA_en_PC:
        if (m_argent >= 1)
        {
            m_argent--;
            m_cuivre += 10;
        }
        break;

    // Convertir les PA et PC en PO
    case PA_PC_en_PO:
        // Conversion des PC en PA
        while (m_cuivre >= 10)
        {
           m_cuivre -= 10;
           m_argent++;
        }
        // Conversion des PA en PO
        while (m_argent >= 10)
        {
            m_argent -= 10;
            m_or++;
        }
        break;
    }
}

QString Richesses::richessesEnregistrement() const
{
    QString richesses = "";

    if (m_or < 10)
        richesses = "00000" + QString::number(m_or) + "_";
    else if (m_or < 100 && m_or > 9)
        richesses = "0000" + QString::number(m_or) + "_";
    else if (m_or < 1000 && m_or > 99)
        richesses = "000" + QString::number(m_or) + "_";
    else if (m_or < 10000 && m_or > 999)
        richesses = "00" + QString::number(m_or) + "_";
    else if (m_or < 100000 && m_or > 9999)
        richesses = "0" + QString::number(m_or) + "_";
    else if (m_or < 1000000 && m_or > 99999)
        richesses = QString::number(m_or) + "_";

    if (m_argent < 10)
        richesses += "00000" + QString::number(m_argent) + "_";
    else if (m_argent < 100 && m_argent > 9)
        richesses += "0000" + QString::number(m_argent) + "_";
    else if (m_argent < 1000 && m_argent > 99)
        richesses += "000" + QString::number(m_argent) + "_";
    else if (m_argent < 10000 && m_argent > 999)
        richesses += "00" + QString::number(m_argent) + "_";
    else if (m_argent < 100000 && m_argent > 9999)
        richesses += "0" + QString::number(m_argent) + "_";
    else if (m_argent < 1000000 && m_argent > 99999)
        richesses += QString::number(m_argent) + "_";

    if (m_cuivre < 10)
        richesses += "00000" + QString::number(m_cuivre);
    else if (m_cuivre < 100 && m_cuivre > 9)
        richesses += "0000" + QString::number(m_cuivre);
    else if (m_cuivre < 1000 && m_cuivre > 99)
        richesses += "000" + QString::number(m_cuivre);
    else if (m_cuivre < 10000 && m_cuivre > 999)
        richesses += "00" + QString::number(m_cuivre);
    else if (m_cuivre < 100000 && m_cuivre > 9999)
        richesses += "0" + QString::number(m_cuivre);
    else if (m_cuivre < 1000000 && m_cuivre > 99999)
        richesses += QString::number(m_cuivre);

    return richesses;
}
