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

#include "EquipModif.h"
#include "ui_EquipModif.h"

EquipModif::EquipModif(Protection *objet)
    : QDialog(), ui(new Ui::EquipModif), modif(false)
{
    ui->setupUi(this);

    m_pr = objet;
    m_arme = 0;
    m_fleche = 0;
    m_vet = 0;

    chargerAffichage();
}

EquipModif::EquipModif(Arme *objet)
    : QDialog(), ui(new Ui::EquipModif), modif(false)
{
    ui->setupUi(this);

    m_pr = 0;
    m_arme = objet;
    m_fleche = 0;
    m_vet = 0;

    chargerAffichage();
}

EquipModif::EquipModif(Fleche *objet)
    : QDialog(), ui(new Ui::EquipModif), modif(false)
{
    ui->setupUi(this);

    m_pr = 0;
    m_arme = 0;
    m_fleche = objet;
    m_vet = 0;

    chargerAffichage();
}

EquipModif::EquipModif(Vetement *objet)
    : QDialog(), ui(new Ui::EquipModif), modif(false)
{
    ui->setupUi(this);

    m_pr = 0;
    m_arme = 0;
    m_fleche = 0;
    m_vet = objet;

    chargerAffichage();
}


EquipModif::~EquipModif()
{
    delete ui;
}


void EquipModif::on_vider_clicked()
{
    verifModif();

    if (m_pr != 0)
    {
        m_pr->setNom("Pas de protection");
        m_pr->setPR(0);
        m_pr->setBonus(Caracteristiques(0, 0, 0, 0, 0, 0, 0));
        m_pr->setMalus(Caracteristiques(0, 0, 0, 0, 0, 0, 0));
        m_pr->setRupture(0);
    }
    else if (m_arme != 0)
    {
        m_arme->setNom("A mains nues");
        m_arme->setDegats(1, -2);
        m_arme->setBonus(Caracteristiques(0, 0, 0, 0, 0, 0, 0));
        m_arme->setMalus(Caracteristiques(0, 0, 0, 0, 0, 4, 0));
        m_arme->setRupture(0);
    }
    else if (m_fleche != 0)
    {
        m_fleche->setNom("Pas de flèches");
        m_fleche->setNombre(0);
        m_fleche->setAD(0);
        m_fleche->setNbDes(0);
        m_fleche->setPI(0);
        m_fleche->setRupture(0);
    }
    else if (m_vet != 0)
    {
        m_vet->setNom("Nu");
        m_vet->setBonus(Caracteristiques(0, 0, 0, 0, 0));
        m_vet->setMalus(Caracteristiques(0, 0, 0, 0, 0));
    }
    else
        fatalError("Aucun équipement valide envoyé à la fenêtre de modification !");

    QDialog::accept();
}


