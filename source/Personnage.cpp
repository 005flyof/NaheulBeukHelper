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

#include "Personnage.h"
#include "ui_Personnage.h"

Personnage::Personnage(QString fichier)
    : QTabWidget(), ui(new Ui::Personnage),
      m_fichierPerso(0),
      m_cheminEnregistrement(fichier),
      modifNonRec(false)
{
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(persoModifie()), this, SLOT(modifierPerso()));
}
Personnage::~Personnage()
{
    delete ui;
}


// Accesseurs
QString Personnage::getNom() const
{
    return m_nom;
}
QScrollArea* Personnage::getScroll() const
{
    return ui->scroll;
}


// Affichage
void Personnage::setAffichage()
{
// Informations générales
    ui->nom->setText(m_nom);
    ui->sexe->setText(m_sexe);
    ui->origine->setText(m_origine);
    ui->metier->setText(m_metier);

    ui->lvl->setText(QString::number(m_niveau));
    ui->xp->setText(QString::number(m_experience));
    ui->destin->setText(QString::number(m_ptsDestin));

// Richesses
    rafraichirRichesses();

// Caractéristiques
    rafraichirCarac();

// Protections
    rafraichirProtections();

// Armes
    rafraichirArmes();

// Flèches
    rafraichirFleches();

// Vêtements
    rafraichirVetements();

// Equipements
    ui->equips_1->setText(m_equipements[0]);
    ui->equips_2->setText(m_equipements[1]);
    ui->equips_3->setText(m_equipements[2]);
    ui->equips_4->setText(m_equipements[3]);
    ui->equips_5->setText(m_equipements[4]);
    ui->equips_6->setText(m_equipements[5]);
    ui->equips_7->setText(m_equipements[6]);
    ui->equips_8->setText(m_equipements[7]);
    ui->equips_9->setText(m_equipements[8]);
    ui->equips_10->setText(m_equipements[9]);

// Compétences
    if (m_competences.empty())
    {
        bool ok(true);
        int nb = QInputDialog::getInt(this, m_nom + " -> Aucunes compétences",
                                      m_nom + " ne semble pas avoir de compétence, est-il si nul que ça ?\n"
                                      "Combien de compétences voulez-vous lui rajouter ?\n"
                                      "Cliquez sur annuler pour ne pas en ajouter !", 1, 1, 50, 1, &ok);
        if (ok)
            for (int i(0); i < nb; i++)
                ajouterCompetence();
        return;
    }

    QVBoxLayout *layoutCompetences = new QVBoxLayout;

    for (int i(0); i < m_competences.count(); i++)
        layoutCompetences->addWidget(m_competences.at(i)->getWidget());

    ui->competencesScrollWidgetContents->setLayout(layoutCompetences);
}
void Personnage::rafraichirRichesses()
{
// PO
    ui->po->setText(QString::number(m_richesses->getOr()));
    if (m_richesses->getOr() == -99999)
    {
        ui->poMoins->setEnabled(false);
        ui->poPlus->setEnabled(true);
    }
    else if (m_richesses->getOr() == 999999)
    {
        ui->poMoins->setEnabled(true);
        ui->poPlus->setEnabled(false);
    }
    else
    {
        ui->poMoins->setEnabled(true);
        ui->poPlus->setEnabled(true);
    }

// PA
    ui->pa->setText(QString::number(m_richesses->getArgent()));
    if (m_richesses->getArgent() == -99999)
    {
        ui->paMoins->setEnabled(false);
        ui->paPlus->setEnabled(true);
    }
    else if (m_richesses->getArgent() == 999999)
    {
        ui->paMoins->setEnabled(true);
        ui->paPlus->setEnabled(false);
    }
    else
    {
        ui->paMoins->setEnabled(true);
        ui->paPlus->setEnabled(true);
    }

// PC
    ui->pc->setText(QString::number(m_richesses->getCuivre()));
    if (m_richesses->getCuivre() == -99999)
    {
        ui->pcMoins->setEnabled(false);
        ui->pcPlus->setEnabled(true);
    }
    else if (m_richesses->getCuivre() == 999999)
    {
        ui->pcMoins->setEnabled(true);
        ui->pcPlus->setEnabled(false);
    }
    else
    {
        ui->pcMoins->setEnabled(true);
        ui->pcPlus->setEnabled(true);
    }
}
void Personnage::rafraichirCarac()
{
    if (ui->remiseAZero->isChecked())
        calculerCarac();
    calculerCaracSupInfMoy();

    ui->ev->setText(QString::number(m_EV));
    ui->evModif->setText(QString::number(m_EV_modif));
        ui->evPlus->setEnabled(true);
        ui->evMoins->setEnabled(true);
        if (m_EV_modif == m_EV)
            ui->evPlus->setEnabled(false);
        else if (m_EV_modif == 0)
            ui->evMoins->setEnabled(false);

    if (m_presenceEA)
    {
        ui->ea->setText(QString::number(m_EA));
        ui->eaModif->setText(QString::number(m_EA_modif));
            ui->eaPlus->setEnabled(true);
            ui->eaMoins->setEnabled(true);
            if (m_EA_modif == m_EA)
                ui->eaPlus->setEnabled(false);
            else if (m_EA_modif == 0)
                ui->eaMoins->setEnabled(false);
        ui->typeEa->setText(m_typeEA);
        ui->magiePhys->setText(QString::number((m_carac_modif->getIntelligence() + m_carac_modif->getAdresse() ) / 2));
        ui->magiePsy->setText(QString::number((m_carac_modif->getIntelligence() + m_carac_modif->getCharisme() ) / 2));
    }
    else
    {
        ui->eaModif->setEnabled(false);
        ui->eaPlus->setEnabled(false);
        ui->eaMoins->setEnabled(false);

        ui->ea->setText("-");
        ui->eaModif->setText("-");
        ui->typeEa->setText("-");
        ui->magiePhys->setText("-");
        ui->magiePsy->setText("-");
    }
    ui->resistMagie->setText(QString::number((m_carac_modif->getIntelligence() + m_carac_modif->getCourage() + m_carac_modif->getForce() ) / 3));

    ui->cou->setText(QString::number(m_carac->getCourage()));
    ui->couModif->setText(QString::number(m_carac_modif->getCourage()));
        ui->couPlus->setEnabled(true);
        ui->couMoins->setEnabled(true);
        if (m_carac_modif->getCourage() == 18)
            ui->couPlus->setEnabled(false);
        else if (m_carac_modif->getCourage() == 2)
            ui->couMoins->setEnabled(false);

    ui->intel->setText(QString::number(m_carac->getIntelligence()));
    ui->intelModif->setText(QString::number(m_carac_modif->getIntelligence()));
        ui->intelPlus->setEnabled(true);
        ui->intelMoins->setEnabled(true);
        if (m_carac_modif->getIntelligence() == 18)
            ui->intelPlus->setEnabled(false);
        else if (m_carac_modif->getIntelligence() == 2)
            ui->intelMoins->setEnabled(false);

    ui->cha->setText(QString::number(m_carac->getCharisme()));
    ui->chaModif->setText(QString::number(m_carac_modif->getCharisme()));
        ui->chaPlus->setEnabled(true);
        ui->chaMoins->setEnabled(true);
        if (m_carac_modif->getCharisme() == 18)
            ui->chaPlus->setEnabled(false);
        else if (m_carac_modif->getCharisme() == 2)
            ui->chaMoins->setEnabled(false);

    ui->ad->setText(QString::number(m_carac->getAdresse()));
    ui->adModif->setText(QString::number(m_carac_modif->getAdresse()));
        ui->adPlus->setEnabled(true);
        ui->adMoins->setEnabled(true);
        if (m_carac_modif->getAdresse() == 18)
            ui->adPlus->setEnabled(false);
        else if (m_carac_modif->getAdresse() == 2)
            ui->adMoins->setEnabled(false);

    ui->fo->setText(QString::number(m_carac->getForce()));
    ui->foModif->setText(QString::number(m_carac_modif->getForce()));
        ui->foPlus->setEnabled(true);
        ui->foMoins->setEnabled(true);
        if (m_carac_modif->getForce() == 18)
            ui->foPlus->setEnabled(false);
        else if (m_carac_modif->getForce() == 2)
            ui->foMoins->setEnabled(false);

    ui->at->setText(QString::number(m_carac->getAttaque()));
    ui->atModif->setText(QString::number(m_carac_modif->getAttaque()));
        ui->atPlus->setEnabled(true);
        ui->atMoins->setEnabled(true);
        if (m_carac_modif->getAttaque() == 18)
            ui->atPlus->setEnabled(false);
        else if (m_carac_modif->getAttaque() == 2)
            ui->atMoins->setEnabled(false);

    ui->prd->setText(QString::number(m_carac->getParade()));
    ui->prdModif->setText(QString::number(m_carac_modif->getParade()));
        ui->prdPlus->setEnabled(true);
        ui->prdMoins->setEnabled(true);
        if (m_carac_modif->getParade() == 18)
            ui->prdPlus->setEnabled(false);
        else if (m_carac_modif->getParade() == 2)
            ui->prdMoins->setEnabled(false);


    for (int i(0); i < MAX_ARME; i++)
    {
        m_AT_modif[i] = m_carac_modif->getAttaque() + m_armes[i]->getBonus().getAttaque() - m_armes[i]->getMalus().getAttaque();
        m_PRD_modif[i] = m_carac_modif->getParade() + m_armes[i]->getBonus().getParade() - m_armes[i]->getMalus().getParade();
    }

    ui->AT_arme_1->setText(QString::number(m_AT_modif[0]));
    ui->AT_arme_2->setText(QString::number(m_AT_modif[1]));
    ui->AT_arme_3->setText(QString::number(m_AT_modif[2]));
    ui->AT_arme_4->setText(QString::number(m_AT_modif[3]));

    ui->PRD_arme_1->setText(QString::number(m_PRD_modif[0]));
    ui->PRD_arme_2->setText(QString::number(m_PRD_modif[1]));
    ui->PRD_arme_3->setText(QString::number(m_PRD_modif[2]));
    ui->PRD_arme_4->setText(QString::number(m_PRD_modif[3]));
}
void Personnage::rafraichirProtections()
{
    ui->prNom_1->setText(m_protections[0]->getNom());
    ui->prBonus_1->setText(m_protections[0]->getBonusAffichage());
    ui->prMalus_1->setText(m_protections[0]->getMalusAffichage());
    ui->prPr_1->setText(QString::number(m_protections[0]->getNbPR()));
    ui->prRupt_1->setText(m_protections[0]->getRuptAffichage());

    ui->prNom_2->setText(m_protections[1]->getNom());
    ui->prBonus_2->setText(m_protections[1]->getBonusAffichage());
    ui->prMalus_2->setText(m_protections[1]->getMalusAffichage());
    ui->prPr_2->setText(QString::number(m_protections[1]->getNbPR()));
    ui->prRupt_2->setText(m_protections[1]->getRuptAffichage());

    ui->prNom_3->setText(m_protections[2]->getNom());
    ui->prBonus_3->setText(m_protections[2]->getBonusAffichage());
    ui->prMalus_3->setText(m_protections[2]->getMalusAffichage());
    ui->prPr_3->setText(QString::number(m_protections[2]->getNbPR()));
    ui->prRupt_3->setText(m_protections[2]->getRuptAffichage());

    ui->prNom_4->setText(m_protections[3]->getNom());
    ui->prBonus_4->setText(m_protections[3]->getBonusAffichage());
    ui->prMalus_4->setText(m_protections[3]->getMalusAffichage());
    ui->prPr_4->setText(QString::number(m_protections[3]->getNbPR()));
    ui->prRupt_4->setText(m_protections[3]->getRuptAffichage());

    ui->prNom_5->setText(m_protections[4]->getNom());
    ui->prBonus_5->setText(m_protections[4]->getBonusAffichage());
    ui->prMalus_5->setText(m_protections[4]->getMalusAffichage());
    ui->prPr_5->setText(QString::number(m_protections[4]->getNbPR()));
    ui->prRupt_5->setText(m_protections[4]->getRuptAffichage());

    ui->prNom_6->setText(m_protections[5]->getNom());
    ui->prBonus_6->setText(m_protections[5]->getBonusAffichage());
    ui->prMalus_6->setText(m_protections[5]->getMalusAffichage());
    ui->prPr_6->setText(QString::number(m_protections[5]->getNbPR()));
    ui->prRupt_6->setText(m_protections[5]->getRuptAffichage());

    m_prTotale = m_protections[0]->getNbPR()
               + m_protections[1]->getNbPR()
               + m_protections[2]->getNbPR()
               + m_protections[3]->getNbPR()
               + m_protections[4]->getNbPR()
               + m_protections[5]->getNbPR();
    ui->prTotale->setText(QString::number(m_prTotale));

    rafraichirCarac();
}
void Personnage::rafraichirArmes()
{
    ui->armesNom_1->setText(m_armes[0]->getNom());
    ui->armesBonus_1->setText(m_armes[0]->getBonusAffichage());
    ui->armesMalus_1->setText(m_armes[0]->getMalusAffichage());
    ui->armesPi_1->setText(m_armes[0]->getDegatsAffichage());
    ui->armesRupt_1->setText(m_armes[0]->getRuptAffichage());

    ui->armesNom_2->setText(m_armes[1]->getNom());
    ui->armesBonus_2->setText(m_armes[1]->getBonusAffichage());
    ui->armesMalus_2->setText(m_armes[1]->getMalusAffichage());
    ui->armesPi_2->setText(m_armes[1]->getDegatsAffichage());
    ui->armesRupt_2->setText(m_armes[1]->getRuptAffichage());

    ui->armesNom_3->setText(m_armes[2]->getNom());
    ui->armesBonus_3->setText(m_armes[2]->getBonusAffichage());
    ui->armesMalus_3->setText(m_armes[2]->getMalusAffichage());
    ui->armesPi_3->setText(m_armes[2]->getDegatsAffichage());
    ui->armesRupt_3->setText(m_armes[2]->getRuptAffichage());

    ui->armesNom_4->setText(m_armes[3]->getNom());
    ui->armesBonus_4->setText(m_armes[3]->getBonusAffichage());
    ui->armesMalus_4->setText(m_armes[3]->getMalusAffichage());
    ui->armesPi_4->setText(m_armes[3]->getDegatsAffichage());
    ui->armesRupt_4->setText(m_armes[3]->getRuptAffichage());

    rafraichirCarac();
}
void Personnage::rafraichirFleches()
{
    ui->flechesNom_1->setText(m_fleches[0]->getNom());
    ui->flechesBonus_1->setText(m_fleches[0]->getBonusAffichage());
    ui->flechesNb_1->setText(QString::number(m_fleches[0]->getNombre()));
    ui->flechesRupt_1->setText(m_fleches[0]->getRuptAffichage());
    if (m_fleches[0]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_1->setEnabled(false);
        ui->flechesPlus_1->setEnabled(false);
        ui->flechesMoins_1->setEnabled(false);
    }
    else if (m_fleches[0]->getNombre() == 0)
    {
        ui->flechesNb_1->setEnabled(true);
        ui->flechesPlus_1->setEnabled(true);
        ui->flechesMoins_1->setEnabled(false);
    }
    else
    {
        ui->flechesNb_1->setEnabled(true);
        ui->flechesPlus_1->setEnabled(true);
        ui->flechesMoins_1->setEnabled(true);
    }

    ui->flechesNom_2->setText(m_fleches[1]->getNom());
    ui->flechesBonus_2->setText(m_fleches[1]->getBonusAffichage());
    ui->flechesNb_2->setText(QString::number(m_fleches[1]->getNombre()));
    ui->flechesRupt_2->setText(m_fleches[1]->getRuptAffichage());
    if (m_fleches[1]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_2->setEnabled(false);
        ui->flechesPlus_2->setEnabled(false);
        ui->flechesMoins_2->setEnabled(false);
    }
    else if (m_fleches[1]->getNombre() == 0)
    {
        ui->flechesNb_2->setEnabled(true);
        ui->flechesPlus_2->setEnabled(true);
        ui->flechesMoins_2->setEnabled(false);
    }
    else
    {
        ui->flechesNb_2->setEnabled(true);
        ui->flechesPlus_2->setEnabled(true);
        ui->flechesMoins_2->setEnabled(true);
    }

    ui->flechesNom_3->setText(m_fleches[2]->getNom());
    ui->flechesBonus_3->setText(m_fleches[2]->getBonusAffichage());
    ui->flechesNb_3->setText(QString::number(m_fleches[2]->getNombre()));
    ui->flechesRupt_3->setText(m_fleches[2]->getRuptAffichage());
    if (m_fleches[2]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_3->setEnabled(false);
        ui->flechesPlus_3->setEnabled(false);
        ui->flechesMoins_3->setEnabled(false);
    }
    else if (m_fleches[2]->getNombre() == 0)
    {
        ui->flechesNb_3->setEnabled(true);
        ui->flechesPlus_3->setEnabled(true);
        ui->flechesMoins_3->setEnabled(false);
    }
    else
    {
        ui->flechesNb_3->setEnabled(true);
        ui->flechesPlus_3->setEnabled(true);
        ui->flechesMoins_3->setEnabled(true);
    }

    ui->flechesNom_4->setText(m_fleches[3]->getNom());
    ui->flechesBonus_4->setText(m_fleches[3]->getBonusAffichage());
    ui->flechesNb_4->setText(QString::number(m_fleches[3]->getNombre()));
    ui->flechesRupt_4->setText(m_fleches[3]->getRuptAffichage());
    if (m_fleches[3]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_4->setEnabled(false);
        ui->flechesPlus_4->setEnabled(false);
        ui->flechesMoins_4->setEnabled(false);
    }
    else if (m_fleches[3]->getNombre() == 0)
    {
        ui->flechesNb_4->setEnabled(true);
        ui->flechesPlus_4->setEnabled(true);
        ui->flechesMoins_4->setEnabled(false);
    }
    else
    {
        ui->flechesNb_4->setEnabled(true);
        ui->flechesPlus_4->setEnabled(true);
        ui->flechesMoins_4->setEnabled(true);
    }

    ui->flechesNom_5->setText(m_fleches[4]->getNom());
    ui->flechesBonus_5->setText(m_fleches[4]->getBonusAffichage());
    ui->flechesNb_5->setText(QString::number(m_fleches[4]->getNombre()));
    ui->flechesRupt_5->setText(m_fleches[4]->getRuptAffichage());
    if (m_fleches[4]->getNom() == "Pas de flèches")
    {
        ui->flechesNb_5->setEnabled(false);
        ui->flechesPlus_5->setEnabled(false);
        ui->flechesMoins_5->setEnabled(false);
    }
    else if (m_fleches[4]->getNombre() == 0)
    {
        ui->flechesNb_5->setEnabled(true);
        ui->flechesPlus_5->setEnabled(true);
        ui->flechesMoins_5->setEnabled(false);
    }
    else
    {
        ui->flechesNb_5->setEnabled(true);
        ui->flechesPlus_5->setEnabled(true);
        ui->flechesMoins_5->setEnabled(true);
    }

    rafraichirCarac();
}
void Personnage::rafraichirVetements()
{
    ui->vetNom_1->setText(m_vetements[0]->getNom());
    ui->vetBonus_1->setText(m_vetements[0]->getBonusAffichage());
    ui->vetMalus_1->setText(m_vetements[0]->getMalusAffichage());
    ui->vetVisible_1->setChecked(m_vetements[0]->isVisible());

    ui->vetNom_2->setText(m_vetements[1]->getNom());
    ui->vetBonus_2->setText(m_vetements[1]->getBonusAffichage());
    ui->vetMalus_2->setText(m_vetements[1]->getMalusAffichage());
    ui->vetVisible_2->setChecked(m_vetements[1]->isVisible());

    ui->vetNom_3->setText(m_vetements[2]->getNom());
    ui->vetBonus_3->setText(m_vetements[2]->getBonusAffichage());
    ui->vetMalus_3->setText(m_vetements[2]->getMalusAffichage());
    ui->vetVisible_3->setChecked(m_vetements[2]->isVisible());

    ui->vetNom_4->setText(m_vetements[3]->getNom());
    ui->vetBonus_4->setText(m_vetements[3]->getBonusAffichage());
    ui->vetMalus_4->setText(m_vetements[3]->getMalusAffichage());
    ui->vetVisible_4->setChecked(m_vetements[3]->isVisible());

    ui->vetNom_5->setText(m_vetements[4]->getNom());
    ui->vetBonus_5->setText(m_vetements[4]->getBonusAffichage());
    ui->vetMalus_5->setText(m_vetements[4]->getMalusAffichage());
    ui->vetVisible_5->setChecked(m_vetements[4]->isVisible());

    rafraichirCarac();
}
void Personnage::calculerCarac()
{
// On remet à zéro
    *m_carac_modif = *m_carac;

// On calcule
    for (int i(0); i < MAX_PROTECTION; i++)
    {
        *m_carac_modif += m_protections[i]->getBonus();
        *m_carac_modif -= m_protections[i]->getMalus();
    }

    for (int i(0); i < MAX_ARME; i++)
    {
        *m_carac_modif += Caracteristiques(m_armes[i]->getBonus().getCourage(),
                                           m_armes[i]->getBonus().getIntelligence(),
                                           m_armes[i]->getBonus().getCharisme(),
                                           m_armes[i]->getBonus().getAdresse(),
                                           m_armes[i]->getBonus().getForce());
        *m_carac_modif -= Caracteristiques(m_armes[i]->getMalus().getCourage(),
                                           m_armes[i]->getMalus().getIntelligence(),
                                           m_armes[i]->getMalus().getCharisme(),
                                           m_armes[i]->getMalus().getAdresse(),
                                           m_armes[i]->getMalus().getForce());
    }

    for (int i(0); i < MAX_FLECHE; i++)
        m_carac_modif->setAdresse(m_carac_modif->getAdresse() + m_fleches[i]->getAD());

    for (int i(0); i < MAX_VETEMENT; i++)
    {
        if (m_vetements[i]->isVisible())
        {
            *m_carac_modif += m_vetements[i]->getBonus();
            *m_carac_modif -= m_vetements[i]->getMalus();
        }
        else
        {
            *m_carac_modif += Caracteristiques(m_vetements[i]->getBonus().getCourage(),
                                              m_vetements[i]->getBonus().getIntelligence(),
                                              0,
                                              m_vetements[i]->getBonus().getAdresse(),
                                              m_vetements[i]->getBonus().getForce());
            *m_carac_modif -= Caracteristiques(m_vetements[i]->getMalus().getCourage(),
                                              m_vetements[i]->getMalus().getIntelligence(),
                                              0,
                                              m_vetements[i]->getMalus().getAdresse(),
                                              m_vetements[i]->getMalus().getForce());
        }
    }
}
void Personnage::calculerCaracSupInfMoy()
{
    if (!m_bonusMalus_carac_calcules)
    {
        m_bonusMalus_carac_calcules = true;

        int bonus_degats_vieux = m_bonus_degats;
        int bonus_degats_magiques_vieux = m_bonus_degatsMagiques;

        m_bonus_degats = 0;
        m_bonus_degatsMagiques = 0;

    // Bonus / Malus de FO
        for (int fo(m_carac_modif->getForce()); fo > 12; fo--)
            m_bonus_degats++;
        for (int fo(m_carac_modif->getForce()); fo <8; fo++)
            m_bonus_degats--;

        if (bonus_degats_vieux != m_bonus_degats
            && m_bonus_degats > 0)
        {
            QMessageBox::information(this, "Caractéristiques inférieures ou supérieures à la moyenne",
                                     m_nom + " a un bonus de dégâts de " + QString::number(m_bonus_degats) + " en raison de sa force grandiose !");
            emit persoModifie();
        }
        else if (bonus_degats_vieux != m_bonus_degats
                 && m_bonus_degats < 0)
        {
            QMessageBox::information(this, "Caractéristiques inférieures ou supérieures à la moyenne",
                                     m_nom + " a un malus de dégâts de " + QString::number(m_bonus_degats) + " en raison de sa force nullissime !");
            emit persoModifie();
        }
        else if (bonus_degats_vieux != m_bonus_degats)
        {
            QMessageBox::information(this, "Caractéristiques inférieures ou supérieures à la moyenne",
                                     m_nom + " perd son bonus / malus de dégâts !");
            emit persoModifie();
        }

    // Bonus / malus de AD
        if (!m_bonusMalus_ATPRD_calcules)
        {
            m_bonusMalus_ATPRD_calcules = true;

            m_bonus_attaque = 0;
            m_bonus_parade = 0;

            if (m_carac_modif->getAdresse() > 12)
            {
                bool ok(false);
                QStringList at_prd;
                at_prd << "Attaque (" + QString::number(m_carac->getAttaque()) + ")"
                       << "Parade (" + QString::number(m_carac->getParade()) + ")";
                QString choix("");

                while (!ok)
                    choix = QInputDialog::getItem(this, m_nom + " -> Caractéristiques inférieures à la normale.",
                                                  m_nom + " a un malus de 1 point, en raison de son adresse nullissime, sur :",
                                                  at_prd, 0, false, &ok);
                if (choix == "Attaque (" + QString::number(m_carac->getAttaque()) + ")")
                {
                    m_carac_modif->setAttaque(m_carac_modif->getAttaque() + 1);
                    m_bonus_attaque = 1;
                }
                if (choix == "Parade (" + QString::number(m_carac->getParade()) + ")")
                {
                    m_carac_modif->setParade(m_carac_modif->getParade() + 1);
                    m_bonus_parade = 1;
                }

                emit persoModifie();
            }
            if (m_carac_modif->getAdresse() < 8)
            {
                bool ok(false);
                QStringList at_prd;
                at_prd << "Attaque (" + QString::number(m_carac->getAttaque()) + ")"
                       << "Parade (" + QString::number(m_carac->getParade()) + ")";
                QString choix("");

                while (!ok)
                    choix = QInputDialog::getItem(this, m_nom + " -> Caractéristiques inférieures à la normale.",
                                                  m_nom + " a un malus de 1 point, en raison de son adresse nullissime, sur :",
                                                  at_prd, 0, false, &ok);
                if (choix == "Attaque (" + QString::number(m_carac->getAttaque()) + ")")
                {
                    m_carac_modif->setAttaque(m_carac_modif->getAttaque() - 1);
                    m_bonus_attaque = -1;
                }
                if (choix == "Parade (" + QString::number(m_carac->getParade()) + ")")
                {
                    m_carac_modif->setParade(m_carac_modif->getParade() - 1);
                    m_bonus_parade = -1;
                }

                emit persoModifie();
            }
        }

    // Bonus / malus de INT
        for (int intel(m_carac_modif->getIntelligence()); intel > 12; intel--)
            m_bonus_degatsMagiques++;
        for (int intel(m_carac_modif->getIntelligence()); intel < 8; intel++)
            m_bonus_degatsMagiques--;


        if (bonus_degats_magiques_vieux != m_bonus_degatsMagiques
            && m_bonus_degatsMagiques > 0)
        {
            QMessageBox::information(this, "Caractéristiques inférieures ou supérieures à la moyenne",
                                     m_nom + " a un bonus de dégâts magiques de " + QString::number(m_bonus_degatsMagiques) + " en raison de son intelligence grandiose !");
            emit persoModifie();
        }
        else if (bonus_degats_magiques_vieux != m_bonus_degatsMagiques
                 && m_bonus_degatsMagiques < 0)
        {
            QMessageBox::information(this, "Caractéristiques inférieures ou supérieures à la moyenne",
                                     m_nom + " a un malus de dégâts magiques de " + QString::number(m_bonus_degatsMagiques) + " en raison de son intelligence nullissime !");
            emit persoModifie();
        }
        else if (bonus_degats_magiques_vieux != m_bonus_degatsMagiques)
        {
            QMessageBox::information(this, "Caractéristiques inférieures ou supérieures à la moyenne",
                                     m_nom + " perd son bonus / malus de dégâts magiques !");
            emit persoModifie();
        }
    }

// Affichage
    ui->bonus_degats->setText(QString::number(m_bonus_degats));
    ui->bonus_AT->setText(QString::number(m_bonus_attaque));
    ui->bonus_PRD->setText(QString::number(m_bonus_parade));
    ui->bonus_magie->setText(QString::number(m_bonus_degatsMagiques));
}


