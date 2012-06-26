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

/*
 * Constructeurs
 */
Caracteristiques::Caracteristiques(int COU, int INT, int CHA, int AD, int FO)
    : m_courage(COU), m_intelligence(INT), m_charisme(CHA), m_adresse(AD), m_force(FO),
      utilisation_AT_PRD(false), m_attaque(0), m_parade(0)
{}
Caracteristiques::Caracteristiques(int COU, int INT, int CHA, int AD, int F0, int AT, int PRD)
: m_courage(COU), m_intelligence(INT), m_charisme(CHA), m_adresse(AD), m_force(FO),
  utilisation_AT_PRD(true), m_attaque(AT), m_parade(PRD)
{}


/*
 * Opérateurs
 */
bool Caracteristiques::estEgal(Caracteristiques const& b) const
{
    if (m_courage == b.m_courage
            && m_intelligence == b.m_intelligence
            && m_charisme == b.m_charisme
            && m_adresse == b.m_adresse
            && m_force == b.m_force
            && utilisation_AT_PRD == b.utilisation_AT_PRD
            && m_attaque == b.m_attaque
            && m_parade == b.m_parade)
        return true;
    else
        return false;
}
bool operator==(Caracteristiques const& a, Caracteristiques const& b)
{
    return a.estEgal(b);
}
bool Caracteristiques::estInfOuEgal(Caracteristiques const& b) const
{
    // si il y a AT et PRD
    if (utilisation_AT_PRD == b.utilisation_AT_PRD)
    {
        if (m_courage <= b.m_courage
                && m_intelligence <= b.m_intelligence
                && m_charisme <= b.m_charisme
                && m_adresse <= b.m_adresse
                && m_force <= b.m_force
                && m_attaque <= b.m_attaque
                && m_parade <= b.m_parade)
            return true;
        else
            return false;
    }
    // sinon
    else
    {
        if (m_courage <= b.m_courage
                && m_intelligence <= b.m_intelligence
                && m_charisme <= b.m_charisme
                && m_adresse <= b.m_adresse
                && m_force <= b.m_force)
            return true;
        else
            return false;
    }
}
bool operator<=(Caracteristiques const& a, Caracteristiques const& b)
{
    return a.estInfOuEgal(b);
}
bool Caracteristiques::estSupOuEgal(Caracteristiques const& b) const
{
    // si il y a AT et PRD
    if (utilisation_AT_PRD == b.utilisation_AT_PRD)
    {
        if (m_courage >= b.m_courage
                && m_intelligence >= b.m_intelligence
                && m_charisme >= b.m_charisme
                && m_adresse >= b.m_adresse
                && m_force >= b.m_force
                && m_attaque >= b.m_attaque
                && m_parade >= b.m_parade)
            return true;
        else
            return false;
    }
    // sinon
    else
    {
        if (m_courage >= b.m_courage
                && m_intelligence >= b.m_intelligence
                && m_charisme >= b.m_charisme
                && m_adresse >= b.m_adresse
                && m_force >= b.m_force)
            return true;
        else
            return false;
    }
}
bool operator>=(Caracteristiques const& a, Caracteristiques const& b)
{
    return a.estSupOuEgal(b);
}