void EquipModif::chargerAffichage()
{
    if (m_pr != 0)
    {
        ui->nom->setText(m_pr->getNom());

        ui->pr->setValue(m_pr->getNbPR());
        ui->rupt->setValue(m_pr->getRupture());

        ui->COU->setValue(m_pr->getBonus().getCourage());
        ui->INTEL->setValue(m_pr->getBonus().getIntelligence());
        ui->CHA->setValue(m_pr->getBonus().getCharisme());
        ui->AD->setValue(m_pr->getBonus().getAdresse());
        ui->FO->setValue(m_pr->getBonus().getForce());
        ui->AT->setValue(m_pr->getBonus().getAttaque());
        ui->PRD->setValue(m_pr->getBonus().getParade());

        ui->cou->setValue(m_pr->getMalus().getCourage());
        ui->intel->setValue(m_pr->getMalus().getIntelligence());
        ui->cha->setValue(m_pr->getMalus().getCharisme());
        ui->ad->setValue(m_pr->getMalus().getAdresse());
        ui->fo->setValue(m_pr->getMalus().getForce());
        ui->at->setValue(m_pr->getMalus().getAttaque());
        ui->prd->setValue(m_pr->getMalus().getParade());

        // On cache le reste
        ui->deLabel->hide();
            ui->de->hide();
        ui->PILabel->hide();
            ui->PI->hide();
        ui->nbLabel->hide();
            ui->nb->hide();
        ui->typeLabel->hide();
            ui->type->hide();
    }
    else if (m_arme != 0)
    {
        ui->nom->setText(m_arme->getNom());

        ui->rupt->setValue(m_arme->getRupture());
        ui->de->setValue(m_arme->getNbDes());
        ui->PI->setValue(m_arme->getDegatsEnPlus());

        ui->COU->setValue(m_arme->getBonus().getCourage());
        ui->INTEL->setValue(m_arme->getBonus().getIntelligence());
        ui->CHA->setValue(m_arme->getBonus().getCharisme());
        ui->AD->setValue(m_arme->getBonus().getAdresse());
        ui->FO->setValue(m_arme->getBonus().getForce());
        ui->AT->setValue(m_arme->getBonus().getAttaque());
        ui->PRD->setValue(m_arme->getBonus().getParade());

        ui->cou->setValue(m_arme->getMalus().getCourage());
        ui->intel->setValue(m_arme->getMalus().getIntelligence());
        ui->cha->setValue(m_arme->getMalus().getCharisme());
        ui->ad->setValue(m_arme->getMalus().getAdresse());
        ui->fo->setValue(m_arme->getMalus().getForce());
        ui->at->setValue(m_arme->getMalus().getAttaque());
        ui->prd->setValue(m_arme->getMalus().getParade());

        if (m_arme->getType() == Arme::MainNue)
            ui->type->setCurrentIndex(0);
        else if (m_arme->getType() == Arme::Contandante)
            ui->type->setCurrentIndex(1);
        else if (m_arme->getType() == Arme::Tranchante)
            ui->type->setCurrentIndex(2);
        else if (m_arme->getType() == Arme::Projectile)
            ui->type->setCurrentIndex(3);

        // On cache le reste
        ui->prLabel->hide();
            ui->pr->hide();
        ui->nbLabel->hide();
            ui->nb->hide();
    }
    else if (m_fleche != 0)
    {
        ui->nom->setText(m_fleche->getNom());

        ui->rupt->setValue(m_fleche->getRupture());
        ui->de->setValue(m_fleche->getNbDes());
        ui->PI->setValue(m_fleche->getPI());
        ui->nb->setValue(m_fleche->getNombre());

        ui->AD->setValue(m_fleche->getAD());

        // On cache le reste
        ui->prLabel->hide();
            ui->pr->hide();

        ui->COULabel->hide();
            ui->COU->hide();
        ui->INTELLabel->hide();
            ui->INTEL->hide();
        ui->CHALabel->hide();
            ui->CHA->hide();
        ui->FOLabel->hide();
            ui->FO->hide();
        ui->ATLabel->hide();
            ui->AT->hide();
        ui->PRDLabel->hide();
            ui->PRD->hide();


        ui->malusGroup->hide();
        ui->line_3->hide();

        ui->typeLabel->hide();
            ui->type->hide();
    }
    else if (m_vet != 0)
    {
        ui->nom->setText(m_vet->getNom());

        ui->COU->setValue(m_vet->getBonus().getCourage());
        ui->INTEL->setValue(m_vet->getBonus().getIntelligence());
        ui->CHA->setValue(m_vet->getBonus().getCharisme());
        ui->AD->setValue(m_vet->getBonus().getAdresse());
        ui->FO->setValue(m_vet->getBonus().getForce());

        ui->cou->setValue(m_vet->getMalus().getCourage());
        ui->intel->setValue(m_vet->getMalus().getIntelligence());
        ui->cha->setValue(m_vet->getMalus().getCharisme());
        ui->ad->setValue(m_vet->getMalus().getAdresse());
        ui->fo->setValue(m_vet->getMalus().getForce());

        // On cache le reste
        ui->deLabel->hide();
            ui->de->hide();
        ui->PILabel->hide();
            ui->PI->hide();
        ui->prLabel->hide();
            ui->pr->hide();
        ui->nbLabel->hide();
            ui->nb->hide();
        ui->ruptLabel->hide();
            ui->rupt->hide();

        ui->ATLabel->hide();
            ui->AT->hide();
        ui->PRDLabel->hide();
            ui->PRD->hide();

        ui->atLabel->hide();
            ui->at->hide();
        ui->prdLabel->hide();
            ui->prd->hide();
        ui->typeLabel->hide();
            ui->type->hide();
    }
    else
        fatalError("Aucun équipement valide envoyé à la fenêtre de modification !");
}


