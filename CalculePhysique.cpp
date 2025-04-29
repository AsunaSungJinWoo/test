#include "Affichage.h"
#include "CalculePhysique.h"
#include "InterfaceGraphique.h"
#include "logger.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cassert>
#include <iostream>
#include <filesystem>

#define _CRT_SECURE_NO_WARNINGS

Logger logger("log.txt");

using namespace std;

Tensions CalculerTension(int choixFormule, int choixDonnees, float masseCabine, float masseContrepoids,
    float acceleration, float momentsInertie, float rayon, float pMoteur, float vitesse) {

    logger.log(LogLevel::INFO, "Appel de CalculerTension");

    float tensionCabine = 0, tensionContrepoids = 0;

    if (choixFormule == CHOIX_CALCUL_TENSION_AVEC_SOMME_FORCE) {
        tensionCabine = masseCabine * (acceleration + Graviter);
        tensionContrepoids = masseContrepoids * (Graviter - acceleration);
    }
    else if (choixFormule == CHOIX_CALCUL_TENSION_AVEC_CM) {
        tensionCabine = masseContrepoids * (Graviter - acceleration) - (pMoteur / momentsInertie);
        tensionContrepoids = (pMoteur + (momentsInertie * masseCabine) * (acceleration + Graviter)) / momentsInertie;
    }
    else {
        logger.log(LogLevel::WARNING, "Le choix de la formule CalculerTension nest pas valide");
        return { 0, 0 };
    }

    Tensions result;
    switch (choixDonnees) {
    case CHOIX_TENSION_CABINE: result = { tensionCabine, 0 }; break;
    case CHOIX_TENSION_CONTREPOIDS: result = { 0, tensionContrepoids }; break;
    case CHOIX_DES_DEUX_TENSIONS: result = { tensionCabine, tensionContrepoids }; break;
    default:
        logger.log(LogLevel::WARNING, "Le choix de la sortie de CalculerTension nest pas valide");
        return { 0, 0 };
    }

    logger.log(LogLevel::INFO, "CalculerTension - Resultat: " + std::to_string(tensionCabine) + ", " + std::to_string(tensionContrepoids));
    return result;
}

float CoupleMoteur(int choix, float tensionCabine, float tensionContrepoids, float acceleration,
    float momentsInertie, float rayon, float pMoteur, float vitesse) {

    logger.log(LogLevel::INFO, "Appel de CoupleMoteur");

    float cm = 0;
    switch (choix) {
    case 0:
        cm = pMoteur / (vitesse / rayon);
        break;
    case 1:
        cm = (((momentsInertie * acceleration) / rayon) - rayon * (tensionContrepoids - tensionCabine));
        break;
    default:
        logger.log(LogLevel::WARNING, "Le choix de la formule CoupleMoteur nest pas valide");
        return 0;
    }

    cm = (cm < 0) ? -cm : cm;
    logger.log(LogLevel::INFO, "CoupleMoteur - Resultat: " + std::to_string(cm));
    return cm;
}

float PuissanceMoteur(float coupleMot, float vitesse, float rayon) {
    logger.log(LogLevel::INFO, "Appel de PuissanceMoteur");
    if (rayon == 0) {
        logger.log(LogLevel::WARNING, "Division par 0 dans PuissanceMoteur");
        return 0;
    }
    float result = coupleMot * (vitesse / rayon);
    logger.log(LogLevel::INFO, "PuissanceMoteur - Resultat: " + std::to_string(result));
    return result;
}

float RayonPoulie(int choix, float vitesse, float vitesseAngulaire, float CoupleMoteur, float PuissanceMoteur) {
    logger.log(LogLevel::INFO, "Appel de RayonPoulie");
    float result = (choix == 0) ? (vitesse / vitesseAngulaire) : ((choix == 1) ? (vitesse * CoupleMoteur) / PuissanceMoteur : 0.0f);
    logger.log(LogLevel::INFO, "RayonPoulie - Resultat: " + std::to_string(result));
    return result;
}

