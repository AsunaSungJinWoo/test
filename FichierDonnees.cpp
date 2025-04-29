#include "Affichage.h"
#include "CalculePhysique.h"
#include "FichierDonnees.h"
#include "InterfaceGraphique.h"

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>



using namespace std;

// Énumération pour les choix du menu
enum MenuOption {
    gi_CalculTension = 1,
    gi_CalculCouple = 2,
    gi_CalculPuissance = 3,
    gi_CalculRayon = 4,
    gi_CalculVitesseRotation = 5,
    gi_CalculTempsMontee = 6,
    gi_CalculAcceleration = 7,
    gi_VoirSimulation = 8,
    gi_ExecuterTests = 9,
    gi_Quitter = 10,
};

void AffichageAvecDonnees(void) {
    // Initialisation des variables

    float lfMasseCabine = 0.0;
    float lfMasseContrepoids = 0.0;
    float lfTensionCabine = 0.0;
    float lfTensionContrepoids = 0.0;
    float lfRayonPoulie = 0.0;
    float lfVitesseMax = 0.0;
    float lfDureeAcceleration = 0.0;
    float lfCoupleMoteur = 0.0;
    float lfPuissanceMoteur = 0.0;
    float lfVitesseAngulaire = 0.0;
    float lfMomentInertie = 0.0;
    float lfDistance = 0.0;
    float lfAccelerationAngulaire = 0.0;

    int liChoixDonne = 0;

    string lsLigne; // On utiliseras une chaine de charactères
    ifstream lsFichier; // Flux de fichier d'entrée, ifstream est utilisé pour lire des données à partir de fichiers.

    // Algorithme
    lsFichier.open("../dependances_exterieurs/Fichier_Donnee.csv", ios::in); // Ouverture du fichier en lecture
    if (lsFichier.is_open()) {
        // Nous lisons les lignes et ignorons la première ligne car inutile (indique quelle valeur est assignée la colonne)
        getline(lsFichier, lsLigne);

        // Lire la deuxième ligne
        getline(lsFichier, lsLigne);

        lsFichier.close(); //On ferme le fichier


        std::vector<char> lvStr(lsLigne.begin(), lsLigne.end()); 
        /*Utilité: Copie chaque caractère de la chaîne lsLigne dans le vecteur lvStr,
        cela permet de convertir la chaîne de caractères en un tableau de caractères dynamique.

            Explications:
            crée un vecteur de caractères (std::vector<char>) nommé lvStr.
            LsLigne.begin et Ls.end sont respectivement le début et la fin de la chaîne Ls ligne
            */

        lvStr.push_back('\0'); // Ajouter un caractère nul à la fin, utile pour marquer la fin d'une chaîne de charactères.


        char* pch = strtok(lvStr.data(), " ,");

        /* Utilité: sert à décomposer la ligne en tokens
           strkok sert à découper la chaîne de charactères en tokens (qui sont ,
           lvStr.data() renvoie un pointeur vers le premier élément de lvStr,

        */
        
        
        if (pch != nullptr) {                   //vérifie si il reste des tokens à traiter


            lfMasseCabine = (float)atof(pch);   //convertit le token pointé par pch en un nombre à virgule flottante.
                                                //atof sert à convertir une chaîne de caractères en un double.
                                                //Le résultat de atof est ensuite converti en float et assigné à la variable lfMasseCabine.

            pch = strtok(nullptr, " ,");// Lorsque strtok est appelée avec nullptr comme premier argument, elle continue à découper la chaîne à partir de l'endroit où elle s'était arrêtée précédemment.
                                        // Globalement cela permet de récupérer le token suivant dans la chaîne, en utilisant les mêmes délimiteurs (virgules).
       
        
        }


        if (pch != nullptr) {
            lfMasseContrepoids = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfRayonPoulie = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfVitesseMax = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfDureeAcceleration = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfCoupleMoteur = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfPuissanceMoteur = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfTensionCabine = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfTensionContrepoids = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfVitesseAngulaire = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfMomentInertie = (float)atof(pch);
            pch = strtok(nullptr, " ,");
        }
        if (pch != nullptr) {
            lfDistance = (float)atof(pch);
        }
        
        if (pch != nullptr) {
            lfAccelerationAngulaire = (float)atof(pch);
        }

        // Afficher les valeurs des variables
        cout << "Masse de la cabine: " << lfMasseCabine << endl;
        cout << "Masse du contrepoids: " << lfMasseContrepoids << endl;
        cout << "Rayon de la poulie: " << lfRayonPoulie << endl;
        cout << "Vitesse maximum: " << lfVitesseMax << endl;
        cout << "Duree de l'acceleration: " << lfDureeAcceleration << endl;
        cout << "Couple moteur: " << lfCoupleMoteur << endl;
        cout << "Couple moteur: " << lfPuissanceMoteur << endl;
        cout << "Tension de la cabine: " << lfTensionCabine << endl;
        cout << "Tension du contrepoids: " << lfTensionContrepoids << endl;
        cout << "Vitesse angulaire: " << lfVitesseAngulaire << endl;
        cout << "Moment d'inertie: " << lfMomentInertie << endl;
        cout << "Distance: " << lfDistance << endl;
        cout << "Acceleration angulaire: " << lfAccelerationAngulaire << endl;

        while (true) { // Boucle pour répéter le menu après chaque calcul/choix
            cout << "\n==== MENU PRINCIPAL (Fichier .csv actif) ====\n"
                << " 1. Calculer la tension\n"
                << " 2. Calculer le couple moteur\n"
                << " 3. Calculer la puissance moteur\n"
                << " 4. Calculer le rayon de la poulie\n"
                << " 5. Calculer la vitesse de rotation\n"
                << " 6. Calculer le temps de montee/descente\n"
                << " 7. Calculer l'acceleration\n"
                << " 8. Voir la simulation\n"
                << " 9. Executer les tests\n"
                << "10. Quitter le .csv\n"
                << "Entrez votre choix : ";
            cin >> liChoixDonne;

            int liChoixTension, liChoixResult;


            switch (liChoixDonne) {
            case gi_CalculTension: {
                float lfAccelerationAngulaire2 = lfAccelerationAngulaire,
                    lfMomentInertie2 = lfMomentInertie,
                    lfMasseCabine2 = lfMasseCabine,
                    lfMasseContrepoids2 = lfMasseContrepoids,
                    lfRayonPoulie2 = lfRayonPoulie,
                    lfPuissanceMoteur2 = lfPuissanceMoteur,
                    lfVitesseMax2 = lfVitesseMax;




                cout << "Donner la formule a utiliser en fonction des valeurs que vous avez: \n"
                    << "0 = acceleration et masse \n"
                    << "1 = les moments de force, les moments d'inertie et acceleration \n";
                i_SecuriserSaisie(liChoixTension);

                if (liChoixTension == 0 and
                   (lfAccelerationAngulaire2 == 0 ||
                   lfMasseCabine2 == 0 ||
                   lfMasseContrepoids2 == 0))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                if (liChoixTension == 1 and 
                   (lfAccelerationAngulaire2 == 0 || 
                   lfMasseCabine2 == 0 ||
                   lfMasseContrepoids2 == 0 || 
                   lfPuissanceMoteur2 == 0 || 
                   lfMomentInertie2 == 0))

                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                cout << "Donner le resultat que vous voulez \n"
                    << "0 = tension de la cabine \n"
                    << "1 = tension du contrepoids \n"
                    << "2 = les deux \n";
                i_SecuriserSaisie(liChoixResult);
 

                Tensions lsResult = CalculerTension(
                    liChoixTension,
                    liChoixResult,
                    lfMasseCabine2,
                    lfMasseContrepoids2,
                    lfAccelerationAngulaire2,
                    lfMomentInertie2,
                    lfRayonPoulie2,
                    lfPuissanceMoteur2,
                    lfVitesseMax2);

                cout << "Tension cabine: " << lsResult.cabine << " N, Tension contrepoids: " << lsResult.contrepoids << " N\n";
                break;
            }

            case gi_CalculCouple: {
                float lfTensionCabine2 = lfTensionCabine,
                    lfTensionContrepoids2 = lfTensionContrepoids,
                    lfAlpha2 = lfAccelerationAngulaire,
                    lfMomentsInertie2 = lfMomentInertie,
                    lfRayon2 = lfRayonPoulie,
                    lfPuissanceMoteur2 = lfPuissanceMoteur,
                    lfVitesse2 = lfVitesseMax;

                int liChoixCouple;

                cout << "Choisissez votre methode de calcul \n"
                    << "0 = couple moteur par puissance \n"
                    << "1 = couple moteur par tensions) \n";
                i_SecuriserSaisie(liChoixCouple);


                if (liChoixCouple == 0 and
                    (lfPuissanceMoteur2 == 0 ||
                        lfVitesse2 == 0 ||
                        lfRayon2 == 0 ))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                if (liChoixCouple == 1 and
                    (lfMomentsInertie2 == 0 ||
                    lfAlpha2 == 0 ||
                    lfRayon2 == 0 ||
                    lfTensionCabine2 == 0 ||
                    lfTensionContrepoids2 == 0))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                cout << "Couple moteur : " << CoupleMoteur(
                    liChoixCouple,
                    lfTensionCabine2,
                    lfTensionContrepoids2,
                    lfAlpha2,
                    lfMomentsInertie2,
                    lfRayon2,
                    lfPuissanceMoteur2,
                    lfVitesse2)
                    << " Nm\n";
                break;
            }

            case gi_CalculPuissance: {
                float lfCoupleMot2 = lfCoupleMoteur,
                      lfVitesse2 = lfVitesseMax,
                      lfRayon2 = lfRayonPoulie;

                if (lfCoupleMot2 == 0 ||
                        lfVitesse2 == 0 ||
                        lfRayon2 == 0)
                {
                    cout << "Erreur dans les donnees du fichier, il y a présence d'une valeur erronnee ou nulle";
                    break;
                }

                cout << "Puissance moteur : " << PuissanceMoteur(
                    lfCoupleMot2,
                    lfVitesse2,
                    lfRayon2)
                    << " W\n";
                break;
            }

            case gi_CalculRayon: {
                float lfVitesse2 = lfVitesseMax,
                      lfVitesseAngulaire2 = lfAccelerationAngulaire,
                      lfCoupleMoteur2 = lfCoupleMoteur,
                      lfPuissanceMoteur2 = lfPuissanceMoteur;

                int li_ChoixCalcul2;
                cout << "Choisissez la formule :\n"
                    << "0 = Utiliser vitesse lineaire et vitesse angulaire\n"
                    << "1 = Utiliser vitesse ,cm ,pm\n"
                    << "Votre choix : ";

                cin >> li_ChoixCalcul2;
                i_SecuriserSaisie(li_ChoixCalcul2);

                if (li_ChoixCalcul2 == 0 and
                   (lfVitesse2 == 0 ||
                    lfVitesseAngulaire2 == 0))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                if (li_ChoixCalcul2 == 1 and
                    (lfVitesse2 == 0 ||
                     lfCoupleMoteur2 == 0 ||
                     lfPuissanceMoteur2 == 0))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                cout << "Rayon de la poulie : " << RayonPoulie(
                    li_ChoixCalcul2,
                    lfVitesse2,
                    lfVitesseAngulaire2,
                    lfCoupleMoteur2,
                    lfPuissanceMoteur2)
                    << " m\n";
                break;
            }


            case gi_CalculVitesseRotation: {
                float lfVitesseAngulaire2 = lfAccelerationAngulaire;

                if (lfVitesseAngulaire2 == 0)
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }
                cout << "Vitesse de rotation : " << VitesseRotation(lfVitesseAngulaire2) << " tr/min\n";
                break;
            }


            case gi_CalculTempsMontee: {
                float lfDistance2 = lfDistance,
                      lfVitesse2 = lfVitesseMax;

                if (lfDistance2 == 0 || lfVitesse2 == 0)
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                cout << "Temps de montee/descente : " << TempsMonteeAndDescente(lfDistance2, lfVitesse2) << " s\n";
                break;
            }

            case gi_CalculAcceleration: {
                float lfMasseCabine2 = lfMasseCabine,
                    lfMasseContrepoids2 = lfMasseContrepoids,
                    lfTensionCabine2 = lfTensionCabine,
                    lfTensionContrepoids2 = lfTensionContrepoids;

                int liChoixAcc=0.0;

                cout << "Choisissez la formule :\n"
                    << "0 = Utiliser tensionCabine, masseCabine \n"
                    << "1 = Utiliser tensionContrepoids, masseContrepoids\n"
                    << "Votre choix : ";
                i_SecuriserSaisie(liChoixAcc);

                if (liChoixAcc == 0 and
                    (lfMasseCabine2 == 0 ||
                     lfTensionCabine2 == 0 ))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }    

                if (liChoixAcc == 1 and
                    (lfMasseContrepoids2 == 0 ||
                     lfTensionContrepoids2 == 0))
                {
                    cout << "Erreur dans les donnees du fichier, il y a presence d'une valeur erronnee ou nulle";
                    break;
                }

                cout << "valeur de l'acceleration : " << Acceleration(
                    liChoixAcc,
                    lfMasseContrepoids2,
                    lfMasseCabine,
                    lfTensionContrepoids2,
                    lfTensionCabine2) << "m/s2";
                break;
            }

            case gi_VoirSimulation:
                SFMLSimulation();

                break;
            case gi_ExecuterTests:
                TestFonction();

                break;
            case gi_Quitter:
                cout << "Arret du fichier .csv\n";
                return;

            default:
                cout << "Choix invalide, veuillez reessayer.\n";
                break;
            }
        }
    }
    else {
        cout << "Impossible d'ouvrir le fichier." << endl; // si on n'arrive à ouvrir le fichier, on renvoie une erreur 
    }
}