void EquipModif::accept()
{
    verifModif();

    if (m_pr != 0)
    {
        m_pr->setNom(ui->nom->text());
        m_pr->setPR(ui->pr->value());
        m_pr->setBonus(Caracteristiques(ui->COU->value(),
                                        ui->INTEL->value(),
                                        ui->CHA->value(),
                                        ui->AD->value(),
                                        ui->FO->value(),
                                        ui->AT->value(),
                                        ui->PRD->value()));
        m_pr->setMalus(Caracteristiques(ui->cou->value(),
                                        ui->intel->value(),
                                        ui->cha->value(),
                                        ui->ad->value(),
                                        ui->fo->value(),
                                        ui->at->value(),
                                        ui->prd->value()));
        m_pr->setRupture(ui->rupt->value());
    }
    else if (m_arme != 0)
    {
        m_arme->setNom(ui->nom->text());
        m_arme->setDegats(ui->de->value(), ui->PI->value());
        m_arme->setBonus(Caracteristiques(ui->COU->value(),
                                          ui->INTEL->value(),
                                          ui->CHA->value(),
                                          ui->AD->value(),
                                          ui->FO->value(),
                                          ui->AT->value(),
                                          ui->PRD->value()));
        m_arme->setMalus(Caracteristiques(ui->cou->value(),
                                          ui->intel->value(),
                                          ui->cha->value(),
                                          ui->ad->value(),
                                          ui->fo->value(),
                                          ui->at->value(),
                                          ui->prd->value()));
        m_arme->setRupture(ui->rupt->value());
        switch(ui->type->currentIndex())
        {
        case 0:
            m_arme->setType(Arme::MainNue);
            break;

        case 1:
            m_arme->setType(Arme::Contandante);
            break;

        case 2:
            m_arme->setType(Arme::Tranchante);
            break;

        case 3:
            m_arme->setType(Arme::Projectile);
            break;
        }
    }
    else if (m_fleche != 0)
    {
        m_fleche->setNom(ui->nom->text());
        m_fleche->setNombre(ui->nb->value());
        m_fleche->setAD(ui->AD->value());
        m_fleche->setNbDes(ui->de->value());
        m_fleche->setPI(ui->PI->value());
        m_fleche->setRupture(ui->rupt->value());
    }
    else if (m_vet != 0)
    {
        m_vet->setNom(ui->nom->text());
        m_vet->setBonus(Caracteristiques(ui->COU->value(),
                                        ui->INTEL->value(),
                                        ui->CHA->value(),
                                        ui->AD->value(),
                                        ui->FO->value()));
        m_vet->setMalus(Caracteristiques(ui->cou->value(),
                                        ui->intel->value(),
                                        ui->cha->value(),
                                        ui->ad->value(),
                                        ui->fo->value()));
    }
    else
        fatalError("Aucun équipement valide envoyé à la fenêtre de modification !");

    QDialog::accept();
}


void EquipModif::verifModif()
{
    if (m_pr != 0)
    {
        Protection temp(ui->nom->text(),
                        ui->pr->value(),
                        ui->cou->value(),
                        ui->intel->value(),
                        ui->cha->value(),
                        ui->ad->value(),
                        ui->fo->value(),
                        ui->at->value(),
                        ui->prd->value(),
                        ui->COU->value(),
                        ui->INTEL->value(),
                        ui->CHA->value(),
                        ui->AD->value(),
                        ui->FO->value(),
                        ui->AT->value(),
                        ui->PRD->value());
        temp.setRupture(ui->rupt->value());

        if (m_pr->protectionEnregistrement() != temp.protectionEnregistrement())
            modif = true;
    }
    else if (m_arme != 0)
    {
        Arme temp(ui->nom->text(),
                  ui->de->value(),
                  ui->PI->value(),
                  ui->cou->value(),
                  ui->intel->value(),
                  ui->cha->value(),
                  ui->ad->value(),
                  ui->fo->value(),
                  ui->at->value(),
                  ui->prd->value(),
                  ui->COU->value(),
                  ui->INTEL->value(),
                  ui->CHA->value(),
                  ui->AD->value(),
                  ui->FO->value(),
                  ui->AT->value(),
                  ui->PRD->value());
        temp.setRupture(ui->rupt->value());
        switch(ui->type->currentIndex())
        {
        case 0:
            temp.setType(Arme::MainNue);
            break;

        case 1:
            temp.setType(Arme::Contandante);
            break;

        case 2:
            temp.setType(Arme::Tranchante);
            break;

        case 3:
            temp.setType(Arme::Projectile);
            break;
        }

        if (m_arme->armeEnregistrement() != temp.armeEnregistrement())
            modif = true;
    }
    else if (m_fleche != 0)
    {
        Fleche temp(ui->nom->text(),
                    ui->nb->value(),
                    ui->PI->value(),
                    ui->AD->value());
        temp.setRupture(ui->rupt->value());

        if (m_fleche->flechesEnregistrement() != temp.flechesEnregistrement())
            modif = true;
    }
    else if (m_vet != 0)
    {
        Vetement temp(ui->nom->text(),
                      ui->cou->value(),
                      ui->intel->value(),
                      ui->cha->value(),
                      ui->ad->value(),
                      ui->fo->value(),
                      ui->COU->value(),
                      ui->INTEL->value(),
                      ui->CHA->value(),
                      ui->AD->value(),
                      ui->FO->value());

        if (m_vet->vetementEnregistrement() != temp.vetementEnregistrement())
            modif = true;
    }
    else
        fatalError("Aucun équipement valide envoyé à la fenêtre de modification !");

    QDialog::accept();
}
bool EquipModif::equipementModifie()
{
    return modif;
}