Caracteristiques& Caracteristiques::operator=(Caracteristiques const& b)
{
    if(this != &b)
    {
        utilisation_AT_PRD = b.utilisation_AT_PRD;

        m_courage = b.m_courage;
        m_intelligence = b.m_intelligence;
        m_charisme = b.m_charisme;
        m_adresse = b.m_adresse;
        m_force = b.m_force;
        m_attaque = b.m_attaque;
        m_parade = b.m_parade;
    }

    return *this;
}
Caracteristiques& Caracteristiques::operator+=(Caracteristiques const& b)
{
    if ((m_courage + b.m_courage) > MAX_CARAC)
        m_courage = MAX_CARAC;
    else
        m_courage += b.m_courage;

    if ((m_intelligence + b.m_intelligence) > MAX_CARAC)
        m_intelligence = MAX_CARAC;
    else
        m_intelligence += b.m_intelligence;

    if ((m_charisme + b.m_charisme) > MAX_CARAC)
        m_charisme = MAX_CARAC;
    else
        m_charisme += b.m_charisme;

    if ((m_adresse + b.m_adresse) > MAX_CARAC)
        m_adresse = MAX_CARAC;
    else
        m_adresse += b.m_adresse;

    if ((m_force + b.m_force) > MAX_CARAC)
        m_force = MAX_CARAC;
    else
        m_force += b.m_force;

    if (utilisation_AT_PRD)
    {
        if ((m_attaque + b.m_attaque) > MAX_CARAC)
            m_attaque = MAX_CARAC;
        else
            m_attaque += b.m_attaque;

        if ((m_parade + b.m_parade) > MAX_CARAC)
            m_parade = MAX_CARAC;
        else
            m_parade += b.m_parade;
    }

    return *this;
}
Caracteristiques& Caracteristiques::operator-=(Caracteristiques const& b)
{
    if (m_courage != MIN_CARAC)
        m_courage -= b.m_courage;
    else if ((m_courage - b.m_courage) < MIN_CARAC)
        m_courage = MIN_CARAC;

    if (m_intelligence != MIN_CARAC)
        m_intelligence -= b.m_intelligence;
    else if ((m_intelligence - b.m_intelligence) < MIN_CARAC)
        m_intelligence = MIN_CARAC;

    if (m_charisme != MIN_CARAC)
        m_charisme -= b.m_charisme;
    else if ((m_charisme - b.m_charisme) < MIN_CARAC)
        m_charisme = MIN_CARAC;

    if (m_adresse != MIN_CARAC)
        m_adresse -= b.m_adresse;
    else if ((m_adresse - b.m_adresse) < MIN_CARAC)
        m_adresse = MIN_CARAC;

    if (m_force != MIN_CARAC)
        m_force -= b.m_force;
    else if ((m_force - b.m_force) < MIN_CARAC)
        m_force = MIN_CARAC;

    if (utilisation_AT_PRD)
    {
        if (m_attaque != MIN_CARAC)
            m_attaque -= b.m_attaque;
        else if ((m_attaque - b.m_attaque) < MIN_CARAC)
            m_attaque = MIN_CARAC;

        if (m_parade != MIN_CARAC)
            m_parade -= b.m_parade;
        else if ((m_parade - b.m_parade) < MIN_CARAC)
            m_parade = MIN_CARAC;
    }

    return *this;
}


/*
 * Remplissage
 */
void Caracteristiques::caracRemplir(int COU, int INT, int CHA, int AD, int FO)
{
    m_courage = COU;
    m_intelligence = INT;
    m_charisme = CHA;
    m_adresse = AD;
    m_force = FO;

    utilisation_AT_PRD = false;
    m_attaque = 0;
    m_parade = 0;
}
void Caracteristiques::caracRemplir(int COU, int INT, int CHA, int AD, int FO, int AT, int PRD)
{
    m_courage = COU;
    m_intelligence = INT;
    m_charisme = CHA;
    m_adresse = AD;
    m_force = FO;

    utilisation_AT_PRD = true;
    m_attaque = AT;
    m_parade = PRD;
}


/*
 * Récupération
 */
QString Caracteristiques::caracAffichage(bool plus)
{
    QString string = "";

    if (plus)
    {
        if (m_courage != 0)
            string = "COU+" + QString::number(m_courage);

        if (m_intelligence != 0 && string != "")
            string += " ; INT+" + QString::number(m_intelligence);
        else if (m_intelligence != 0 && string == "")
            string += "INT+" + QString::number(m_intelligence);

        if (m_charisme != 0 && string != "")
            string += " ; CHA+" + QString::number(m_charisme);
        else if (m_charisme != 0 && string == "")
            string += "CHA+" + QString::number(m_charisme);

        if (m_adresse != 0 && string != "")
            string += " ; AD+" + QString::number(m_adresse);
        else if (m_adresse != 0 && string == "")
            string += "AD+" + QString::number(m_adresse);

        if (m_force != 0 && string != "")
            string += " ; FO+" + QString::number(m_force);
        else if (m_force != 0 && string == "")
            string += "FO+" + QString::number(m_force);

        if (m_attaque != 0 && string != "")
            string += " ; AT+" + QString::number(m_attaque);
        else if (m_attaque != 0 && string == "")
            string += "AT+" + QString::number(m_attaque);

        if (m_parade != 0 && string != "")
            string += " ; PRD+" + QString::number(m_parade);
        else if (m_parade != 0 && string == "")
            string += "PRD+" + QString::number(m_parade);

        if (string == "")
            string += "aucun";
    }
    else
    {
        if (m_courage != 0)
            string = "COU-" + QString::number(m_courage);

        if (m_intelligence != 0 && string != "")
            string += " ; INT-" + QString::number(m_intelligence);
        else if (m_intelligence != 0 && string == "")
            string += "INT-" + QString::number(m_intelligence);

        if (m_charisme != 0 && string != "")
            string += " ; CHA-" + QString::number(m_charisme);
        else if (m_charisme != 0 && string == "")
            string += "CHA-" + QString::number(m_charisme);

        if (m_adresse != 0 && string != "")
            string += " ; AD-" + QString::number(m_adresse);
        else if (m_adresse != 0 && string == "")
            string += "AD-" + QString::number(m_adresse);

        if (m_force != 0 && string != "")
            string += " ; FO-" + QString::number(m_force);
        else if (m_force != 0 && string == "")
            string += "FO-" + QString::number(m_force);

        if (m_attaque != 0 && string != "")
            string += " ; AT-" + QString::number(m_attaque);
        else if (m_attaque != 0 && string == "")
            string += "AT-" + QString::number(m_attaque);

        if (m_parade != 0 && string != "")
            string += " ; PRD-" + QString::number(m_parade);
        else if (m_parade != 0 && string == "")
            string += "PRD-" + QString::number(m_parade);

        if (string == "")
            string += "aucun";
    }

    return string;
}
QString Caracteristiques::caracEnregistrement() const
{
    QString string;

    if (m_courage < 10)
        string += "0" + QString::number(m_courage) + "_";
    else
        string += QString::number(m_courage) + "_";

    if (m_intelligence < 10)
        string += "0" + QString::number(m_intelligence) + "_";
    else
        string += QString::number(m_intelligence) + "_";

    if (m_charisme < 10)
        string += "0" + QString::number(m_charisme) + "_";
    else
        string += QString::number(m_charisme) + "_";

    if (m_adresse < 10)
        string += "0" + QString::number(m_adresse) + "_";
    else
        string += QString::number(m_adresse) + "_";

    if (utilisation_AT_PRD)
    {
        if (m_force < 10)
            string += "0" + QString::number(m_force) + "_";
        else
            string += QString::number(m_force) + "_";

        if (m_attaque < 10)
            string += "0" + QString::number(m_attaque) + "_";
        else
            string += QString::number(m_attaque) + "_";

        if (m_parade < 10)
            string += "0" + QString::number(m_parade);
        else
            string += QString::number(m_parade);
    }
    else
    {
        if (m_force < 10)
            string += "0" + QString::number(m_force);
        else
            string += QString::number(m_force);
    }

    return string;
}


