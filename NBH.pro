HEADERS += \
    source/Caracteristiques.h \
    source/Origine.h \
    source/Metier.h \
    source/Richesses.h \
    source/Protection.h \
    source/Arme.h \
    source/Fleche.h \
    source/Vetement.h \
    source/fonctions_diverses.h \
    source/FenChargement.h \
    source/ClassesPourPersonnage.h \
    source/Competence.h \
    source/FenPrincipale.h \
    source/FenOrdreMarche.h \
    source/FenMAJ.h \
    source/FenAttaque.h \
    source/Acceuil.h \
    source/NewPerso.h \
    source/AddPerso.h \
    source/EquipModif.h \
    source/Personnage.h \
    source/SelectCompetence.h \
    source/SearchCompetence.h \
    source/AfficherLogs.h

SOURCES += \
    source/main.cpp \
    source/Caracteristiques.cpp \
    source/Origine.cpp \
    source/Metier.cpp \
    source/Richesses.cpp \
    source/Protection.cpp \
    source/Arme.cpp \
    source/Fleche.cpp \
    source/Vetement.cpp \
    source/fonctions_diverses.cpp \
    source/FenChargement.cpp \
    source/Competence.cpp \
    source/FenPrincipale.cpp \
    source/FenOrdreMarche.cpp \
    source/FenMAJ.cpp \
    source/FenAttaque.cpp \
    source/Acceuil.cpp \
    source/NewPerso.cpp \
    source/AddPerso.cpp \
    source/EquipModif.cpp \
    source/Personnage.cpp \
    source/SelectCompetence.cpp \
    source/SearchCompetence.cpp \
    source/AfficherLogs.cpp

QT += network

RC_FILE = res/ressources.rc

OTHER_FILES += \
    res/ressources.rc

RESOURCES += \
    res/ressources.qrc

FORMS += \
    source/FenChargement.ui \
    source/Acceuil.ui \
    source/NewPerso.ui \
    source/AddPerso.ui \
    source/EquipModif.ui \
    source/Personnage.ui \
    source/SelectCompetence.ui \
    source/SearchCompetence.ui \
    source/SearchCompetence.ui \
    source/AfficherLogs.ui
