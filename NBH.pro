HEADERS += \
    source/FenPrincipale.h \
    source/Personnage.h \
    source/ClassePourPersonnage.h \
    source/Caracteristiques.h \
    source/Origine.h \
    source/Metier.h \
    source/Richesses.h \
    source/Protection.h \
    source/Arme.h \
    source/Fleche.h \
    source/Vetement.h \
    source/CheckBox.h \
    source/fonctions_diverses.h \
    source/FenMAJ.h \
    source/Monstre.h \
    source/FenOrdreMarche.h \
    source/FenCheckBox.h \
    source/Competence.h \
    source/FenAttaque.h

SOURCES += \
    source/main.cpp \
    source/FenPrincipale.cpp \
    source/Personnage.cpp \
    source/Caracteristiques.cpp \
    source/Origine.cpp \
    source/Metier.cpp \
    source/Richesses.cpp \
    source/Protection.cpp \
    source/Arme.cpp \
    source/Fleche.cpp \
    source/Vetement.cpp \
    source/CheckBox.cpp \
    source/fonctions_diverses.cpp \
    source/FenMAJ.cpp \
    source/Monstre.cpp \
    source/FenOrdreMarche.cpp \
    source/FenCheckBox.cpp \
    source/Competence.cpp \
    source/FenAttaque.cpp

QT += network

RC_FILE = res/ressources.rc

OTHER_FILES += \
    res/ressources.rc

RESOURCES += \
    res/ressources.qrc