float VitesseRotation(float vitesseAngulaire) {
    logger.log(LogLevel::INFO, "Appel de VitesseRotation");
    float result = (vitesseAngulaire * 30) / M_PI;
    logger.log(LogLevel::INFO, "VitesseRotation - Resultat: " + std::to_string(result));
    return result;
}

float TempsMonteeAndDescente(float distance, float vitesse) {
    logger.log(LogLevel::INFO, "Appel de TempsMonteeAndDescente");
    float result = distance / vitesse;
    logger.log(LogLevel::INFO, "TempsMonteeAndDescente - Resultat: " + std::to_string(result));
    return result;
}

float Acceleration(int choix, float masseContrepoids, float masseCabine, float tensionContrepoids, float tensionCabine) {
    logger.log(LogLevel::INFO, "Appel de Acceleration");
    float result;
    if (choix == 0) {
        result = (Graviter - (tensionCabine / masseCabine));
    }
    else if (choix == 1) {
        result = (-Graviter + (tensionContrepoids / masseContrepoids));
    }
    else {
        logger.log(LogLevel::WARNING, "Le choix de la formule Acceleration nest pas valide");
        return 0;
    }
    logger.log(LogLevel::INFO, "Acceleration - Resultat: " + std::to_string(result));
    return result;
}


void TestFonction() {
    try {
        Tensions t1 = CalculerTension(0, 0, 350, 100, 0.3f, 0, 0, 0, 0);
        assert(fabs(t1.cabine - 3538.5) < 0.01 && "Erreur: CalculerTension test 1");

        float couple = CoupleMoteur(0, 0, 0, 0, 0, 0.3f, 3750, 1.5f);
        assert(fabs(couple - 750) < 0.1 && "Erreur: CoupleMoteur test 1");
        couple = CoupleMoteur(1, 3538.5f, 951, 0.1f, 0.1f, 0.3f, 0, 0);
        assert(fabs(couple - 776.2833) < 0.1 && "Erreur: CoupleMoteur test 2");

        assert(fabs(PuissanceMoteur(750, 1.5f, 0.3f) - 3750) < 0.01 && "Erreur: PuissanceMoteur test 1");

        assert(fabs(RayonPoulie(0, 1.5f, 3, 0, 0) - 0.5f) < 0.01 && "Erreur: RayonPoulie test 1");
        assert(fabs(RayonPoulie(1, 1.5f, 0, 750, 3750) - 0.3f) < 0.01 && "Erreur: RayonPoulie test 1");

        assert(fabs(VitesseRotation(10.0) - 95.49f) < 0.01 && "Erreur: VitesseRotation test 1");

        assert(fabs(TempsMonteeAndDescente(20.0, 2.0) - 10.0) < 0.01 && "Erreur: TempsMonteeAndDescente test 1");

        assert(fabs(Acceleration(0,0, 100,0, 951) - 0.3) < 0.01 && "Erreur: Acceleration test 1");
        assert(fabs(Acceleration(1, 350, 0, 3538.5, 0) - 0.3) < 0.01 && "Erreur: Acceleration test 2");

        sf::Font font;
        std::string fontPath = "../dependances_exterieurs/fonts/Roboto-BlackItalic.ttf";

        cout << "Tous les tests sont reussis !" << endl;
        if (!std::filesystem::exists(fontPath)) {
            std::cerr << "Le fichier " << fontPath << " nexiste pas!" << std::endl;
            logger.log(LogLevel::ERROR, "le fichier de police nexiste pas.");
        }
        else {
            std::cout << "Le fichier " << fontPath << " existe!" << std::endl;
            if (!font.openFromFile(fontPath)) {
                std::cerr << "Erreur lors du chargement de la police!" << std::endl;
                logger.log(LogLevel::WARNING, "le fichier de police ne se charge pas");
            }
            else {
                std::cout << "Police chargee avec succes!" << std::endl;
            }
        }
    }

    catch (const exception& e) {
        cerr << "Erreur lors de l'exécution des tests ! Détails : " << e.what() << endl;
        logger.log(LogLevel::WARNING, "test non valider");
    }
}