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

#include "ClassePourPersonnage.h"

Richesses::Richesses(int OR, int ARGENT, int CUIVRE)
    : m_or(OR), m_argent(ARGENT), m_cuivre(CUIVRE)
{
    pb = new QWidget();
}


void Richesses::setRichesses_Or(unsigned int OR)
{
    if (OR > 999999)
        QMessageBox::information(pb, "Information", "ATTENTION :\nLe nombre maximum de PO (= 999999) a été dépassé !");
    else
        m_or = OR;
}
void Richesses::setRichesses_Argent(unsigned int ARGENT)
{
    if (ARGENT > 999999)
        QMessageBox::information(pb, "Information", "ATTENTION :\nLe nombre maximum de PA (= 999999) a été dépassé !");
    else
        m_argent = ARGENT;
}
void Richesses::setRichesses_Cuivre(unsigned int CUIVRE)
{
    if (CUIVRE > 999999)
        QMessageBox::information(pb, "Information", "ATTENTION :\nLe nombre maximum de PC (= 999999) a été dépassé !");
    else
        m_cuivre = CUIVRE;
}

void Richesses::or_plus(int valeur)
{
    if (valeur < (999999 - m_or))
        m_or += valeur;
    else
        m_or = 999999;
}
void Richesses::argent_plus(int valeur)
{
    if (valeur < (999999 - m_argent))
        m_argent += valeur;
    else
        m_argent = 999999;
}
void Richesses::cuivre_plus(int valeur)
{
    if (valeur < (999999 - m_cuivre))
        m_cuivre += valeur;
    else
        m_cuivre = 999999;
}

void Richesses::or_moins(int valeur)
{
    if (m_or - valeur < 0)
        m_or = 0;
    else
        m_or -= valeur;
}
void Richesses::argent_moins(int valeur)
{
    if (m_argent - valeur < 0)
        m_argent = 0;
    else
        m_argent -= valeur;
}
void Richesses::cuivre_moins(int valeur)
{
    if (m_cuivre - valeur < 0)
        m_cuivre = 0;
    else
        m_cuivre -= valeur;
}


int Richesses::getRichesses_Or() const
{
    return m_or;
}
int Richesses::getRichesses_Argent() const
{
    return m_argent;
}
int Richesses::getRichesses_Cuivre() const
{
    return m_cuivre;
}


QString Richesses::getRichesses() const
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


void Richesses::conversionPAPC_PO()
{
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
}
void Richesses::conversionPO_PA()
{
    if (m_or >= 1)
    {
        m_or--;
        m_argent += 10;
    }
}
void Richesses::conversionPO_PC()
{
    if (m_or >= 1)
    {
        m_or--;
        m_cuivre += 100;
    }
}
void Richesses::conversionPA_PC()
{
    if (m_argent >= 1)
    {
        m_argent--;
        m_cuivre += 10;
    }
}
