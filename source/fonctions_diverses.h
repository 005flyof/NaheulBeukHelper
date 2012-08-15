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

#ifndef FONCTIONS_DIVERSES_H
    #define FONCTIONS_DIVERSES_H

    #include <QtGui>

// Fonctions
    void setIcone(QWidget* widget);
    void fatalError(QString const& message, bool const& logErreur = false);
    void error(QString const& message);

    void log(QString const& message, bool vider = false);
    void log(QString message, int niveau);

    void pause(int msec);

// Variables
    #define SITE_BUGS "https://sourceforge.net/p/naheulbeuk-help/bugs/"

#endif // FONCTIONS_DIVERSES_H