// Diverses
void Personnage::viderVariables()
{
    m_nom = "";
    m_sexe = "";
    m_origine = "";
    m_metier = "";

    m_EV = 0;
    m_EV_modif = 0;

    m_presenceEA = false;
    m_EA = 0;
    m_EA_modif = 0;
    m_typeEA = "";

    m_carac = 0;
    m_carac_modif = 0;

    m_ptsDestin = 0;
    m_niveau = 0;
    m_experience = 0;

    m_richesses = 0;

    for (int lecteur = 0; lecteur < MAX_VETEMENT; lecteur++)
        m_vetements[lecteur] = 0;

    for (int lecteur = 0; lecteur < MAX_EQUIPEMENT; lecteur++)
        m_equipements[lecteur] = "";

    for (int lecteur = 0; lecteur < MAX_PROTECTION; lecteur++)
        m_protections[lecteur] = 0;
    m_prTotale = 0;

    for (int lecteur = 0; lecteur < MAX_ARME; lecteur++)
    {
        m_armes[lecteur] = 0;
        m_AT_modif[lecteur] = 8;
        m_PRD_modif[lecteur] = 10;
    }

    for (int lecteur = 0; lecteur < MAX_FLECHE; lecteur++)
        m_fleches[lecteur] = 0;

    // Bonus
    m_bonusMalus_carac_calcules = false;
    m_bonusMalus_ATPRD_calcules = false;

    m_bonus_degats = 0;
    m_bonus_degatsMagiques = 0;
    m_bonus_attaque = 0;
    m_bonus_parade = 0;
}
void Personnage::viderTousEquipements()
{
    for (int i = 0; i < MAX_VETEMENT; i++)
        m_vetements[i] = new Vetement("Nu",
                                      0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_PROTECTION; i++)
        m_protections[i] = new Protection("Pas de protection", 0,
                                          0, 0, 0, 0, 0, 0, 0,
                                          0, 0, 0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_ARME; i++)
        m_armes[i] = new Arme("A mains nues", 1, -2,
                              0, 0, 0, 0, 0, 4, 0,
                              0, 0, 0, 0, 0, 0, 0);

    for (int i = 0; i < MAX_FLECHE; i++)
        m_fleches[i] = new Fleche("Pas de flèches", 0, 0, 0);
}
bool Personnage::setNiveau()
{
    int niveauAncien = m_niveau;

    if (m_experience == 0 || m_experience < 100)
    {
        m_niveau = 1;
    }
    else if (m_experience == 100 || m_experience < 300)
    {
        m_niveau = 2;
    }
    else if (m_experience == 300 || m_experience < 600)
    {
        m_niveau = 3;
    }
    else if (m_experience == 600 || m_experience < 1000)
    {
        m_niveau = 4;
    }
    else if (m_experience == 1000 || m_experience < 1500)
    {
        m_niveau = 5;
    }
    else if (m_experience == 1500 || m_experience < 2100)
    {
        m_niveau = 6;
    }
    else if (m_experience == 2100 || m_experience < 2800)
    {
        m_niveau = 7;
    }
    else if (m_experience == 2800 || m_experience < 3600)
    {
        m_niveau = 8;
    }
    else if (m_experience == 3600 || m_experience < 4500)
    {
        m_niveau = 9;
    }
    else if (m_experience == 4500 || m_experience < 5500)
    {
        m_niveau = 10;
    }
    else if (m_experience == 5500 || m_experience < 6600)
    {
        m_niveau = 11;
    }
    else if (m_experience == 6600 || m_experience < 7800)
    {
        m_niveau = 12;
    }
    else if (m_experience == 7800 || m_experience < 9100)
    {
        m_niveau = 13;
    }
    else if (m_experience == 9100 || m_experience < 10500)
    {
        m_niveau = 14;
    }
    else if (m_experience == 10500 || m_experience < 12000)
    {
        m_niveau = 15;
    }
    else if (m_experience == 12000 || m_experience < 13600)
    {
        m_niveau = 16;
    }
    else if (m_experience == 13600 || m_experience < 15300)
    {
        m_niveau = 17;
    }
    else if (m_experience == 15300 || m_experience < 17100)
    {
        m_niveau = 18;
    }
    else if (m_experience == 17100 || m_experience < 19000)
    {
        m_niveau = 19;
    }
    else if (m_experience == 19000 || m_experience < 21000)
    {
        m_niveau = 20;
    }
    else if (m_experience == 21000 || m_experience < 24000)
    {
        m_niveau = 21;
    }
    else if (m_experience == 24000 || m_experience < 29000)
    {
        m_niveau = 22;
    }
    else if (m_experience == 29000 || m_experience < 35000)
    {
        m_niveau = 23;
    }
    else if (m_experience == 35000 || m_experience < 45000)
    {
        m_niveau = 24;
    }
    else if (m_experience == 45000 || m_experience < 60000)
    {
        m_niveau = 25;
    }
    else if (m_experience >= 6000)
    {
        m_niveau = 26;
    }

    ui->lvl->setText(QString::number(m_niveau));

    // Si le niveau est modifié, on renvoie 'true'
    if (niveauAncien != m_niveau)
        return true;
    else
        return false;
}


