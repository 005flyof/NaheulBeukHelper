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
    source/Personnage.h \
    source/ClassesPourPersonnage.h \
    source/Competence.h

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
    source/Personnage.cpp \
    source/Competence.cpp

QT += network

RC_FILE = res/ressources.rc

OTHER_FILES += \
    res/ressources.rc

RESOURCES += \
    res/ressources.qrc

FORMS += \
    source/FenChargement.ui \
    source/Personnage.ui
