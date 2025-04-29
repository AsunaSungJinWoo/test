#include "Affichage.h"
#include "CalculePhysique.h"
#include "FichierDonnees.h"
#include "InterfaceGraphique.h"
#include "logger.h"

#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

/* ****************************************************************************** */
/*                                                                                */
/*                                                        ____________________    */
/*                                                       |____________________|   */
/*                                                        ____            ____    */
/*   main.cpp                                            |    |   ____   |    |   */
/*                                                       |    |  |  __|  |    |   */
/*                                                       |    |   \ \    |    |   */
/*   By: Theo.G And Bastien.D                            |    |   / /_   |    |   */
/*                                                       |    |  |____|  |    |   */
/*   Created: 2025/03/12   by Theo                       |    | _______  |    |   */
/*   Updated: 2025/03/29   by Theo                       |    ||____   \ |    |   */
/*                                                       |    |     \  | |    |   */
/*                                                       |    |    _/  / |    |   */
/*                                                       |    |   |___/  |    |   */
/*                                                       |    |__________|    |   */
/*                                                        \                  /    */
/*                                                         \                /     */
/*                                                          \______________/      */
/*                                                                                */
/* ****************************************************************************** */

/* IDEE GENERALE DU PROGRAMME */
/*
 * Le programme permet d'obtenir toutes les données relatives à un ascenseur telles que le couple moteur, la puissance du moteur, les tensions, etc.
 * Ce programme est constitué de formules de physique où chaque valeur est calculée dans des fonctions spécifiques.
 */

 // gi = global integer
 // li = local integer

int main()
{
    Logger logger("log.txt");
    logger.log(LogLevel::INFO, "Application demarree");
    Affichage(); // Lancement du programme d'affichage
    logger.log(LogLevel::INFO, "Application termine");
    return 0;
}