// Attaque et parade
void Personnage::attaquer()
{
// On demande avec quelle arme attaquer
    // On parcourt les armes pour prendre le nom
    QStringList nomArmes;
    for (int i(0); i < MAX_ARME; i++)
        nomArmes << m_armes[i]->getNom() + " (AT: " + QString::number(m_AT_modif[i]) + " ; PRD: " + QString::number(m_PRD_modif[i]) + ")";
    bool ok(false);

    // On pose la question
    QString nom_arme = QInputDialog::getItem(this, m_nom + " -> Attaque",
                                             "Avec quelle arme " + m_nom + " veut-il attaquer ?",
                                             nomArmes, 0, false, &ok);

// Si on annule, on arrête tout
    if (!ok)
        return;

// On parcourt pour savoir avec quelle arme attaquer
    int i(0);
    bool attaqueFaite(false);
    while (!attaqueFaite)
    {
        int totalDegats(0);

        // On teste si c'est l'arme choisi est celle correspondant à i
        if (nom_arme == m_armes[i]->getNom() + " (AT: " + QString::number(m_AT_modif[i]) + " ; PRD: " + QString::number(m_PRD_modif[i]) + ")")
        {
        // Si l'arme est un projectile
            if (m_armes[i]->getType() == Arme::Projectile)
            {
                // Valeur de D20 pour savoir s'il peut attaquer
                int vingt = QInputDialog::getInt(this, m_nom + " -> Attaque -> Test au D20",
                                                 "Lancez et rentrez la valeur du D20 :",
                                                 1, 1, 20, 1, &ok);

                if (!ok)
                    return;

                bool tirageDegats(false), tirageDegatsCritiques(false);

                // Echec critique
                if (vingt == 19 || vingt == 20)
                {
                    bool valid(false);
                    int de(0);

                    while (!valid)
                        de = QInputDialog::getInt(this, m_nom + " -> Attaque -> Echec critique",
                                                  m_nom + " a fait un échec critique en essayant d'attaquer.\n"
                                                  "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                                  1, 1, 20, 1, &valid);

                    log(m_nom + " fait un échec critique avec '" + m_armes[i]->getNom() + "' :");

                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " rattrape son erreur in extremis, mais le projectile n'atteint pas sa cible !");
                        log("il rattrape son erreur in extremis, mais le projectile n'atteint pas sa cible.", 1);
                    }
                    else if (de >= 3 && de <= 5)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " lache son arme comme un loser !\n"
                                                 "=> combat à main nue, change d'arme");
                        log("il lache son arme comme un loser !\n"
                            "=> combat à main nue, change d'arme", 1);
                        m_armes[i]->setNom("(lachée) " + m_armes[i]->getNom());
                    }
                    else if (de == 6 || de == 7)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe un allié proche vers la gauche !\n"
                                                 "=> tirer les dégâts sur l'allié.");
                        log("il frappe un allié proche vers la gauche !\n"
                            "=> tirer les dégâts sur l'allié.", 1);
                        tirageDegats = true;
                    }
                    else if (de == 8 || de == 9)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe un allié proche vers la droite !\n"
                                                 "=> tirer les dégâts sur l'allié.");
                        log("il frappe un allié proche vers la droite !\n"
                            "=> tirer les dégâts sur l'allié.", 1);
                        tirageDegats = true;
                    }
                    else if (de >= 10 && de <= 12)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe l'allié le plus lointain !\n"
                                                 "=> tirer les dégâts sur l'allié");
                        log("il frappe l'allié le plus lointain !\n"
                            "=> tirer les dégâts sur l'allié", 1);
                        tirageDegats = true;
                    }
                    else if (de >= 13 && de <= 15)
                    {

                        bool valid2(false);
                        int rupt(0);

                        while (!valid2)
                            rupt = QInputDialog::getInt(this, m_nom + " -> Attaque -> Echec critique -> Rupture",
                                                        "Veuillez rentrer le score indiqué par un D6 pour vérifier que l'arme n'est pas cassée !",
                                                        1, 1, 6, 1, &valid2);

                        if (rupt <= m_armes[i]->getRupture())
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique -> Rupture",
                                                     m_nom + " casse son arme !");
                            log("il casse son arme !", 1);
                            m_armes[i]->setNom("(cassée) " + m_armes[i]->getNom());
                        }
                    }
                    else if (de >= 16 && de <= 18)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " se tire dans le pied !\n"
                                                 "=> tirer les dégâts (+2) sur le combattant.");
                        log("il se tire dans le pied !\n"
                            "=> tirer les dégâts (+2) sur le combattant.", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " se blesse très sévèrement de façon atroce et douloureuse !\n"
                                                 "=> tirer des dégâts critiques sur le combattant.");
                        log("il se blesse très sévèrement de façon atroce et douloureuse !\n"
                            "=> tirer des dégâts critiques sur le combattant.", 1);
                        tirageDegatsCritiques = true;
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " crève l'œil de l'allié le plus proche !\n"
                                                 "=> blessure grave.");
                        log("il crève l'œil de l'allié le plus proche !\n"
                            "=> blessure grave.", 1);
                    }
                }

                // Réussite critique
                if (vingt == 1 || vingt == 2 || tirageDegatsCritiques)
                {
                    bool valid(false);
                    int de(0);

                    while (!valid)
                        de = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                  m_nom + " a fait une réussite critique en essayant d'attaquer.\n"
                                                  "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                                  1, 1, 20, 1, &valid);

                    log(m_nom + " fait une réussite critique avec '" + m_armes[i]->getNom() + "' :");

                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " lance bien son projectile : dégâts +1 !");
                        log("il lance bien son projectile : dégâts +1 !", 1);
                        totalDegats++;
                        tirageDegats = true;
                    }
                    else if (de == 3 || de == 4)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " lance magistralement bien son projectile : dégâts +2 !");
                        log("il lance magistralement bien son projectile : dégâts +2 !", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 5 || de == 6)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Le projectile de " + m_nom + " atteint l'ennemi dans une articulation du bras.\n"
                                                 "=> dégâts +3 et AT/PRD-2");
                        log("Le projectile de " + m_nom + " atteint l'ennemi dans une articulation du bras.\n"
                            "=> dégâts +3 et AT/PRD-2", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 7 || de == 8)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Le projectile de " + m_nom + " atteint l'ennemi dans une articulation de la jambe.\n"
                                                 "=> dégâts +3 et MV-50%");
                        log("Le projectile de " + m_nom + " atteint l'ennemi dans une articulation de la jambe.\n"
                            "=> dégâts +3 et MV-50%", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de >= 9 && de <= 11)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Le projectile de " + m_nom + " atteint l'ennemi dans un poumon.\n"
                                                 "=> dégâts +3 et toutes caractéristiques -1");
                        log("Le projectile de " + m_nom + " atteint l'ennemi dans un poumon.\n"
                            "=> dégâts +3 et toutes caractéristiques -1", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de >= 12 && de <= 16)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Projectile de maître !\n"
                                                 "=> dégâts +5");
                        log("Projectile de maître !\n"
                            "=> dégâts +5", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 17)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans les organes génitaux de l'ennemi, bien fait !\n"
                                                 "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)");
                        log("il tire en plein dans les organes génitaux de l'ennemi, bien fait !\n"
                            "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 18)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans un organe vital de l'ennemi, bien fait !\n"
                                                 "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)");
                        log("il tire en plein dans un organe vital de l'ennemi, bien fait !\n"
                            "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)", 1);
                        totalDegats += 6;
                        tirageDegats = true;
                    }
                    else if (de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans cœur de l'ennemi et le transperce !\n"
                                                 "=> décès !");
                        log("il tire en plein dans cœur de l'ennemi et le transperce !\n"
                            "=> décès !", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans l'œil et le cerveau de l'ennemi et les transperce !\n"
                                                 "=> décès !");
                        log("il tire en plein dans l'œil et le cerveau de l'ennemi et les transperce !\n"
                            "=> décès !", 1);
                    }
                }

                // Attaque
                if (vingt < m_carac_modif->getAdresse() || tirageDegats)
                {
                    // On demande les résultats des dés
                    int i2(1);
                    totalDegats += m_armes[i]->getDegatsEnPlus();
                    while (i2 <= m_armes[i]->getNbDes())
                    {
                        bool valid(false);

                        while (!valid)
                            totalDegats += QInputDialog::getInt(this, m_nom + " -> Attaque -> Dégâts",
                                                                "Rentrez le score indiqué par le D6 :",
                                                                1, 1, 6, 1, &valid);
                        i2++;
                    }

                    // S'il n'y a pas d'arme
                    if (m_armes[i]->getNom() == "A mains nues")
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                                 m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                                 "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                        log(m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.");
                    }
                    // Si l'arme est une arme normale
                    else
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                                 m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                                 "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                        log(m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.");
                    }
                }

                // Attaque pas
                if (vingt > m_carac_modif->getAdresse() && vingt != 19 && vingt != 20)
                {
                    QMessageBox::information(this, m_nom + " -> Attaque impossible",
                                             m_nom + " ne peut pas attaquer.");
                    log(m_nom + " essaye d'attaquer, mais se rate son attaque.");
                }

                // On dit au while que l'attaque a été faite
                attaqueFaite = true;

                return;
            }

        // Si l'arme n'est pas un projectile
            // Valeur de D20 pour savoir s'il peut attaquer
            int vingt = QInputDialog::getInt(this, m_nom + " -> Attaque -> Test au D20",
                                             "Lancez et rentrez la valeur du D20 :",
                                             1, 1, 20, 1, &ok);

            if (!ok)
                return;

            bool tirageDegats(false), tirageDegatsCritiques(false);

            // Echec critique
            if (vingt == 19 || vingt == 20)
            {
                bool valid(false);
                int de(0);

                while (!valid)
                    de = QInputDialog::getInt(this, m_nom + " -> Attaque -> Echec critique",
                                              m_nom + " a fait un échec critique en essayant d'attaquer.\n"
                                              "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                              1, 1, 20, 1, &valid);

                log(m_nom + " fait un échec critique avec '" + m_armes[i]->getNom() + "' :");

            // A mains nues
                if (m_armes[i]->getType() == Arme::MainNue)
                {
                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " rattrape son erreur in extremis, mais l'attaque échoue !");
                        log("il rattrape son erreur in extremis, mais l'attaque échoue.", 1);
                    }
                    else if (de >= 3 && de <= 10)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " tombe et s'écrase le nez par terre !\n"
                                                 "=> il pert deux assauts et reçoit 2BL.");
                        log("il tombe et s'écrase le nez par terre !\n"
                            "=> il pert deux assauts et reçoit 2BL.", 1);
                    }
                    else if (de == 11 || de == 12)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe un allié proche vers la gauche !\n"
                                                 "=> tirer les dégâts sur l'allié.");
                        log("il frappe un allié proche vers la gauche !\n"
                            "=> tirer les dégâts sur l'allié.", 1);
                        tirageDegats = true;
                    }
                    else if (de == 13 || de == 14)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe un allié proche vers la droite !\n"
                                                 "=> tirer les dégâts sur l'allié.");
                        log("il frappe un allié proche vers la droite !\n"
                            "=> tirer les dégâts sur l'allié.", 1);
                        tirageDegats = true;
                    }
                    else if (de == 15 || de == 16)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " se brise la main tout seul comme une tanche !\n"
                                                 "=> 3BL et blessure grave");
                        log("il se brise la main tout seul comme une tanche !\n"
                            "=> 3BL et blessure grave", 1);
                    }
                    else if (de >= 17 && de <= 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " se casse un bras bêtement !\n"
                                                 "=> 6BL et blessure grave.");
                        log("il se casse un bras bêtement !\n"
                            "=> 6BL et blessure grave.", 1);
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " tombe en arrière et s'assomme !\n"
                                                 "=> il pert connaissance.");
                        log("il tombe en arrière et s'assome !\n"
                            "=> il pert connaissance.", 1);
                    }
                }
            // Normalement
                else
                {
                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " rattrape son erreur in extremis, mais l'attaque échoue !");
                        log("il rattrape son erreur in extremis, mais l'attaque échoue.", 1);
                    }
                    else if (de >= 3 && de <= 5)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " trébuche et chutte maladroitement !\n"
                                                 "=> il rate 2 assauts.");
                        log("il trébuche et chutte maladroitement !\n"
                            "=> il rate 2 assauts.", 1);
                    }
                    else if (de == 6 || de == 7)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe un allié proche vers la gauche !\n"
                                                 "=> tirer les dégâts sur l'allié.");
                        log("il frappe un allié proche vers la gauche !\n"
                            "=> tirer les dégâts sur l'allié.", 1);
                        tirageDegats = true;
                    }
                    else if (de == 8 || de == 9)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " frappe un allié proche vers la droite !\n"
                                                 "=> tirer les dégâts sur l'allié.");
                        log("il frappe un allié proche vers la droite !\n"
                            "=> tirer les dégâts sur l'allié.", 1);
                        tirageDegats = true;
                    }
                    else if (de >= 10 && de <= 12)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " lache son arme comme un loser !\n"
                                                 "=> combat à main nue, change d'arme");
                        log("il lache son arme comme un loser !\n"
                            "=> combat à main nue, change d'arme", 1);
                        m_armes[i]->setNom("(cassée) " + m_armes[i]->getNom());
                    }
                    else if (de >= 13 && de <= 15)
                    {
                        bool valid2(false);
                        int rupt(0);

                        while (!valid2)
                            rupt = QInputDialog::getInt(this, m_nom + " -> Attaque -> Echec critique -> Rupture",
                                                        "Veuillez rentrer le score indiqué par un D6 pour vérifier que l'arme n'est pas cassée !",
                                                        1, 1, 6, 1, &valid2);
                        if (rupt <= m_armes[i]->getRupture())
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique -> Rupture",
                                                     m_nom + " casse son arme !");
                            log("il casse son arme !", 1);
                        }
                    }
                    else if (de >= 16 && de <= 18)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " se blesse tout seul comme un cake !\n"
                                                 "=> tirer les dégâts sur le combattant.");
                        log("il se blesse tout seul comme un cake !\n"
                            "=> tirer les dégâts sur le combattant.", 1);
                        tirageDegats = true;
                    }
                    else if (de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique",
                                                 m_nom + " se blesse très sévèrement de façon atroce et douloureuse !\n"
                                                 "=> tirer des dégâts critiques sur le combattant.");
                        log("il se blesse très sévèrement de façon atroce et douloureuse !\n"
                            "=> tirer des dégâts critiques sur le combattant.", 1);
                        tirageDegatsCritiques = true;
                    }
                    else if (de == 20)
                    {
                        bool valid2(false);
                        int de6(0);

                        while (!valid2)
                            de6 = QInputDialog::getInt(this, m_nom + " -> Attaque -> Echec critique -> Perte d'un membre",
                                                       m_nom + " va perdre un membre, veuillez lancer un D6 et rentrer le score indiqué pour savoir quel membre est perdu...",
                                                       1, 1, 6, 1, &valid2);

                        if (de6 <= 2)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique -> Perte d'un membre",
                                                     m_nom + " perd un œil !\n"
                                                     "=> blessure grave.");
                            log("il perd un œil !\n"
                                "=> blessure grave.", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Echec critique -> Perte d'un membre",
                                                     m_nom + " perd un doigt !\n"
                                                     "=> blessure grave.");
                            log("il perd un doigt !\n"
                                "=> blessure grave.", 1);
                        }
                    }
                }
            }

            // Réussite critique
            if (vingt == 1 || vingt == 2 || tirageDegatsCritiques)
            {
                bool valid(false);
                int de(0);

                while (!valid)
                    de = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                              m_nom + " a fait une réussite critique en essayant d'attaquer.\n"
                                              "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                              1, 1, 20, 1, &valid);
                log(m_nom + " fait une réussite critique avec '" + m_armes[i]->getNom() + "' :");

                if (m_armes[i]->getType() == Arme::MainNue)
                {
                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " provoque un ématome impressionnant sur l'ennemi : dégâts +1 !");
                        log("il provoque un ématome impressionnant sur l'ennemi : dégâts +1 !", 1);
                        totalDegats++;
                        tirageDegats = true;
                    }
                    else if (de == 3 || de == 4)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " provoque un ématome et une luxation d'un membre de l'ennemi : dégâts +2 !");
                        log("il provoque un ématome et une luxation d'un membre de l'ennemi : dégâts +2 !", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 5 || de == 6)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fracasse le nez de l'ennemi et provoque une hémorragie nasale : dégâts +3");
                        log("il fracasse le nez de l'ennemi et provoque une hémorragie nasale : dégâts +3", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 7 || de == 8)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fracasse une côte de l'ennemi : dégâts +4");
                        log("il fracasse une côte de l'ennemi : dégâts +4", 1);
                        totalDegats += 4;
                        tirageDegats = true;
                    }
                    else if (de == 9 || de == 10)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " frappe d'un coup précis de bourrin la tempe de l'ennemi\n"
                                                 "=> dégâts +2 et étourdissement de la cible pour 3 assauts");
                        log("il frappe d'un coup précis de bourrin la tempe de l'ennemi\n"
                            "=> dégâts +2 et étourdissement de la cible pour 3 assauts", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 11)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " frappe d'un coup précis le sternum de l'ennemi\n"
                                                 "=> étourdissement de la cible pour 4 assauts");
                        log("il frappe d'un coup précis le sternum de l'ennemi\n"
                            "=> étourdissement de la cible pour 4 assauts", 1);
                    }
                    else if (de == 12)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " luxe le genou de l'ennemi !\n"
                                                 "=> dégâts +3 et blessure grave !");
                        log("il luxe le genou de l'ennemi !\n"
                            "=> dégâts +3 et blessure grave !", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 13)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quelle main est cassée...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " casse la main droite de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il casse la main droite de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " casse la main gauche de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il casse la main gauche de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 14)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " brise la mâchoire de l'ennemi !\n"
                                                 "=> dégâts +3 et incapacité à parler !");
                        log("il brise la mâchoire de l'ennemi !\n"
                            "=> dégâts +3 et incapacité à parler !", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 15)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quel bras est cassé...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " casse le bras droit de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il casse le bras droit de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " casse le bras gauche de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il casse le bras gauche de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 16 || de == 17)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " écrase les organes génitaux de l'ennemi !\n"
                                                 "=> dégâts +5 et blessure grave !");
                        log("il écrase les organes génitaux de l'ennemi !\n"
                            "=> dégâts +5 et blessure grave !", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 18 || de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " assomme l'ennemi !\n"
                                                 "=> inconscient !");
                        log("il assomme l'ennemi !\n"
                            "=> inconscient !", 1);
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " enfonce le nez de l'ennemi dans son cerveau !\n"
                                                 "=> décès !");
                        log("il enfonce le nez de l'ennemi dans son cerveau !\n"
                            "=> décès !", 1);
                    }
                }
                else if (m_armes[i]->getType() == Arme::Tranchante)
                {
                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une incision profonde à l'ennemi : dégâts +1 !");
                        log("il fait une incision profonde à l'ennemi : dégâts +1 !", 1);
                        totalDegats++;
                        tirageDegats = true;
                    }
                    else if (de == 3 || de == 4)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une incision vraiment profonde à l'ennemi : dégâts +2 !");
                        log("il fait une incision vraiment profonde à l'ennemi : dégâts +2 !", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 5 || de == 6)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une plaie impressionnante et des dommages à l'armure !\n"
                                                 "=> dégâts +3 et pièce d'armure PR -1");
                        log("il fait une plaie impressionnante et des dommages à l'armure !\n"
                            "=> dégâts +3 et pièce d'armure PR -1", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 7 || de == 8)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une plaie impressionnante et des dommages à l'armure !\n"
                                                 "=> dégâts +4 et pièce d'armure PR -2");
                        log("il fait une plaie impressionnante et des dommages à l'armure !\n"
                            "=> dégâts +4 et pièce d'armure PR -2", 1);
                        totalDegats += 4;
                        tirageDegats = true;
                    }
                    else if (de == 9 || de == 10)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une plaie impressionnante et des dommages à l'armure !\n"
                                                 "=> dégâts +5 et pièce d'armure PR -3");
                        log("il fait une plaie impressionnante et des dommages à l'armure !\n"
                            "=> dégâts +5 et pièce d'armure PR -3", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 11)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " détruit une partie de l'amure de l'ennemi\n"
                                                 "=> pièce de l'armure concernée : PR = 0");
                        log("il détruit une partie de l'amure de l'ennemi\n"
                            "=> pièce de l'armure concernée : PR = 0", 1);
                    }
                    else if (de == 12)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " crève un œil de l'ennemi !\n"
                                                 "=> dégâts +5 et blessure grave !");
                        log("il crève un œil de l'ennemi !\n"
                            "=> dégâts +5 et blessure grave !", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 13)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quelle main est tranchée...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la main droite de l'ennemi !\n"
                                                     "=> dégâts +6 et blessure grave !");
                            log("il tranche la main droite de l'ennemi !\n"
                                "=> dégâts +6 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la main gauche de l'ennemi !\n"
                                                     "=> dégâts +6 et blessure grave !");
                            log("il tranche la main gauche de l'ennemi !\n"
                                "=> dégâts +6 et blessure grave !", 1);
                        }
                        totalDegats += 6;
                        tirageDegats = true;
                    }
                    else if (de == 14)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quel pied est tranché...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche le pied droit de l'ennemi !\n"
                                                     "=> dégâts +6 et blessure grave !");
                            log("il tranche le pied droit de l'ennemi !\n"
                                "=> dégâts +6 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche le pied gauche de l'ennemi !\n"
                                                     "=> dégâts +6 et blessure grave !");
                            log("il tranche le pied gauche de l'ennemi !\n"
                                "=> dégâts +6 et blessure grave !", 1);
                        }
                        totalDegats += 6;
                        tirageDegats = true;
                    }
                    else if (de == 15)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quel bras est tranché...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche le bras droit de l'ennemi !\n"
                                                     "=> dégâts +7 et blessure grave !");
                            log("il tranche le bras droit de l'ennemi !\n"
                                "=> dégâts +7 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la main gauche de l'ennemi !\n"
                                                     "=> dégâts +7 et blessure grave !");
                            log("il tranche la main gauche de l'ennemi !\n"
                                "=> dégâts +7 et blessure grave !", 1);
                        }
                        totalDegats += 7;
                        tirageDegats = true;
                    }
                    else if (de == 16)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quelle jambe est tranchée...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la jambe droite de l'ennemi !\n"
                                                     "=> dégâts +8 et blessure grave !");
                            log("il tranche la jambe droite de l'ennemi !\n"
                                "=> dégâts +8 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la jambe gauche de l'ennemi !\n"
                                                     "=> dégâts +8 et blessure grave !");
                            log("il tranche la jambe gauche de l'ennemi !\n"
                                "=> dégâts +8 et blessure grave !", 1);
                        }
                        totalDegats += 8;
                        tirageDegats = true;
                    }
                    else if (de == 17)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " endommage un organe génital de l'ennemi !\n"
                                                 "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !");
                        log("il endommage un organe génital de l'ennemi !\n"
                            "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 18)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " endommage un organe vital de l'ennemi !\n"
                                                 "=> dégâts +9 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !");
                        log("il endommage un organe vital de l'ennemi !\n"
                            "=> dégâts +9 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !", 1);
                        totalDegats += 9;
                        tirageDegats = true;
                    }
                    else if (de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une blessure au cœur de l'ennemi !\n"
                                                 "=> décès !");
                        log("il fait une blessure au cœur de l'ennemi !\n"
                            "=> décès !", 1);
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait une blessure grave à la tête de l'ennemi !\n"
                                                 "=> décès !");
                        log("il fait une blessure grave à la tête de l'ennemi !\n"
                            "=> décès !", 1);
                    }
                }
                else if (m_armes[i]->getType() == Arme::Contandante)
                {
                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait un ématome impressionnant à l'ennemi : dégâts +1 !");
                        log("il fait un ématome impressionnant à l'ennemi : dégâts +1 !", 1);
                        totalDegats++;
                        tirageDegats = true;
                    }
                    else if (de == 3 || de == 4)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait un ématome impressionnant à l'ennemi et lui luxe un membre : dégâts +2 !");
                        log("il fait un ématome impressionnant à l'ennemi et lui luxe un membre : dégâts +2 !", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 5 || de == 6)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fracture une côte de l'ennemi : dégâts +3 !");
                        log("il fracture une côte de l'ennemi : dégâts +3 !", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 7 || de == 8)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait un coup précis et des dommages à l'armure !\n"
                                                 "=> dégâts +4 et pièce d'armure PR -1");
                        log("il fait un coup précis et des dommages à l'armure !\n"
                            "=> dégâts +4 et pièce d'armure PR -1", 1);
                        totalDegats += 4;
                        tirageDegats = true;
                    }
                    else if (de == 9 || de == 10)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fait un coup précis de bourrin et des dommages à l'armure !\n"
                                                 "=> dégâts +5 et pièce d'armure PR -2");
                        log("il fait un coup précis de bourrin et des dommages à l'armure !\n"
                            "=> dégâts +5 et pièce d'armure PR -2", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 11)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " détruit une partie de l'amure de l'ennemi\n"
                                                 "=> pièce de l'armure concernée : PR = 0");
                        log("il détruit une partie de l'amure de l'ennemi\n"
                            "=> pièce de l'armure concernée : PR = 0", 1);
                    }
                    else if (de == 12)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " luxe un genou de l'ennemi !\n"
                                                 "=> dégâts +3 et blessure grave !");
                        log("il luxe un genou de l'ennemi !\n"
                            "=> dégâts +3 et blessure grave !", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 13)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quelle main est tranchée...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la main droite de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il tranche la main droite de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la main gauche de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il tranche la main gauche de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 14)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quel pied est tranché...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche le pied droit de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il tranche le pied droit de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche le pied gauche de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il tranche le pied gauche de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                        }
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 15)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quel bras est tranché...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche le bras droit de l'ennemi !\n"
                                                     "=> dégâts +4 et blessure grave !");
                            log("il tranche le bras droit de l'ennemi !\n"
                                "=> dégâts +4 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la main gauche de l'ennemi !\n"
                                                     "=> dégâts +4 et blessure grave !");
                            log("il tranche la main gauche de l'ennemi !\n"
                                "=> dégâts +4 et blessure grave !", 1);
                        }
                        totalDegats += 4;
                        tirageDegats = true;
                    }
                    else if (de == 16)
                    {
                        int cote(0);
                        bool valid(false);

                        while (!valid)
                            cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                        "Veuillez rentrer le score indiqué par un D6 pour savoir quelle jambe est tranchée...",
                                                        1, 1, 6, 1, &valid);
                        if (cote <= 3)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la jambe droite de l'ennemi !\n"
                                                     "=> dégâts +5 et blessure grave !");
                            log("il tranche la jambe droite de l'ennemi !\n"
                                "=> dégâts +5 et blessure grave !", 1);
                        }
                        else
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " tranche la jambe gauche de l'ennemi !\n"
                                                     "=> dégâts +5 et blessure grave !");
                            log("il tranche la jambe gauche de l'ennemi !\n"
                                "=> dégâts +5 et blessure grave !", 1);
                        }
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 17)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " endommage un organe génital de l'ennemi !\n"
                                                 "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !");
                        log("il endommage un organe génital de l'ennemi !\n"
                            "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 18)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " assomme l'ennemi !\n"
                                                 "=> inconscient !");
                        log("il assomme l'ennemi !\n"
                            "=> inconscient !", 1);
                    }
                    else if (de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " fracture le crâne de l'ennemi !\n"
                                                 "=> décès !");
                        log("il fracture le crâne de l'ennemi !\n"
                            "=> décès !", 1);
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " écrase violemment un organe vital de l'ennemi !\n"
                                                 "=> décès !");
                        log("il écrase violemment un organe vital de l'ennemi !\n"
                            "=> décès !", 1);
                    }
                }
            }

            // Attaque
            if ((vingt < m_carac_modif->getAttaque() && vingt != 1 && vingt != 2)
                    || tirageDegats)
            {
                // On demande les résultats des dés
                int i2(1);
                totalDegats += m_armes[i]->getDegatsEnPlus();
                while (i2 <= m_armes[i]->getNbDes())
                {
                    bool valid(false);

                    while (!valid)
                        totalDegats += QInputDialog::getInt(this, m_nom + " -> Attaque -> Dégâts",
                                                            "Rentrez le score indiqué par le D6 :", 1, 1, 6, 1, &valid);
                    i2++;
                }

                // S'il n'y a pas d'arme
                if (m_armes[i]->getNom() == "A mains nues")
                {
                    QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                             m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                             "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                    log(m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.");
                }
                // Si l'arme est une arme normale
                else
                {
                    QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                             m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                             "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                    log(m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.");
                }
            }

            // Attaque pas
            if (vingt > m_carac_modif->getAttaque() && vingt != 19 && vingt != 20)
            {
                QMessageBox::information(this, m_nom + " -> Attaque impossible",
                                         m_nom + " ne peut pas attaquer.");
                log(m_nom + " essaye d'attaquer, mais se rate son attaque.");
            }

            // On dit au while que l'attaque a été faite
            attaqueFaite = true;
        }

        // On dit au while que l'attaque a été faite
        if (i >= MAX_ARME)
            attaqueFaite = true;

        // On incrémente i pour passer à l'arme suivante
        i++;
    }
}
void Personnage::parer()
{
// On demande avec quelle arme parer
    // On parcourt les armes pour prendre le nom
    QStringList nomArmes;
    for (int i(0); i < MAX_ARME; i++)
        nomArmes << m_armes[i]->getNom() + " (AT: " + QString::number(m_AT_modif[i]) + " ; PRD: " + QString::number(m_PRD_modif[i]) + ")";
    bool ok(false);

    // On pose la question
    QString nom_arme = QInputDialog::getItem(this, m_nom + " -> Parade",
                                             "Avec quelle arme " + m_nom + " veut-il parer ?",
                                             nomArmes, 0, false, &ok);

// Si on annule, on arrête tout
    if (!ok)
        return;

// On parcourt pour savoir avec quelle arme parer
    int i(0);
    bool paradeFaite(false);
    while (!paradeFaite)
    {
        // On teste si c'est l'arme choisi est celle correspondant à i
        if (nom_arme == m_armes[i]->getNom() + " (AT: " + QString::number(m_AT_modif[i]) + " ; PRD: " + QString::number(m_PRD_modif[i]) + ")")
        {
            // Valeur de D20 pour savoir s'il peut parer
            int vingt = QInputDialog::getInt(this, m_nom + " -> Parade -> Test au D20",
                                             "Lancez et rentrez la valeur du D20 :",
                                             1, 1, 20, 1, &ok);

            if (!ok)
                return;

            bool tirerDegats(false), tirerDegatsCritiques(false);

            // Echec critique
            if (vingt == 19 || vingt == 20)
            {
                bool valid(false);
                int de(0);

                while (!valid)
                    de = QInputDialog::getInt(this, m_nom + " -> Parade -> Echec critique",
                                              m_nom + " a fait un échec critique en essayant de parer.\n"
                                              "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                              1, 1, 20, 1, &valid);

                log(m_nom + " fait un échec critique de parade avec '" + m_armes[i]->getNom() + "' :");

                if (de == 1 || de == 2)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " rattrape son erreur in extremis, mais la parade échoue !");
                    log("il rattrape son erreur in extremis, mais l'attaque échoue.", 1);
                }
                else if (de >= 3 && de <= 5)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " trébuche et chutte maladroitement !\n"
                                             "=> il rate 2 assauts.");
                    log("il trébuche et chutte maladroitement !\n"
                        "=> il rate 2 assauts.", 1);
                }
                else if (de == 6 || de == 7)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " frappe un allié proche vers la gauche !\n"
                                             "=> tirer les dégâts sur l'allié.");
                    log("il frappe un allié proche vers la gauche !\n"
                        "=> tirer les dégâts sur l'allié.", 1);
                    tirerDegats = true;
                }
                else if (de == 8 || de == 9)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " frappe un allié proche vers la droite !\n"
                                             "=> tirer les dégâts sur l'allié.");
                    log("il frappe un allié proche vers la droite !\n"
                        "=> tirer les dégâts sur l'allié.", 1);
                    tirerDegats = true;
                }
                else if (de >= 10 && de <= 12)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " lache son arme comme un loser !\n"
                                             "=> combat à main nue, change d'arme");
                    log("il lache son arme comme un loser !\n"
                        "=> combat à main nue, change d'arme", 1);
                    m_armes[i]->setNom("(cassée) " + m_armes[i]->getNom());
                }
                else if (de >= 13 && de <= 15)
                {
                    bool valid2(false);
                    int rupt(0);

                    while (!valid2)
                        rupt = QInputDialog::getInt(this, m_nom + " -> Parade -> Echec critique -> Rupture",
                                                    "Veuillez rentrer le score indiqué par un D6 pour vérifier que l'arme n'est pas cassée !",
                                                    1, 1, 6, 1, &valid2);
                    if (rupt <= m_armes[i]->getRupture())
                    {
                        QMessageBox::information(this, m_nom + " -> Parade -> Echec critique -> Rupture",
                                                 m_nom + " casse son arme !");
                        log("il casse son arme !", 1);
                    }
                }
                else if (de >= 16 && de <= 18)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " se blesse tout seul comme un cake !\n"
                                             "=> tirer les dégâts sur le combattant.");
                    log("il se blesse tout seul comme un cake !\n"
                        "=> tirer les dégâts sur le combattant.", 1);
                    tirerDegats = true;
                }
                else if (de == 19)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Echec critique",
                                             m_nom + " se blesse très sévèrement de façon atroce et douloureuse !\n"
                                             "=> tirer des dégâts critiques sur le combattant.");
                    log("il se blesse très sévèrement de façon atroce et douloureuse !\n"
                        "=> tirer des dégâts critiques sur le combattant.", 1);
                    tirerDegatsCritiques = true;
                }
                else if (de == 20)
                {
                    bool valid2(false);
                    int de6(0);

                    while (!valid2)
                        de6 = QInputDialog::getInt(this, m_nom + " -> Parade -> Echec critique -> Perte d'un membre",
                                                   m_nom + " va perdre un membre, veuillez lancer un D6 et rentrer le score indiqué pour savoir quel membre est perdu...",
                                                   1, 1, 6, 1, &valid2);

                    if (de6 <= 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Parade -> Echec critique -> Perte d'un membre",
                                                 m_nom + " perd un œil !\n"
                                                 "=> blessure grave.");
                        log("il perd un œil !\n"
                            "=> blessure grave.", 1);
                    }
                    else
                    {
                        QMessageBox::information(this, m_nom + " -> Parade -> Echec critique -> Perte d'un membre",
                                                 m_nom + " perd un doigt !\n"
                                                 "=> blessure grave.");
                        log("il perd un doigt !\n"
                            "=> blessure grave.", 1);
                    }
                }
            }

            // Réussite critique
            if (vingt == 1 || vingt == 2)
            {
                bool valid(false);
                int de(0);

                while (!valid)
                    de = QInputDialog::getInt(this, m_nom + " -> Parade -> Réussite critique",
                                              m_nom + " a fait une réussite critique en essayant de parer.\n"
                                              "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                              1, 1, 20, 1, &valid);
                log(m_nom + " fait une réussite critique de parade avec '" + m_armes[i]->getNom() + "' :");

                if (de == 1 || de == 2)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " fait une parade normale en fait !");
                    log("il fait une parade normale en fait !", 1);
                }
                else if (de == 3 || de == 4 || de == 5)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " repousse l'ennemi !\n"
                                             "=> l'ennemi rate 1 assaut");
                    log("il repousse l'ennemi !\n"
                        "=> l'ennemi rate 1 assaut", 1);
                }
                else if (de == 6 || de == 7)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " fait trébucher l'ennemi\n"
                                             "=> l'ennemi subit 1 attaque imparable");
                    log("il fait trébucher l'ennemi\n"
                        "=> l'ennemi subit 1 attaque imparable", 1);
                }
                else if (de == 8 || de == 9)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " fait tomber l'ennemi\n"
                                             "=> l'ennemi subit 2 attaques imparables");
                    log("il fait tomber l'ennemi\n"
                        "=> l'ennemi subit 2 attaques imparables", 1);
                }
                else if (de == 10 || de == 11 || de == 12)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " fait lâcher l'arme de l'ennemi à 1D6 mètres\n"
                                             "=> l'ennemi combat à mains nues");
                    log("il fait lâcher l'arme de l'ennemi à 1D6 mètres\n"
                        "=> l'ennemi combat à mains nues", 1);
                }
                else if (de == 13 || de == 14 || de == 15)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " casse l'arme de l'ennemi !\n"
                                             "=> l'ennemi combat à mains nues");
                    log("il casse l'arme de l'ennemi !\n"
                        "=> l'ennemi combat à mains nues", 1);
                }
                else if (de == 16 || de == 17 || de == 18)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " donne un coup de son arme à l'ennemi !\n"
                                             "=> l'ennemi subit des dégâts");
                    log("il donne un coup de son arme à l'ennemi !\n"
                        "=> l'ennemi subit des dégâts", 1);
                    tirerDegats = true;
                }
                else if (de == 19)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             m_nom + " donne un coup critique de son arme à l'ennemi !\n"
                                             "=> l'ennemi subit des dégâts");
                    log("il donne un coup critique de son arme à l'ennemi !\n"
                        "=> l'ennemi subit des dégâts", 1);
                    tirerDegats = true;
                }
                else if (de == 20)
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Réussite critique",
                                             "L'ennemi, ce loser, subit un coup critique de sa propre arme !");
                    log("L'ennemi, ce loser, subit un coup critique de sa propre arme !", 1);
                    tirerDegats = true;
                }
            }

            // Parade
            if (vingt < m_carac_modif->getParade() && vingt != 1 && vingt != 2)
            {
                // S'il n'y a pas d'arme
                if (m_armes[i]->getNom() == "A mains nues")
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Récapitulatif",
                                             m_nom + " pare à mains nues !");
                    log(m_nom + " pare à mains nues !");
                }
                // Si l'arme est une arme normale
                else
                {
                    QMessageBox::information(this, m_nom + " -> Parade -> Récapitulatif",
                                             m_nom + " pare avec '" + m_armes[i]->getNom() + "' !");
                    log(m_nom + " pare avec '" + m_armes[i]->getNom() + "' !");
                }
            }

            // Ne pare pas
            if (vingt > m_carac_modif->getAttaque() && vingt != 19 && vingt != 20)
            {
                QMessageBox::information(this, m_nom + " -> Parade impossible",
                                         m_nom + " ne peut pas parer.");
                log(m_nom + " essaye de parer, mais se rate sa parade.");
            }

            // On dit au while que la parade a été faite
            paradeFaite = true;




            // Si il faut tirer des dégâts
            if (tirerDegats)
            {
                // On demande les résultats des dés
                int i2(1);
                int totalDegats = m_armes[i]->getDegatsEnPlus();
                while (i2 <= m_armes[i]->getNbDes())
                {
                    bool valid(false);

                    while (!valid)
                        totalDegats += QInputDialog::getInt(this, m_nom + " -> Attaque -> Dégâts",
                                                            "Rentrez le score indiqué par le D6 :", 1, 1, 6, 1, &valid);
                    i2++;
                }

                // S'il n'y a pas d'arme
                if (m_armes[i]->getNom() == "A mains nues")
                {
                    QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                             m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                             "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                    log(m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.");
                }
                // Si l'arme est une arme normale
                else
                {
                    QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                             m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                             "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                    log(m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.");
                }
            }
            if (tirerDegatsCritiques)
            {
                bool tirageDegats(false);
                int totalDegats(0);

                if (m_armes[i]->getType() == Arme::Projectile)
                {
                    bool valid(false);
                    int de(0);

                    while (!valid)
                        de = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                  m_nom + " a fait une réussite critique en essayant d'attaquer.\n"
                                                  "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                                  1, 1, 20, 1, &valid);

                    log(m_nom + " fait une réussite critique avec '" + m_armes[i]->getNom() + "' :");

                    if (de == 1 || de == 2)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " lance bien son projectile : dégâts +1 !");
                        log("il lance bien son projectile : dégâts +1 !", 1);
                        totalDegats++;
                        tirageDegats = true;
                    }
                    else if (de == 3 || de == 4)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " lance magistralement bien son projectile : dégâts +2 !");
                        log("il lance magistralement bien son projectile : dégâts +2 !", 1);
                        totalDegats += 2;
                        tirageDegats = true;
                    }
                    else if (de == 5 || de == 6)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Le projectile de " + m_nom + " atteint l'ennemi dans une articulation du bras.\n"
                                                 "=> dégâts +3 et AT/PRD-2");
                        log("Le projectile de " + m_nom + " atteint l'ennemi dans une articulation du bras.\n"
                            "=> dégâts +3 et AT/PRD-2", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de == 7 || de == 8)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Le projectile de " + m_nom + " atteint l'ennemi dans une articulation de la jambe.\n"
                                                 "=> dégâts +3 et MV-50%");
                        log("Le projectile de " + m_nom + " atteint l'ennemi dans une articulation de la jambe.\n"
                            "=> dégâts +3 et MV-50%", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de >= 9 && de <= 11)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Le projectile de " + m_nom + " atteint l'ennemi dans un poumon.\n"
                                                 "=> dégâts +3 et toutes caractéristiques -1");
                        log("Le projectile de " + m_nom + " atteint l'ennemi dans un poumon.\n"
                            "=> dégâts +3 et toutes caractéristiques -1", 1);
                        totalDegats += 3;
                        tirageDegats = true;
                    }
                    else if (de >= 12 && de <= 16)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 "Projectile de maître !\n"
                                                 "=> dégâts +5");
                        log("Projectile de maître !\n"
                            "=> dégâts +5", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 17)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans les organes génitaux de l'ennemi, bien fait !\n"
                                                 "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)");
                        log("il tire en plein dans les organes génitaux de l'ennemi, bien fait !\n"
                            "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 18)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans un organe vital de l'ennemi, bien fait !\n"
                                                 "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)");
                        log("il tire en plein dans un organe vital de l'ennemi, bien fait !\n"
                            "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne)", 1);
                        totalDegats += 6;
                        tirageDegats = true;
                    }
                    else if (de == 19)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans cœur de l'ennemi et le transperce !\n"
                                                 "=> décès !");
                        log("il tire en plein dans cœur de l'ennemi et le transperce !\n"
                            "=> décès !", 1);
                        totalDegats += 5;
                        tirageDegats = true;
                    }
                    else if (de == 20)
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                 m_nom + " tire en plein dans l'œil et le cerveau de l'ennemi et les transperce !\n"
                                                 "=> décès !");
                        log("il tire en plein dans l'œil et le cerveau de l'ennemi et les transperce !\n"
                            "=> décès !", 1);
                    }
                }
                else
                {
                    bool valid(false);
                    int de(0);

                    while (!valid)
                        de = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                  m_nom + " a fait une réussite critique en essayant d'attaquer.\n"
                                                  "Veuillez lancer une deuxième fois le dé 20 et rentrer le score indiqué.",
                                                  1, 1, 20, 1, &valid);
                    log(m_nom + " fait une réussite critique avec '" + m_armes[i]->getNom() + "' :");

                    if (m_armes[i]->getType() == Arme::MainNue)
                    {
                        if (de == 1 || de == 2)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " provoque un ématome impressionnant sur l'ennemi : dégâts +1 !");
                            log("il provoque un ématome impressionnant sur l'ennemi : dégâts +1 !", 1);
                            totalDegats++;
                            tirageDegats = true;
                        }
                        else if (de == 3 || de == 4)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " provoque un ématome et une luxation d'un membre de l'ennemi : dégâts +2 !");
                            log("il provoque un ématome et une luxation d'un membre de l'ennemi : dégâts +2 !", 1);
                            totalDegats += 2;
                            tirageDegats = true;
                        }
                        else if (de == 5 || de == 6)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fracasse le nez de l'ennemi et provoque une hémorragie nasale : dégâts +3");
                            log("il fracasse le nez de l'ennemi et provoque une hémorragie nasale : dégâts +3", 1);
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 7 || de == 8)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fracasse une côte de l'ennemi : dégâts +4");
                            log("il fracasse une côte de l'ennemi : dégâts +4", 1);
                            totalDegats += 4;
                            tirageDegats = true;
                        }
                        else if (de == 9 || de == 10)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " frappe d'un coup précis de bourrin la tempe de l'ennemi\n"
                                                     "=> dégâts +2 et étourdissement de la cible pour 3 assauts");
                            log("il frappe d'un coup précis de bourrin la tempe de l'ennemi\n"
                                "=> dégâts +2 et étourdissement de la cible pour 3 assauts", 1);
                            totalDegats += 2;
                            tirageDegats = true;
                        }
                        else if (de == 11)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " frappe d'un coup précis le sternum de l'ennemi\n"
                                                     "=> étourdissement de la cible pour 4 assauts");
                            log("il frappe d'un coup précis le sternum de l'ennemi\n"
                                "=> étourdissement de la cible pour 4 assauts", 1);
                        }
                        else if (de == 12)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " luxe le genou de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il luxe le genou de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 13)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quelle main est cassée...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " casse la main droite de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il casse la main droite de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " casse la main gauche de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il casse la main gauche de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 14)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " brise la mâchoire de l'ennemi !\n"
                                                     "=> dégâts +3 et incapacité à parler !");
                            log("il brise la mâchoire de l'ennemi !\n"
                                "=> dégâts +3 et incapacité à parler !", 1);
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 15)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quel bras est cassé...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " casse le bras droit de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il casse le bras droit de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " casse le bras gauche de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il casse le bras gauche de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 16 || de == 17)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " écrase les organes génitaux de l'ennemi !\n"
                                                     "=> dégâts +5 et blessure grave !");
                            log("il écrase les organes génitaux de l'ennemi !\n"
                                "=> dégâts +5 et blessure grave !", 1);
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 18 || de == 19)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " assomme l'ennemi !\n"
                                                     "=> inconscient !");
                            log("il assomme l'ennemi !\n"
                                "=> inconscient !", 1);
                        }
                        else if (de == 20)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " enfonce le nez de l'ennemi dans son cerveau !\n"
                                                     "=> décès !");
                            log("il enfonce le nez de l'ennemi dans son cerveau !\n"
                                "=> décès !", 1);
                        }
                    }
                    else if (m_armes[i]->getType() == Arme::Tranchante)
                    {
                        if (de == 1 || de == 2)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une incision profonde à l'ennemi : dégâts +1 !");
                            log("il fait une incision profonde à l'ennemi : dégâts +1 !", 1);
                            totalDegats++;
                            tirageDegats = true;
                        }
                        else if (de == 3 || de == 4)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une incision vraiment profonde à l'ennemi : dégâts +2 !");
                            log("il fait une incision vraiment profonde à l'ennemi : dégâts +2 !", 1);
                            totalDegats += 2;
                            tirageDegats = true;
                        }
                        else if (de == 5 || de == 6)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une plaie impressionnante et des dommages à l'armure !\n"
                                                     "=> dégâts +3 et pièce d'armure PR -1");
                            log("il fait une plaie impressionnante et des dommages à l'armure !\n"
                                "=> dégâts +3 et pièce d'armure PR -1", 1);
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 7 || de == 8)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une plaie impressionnante et des dommages à l'armure !\n"
                                                     "=> dégâts +4 et pièce d'armure PR -2");
                            log("il fait une plaie impressionnante et des dommages à l'armure !\n"
                                "=> dégâts +4 et pièce d'armure PR -2", 1);
                            totalDegats += 4;
                            tirageDegats = true;
                        }
                        else if (de == 9 || de == 10)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une plaie impressionnante et des dommages à l'armure !\n"
                                                     "=> dégâts +5 et pièce d'armure PR -3");
                            log("il fait une plaie impressionnante et des dommages à l'armure !\n"
                                "=> dégâts +5 et pièce d'armure PR -3", 1);
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 11)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " détruit une partie de l'amure de l'ennemi\n"
                                                     "=> pièce de l'armure concernée : PR = 0");
                            log("il détruit une partie de l'amure de l'ennemi\n"
                                "=> pièce de l'armure concernée : PR = 0", 1);
                        }
                        else if (de == 12)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " crève un œil de l'ennemi !\n"
                                                     "=> dégâts +5 et blessure grave !");
                            log("il crève un œil de l'ennemi !\n"
                                "=> dégâts +5 et blessure grave !", 1);
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 13)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quelle main est tranchée...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la main droite de l'ennemi !\n"
                                                         "=> dégâts +6 et blessure grave !");
                                log("il tranche la main droite de l'ennemi !\n"
                                    "=> dégâts +6 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la main gauche de l'ennemi !\n"
                                                         "=> dégâts +6 et blessure grave !");
                                log("il tranche la main gauche de l'ennemi !\n"
                                    "=> dégâts +6 et blessure grave !", 1);
                            }
                            totalDegats += 6;
                            tirageDegats = true;
                        }
                        else if (de == 14)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quel pied est tranché...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche le pied droit de l'ennemi !\n"
                                                         "=> dégâts +6 et blessure grave !");
                                log("il tranche le pied droit de l'ennemi !\n"
                                    "=> dégâts +6 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche le pied gauche de l'ennemi !\n"
                                                         "=> dégâts +6 et blessure grave !");
                                log("il tranche le pied gauche de l'ennemi !\n"
                                    "=> dégâts +6 et blessure grave !", 1);
                            }
                            totalDegats += 6;
                            tirageDegats = true;
                        }
                        else if (de == 15)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quel bras est tranché...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche le bras droit de l'ennemi !\n"
                                                         "=> dégâts +7 et blessure grave !");
                                log("il tranche le bras droit de l'ennemi !\n"
                                    "=> dégâts +7 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la main gauche de l'ennemi !\n"
                                                         "=> dégâts +7 et blessure grave !");
                                log("il tranche la main gauche de l'ennemi !\n"
                                    "=> dégâts +7 et blessure grave !", 1);
                            }
                            totalDegats += 7;
                            tirageDegats = true;
                        }
                        else if (de == 16)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quelle jambe est tranchée...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la jambe droite de l'ennemi !\n"
                                                         "=> dégâts +8 et blessure grave !");
                                log("il tranche la jambe droite de l'ennemi !\n"
                                    "=> dégâts +8 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la jambe gauche de l'ennemi !\n"
                                                         "=> dégâts +8 et blessure grave !");
                                log("il tranche la jambe gauche de l'ennemi !\n"
                                    "=> dégâts +8 et blessure grave !", 1);
                            }
                            totalDegats += 8;
                            tirageDegats = true;
                        }
                        else if (de == 17)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " endommage un organe génital de l'ennemi !\n"
                                                     "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !");
                            log("il endommage un organe génital de l'ennemi !\n"
                                "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !", 1);
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 18)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " endommage un organe vital de l'ennemi !\n"
                                                     "=> dégâts +9 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !");
                            log("il endommage un organe vital de l'ennemi !\n"
                                "=> dégâts +9 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !", 1);
                            totalDegats += 9;
                            tirageDegats = true;
                        }
                        else if (de == 19)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une blessure au cœur de l'ennemi !\n"
                                                     "=> décès !");
                            log("il fait une blessure au cœur de l'ennemi !\n"
                                "=> décès !", 1);
                        }
                        else if (de == 20)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait une blessure grave à la tête de l'ennemi !\n"
                                                     "=> décès !");
                            log("il fait une blessure grave à la tête de l'ennemi !\n"
                                "=> décès !", 1);
                        }
                    }
                    else if (m_armes[i]->getType() == Arme::Contandante)
                    {
                        if (de == 1 || de == 2)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait un ématome impressionnant à l'ennemi : dégâts +1 !");
                            log("il fait un ématome impressionnant à l'ennemi : dégâts +1 !", 1);
                            totalDegats++;
                            tirageDegats = true;
                        }
                        else if (de == 3 || de == 4)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait un ématome impressionnant à l'ennemi et lui luxe un membre : dégâts +2 !");
                            log("il fait un ématome impressionnant à l'ennemi et lui luxe un membre : dégâts +2 !", 1);
                            totalDegats += 2;
                            tirageDegats = true;
                        }
                        else if (de == 5 || de == 6)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fracture une côte de l'ennemi : dégâts +3 !");
                            log("il fracture une côte de l'ennemi : dégâts +3 !", 1);
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 7 || de == 8)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait un coup précis et des dommages à l'armure !\n"
                                                     "=> dégâts +4 et pièce d'armure PR -1");
                            log("il fait un coup précis et des dommages à l'armure !\n"
                                "=> dégâts +4 et pièce d'armure PR -1", 1);
                            totalDegats += 4;
                            tirageDegats = true;
                        }
                        else if (de == 9 || de == 10)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fait un coup précis de bourrin et des dommages à l'armure !\n"
                                                     "=> dégâts +5 et pièce d'armure PR -2");
                            log("il fait un coup précis de bourrin et des dommages à l'armure !\n"
                                "=> dégâts +5 et pièce d'armure PR -2", 1);
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 11)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " détruit une partie de l'amure de l'ennemi\n"
                                                     "=> pièce de l'armure concernée : PR = 0");
                            log("il détruit une partie de l'amure de l'ennemi\n"
                                "=> pièce de l'armure concernée : PR = 0", 1);
                        }
                        else if (de == 12)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " luxe un genou de l'ennemi !\n"
                                                     "=> dégâts +3 et blessure grave !");
                            log("il luxe un genou de l'ennemi !\n"
                                "=> dégâts +3 et blessure grave !", 1);
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 13)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quelle main est tranchée...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la main droite de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il tranche la main droite de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la main gauche de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il tranche la main gauche de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 14)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quel pied est tranché...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche le pied droit de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il tranche le pied droit de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche le pied gauche de l'ennemi !\n"
                                                         "=> dégâts +3 et blessure grave !");
                                log("il tranche le pied gauche de l'ennemi !\n"
                                    "=> dégâts +3 et blessure grave !", 1);
                            }
                            totalDegats += 3;
                            tirageDegats = true;
                        }
                        else if (de == 15)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quel bras est tranché...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche le bras droit de l'ennemi !\n"
                                                         "=> dégâts +4 et blessure grave !");
                                log("il tranche le bras droit de l'ennemi !\n"
                                    "=> dégâts +4 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la main gauche de l'ennemi !\n"
                                                         "=> dégâts +4 et blessure grave !");
                                log("il tranche la main gauche de l'ennemi !\n"
                                    "=> dégâts +4 et blessure grave !", 1);
                            }
                            totalDegats += 4;
                            tirageDegats = true;
                        }
                        else if (de == 16)
                        {
                            int cote(0);
                            bool valid(false);

                            while (!valid)
                                cote = QInputDialog::getInt(this, m_nom + " -> Attaque -> Réussite critique",
                                                            "Veuillez rentrer le score indiqué par un D6 pour savoir quelle jambe est tranchée...",
                                                            1, 1, 6, 1, &valid);
                            if (cote <= 3)
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la jambe droite de l'ennemi !\n"
                                                         "=> dégâts +5 et blessure grave !");
                                log("il tranche la jambe droite de l'ennemi !\n"
                                    "=> dégâts +5 et blessure grave !", 1);
                            }
                            else
                            {
                                QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                         m_nom + " tranche la jambe gauche de l'ennemi !\n"
                                                         "=> dégâts +5 et blessure grave !");
                                log("il tranche la jambe gauche de l'ennemi !\n"
                                    "=> dégâts +5 et blessure grave !", 1);
                            }
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 17)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " endommage un organe génital de l'ennemi !\n"
                                                     "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !");
                            log("il endommage un organe génital de l'ennemi !\n"
                                "=> dégâts +5 et hémorragie (la victime perd 1D6 de PV chaque minute jusqu'à ce qu'on la soigne) !", 1);
                            totalDegats += 5;
                            tirageDegats = true;
                        }
                        else if (de == 18)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " assomme l'ennemi !\n"
                                                     "=> inconscient !");
                            log("il assomme l'ennemi !\n"
                                "=> inconscient !", 1);
                        }
                        else if (de == 19)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " fracture le crâne de l'ennemi !\n"
                                                     "=> décès !");
                            log("il fracture le crâne de l'ennemi !\n"
                                "=> décès !", 1);
                        }
                        else if (de == 20)
                        {
                            QMessageBox::information(this, m_nom + " -> Attaque -> Réussite critique",
                                                     m_nom + " écrase violemment un organe vital de l'ennemi !\n"
                                                     "=> décès !");
                            log("il écrase violemment un organe vital de l'ennemi !\n"
                                "=> décès !", 1);
                        }
                    }
                }

                // Attaque
                if (tirageDegats)
                {
                    // On demande les résultats des dés
                    int i2(1);
                    totalDegats += m_armes[i]->getDegatsEnPlus();
                    while (i2 <= m_armes[i]->getNbDes())
                    {
                        bool valid(false);

                        while (!valid)
                            totalDegats += QInputDialog::getInt(this, m_nom + " -> Attaque -> Dégâts",
                                                                "Rentrez le score indiqué par le D6 :",
                                                                1, 1, 6, 1, &valid);
                        i2++;
                    }

                    // S'il n'y a pas d'arme
                    if (m_armes[i]->getNom() == "A mains nues")
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                                 m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                                 "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                        log(m_nom + " attaque à mains nues et fait " + QString::number(totalDegats) + " de dégâts.");
                    }
                    // Si l'arme est une arme normale
                    else
                    {
                        QMessageBox::information(this, m_nom + " -> Attaque -> Récapitulatif",
                                                 m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.\n"
                                                 "A cela, il faut enlever la valeur de protection de la personne/monstre attaqué(e) !");
                        log(m_nom + " attaque avec '" + m_armes[i]->getNom() + "' et fait " + QString::number(totalDegats) + " de dégâts.");
                    }
                }
            }
        }

        // On dit au while que la parade a été faite
        if (i >= MAX_ARME)
            paradeFaite = true;

        // On incrémente i pour passer à l'arme suivante
        i++;
    }
}
void Personnage::esquiver()
{
    int oui = QMessageBox::question(this, m_nom + " -> Esquive",
                                    m_nom + " s'apprète à esquiver une attaque, pour cela, il faut :\n"
                                    "     - qu'il y ai assez d'espace autour de lui ;\n"
                                    "     - et qu'il dise vers où il esquive.\n\n"
                                    "Cependant, l'esquive n'est pas sans inconvénient :\n"
                                    "     - si le joueur esquive, il s'éloigne de 2 mètres, et quitte donc la zone de combat.\n"
                                    "     - si le joueur esquive, il ne pourra pas attaquer lors du prochain assaut.\n\n"
                                    "Continuer ?", QMessageBox::No, QMessageBox::Yes);

    if (oui == QMessageBox::No)
        return;

    int adresse(m_carac_modif->getAdresse());

// On vérifie la protection
    if (m_prTotale == 0 || m_prTotale == 1)
        adresse++;
    else if (m_prTotale == 2);
    else if (m_prTotale == 3 || m_prTotale == 4)
        adresse -= 2;
    else if (m_prTotale == 5)
        adresse -= 4;
    else if (m_prTotale == 6)
        adresse -= 5;
    else if (m_prTotale == 7)
        adresse -= 6;
    else
    {
        QMessageBox::information(this, m_nom + " -> Esquive impossible",
                                 m_nom + " ne peut pas esquiver car il est trop protégé et son armure l'empèche de bouger rapidement !");
        return;
    }

// On vérifie l'encombrement
    bool ok(false);
    QStringList sac;
    sac << "Sac contenant peu d'équipement, petite besace" << "Sac plein" << "Equipement très encombrant";

    QString result = QInputDialog::getItem(this, m_nom + " -> Esquive -> Encombrement",
                                           "Veuillez indiquer comment est l'équipement transporté par " + m_nom,
                                           sac, 0, false, &ok);
    if (!ok)
        return;

    if (result == "Sac plein")
        adresse -= 2;
    else if (result == "Equipement très encombrant")
    {
        QMessageBox::information(this, m_nom + " -> Esquive impossible",
                                 m_nom + " ne peut pas esquiver car il est trop encombré par son équipement qui l'empèche de bouger rapidement !");
        return;
    }

// Enfin, on esquive
    ok = false;
    int de = QInputDialog::getInt(this, m_nom + " -> Esquive",
                                  m_nom + " va esquiver, veuillez lancer un D20 et entrer le score indiqué pour vérifier qu'il peut esquiver...",
                                  1, 1, 20, 1, &ok);

    if (!ok)
        return;

    if (de <= adresse)
    {
        QMessageBox::information(this, m_nom + " -> Esquive",
                                 m_nom + " esquive l'attaque qui lui était destinée.");
        log(m_nom + " esquive l'attaque qui lui était destinée.");
    }
    else
    {
        QMessageBox::information(this, m_nom + " -> Esquive ratée",
                                 m_nom + " n'esquive pas l'attaque qui lui était destinée.");
        log(m_nom + " n'esquive pas l'attaque qui lui était destinée.");
    }
}


