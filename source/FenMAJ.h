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

#ifndef FenMAJ_H
    #define FenMAJ_H

// Pour MAC
    #if defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
        #define OS 2
    #endif
// Pour Linux
    #ifdef __linux__
        #define OS 1
    #endif
// Pour Windows
    #ifdef _WIN32
        #define OS 0
    #endif

    #define VERSION "1.8.5"

    #include <QtGui>
    #include <QtNetwork>

    class FenMAJ : public QDialog
    {
    Q_OBJECT

    public:
        FenMAJ(QWidget* parent);

    public slots:
        void verifierMAJ();
        void verifierMAJ_2();
        void telechargement();
        void progressionTelechargement(qint64 bytesReceived, qint64 bytesTotal);
        void messageErreur(QNetworkReply::NetworkError);

    private:
        // Pour le téléchargement
        QVBoxLayout *verticalLayout;
        QLabel *label;
        QLineEdit *urlEdit;
        QPushButton *demarrerTelechargement;
        QPushButton *verifier;
        QProgressBar *progression;
        bool erreurTrouvee; //Variable qui nous permet de savoir s'il y a eu une erreur ou non.
    };

#endif // FenMAJ_H