/*
 * Accesseurs
 */
int Caracteristiques::getCourage() const
{
    return m_courage;
}
int Caracteristiques::getIntelligence() const
{
    return m_intelligence;
}
int Caracteristiques::getCharisme() const
{
    return m_charisme;
}
int Caracteristiques::getAdresse() const
{
    return m_adresse;
}
int Caracteristiques::getForce() const
{
    return m_force;
}
int Caracteristiques::getAttaque() const
{
    if (utilisation_AT_PRD)
        return m_attaque;
    else
        fatalError("L'attaque n'a pas été initialisée pour ces caractéristiques\n"
                   "Ceci est une erreur de conception du programme, veuillez la signaler sur " + SITE_BUGS);
}
int Caracteristiques::getParade() const
{
    if (utilisation_AT_PRD)
        return m_parade;
    else
        fatalError("La parade n'a pas été initialisée pour ces caractéristiques\n"
                   "Ceci est une erreur de conception du programme, veuillez la signaler sur " + SITE_BUGS);
}

void Caracteristiques::setCourage(int COU)
{
    if (COU < 2)
        m_courage = 2;
    else if (COU > 18)
        m_courage = 18;
    else
        m_courage = COU;
}
void Caracteristiques::setIntelligence(int INT)
{
    if (INT < 2)
        m_intelligence = 2;
    else if (INT > 18)
        m_intelligence = 18;
    else
        m_intelligence = INT;
}
void Caracteristiques::setCharisme(int CHA)
{
    if (CHA < 2)
        m_charisme = 2;
    else if (CHA > 18)
        m_charisme = 18;
    else
        m_charisme = CHA;
}
void Caracteristiques::setAdresse(int AD)
{
    if (AD < 2)
        m_adresse = 2;
    else if (AD > 18)
        m_adresse = 18;
    else
        m_adresse = AD;
}
void Caracteristiques::setForce(int FO)
{
    if (FO < 2)
        m_force = 2;
    else if (FO > 18)
        m_force = 18;
    else
        m_force = FO;
}
void Caracteristiques::setAttaque(int AT)
{
    if (utilisation_AT_PRD)
    {
        if (AT < 2)
            m_attaque = 2;
        else if (AT > 18)
            m_attaque = 18;
        else
            m_attaque = AT;
    }
    else
        fatalError("L'attaque n'a pas été initialisée pour ces caractéristiques\n"
                   "Ceci est une erreur de conception du programme, veuillez la signaler sur " + SITE_BUGS);
}
void Caracteristiques::setParade(int PRD)
{
    if (utilisation_AT_PRD)
    {
        if (PRD < 2)
            m_parade = 2;
        else if (PRD > 18)
            m_parade = 18;
        else
            m_parade = PRD;
    }
    else
        fatalError("La parade n'a pas été initialisée pour ces caractéristiques\n"
                   "Ceci est une erreur de conception du programme, veuillez la signaler sur " + SITE_BUGS);
}
