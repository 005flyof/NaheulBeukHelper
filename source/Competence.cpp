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

#include "Competence.h"

Competence::Competence(QString const& nom, QString const& description)
    : QWidget(),
      m_nom(nom), m_description(description)
{
    initAffichage();
}
Competence::Competence(Competence const& aCopier)
    : QWidget(),
      m_nom(aCopier.m_nom), m_description(aCopier.m_description)
{
    initAffichage();
}
Competence& Competence::operator=(Competence const& b)
{
    if(this != &b)
    {
        m_nom = b.m_nom;
        m_description = b.m_description;

        initAffichage();
    }

    return *this;
}
void Competence::initAffichage()
{
    nom_label = new QGroupBox(m_nom);
    description_label = new QTextEdit();
        description_label->setPlainText(m_description);
        description_label->setReadOnly(true);
        description_label->setMinimumSize(450, 100);
        description_label->setMaximumSize(450, 100);
    modif = new QPushButton("Modifier");
        modif->setMinimumSize(100, 20);
        modif->setMaximumSize(100, 20);
        QObject::connect(modif, SIGNAL(clicked()), this, SLOT(modifier()));

    QVBoxLayout *layout1 = new QVBoxLayout;
        layout1->addWidget(description_label);

        nom_label->setLayout(layout1);

    QHBoxLayout *layoutHor = new QHBoxLayout;
        layoutHor->addWidget(nom_label);
        layoutHor->addWidget(modif);
        layoutHor->setSpacing(50);

    setLayout(layoutHor);
}

Competence::~Competence()
{}

QString Competence::getNom() const
{
    return m_nom;
}
QString Competence::getDescription() const
{
    return m_description;
}
QWidget* Competence::getWidget()
{
    return this;
}

void Competence::modifier()
{
    fen = new QDialog(this, Qt::WindowCancelButtonHint | Qt::WindowOkButtonHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);

    QGroupBox nom_group("Nom");
        nom_edit = new QLineEdit(m_nom);
        QVBoxLayout layout1;
            layout1.addWidget(nom_edit);
        nom_group.setLayout(&layout1);

    QGroupBox description_group("Description");
        description_edit = new QTextEdit();
            description_edit->setPlainText(m_description);
        QVBoxLayout layout2;
            layout2.addWidget(description_edit);
        description_group.setLayout(&layout2);

    QDialogButtonBox boutons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        QObject::connect(&boutons, SIGNAL(accepted()), this, SLOT(modifier2()));
        QObject::connect(&boutons, SIGNAL(rejected()), fen, SLOT(close()));

    QVBoxLayout total;
        total.addWidget(&nom_group);
        total.addWidget(&description_group);
        total.addWidget(&boutons);

    fen->setLayout(&total);

    fen->exec();
}
void Competence::modifier2()
{
    m_nom = nom_edit->text();
    m_description = description_edit->toPlainText();

    delete nom_edit;
    delete description_edit;

    nom_label->setTitle(m_nom);
    description_label->setText(m_description);

    fen->close();
}