// Fonctions de chargement
Caracteristiques Personnage::chargerCaracStatic(bool *erreur, QString ligne, bool AT_PRD, int numLigne)
{
    if (AT_PRD)
    {
        Caracteristiques renvoyer(0, 0, 0, 0, 0, 0, 0);
        int lecteur(0);
        while (lecteur < ligne.size())
        {
            QString carac("");
            carac += ligne.at(lecteur);
            carac += ligne.at(lecteur + 1);
            switch (lecteur)
            {
            case 0:
                renvoyer.setCourage(carac.toInt());
                break;
            case 3:
                renvoyer.setIntelligence(carac.toInt());
                break;
            case 6:
                renvoyer.setCharisme(carac.toInt());
                break;
            case 9:
                renvoyer.setAdresse(carac.toInt());
                break;
            case 12:
                renvoyer.setForce(carac.toInt());
                break;
            case 15:
                renvoyer.setAttaque(carac.toInt());
                break;
            case 18:
                renvoyer.setParade(carac.toInt());
                break;
            default:
                QMessageBox::critical(new QWidget, "Erreur réparable !",
                                      "Caractéristiques non valides !\n"
                                      "Pour plus d'informations : regardez le fichier de log");
                log("Il y a des caractéristiques invalides à la ligne " + QString::number(numLigne) + " !", 2);
                *erreur = true;
                return renvoyer;
                break;
            }
            lecteur += 3;
        }

        return renvoyer;
    }
    else
    {
        Caracteristiques renvoyer(0, 0, 0, 0, 0);
        int lecteur(0);
        while (lecteur < ligne.size())
        {
            QString carac("");
            carac += ligne.at(lecteur);
            carac += ligne.at(lecteur + 1);
            switch (lecteur)
            {
            case 0:
                renvoyer.setCourage(carac.toInt());
                break;
            case 3:
                renvoyer.setIntelligence(carac.toInt());
                break;
            case 6:
                renvoyer.setCharisme(carac.toInt());
                break;
            case 9:
                renvoyer.setAdresse(carac.toInt());
                break;
            case 12:
                renvoyer.setForce(carac.toInt());
                break;
            default:
                QMessageBox::critical(new QWidget, "Erreur réparable !",
                                      "Caractéristiques non valides !\n"
                                      "Pour plus d'informations : regardez le fichier de log");
                log("Il y a des caractéristiques invalides à la ligne " + QString::number(numLigne) + " !", 2);
                *erreur = true;
                return renvoyer;
                break;
            }
            lecteur += 3;
        }

        return renvoyer;
    }
}
Caracteristiques Personnage::chargerCarac(bool *erreur, QString ligne, bool AT_PRD, int numLigne)
{
    if (AT_PRD)
    {
        Caracteristiques renvoyer(0, 0, 0, 0, 0, 0, 0);
        int lecteur(0);
        while (lecteur < ligne.size())
        {
            QString carac("");
            carac += ligne.at(lecteur);
            carac += ligne.at(lecteur + 1);
            switch (lecteur)
            {
            case 0:
                renvoyer.setCourage(carac.toInt());
                break;
            case 3:
                renvoyer.setIntelligence(carac.toInt());
                break;
            case 6:
                renvoyer.setCharisme(carac.toInt());
                break;
            case 9:
                renvoyer.setAdresse(carac.toInt());
                break;
            case 12:
                renvoyer.setForce(carac.toInt());
                break;
            case 15:
                renvoyer.setAttaque(carac.toInt());
                break;
            case 18:
                renvoyer.setParade(carac.toInt());
                break;
            default:
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Caractéristiques non valides !\n"
                                      "Pour plus d'informations : regardez le fichier de log");
                log("Personnage non ouvert : il y a des caractéristiques invalides à la ligne " + QString::number(numLigne) + " !", 2);
                log("Annulation du chargement du groupe !", 1);
                *erreur = true;
                return renvoyer;
                break;
            }
            lecteur += 3;
        }

        return renvoyer;
    }
    else
    {
        Caracteristiques renvoyer(0, 0, 0, 0, 0);
        int lecteur(0);
        while (lecteur < ligne.size())
        {
            QString carac("");
            carac += ligne.at(lecteur);
            carac += ligne.at(lecteur + 1);
            switch (lecteur)
            {
            case 0:
                renvoyer.setCourage(carac.toInt());
                break;
            case 3:
                renvoyer.setIntelligence(carac.toInt());
                break;
            case 6:
                renvoyer.setCharisme(carac.toInt());
                break;
            case 9:
                renvoyer.setAdresse(carac.toInt());
                break;
            case 12:
                renvoyer.setForce(carac.toInt());
                break;
            default:
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Caractéristiques non valides !\n"
                                      "Pour plus d'informations : regardez le fichier de log");
                log("Personnage non ouvert : il y a des caractéristiques invalides à la ligne " + QString::number(numLigne) + " !", 2);
                log("Annulation du chargement du groupe !", 1);
                *erreur = true;
                return renvoyer;
                break;
            }
            lecteur += 3;
        }

        return renvoyer;
    }
}

bool Personnage::chargerPerso()
{
    viderVariables();

    m_fichierPerso = new QFile(m_cheminEnregistrement);
    if (!m_fichierPerso->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        error("Impossible d'ouvrir le fichier personnage suivant : " + m_cheminEnregistrement + "\n"
              "Ceci peut être dû aux permissions du fichier : il n'est pas accessible.");
        return true;
    }

    QTextStream entree(m_fichierPerso);
    int numLigne(1);

// Informations générales
    // On vérifie que le personnage n'est pas nouveau
    QString ligne1(entree.readLine());
    if (ligne1 == "~!AddPerso!~")
    {
        m_nom = entree.readLine();
        numLigne += 2;
        QMessageBox::information(this, "Ajout d'un personnage ayant déjà joué !",
                                 "Félicitations !\n\n"
                                 "Vous avez bien ajouté " + m_nom + " au groupe.\n"
                                 "Mais pour l'instant, ce personnage est tout nu, non protégé et non armé !\n"
                                 "Vous pouvez lui ajouter des armes, protections et des vêtements dès maintenant ! :)");
        viderTousEquipements();
    }
    else if (ligne1 == "~!NewPerso!~")
    {
        m_nom = entree.readLine();
        numLigne += 2;
        QMessageBox::information(this, "Création d'un nouveau personnage de niveau 1 !",
                                 "Félicitations !\n\n"
                                 "Vous avez bien créé " + m_nom + ", un nouveau personnage de niveau 1.\n"
                                 "Mais pour l'instant, ce personnage est tout nu, non protégé et non armé !\n"
                                 "Vous pouvez lui ajouter des armes, protections et des vêtements dès maintenant ! :)");
        viderTousEquipements();
    }
    else
    {
        m_nom = ligne1;
        numLigne++;
    }

    // On continue
    m_sexe = entree.readLine();
    numLigne++;
    m_origine = entree.readLine();
    numLigne++;
    m_metier = entree.readLine();
    numLigne++;

// Energie Vitale
    m_EV = entree.readLine().toInt();
    numLigne++;
    m_EV_modif = m_EV;

// Informations générales (suite)
    m_ptsDestin = entree.readLine().toInt();
    numLigne++;
    m_experience = entree.readLine().toInt();
    numLigne++;

// Caractéristiques
    bool erreur(false);
    m_carac = new Caracteristiques(chargerCarac(&erreur, entree.readLine(), true, numLigne++));
    if (erreur)
        return true;
    m_carac_modif = new Caracteristiques(chargerCarac(&erreur, entree.readLine(), true, numLigne++));
    if (erreur)
        return true;

// Richesses
    m_richesses = new Richesses(0, 0, 0);
    QString piecesLigne = entree.readLine();
    int lecteur = 0;
    while (lecteur < piecesLigne.size())
    {
        QString piecesString("");
        piecesString += piecesLigne.at(lecteur);
        piecesString += piecesLigne.at(lecteur + 1);
        piecesString += piecesLigne.at(lecteur + 2);
        piecesString += piecesLigne.at(lecteur + 3);
        piecesString += piecesLigne.at(lecteur + 4);
        piecesString += piecesLigne.at(lecteur + 5);

        switch (lecteur)
        {
        case 0:
            m_richesses->setOr(piecesString.toInt());
            break;
        case 7:
            m_richesses->setArgent(piecesString.toInt());
            break;
        case 14:
            m_richesses->setCuivre(piecesString.toInt());
            break;
        default:
            QMessageBox::critical(ui->nom, "Erreur réparable !",
                                  "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                  "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                  "Richesses non valides !\n");
            log("Personnage non ouvert : richesses invalides à la ligne " + QString::number(numLigne++) + " !", 2);
            log("Annulation du chargement du groupe !", 1);
            return true;
        }
        lecteur += 7;
    }

// Ouverture des autres choses
    bool ouvertureFichierTerminee(false);
    int lecteurTableauVetement(0),
            lecteurTableauProtection(0),
            lecteurTableauArme(0),
            lecteurTableauFleche(0),
            lecteurTableauEquipement(0);

    bool ligneDejaLue = false;
    QString ligne = "";

    while (!ouvertureFichierTerminee)
    {
        numLigne++;
        // On charge la ligne si elle n'a pas déjà été lue
        if (!ligneDejaLue)
            ligne = entree.readLine();

        // On remet au défaut la fait que la ligne est lue ou pas
        ligneDejaLue = false;

        // Bonus de caractéristiques
        if (ligne == "~!carac_sup_inf!~")
        {
            m_bonusMalus_carac_calcules = true;
            m_bonusMalus_ATPRD_calcules = true;

            m_bonus_degats = entree.readLine().toInt();
            numLigne++;
            m_bonus_attaque = entree.readLine().toInt();
            numLigne++;
            m_bonus_parade = entree.readLine().toInt();
            numLigne++;
            m_bonus_degatsMagiques = entree.readLine().toInt();
            numLigne++;
        }

        // Si le perso est magicien
        else if (ligne == "~!magie!~")
        {
            m_EA = entree.readLine().toInt();
            numLigne++;
            m_EA_modif = m_EA;
            m_typeEA = entree.readLine();
            numLigne++;
        }

        // Valeurs des énergies modifiées
        else if (ligne == "~!energie_modif!~")
        {
            m_EV_modif = entree.readLine().toInt();
            numLigne++;

            m_EA_modif = entree.readLine().toInt();
            numLigne++;
        }

        // Pour les vêtements
        else if (ligne == "~!chapeau!~"
                 || ligne == "~!haut!~"
                 || ligne == "~!bas!~"
                 || ligne == "~!chaussures!~"
                 || ligne == "~!divers!~"
                 || ligne == "~!vetement!~")
        {
            if (lecteurTableauVetement >= MAX_VETEMENT)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop de vêtements\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                log("Personnage non ouvert : il y a trop de vêtements pour ce personnage (nombre max de vêtements : " + QString::number(MAX_VETEMENT) + ") !", 2);
                log("Annulation du chargement du groupe !", 1);
                return true;
            }
            else
            {
                m_vetements[lecteurTableauVetement] = new Vetement(entree.readLine(),
                                                                   0, 0, 0, 0, 0,
                                                                   0, 0, 0, 0, 0);
                numLigne++;
                m_vetements[lecteurTableauVetement]->setBonus(chargerCarac(&erreur, entree.readLine(), false, numLigne));
                    if (erreur)
                        return true;
                numLigne++;
                m_vetements[lecteurTableauVetement]->setMalus(chargerCarac(&erreur, entree.readLine(), false, numLigne));
                    if (erreur)
                        return true;
                numLigne++;

                ligne = entree.readLine();
                numLigne++;
                if (ligne != "~!protection!~"
                    && ligne != "~!chapeau!~"
                        && ligne != "~!haut!~"
                        && ligne != "~!bas!~"
                        && ligne != "~!chaussures!~"
                        && ligne != "~!divers!~"
                        && ligne != "~!vetement!~")
                {
                    if (ligne == "true")
                        m_vetements[lecteurTableauVetement]->setVisible(true);
                }
                else
                    ligneDejaLue = true;

                lecteurTableauVetement++;
            }
        }

        // Pour les protections
        else if (ligne == "~!protection!~")
        {
            if (lecteurTableauProtection >= MAX_PROTECTION)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop de protections\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                log("Personnage non ouvert : il y a trop de protections pour ce personnage (nombre max de protections : " + QString::number(MAX_PROTECTION) + ") !", 2);
                log("Annulation du chargement du groupe !", 1);
                return true;
            }
            else
            {
                m_protections[lecteurTableauProtection] = new Protection(entree.readLine(), entree.readLine().toInt(),
                                                                         0, 0, 0, 0, 0, 0, 0,
                                                                         0, 0, 0, 0, 0, 0, 0);
                numLigne++;
                numLigne++;
                m_protections[lecteurTableauProtection]->setBonus(chargerCarac(&erreur, entree.readLine(), true, numLigne));
                    if (erreur)
                        return true;
                numLigne++;
                m_protections[lecteurTableauProtection]->setMalus(chargerCarac(&erreur, entree.readLine(), true, numLigne));
                    if (erreur)
                        return true;
                numLigne++;

                ligne = entree.readLine();
                numLigne++;
                if (ligne != "~!protection!~"
                    && ligne != "~!arme!~")
                    m_protections[lecteurTableauProtection]->setRupture(ligne.toInt());
                else
                    ligneDejaLue = true;

                lecteurTableauProtection++;
            }
        }

        // Pour les protections
        else if (ligne == "~!arme!~")
        {
            if (lecteurTableauArme >= MAX_ARME)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop d'armes\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                log("Personnage non ouvert : il y a trop d'armes pour ce personnage (nombre max d'armes : " + QString::number(MAX_ARME) + ") !", 2);
                log("Annulation du chargement du groupe !", 1);
                return true;
            }
            else
            {
                m_armes[lecteurTableauArme] = new Arme(entree.readLine(),               // nom
                                                       entree.readLine().toInt(),       // nb des
                                                       entree.readLine().toInt(),       // degats
                                                       0, 0, 0, 0, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 0);
                numLigne++;
                numLigne++;
                numLigne++;
                m_armes[lecteurTableauArme]->setBonus(chargerCarac(&erreur, entree.readLine(), true, numLigne));
                    if (erreur)
                        return true;
                numLigne++;
                m_armes[lecteurTableauArme]->setMalus(chargerCarac(&erreur, entree.readLine(), true, numLigne));
                    if (erreur)
                        return true;
                numLigne++;
                int type = entree.readLine().toInt();
                numLigne++;
                switch (type)
                {
                case 0:
                    m_armes[lecteurTableauArme]->setType(Arme::MainNue);
                    break;
                case 1:
                    m_armes[lecteurTableauArme]->setType(Arme::Tranchante);
                    break;
                case 2:
                    m_armes[lecteurTableauArme]->setType(Arme::Contandante);
                    break;
                case 3:
                    m_armes[lecteurTableauArme]->setType(Arme::Projectile);
                    break;
                default:
                    m_armes[lecteurTableauArme]->setType(Arme::MainNue);
                }
                m_armes[lecteurTableauArme]->setRupture(entree.readLine().toInt());
                numLigne++;

                lecteurTableauArme++;
            }
        }

        // Pour les flèches
        else if (ligne == "~!fleche!~")
        {
            if (lecteurTableauFleche >= MAX_FLECHE)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop de flèches\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                log("Personnage non ouvert : il y a trop de flèches pour ce personnage (nombre max de flèches : " + QString::number(MAX_FLECHE) + ") !", 2);
                log("Annulation du chargement du groupe !", 1);
                return true;
            }
            else
            {
                m_fleches[lecteurTableauFleche] = new Fleche(entree.readLine(),             // nom
                                                             entree.readLine().toInt(),     // nb
                                                             entree.readLine().toInt(),     // PI
                                                             entree.readLine().toInt());    // bonus AD
                numLigne++;
                numLigne++;
                numLigne++;
                numLigne++;


                ligne = entree.readLine();
                numLigne++;
                if (ligne != "~!fleche!~"
                    && ligne != "~!equipement!~")
                {
                    m_fleches[lecteurTableauFleche]->setNbDes(ligne.toInt());
                    m_fleches[lecteurTableauFleche]->setRupture(entree.readLine().toInt());
                    numLigne++;
                }
                else
                    ligneDejaLue = true;

                lecteurTableauFleche++;
            }
        }

        // Pour l'équipement
        else if (ligne == "~!equipement!~")
        {
            if (lecteurTableauEquipement >= MAX_EQUIPEMENT)
            {
                QMessageBox::critical(ui->nom, "Erreur réparable !",
                                      "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                      "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                      "Trop d'équipements\n"
                                      "Pour plus d'informations : regarder le fichier de log");
                log("Personnage non ouvert : il y a trop d'équipements pour ce personnage (nombre max d'équipements : " + QString::number(MAX_EQUIPEMENT) + ") !", 2);
                log("Annulation du chargement du groupe !", 1);
                return true;
            }
            else
            {
                m_equipements[lecteurTableauEquipement] = entree.readLine();
                numLigne++;

                // On charge la ligne suivante pour vérifier que l'équipement n'est pas sur plusieurs lignes
                ligne = entree.readLine();

                bool fin(false);

                // On vérifier que c'est pas un autre objet qui commence
                if (ligne == "~!equipement!~")
                    fin = true;
                if (ligne == "~!competence!~")
                    fin = true;
                if (ligne == "~!FIN_ENREGISTREMENT!~")
                    fin = true;

                // On inscrit la ligne dans l'équipement tant que ce n'est pas un autre objet
                while (!fin)
                {
                    m_equipements[lecteurTableauEquipement] += "\n" + ligne;
                    numLigne++;
                    ligne = entree.readLine();

                    if (ligne == "~!equipement!~")
                        fin = true;
                    if (ligne == "~!competence!~")
                        fin = true;
                    if (ligne == "~!FIN_ENREGISTREMENT!~")
                        fin = true;
                }

                // On dit au programme que la ligne est déjà lue
                ligneDejaLue = true;

                // On ajoute un équipement :)
                lecteurTableauEquipement++;
            }
        }

        // Pour les compétences
        else if (ligne == "~!competence!~")
        {
            QString nomCompetence = entree.readLine();
            numLigne++;
            QString descriptionCompetence = entree.readLine();
            numLigne++;

            // On vérifier que la ligne suivante n'est pas la suite de la compétence
            ligne = entree.readLine();

            bool fin(false);

            if (ligne == "~!competence!~")
                fin = true;
            if (ligne == "~!FIN_ENREGISTREMENT!~")
                fin = true;

            while (!fin)
            {
                descriptionCompetence += "\n" + ligne;
                numLigne++;
                ligne = entree.readLine();

                if (ligne == "~!competence!~")
                    fin = true;
                if (ligne == "~!FIN_ENREGISTREMENT!~")
                    fin = true;
            }

            // On ajoute la compétence
            m_competences.push_back(new Competence(nomCompetence, descriptionCompetence));

            // On indique au programme que la ligne est déjà lue
            ligneDejaLue = true;
        }

        // Pour finir
        else if (ligne == "~!FIN_ENREGISTREMENT!~")
            ouvertureFichierTerminee = true;

        // Dans les autres cas
        else
        {
            QMessageBox::critical(ui->nom, "Erreur inconnue !",
                                  "ERREUR : Erreur lors de l'ouverture du fichier :\n"
                                  "     -> " + m_cheminEnregistrement + " (" + m_nom + ") !\n\n"
                                  "Elément inconnu !\n");
            log("Personnage non ouvert : élément inconnu à la ligne " + QString::number(numLigne) + " !", 2);
            log("Annulation du chargement du groupe !", 1);
            return true;
        }
    }

    log("Personnage chargé !    (" + m_cheminEnregistrement + ")", 1);
    m_fichierPerso->close();

    setNiveau();
    setAffichage();

    return false;
}
void Personnage::enregistrerPerso()
{
    if (!modifNonRec)
        return;

    QString total = "";

    total += m_nom + "\n";
    total += m_sexe + "\n";
    total += m_origine + "\n";
    total += m_metier + "\n";
    total += QString::number(m_EV) + "\n";
    total += QString::number(m_ptsDestin) + "\n";
    total += QString::number(m_experience) + "\n";
    total += m_carac->caracEnregistrement() + "\n";
    total += m_carac_modif->caracEnregistrement() + "\n";

    total += m_richesses->richessesEnregistrement() + "\n";

    if (m_presenceEA)
        total += "~!magie!~\n" + QString::number(m_EA) + "\n" + m_typeEA + "\n";

    total += "~!energie_modif!~\n";
    total += QString::number(m_EV_modif) + "\n";
    total += QString::number(m_EA_modif) + "\n";

    total += "~!carac_sup_inf!~\n";
    total += QString::number(m_bonus_degats) + "\n";
    total += QString::number(m_bonus_attaque) + "\n";
    total += QString::number(m_bonus_parade) + "\n";
    total += QString::number(m_bonus_degatsMagiques) + "\n";

    for (int lecteur = 0; lecteur < MAX_VETEMENT; lecteur++)
        total += m_vetements[lecteur]->vetementEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_PROTECTION; lecteur++)
        total += m_protections[lecteur]->protectionEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_ARME; lecteur++)
        total += m_armes[lecteur]->armeEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_FLECHE; lecteur++)
        total += m_fleches[lecteur]->flechesEnregistrement() + "\n";

    for (int lecteur = 0; lecteur < MAX_EQUIPEMENT; lecteur++)
        total += "~!equipement!~\n" + m_equipements[lecteur] + "\n";

    for (int lecteur = 0; lecteur < m_competences.count(); lecteur++)
    {
        total += "~!competence!~\n";
        total += m_competences.at(lecteur)->getNom() + "\n";
        total += m_competences.at(lecteur)->getDescription() + "\n";
    }

    total += "~!FIN_ENREGISTREMENT!~";

// Eregistrement
    if (m_fichierPerso == 0)
        fatalError("Impossible d'enregistrer le personnage : il n'a pas été chargé.\n\n"
                   "Le programme va être arrêter car c'est une erreur de programmation.\n"
                   "Veuillez signaler ce bug sur : " SITE_BUGS);
    if (!m_fichierPerso->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        error("Impossible d'enregistrer le fichier de personnage sélectionné.\n"
              "Ceci peut être dû aux permissions du fichier : il n'est pas accessible.");
        return;
    }

    QTextStream sortie(m_fichierPerso);

    sortie << total;

    log("'" + m_nom + "' a été enregistré !", 2);
    m_fichierPerso->close();

    modifNonRec = false;
}


// Lors de la modification
void Personnage::modifierPerso()
{
    modifNonRec = true;
}
bool Personnage::getModif() const
{
    return modifNonRec;
}


// Modification du personnage
void Personnage::ajouterXP(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int XP_EnPlus = QInputDialog::getInteger(ui->nom, "Ajouter de l'expérience", "Ajouter de l'expérience à " + m_nom, 1, 1, 999999, 1, &ok);

        if (ok)
        {
            m_experience += XP_EnPlus;

            log(m_nom + " gagne de l'expérience : " + QString::number(XP_EnPlus) + " point(s) !");
        }
    }
    else
    {
        m_experience += value;

        log(m_nom + " gagne de l'expérience : " + QString::number(value) + " point(s) !");
    }

    if (setNiveau())
    {
    // On informe le MJ que le perso a gagné un niveau
        QString D;
        QMessageBox::information(this, "Niveau", m_nom + " a gagné un niveau, nous allons voir les modifications...");
        log(m_nom + "a gagné un niveau ! Les modifications faites en raison de ce nouveau niveau sont citées en dessous...");


    // On demande de quelle type est l'origine pour l'ajout d'EV
        QStringList D6_D4;
        D6_D4 << "D6" << "D4";

        bool valid(false);
        while (!valid)
            D = QInputDialog::getItem(this, m_nom + " -> Passage d'un niveau -> EV",
                                      "De quel type de dé l'origine de " + m_nom + " a besoin pour l'ajout d'EV ?",
                                      D6_D4, 0, false, &valid);
        int ev;
        if (D == "D6")
        {
            valid = false;

            while (!valid)
                ev = QInputDialog::getInt(this, m_nom + " -> Passage d'un niveau -> EV",
                                          "Quel score le D6 indique-t-il ?", 1, 1, 6, 1, &valid);
            m_EV += ev;
            QMessageBox::information(this, "Information sur l'EV de " + m_nom,
                                     m_nom + " gagne " + QString::number(ev) + " point(s) d'EV en plus");
            log(m_nom + " gagne " + QString::number(ev) + " point(s) d'EV en plus à cause de son nouveau niveau.");
        }
        else if (D == "D4")
        {
            valid = false;

            while (!valid)
                ev = QInputDialog::getInt(this, m_nom + " -> Passage d'un niveau -> EV",
                                          "Quel score le D4 indique-t-il ?", 1, 1, 4, 1, &valid);
            m_EV += ev;
            QMessageBox::information(this, "Information sur l'EV de " + m_nom,
                                     m_nom + " gagne " + QString::number(ev) + " point(s) d'EV en plus");
            log(m_nom + " gagne " + QString::number(ev) + " point(s) d'EV en plus à cause de son nouveau niveau.");
        }


    // Si le perso est un sorcier il peut recevoir de l'EA en plus
        if (m_presenceEA)
        {
            bool validEA(false);
            int ea(0);

            while (!validEA)
                ea = QInputDialog::getInt(this, m_nom + " -> Passage d'un niveau -> EA",
                                          "EA -> Quel score le D6 indique-t-il ?",
                                          1, 1, 6, 1, &validEA);
            m_EA += ea;
            QMessageBox::information(this, "Information sur l'EA de " + m_nom,
                                     m_nom + " gagne " + QString::number(ea) + " point(s) d'EA en plus");

            log(m_nom + " gagne " + QString::number(ea) + " point(s) d'EA en plus à cause de son nouveau niveau.");
        }


    // Ajout de  pt sur une carac au choix du joueur
        QStringList carac;
        if (m_carac->getCourage() < 18)
            carac << "COU (" + QString::number(m_carac->getCourage()) + ")";
        if (m_carac->getIntelligence() < 18)
            carac << "INT (" + QString::number(m_carac->getIntelligence()) + ")";
        if (m_carac->getAdresse() < 18)
            carac << "AD (" + QString::number(m_carac->getAdresse()) + ")";
        if (m_carac->getForce() < 18)
            carac << "FO (" + QString::number(m_carac->getForce()) + ")";

        bool valid1(false);
        while (!valid1)
            D = QInputDialog::getItem(this, m_nom + " -> Passage d'un niveau -> Caractéristiques",
                                      m_nom + " a droit à un point en plus sur les caractéristiques suivantes.\n"
                                      "Choisissez en une !",
                                      carac, 0, false, &valid1);
        if (D == "COU (" + QString::number(m_carac->getCourage()) + ")")
        {
            if (m_carac->getCourage() <= 18)
            {
                QMessageBox::information(this, "Information sur le COU de " + m_nom,
                                         m_nom + " gagne 1 point de COU en plus, en raison de son nouveau niveau");
                m_carac->setCourage(m_carac->getCourage() + 1);
                log(m_nom + " gagne 1 point de COU à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur le COU de " + m_nom,
                                         m_nom + " était censé gagner un point de COU en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }
        else if (D == "INT (" + QString::number(m_carac->getIntelligence()) + ")")
        {
            if (m_carac->getIntelligence() <= 18)
            {
                QMessageBox::information(this, "Information sur l'INT de " + m_nom,
                                         m_nom + " gagne 1 point d'INT en plus en raison de son nouveau niveau.");
                m_carac->setIntelligence(m_carac->getIntelligence() + 1);
                log(m_nom + " gagne 1 point d'INT à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur l'INT de " + m_nom,
                                         m_nom + " était censé gagner un point d'INT en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }
        else if (D == "AD (" + QString::number(m_carac->getAdresse()) + ")")
        {
            if (m_carac->getAdresse() <= 18)
            {
                QMessageBox::information(this, "Information sur l'AD de " + m_nom,
                                         m_nom + " gagne 1 point d'AD en plus en raison de son nouveau niveau.");
                m_carac->setAdresse(m_carac->getAdresse() + 1);
                log(m_nom + " gagne 1 point d'AD à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur l'AD de " + m_nom,
                                         m_nom + " était censé gagner un point d'AD en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }
        else if (D == "FO (" + QString::number(m_carac->getForce()) + ")")
        {
            if (m_carac->getForce() <= 18)
            {
                QMessageBox::information(this, "Information sur la FO de " + m_nom,
                                         m_nom + " gagne 1 point de FO en plus, en raison de son nouveau niveau");
                m_carac->setForce(m_carac->getForce() + 1);
                log(m_nom + " gagne 1 point de FO à cause de son nouveau niveau.");
            }
            else
                QMessageBox::information(this, "Information sur la FO de " + m_nom,
                                         m_nom + " était censé gagner un point de FO en raison de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }


    // si le joueur peut gagner un point de CHA
        if (m_origine == "Elfe Sylvain" || m_origine == "Haut-elfe")
        {
            if (m_carac->getCharisme() <= 18)
            {
                QMessageBox::information(this, "Information sur le CHA de " + m_nom,
                                         m_nom + " gagne 1 point de CHA en plus, en raison de son origine et de son nouveau niveau");
                m_carac->setCharisme(m_carac->getCharisme() + 1);
                log(m_nom + " gagne 1 point de CHA à cause de son nouveau niveau et de son origine.");
            }
            else
                QMessageBox::information(this, "Information sur le CHA de " + m_nom,
                                         m_nom + " était censé gagner un point de CHA en raison de son origine et de son nouveau niveau\n"
                                         "mais il est déjà au maximum possible : 18 points.");
        }


    // Ajout de points sur l'attaque ou la parade
        if (m_carac->getAttaque() < 18 && m_carac->getParade() < 17)
        {
            QStringList At_Prd;
            At_Prd << "AT (" + QString::number(m_carac->getAttaque()) + ")"
                   << "PRD (" + QString::number(m_carac->getParade()) + ")";

            bool valid2(false);

            while (!valid2)
                D = QInputDialog::getItem(this, m_nom + " -> Passage d'un niveau -> AT / PRD",
                                          m_nom + " a droit à un point en plus sur les caractéristiques suivantes.\n"
                                          "Choisissez en une !",
                                          At_Prd, 0, false, &valid2);
            if (D == "AT (" + QString::number(m_carac->getAttaque()) + ")")
            {
                QMessageBox::information(this, "Gain d'un point d'AT",
                                         m_nom + " gagne un point d'AT en raison de son nouveau niveau.");
                log(m_nom + "gagne un point d'AT en raison de son nouveau niveau");
                m_carac->setAttaque(m_carac->getAttaque() + 1);
            }
            else if (D == "PRD (" + QString::number(m_carac->getParade()) + ")")
            {
                QMessageBox::information(this, "Gain d'un point de PRD",
                                         m_nom + " gagne un point de PRD en raison de son nouveau niveau.");
                log(m_nom + "gagne un point de PRD en raison de son nouveau niveau");
                m_carac->setParade(m_carac->getParade() + 1);
            }
        }
        else if (m_carac->getAttaque() < 18 && m_carac->getParade() == 17)
        {
            QMessageBox::information(this, "Gain d'un point d'AT",
                                     m_nom + " gagne un point d'AT car il passe un niveau !");
            log(m_nom + "gagne un point d'AT en raison de son nouveau niveau");
            m_carac->setAttaque(m_carac->getAttaque() + 1);
        }
        else if (m_carac->getAttaque() == 18 && m_carac->getParade() < 17)
        {
            QMessageBox::information(this, "Gain d'un point de PRD",
                                     m_nom + " gagne un point de PRD car il passe un niveau !");
            log(m_nom + "gagne un point de PRD en raison de son nouveau niveau");
            m_carac->setParade(m_carac->getParade() + 1);
        }

    // Autres modifications
        if (m_niveau == 3)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nom + " doit choisir une compétence supplémentaire.");
            ajouterCompetence();
        }
        else if (m_niveau == 5 && m_presenceEA)
        {
            QMessageBox::information(this, "Choix d'une spécialisation supplémentaire",
                                     m_nom + " doit choisir une spécialisation supplémentaire");
        }
        else if (m_niveau == 6)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nom + " doit choisir une compétence supplémentaire.");
            ajouterCompetence();
        }
        else if (m_niveau == 10)
        {
            QMessageBox::information(this, "Choix d'une compétence supplémentaire",
                                     m_nom + " doit choisir une compétence supplémentaire.");
            ajouterCompetence();
        }
        else if (m_niveau == 15 && m_presenceEA)
        {
            QMessageBox::information(this, "Choix d'une spécialisation supplémentaire",
                                     m_nom + " doit choisir une spécialisation supplémentaire");
        }
    }
    emit persoModifie();

    ui->xp->setText(QString::number(m_experience));
}

void Personnage::ajouterPO(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Ajouter des PO",
                                             "Ajouter des Pièces d'Or à " + m_nom,
                                             1, 0, 999999 - m_richesses->getOr(), 1, &ok);

        if (ok)
        {
            m_richesses->setOr(m_richesses->getOr() + value);
            log(m_nom + " gagne " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
        }
    }
    else
    {
        m_richesses->setOr(m_richesses->getOr() + value);
        log(m_nom + " gagne " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
    }

    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::retirerPO(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Retirer des PO",
                                             "Retirer des Pièces d'Or à " + m_nom,
                                             1, 0, 1999998 - m_richesses->getOr(), 1, &ok);

        if (ok)
        {
            m_richesses->setOr(m_richesses->getOr() - value);
            log(m_nom + " perd " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
        }
    }
    else
    {
        m_richesses->setOr(m_richesses->getOr() - value);
        log(m_nom + " perd " + QString::number(value) + " PO ; nouveau solde : " + QString::number(m_richesses->getOr()) + " PO.");
    }

    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::ajouterPA(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Ajouter des PA",
                                             "Ajouter des Pièces d'Argent à " + m_nom,
                                             1, 0, 999999 - m_richesses->getArgent(), 1, &ok);

        if (ok)
        {
            m_richesses->setArgent(m_richesses->getArgent() - value);
            log(m_nom + " gagne " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
        }
    }
    else
    {
        m_richesses->setArgent(m_richesses->getArgent() - value);
        log(m_nom + " gagne " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
    }

    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::retirerPA(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Retirer des PA",
                                             "Retirer des Pièces d'Argent à " + m_nom,
                                             1, 0, 1999998 - m_richesses->getArgent(), 1, &ok);

        if (ok)
        {
            m_richesses->setArgent(m_richesses->getArgent() - value);
            log(m_nom + " perd " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
        }
    }
    else
    {
        m_richesses->setArgent(m_richesses->getArgent() - value);
        log(m_nom + " perd " + QString::number(value) + " PA ; nouveau solde : " + QString::number(m_richesses->getArgent()) + " PA.");
    }

    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::ajouterPC(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Ajouter des PC",
                                             "Ajouter des Pièces de Cuivre à " + m_nom,
                                             1, 0, 999999 - m_richesses->getCuivre(), 1, &ok);

        if (ok)
        {
            m_richesses->setCuivre(m_richesses->getCuivre() + value);
            log(m_nom + " gagne " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
        }
    }
    else
    {
        m_richesses->setCuivre(m_richesses->getCuivre() + value);
        log(m_nom + " gagne " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
    }

    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::retirerPC(int value)
{
    if (value == 0)
    {
        bool ok(false);

        int value = QInputDialog::getInteger(this,
                                             "Retirer des PC",
                                             "Retirer des Pièces de Cuivre à " + m_nom,
                                             1, 1, 1999998 - m_richesses->getCuivre(), 1, &ok);

        if (ok)
        {
            m_richesses->setCuivre(m_richesses->getCuivre() - value);
            log(m_nom + " perd " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
        }
    }
    else
    {
        m_richesses->setCuivre(m_richesses->getCuivre() - value);
        log(m_nom + " perd " + QString::number(value) + " PC ; nouveau solde : " + QString::number(m_richesses->getCuivre()) + " PC.");
    }

    rafraichirRichesses();
    emit persoModifie();
}

void Personnage::achatCOU()
{
    if (m_richesses->getOr() - 400 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nom + " -> Achat de puissance",
                      m_nom + " va acheter pour 400 PO un stage de 1 mois pour obtenir un point de COU...");
    QPushButton *continuer = new QPushButton("Valider");
    verif.addButton(continuer, QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nom + " -> Achat de puissance",
                            m_nom + " achète 400 PO un stage de 1 mois pour obtenir un point de COU en plus.");
    m_carac->setCourage(m_carac->getCourage() + 1);

    m_richesses->setOr(m_richesses->getOr() - 400);

    log(m_nom + " achète un point de COU.");

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}
void Personnage::achatINT()
{
    if (m_richesses->getOr() - 500 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nom + " -> Achat de puissance",
                      m_nom + " va acheter pour 500 PO un stage de 6 mois pour obtenir un point d'INT...");
    QPushButton *continuer = new QPushButton("Valider");
    verif.addButton(continuer, QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nom + " -> Achat de puissance",
                             m_nom + " achète 500 PO un stage de 6 mois pour obtenir un point d'INT en plus.");
    m_carac->setIntelligence(m_carac->getIntelligence() + 1);

    m_richesses->setOr(m_richesses->getOr() - 500);

    log(m_nom + " achète un point d'INT.");

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}
void Personnage::achatCHA()
{
    if (m_richesses->getOr() - 400 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nom + " -> Achat de puissance",
                      m_nom + " va acheter pour 400 PO un stage de 1 semaine pour obtenir un point de CHA...");
    QPushButton *continuer = new QPushButton("Valider");
    verif.addButton(continuer, QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nom + " -> Achat de puissance",
                            m_nom + " achète 400 PO un stage de 1 semaine pour obtenir un point de CHA en plus.");
    m_carac->setCharisme(m_carac->getCharisme() + 1);

    m_richesses->setOr(m_richesses->getOr() - 400);

    log(m_nom + " achète un point de CHA.");

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}
void Personnage::achatFO()
{
    if (m_richesses->getOr() - 400 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nom + " -> Achat de puissance",
                      m_nom + " va acheter pour 400 PO un stage de 1 mois pour obtenir un point de FO...");
    QPushButton *continuer = new QPushButton("Valider");
    verif.addButton(continuer, QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nom + " -> Achat de puissance",
                            m_nom + " achète 400 PO un stage de 1 mois pour obtenir un point de FO en plus.");
    m_carac->setForce(m_carac->getForce() + 1);

    m_richesses->setOr(m_richesses->getOr() - 400);

    log(m_nom + " achète un point de FO.");

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}
void Personnage::achatATPRD()
{
    if (m_richesses->getOr() - 500 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QStringList a;
    a << "AT" << "PRD";
    bool ok(false);
    QString b = QInputDialog::getItem(this, m_nom + " -> Achat de puissance",
                                      m_nom + "s achète un stage pour 500 PO pour obtenir un point de :", a, 0, ok);

    if (!ok)
        return;

    m_richesses->setOr(m_richesses->getOr() - 500);

    if (b == "AT" && ok)
    {
        QMessageBox::information(this, m_nom + " -> Achat de puissance",
                                m_nom + " achète 500 PO un stage d'un mois pour acheter un point d'AT");
        m_carac->setAttaque(m_carac->getAttaque() + 1);

        log(m_nom + " achète un point d'AT.");
    }
    else if (b == "PRD" && ok)
    {
        QMessageBox::information(this, m_nom + " -> Achat de puissance",
                                m_nom + " achète 500 PO un stage d'un mois pour acheter un point de PRD");
        m_carac->setParade(m_carac->getParade() + 1);

        log(m_nom + " achète un point de PRD.");
    }

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}

void Personnage::achatEV()
{
    if (m_richesses->getOr() - 200 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nom + " -> Achat de puissance",
                      m_nom + " va acheter 200 PO un stage de 1 semaine pour obtenir un point d'EV...");
    QPushButton *continuer = new QPushButton("Valider");
    verif.addButton(continuer, QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nom + " -> Achat de puissance",
                            m_nom + " achète 200 PO un stage de 1 semaine pour obtenir un point d'EV en plus.");
    m_EV++;

    m_richesses->setOr(m_richesses->getOr() - 200);

    log(m_nom + " achète un point d'EV.");

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}
void Personnage::achatEA()
{
// Si le perso n'est pas un "mage"
    if (!m_presenceEA)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'est pas un mage ; "
                                 "il ne peut donc pas suivre un stage pour gagner de l'EA!");
        return;
    }

// si le perso est un "mage"
    if (m_richesses->getOr() - 200 < -99999)
    {
        QMessageBox::information(this, "Action impossible !",
                                 m_nom + " n'a pas assez de PO pour se payer ce stage !");
        return;
    }

    QMessageBox verif(QMessageBox::Question, m_nom + " -> Achat de puissance",
                      m_nom + " va acheter 200 PO un stage de 1 mois pour obtenir un point d'EA...");
    QPushButton *continuer = new QPushButton("Valider");
    verif.addButton(continuer, QMessageBox::ActionRole);
    QPushButton *annuler = verif.addButton(QMessageBox::Abort);
    setIcone(&verif);
    verif.exec();
    if (verif.clickedButton() == annuler)
        return;

    QMessageBox::information(this, m_nom + " -> Achat de puissance",
                            m_nom + " achète 200 PO un stage de 1 mois pour obtenir un point d'EA en plus.");
    m_EA++;

    m_richesses->setOr(m_richesses->getOr() - 200);

    log(m_nom + " achète un point d'EA.");

    rafraichirRichesses();
    rafraichirCarac();
    emit persoModifie();
}


// Slots automatiques de Qt
// Informations générales
void Personnage::on_nomEdit_clicked(bool checked)
{
    if (!checked)
    {
        m_nom = ui->nom->text();
        emit persoModifie();
    }
    else
        ui->nom->setText(m_nom);

    ui->nom->setEnabled(checked);
}
void Personnage::on_sexeEdit_clicked(bool checked)
{
    if (!checked)
    {
        m_sexe = ui->sexe->text();
        emit persoModifie();
    }
    else
        ui->sexe->setText(m_sexe);

    ui->sexe->setEnabled(checked);
}
void Personnage::on_xpPlus_clicked()
{
    ajouterXP();
}
void Personnage::on_destinMoins_clicked()
{
    if (m_ptsDestin > 1)
    {
        m_ptsDestin--;
        ui->destin->setText(QString::number(m_ptsDestin));

        log(m_nom + " perd 1 point de destin");
    }
    else if (m_ptsDestin == 1)
    {
        m_ptsDestin--;
        ui->destin->setText(QString::number(m_ptsDestin));
        ui->destinMoins->setEnabled(false);

        log(m_nom + " perd 1 point de destin");
    }
    else
        QMessageBox::information(this, "Erreur !",
                                 m_nom + " ne peut pas perdre de points de destin : il n'en a déjà plus !");
    emit persoModifie();
}

// Richesses
void Personnage::on_poPlus_clicked()
{
    ajouterPO();
}
void Personnage::on_poMoins_clicked()
{
    retirerPO();
}
void Personnage::on_paPlus_clicked()
{
    ajouterPA();
}
void Personnage::on_paMoins_clicked()
{
    retirerPA();
}
void Personnage::on_pcPlus_clicked()
{
    ajouterPC();
}
void Personnage::on_pcMoins_clicked()
{
    retirerPC();
}

void Personnage::on_conversionPA_et_PC_en_PO_clicked()
{
    m_richesses->convertir(Richesses::PA_PC_en_PO);
    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::on_conversionPO_en_PA_clicked()
{
    m_richesses->convertir(Richesses::PO_en_PA);
    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::on_conversionPO_en_PC_clicked()
{
    m_richesses->convertir(Richesses::PO_en_PC);
    rafraichirRichesses();
    emit persoModifie();
}
void Personnage::on_conversionPA_en_PC_clicked()
{
    m_richesses->convertir(Richesses::PA_en_PC);
    rafraichirRichesses();
    emit persoModifie();
}

// Protections
void Personnage::on_prEdit_1_clicked()
{
    EquipModif modif(m_protections[0]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirProtections();

        emit persoModifie();
    }
}
void Personnage::on_prEdit_2_clicked()
{
    EquipModif modif(m_protections[1]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirProtections();

        emit persoModifie();
    }
}
void Personnage::on_prEdit_3_clicked()
{
    EquipModif modif(m_protections[2]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirProtections();

        emit persoModifie();
    }
}
void Personnage::on_prEdit_4_clicked()
{
    EquipModif modif(m_protections[3]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirProtections();

        emit persoModifie();
    }
}
void Personnage::on_prEdit_5_clicked()
{
    EquipModif modif(m_protections[4]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirProtections();

        emit persoModifie();
    }
}
void Personnage::on_prEdit_6_clicked()
{
    EquipModif modif(m_protections[5]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirProtections();

        emit persoModifie();
    }
}

// Armes
void Personnage::on_armesEdit_1_clicked()
{
    EquipModif modif(m_armes[0]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirArmes();

        emit persoModifie();
    }
}
void Personnage::on_armesEdit_2_clicked()
{
    EquipModif modif(m_armes[1]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirArmes();

        emit persoModifie();
    }
}
void Personnage::on_armesEdit_3_clicked()
{
    EquipModif modif(m_armes[2]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirArmes();

        emit persoModifie();
    }
}
void Personnage::on_armesEdit_4_clicked()
{
    EquipModif modif(m_armes[3]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_ATPRD_calcules = false;
        m_bonusMalus_carac_calcules = false;
        rafraichirArmes();

        emit persoModifie();
    }
}

// Fleches
void Personnage::on_flechesEdit_1_clicked()
{
    EquipModif modif(m_fleches[0]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirFleches();

        emit persoModifie();
    }
}
void Personnage::on_flechesEdit_2_clicked()
{
    EquipModif modif(m_fleches[1]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirFleches();

        emit persoModifie();
    }
}
void Personnage::on_flechesEdit_3_clicked()
{
    EquipModif modif(m_fleches[2]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirFleches();

        emit persoModifie();
    }
}
void Personnage::on_flechesEdit_4_clicked()
{
    EquipModif modif(m_fleches[3]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirFleches();

        emit persoModifie();
    }
}
void Personnage::on_flechesEdit_5_clicked()
{
    EquipModif modif(m_fleches[4]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirFleches();

        emit persoModifie();
    }
}

void Personnage::on_flechesPlus_1_clicked()
{
    m_fleches[0]->setNombre(m_fleches[0]->getNombre() + 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesPlus_2_clicked()
{
    m_fleches[1]->setNombre(m_fleches[1]->getNombre() + 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesPlus_3_clicked()
{
    m_fleches[2]->setNombre(m_fleches[2]->getNombre() + 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesPlus_4_clicked()
{
    m_fleches[3]->setNombre(m_fleches[3]->getNombre() + 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesPlus_5_clicked()
{
    m_fleches[4]->setNombre(m_fleches[4]->getNombre() + 1);

    rafraichirFleches();

    emit persoModifie();
}

void Personnage::on_flechesMoins_1_clicked()
{
    m_fleches[0]->setNombre(m_fleches[0]->getNombre() - 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesMoins_2_clicked()
{
    m_fleches[1]->setNombre(m_fleches[1]->getNombre() - 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesMoins_3_clicked()
{
    m_fleches[2]->setNombre(m_fleches[2]->getNombre() - 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesMoins_4_clicked()
{
    m_fleches[3]->setNombre(m_fleches[3]->getNombre() - 1);

    rafraichirFleches();

    emit persoModifie();
}
void Personnage::on_flechesMoins_5_clicked()
{
    m_fleches[4]->setNombre(m_fleches[4]->getNombre() - 1);

    rafraichirFleches();

    emit persoModifie();
}

// Vêtements
void Personnage::on_vetEdit_1_clicked()
{
    EquipModif modif(m_vetements[0]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirVetements();

        emit persoModifie();
    }
}
void Personnage::on_vetEdit_2_clicked()
{
    EquipModif modif(m_vetements[1]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirVetements();

        emit persoModifie();
    }
}
void Personnage::on_vetEdit_3_clicked()
{
    EquipModif modif(m_vetements[2]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirVetements();

        emit persoModifie();
    }
}
void Personnage::on_vetEdit_4_clicked()
{
    EquipModif modif(m_vetements[3]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirVetements();

        emit persoModifie();
    }
}
void Personnage::on_vetEdit_5_clicked()
{
    EquipModif modif(m_vetements[4]);
    modif.exec();

    if (modif.equipementModifie())
    {
        m_bonusMalus_carac_calcules = false;
        rafraichirVetements();

        emit persoModifie();
    }
}

void Personnage::on_vetVisible_1_clicked(bool checked)
{
    m_vetements[0]->setVisible(checked);

    emit persoModifie();
}
void Personnage::on_vetVisible_2_clicked(bool checked)
{
    m_vetements[1]->setVisible(checked);

    emit persoModifie();
}
void Personnage::on_vetVisible_3_clicked(bool checked)
{
    m_vetements[2]->setVisible(checked);

    emit persoModifie();
}
void Personnage::on_vetVisible_4_clicked(bool checked)
{
    m_vetements[3]->setVisible(checked);

    emit persoModifie();
}
void Personnage::on_vetVisible_5_clicked(bool checked)
{
    m_vetements[4]->setVisible(checked);

    emit persoModifie();
}

// Equipements
void Personnage::on_equipsEdit_1_clicked(bool checked)
{
    if (!checked)
        m_equipements[0] = ui->equips_1->toPlainText();
    else
        ui->equips_1->setPlainText(m_equipements[0]);

    ui->equips_1->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_2_clicked(bool checked)
{
    if (!checked)
        m_equipements[1] = ui->equips_2->toPlainText();
    else
        ui->equips_2->setPlainText(m_equipements[1]);

    ui->equips_2->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_3_clicked(bool checked)
{
    if (!checked)
        m_equipements[2] = ui->equips_3->toPlainText();
    else
        ui->equips_3->setPlainText(m_equipements[2]);

    ui->equips_3->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_4_clicked(bool checked)
{
    if (!checked)
        m_equipements[3] = ui->equips_4->toPlainText();
    else
        ui->equips_4->setPlainText(m_equipements[3]);

    ui->equips_4->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_5_clicked(bool checked)
{
    if (!checked)
        m_equipements[4] = ui->equips_5->toPlainText();
    else
        ui->equips_5->setPlainText(m_equipements[4]);

    ui->equips_5->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_6_clicked(bool checked)
{
    if (!checked)
        m_equipements[5] = ui->equips_6->toPlainText();
    else
        ui->equips_6->setPlainText(m_equipements[5]);

    ui->equips_6->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_7_clicked(bool checked)
{
    if (!checked)
        m_equipements[6] = ui->equips_7->toPlainText();
    else
        ui->equips_7->setPlainText(m_equipements[6]);

    ui->equips_7->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_8_clicked(bool checked)
{
    if (!checked)
        m_equipements[7] = ui->equips_8->toPlainText();
    else
        ui->equips_8->setPlainText(m_equipements[7]);

    ui->equips_8->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_9_clicked(bool checked)
{
    if (!checked)
        m_equipements[8] = ui->equips_9->toPlainText();
    else
        ui->equips_9->setPlainText(m_equipements[8]);

    ui->equips_9->setReadOnly(!checked);
    emit persoModifie();
}
void Personnage::on_equipsEdit_10_clicked(bool checked)
{
    if (!checked)
        m_equipements[9] = ui->equips_10->toPlainText();
    else
        ui->equips_10->setPlainText(m_equipements[9]);

    ui->equips_10->setReadOnly(!checked);
    emit persoModifie();
}

// Caractéristiques
void Personnage::on_evPlus_clicked()
{
    m_EV_modif++;

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_evMoins_clicked()
{
    m_EV_modif--;

    if (m_EV_modif == 1)
        QMessageBox::information(this, m_nom + " -> Perte d'un point de vie",
                                 m_nom + " n'a plus qu'un point de vie, il tombe dans le coma.");

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_eaPlus_clicked()
{
    m_EA_modif++;

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_eaMoins_clicked()
{
    m_EA_modif--;

    emit persoModifie();
    rafraichirCarac();
}

void Personnage::on_couPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setCourage(m_carac_modif->getCourage() + 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_couMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setCourage(m_carac_modif->getCourage() - 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_intelPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setIntelligence(m_carac_modif->getIntelligence() + 1);

    m_bonusMalus_carac_calcules = false;
    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_intelMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setIntelligence(m_carac_modif->getIntelligence() - 1);

    m_bonusMalus_carac_calcules = false;
    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_chaPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setCharisme(m_carac_modif->getCharisme() + 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_chaMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setCharisme(m_carac_modif->getCharisme() - 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_adPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setAdresse(m_carac_modif->getAdresse() + 1);

    m_bonusMalus_carac_calcules = false;
    m_bonusMalus_ATPRD_calcules = false;
    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_adMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setAdresse(m_carac_modif->getAdresse() - 1);

    m_bonusMalus_carac_calcules = false;
    m_bonusMalus_ATPRD_calcules = false;
    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_foPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setForce(m_carac_modif->getForce() + 1);

    m_bonusMalus_carac_calcules = false;
    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_foMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setForce(m_carac_modif->getForce() - 1);

    m_bonusMalus_carac_calcules = false;
    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_atPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setAttaque(m_carac_modif->getAttaque() + 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_atMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setAttaque(m_carac_modif->getAttaque() - 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_prdPlus_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setParade(m_carac_modif->getParade() + 1);

    emit persoModifie();
    rafraichirCarac();
}
void Personnage::on_prdMoins_clicked()
{
    if (ui->remiseAZero->isChecked())
    {
        ui->remiseAZero->setChecked(false);
    }
    m_carac_modif->setParade(m_carac_modif->getParade() - 1);

    emit persoModifie();
    rafraichirCarac();
}

void Personnage::on_remiseAZero_clicked(bool checked)
{
    if (checked)
        rafraichirCarac();
}

// Compétences
void Personnage::setCompetencesPossibles(QVector<Competence *> tab)
{
// On copie
    competencesPossibles = tab;

// On enlève celles que l'on a déjà
    for (int i(0); i < m_competences.count(); i++)
        if (competencesPossibles.contains(m_competences.at(i)))
        {
            int index = competencesPossibles.indexOf(m_competences.at(i));
            competencesPossibles.remove(index);
        }
}

void Personnage::on_addCompetence_clicked()
{
    ajouterCompetence();
}
void Personnage::ajouterCompetence()
{
    SelectCompetence *dialogue = new SelectCompetence(competencesPossibles, this);
    int result = dialogue->exec();

    if (result == QDialog::Accepted)
    {
        QString nom = dialogue->getChoix();

        // On ajoute la compétence à la liste
        for (int i(0); i < competencesPossibles.count(); i++)
            if (competencesPossibles.at(i)->getNom() == nom)
            {
                m_competences.push_back(competencesPossibles.at(i));
                competencesPossibles.remove(i);
            }

        // On affiche
        if (m_competences.count() == 1)
        {
            QVBoxLayout *layoutCompetences = new QVBoxLayout;

            layoutCompetences->addWidget(m_competences.at(0)->getWidget());

            ui->competencesScrollWidgetContents->setLayout(layoutCompetences);
        }
        else
            ui->competencesScrollWidgetContents->layout()->addWidget(m_competences.at(m_competences.count() - 1)->getWidget());

        emit persoModifie();
    }
}

void Personnage::on_addCompetencePerso_clicked()
{
    ajouterCompetencePerso();
}
void Personnage::ajouterCompetencePerso()
{
    QDialog *dialogue = new QDialog(this, Qt::Dialog);
    dialogue->setWindowTitle(m_nom + " -> ajout d'une compétence !");

    QGroupBox nom_group("Nom");
        QLineEdit *nom = new QLineEdit();
        QVBoxLayout layout1;
            layout1.addWidget(nom);
        nom_group.setLayout(&layout1);

    QGroupBox description_group("Description");
        QTextEdit *description = new QTextEdit();
        QVBoxLayout layout2;
            layout2.addWidget(description);
        description_group.setLayout(&layout2);

    QDialogButtonBox boutons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        QObject::connect(&boutons, SIGNAL(accepted()), dialogue, SLOT(accept()));
        QObject::connect(&boutons, SIGNAL(rejected()), dialogue, SLOT(reject()));

    QVBoxLayout total;
        total.addWidget(&nom_group);
        total.addWidget(&description_group);
        total.addWidget(&boutons);

    dialogue->setLayout(&total);

    int result = dialogue->exec();

    if (result == QDialog::Accepted)
    {
        m_competences.push_back(new Competence(nom->text(), description->toPlainText()));

        if (m_competences.count() == 1)
        {
            QVBoxLayout *layoutCompetences = new QVBoxLayout;

            layoutCompetences->addWidget(m_competences.at(0)->getWidget());

            ui->competencesScrollWidgetContents->setLayout(layoutCompetences);
        }
        else
            ui->competencesScrollWidgetContents->layout()->addWidget(m_competences.at(m_competences.count() - 1)->getWidget());

        emit persoModifie();
    }
}

QVector<Competence*> Personnage::getCompetence() const
{
    return m_competences;
}
