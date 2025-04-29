#include "Affichage.h"
#include "CalculePhysique.h"
#include "FichierDonnees.h"
#include "InterfaceGraphique.h"
#include "logger.h"

#include <SFML/Graphics.hpp>
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
    gi_UtiliserCsv = 8,
    gi_VoirSimulation = 9,
    gi_ExecuterTests = 10,
    gi_Quitter = 11,
};

// Fonction pour sécuriser la saisie d'un entier
void i_SecuriserSaisie(int& valeur) {  //cree une refenrences 
    while (true) {
        cin >> valeur;

        if (cin.fail()) {  // Vérifie si la saisie est invalide
            cout << "Saisie invalide. Veuillez entrer un nombre entier valide : ";
            cin.clear();  // Efface l'état d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Vide le buffer
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Supprime les caractères superflus
            break;  // Sort de la boucle si la saisie est correcte
        }
    }
}

// Fonction pour sécuriser la saisie d'un flottant
void f_SecuriserSaisie(float& valeur) {
    while (true) {
        cin >> valeur;

        if (cin.fail()) {  // Vérifie si la saisie est invalide
            cout << "Saisie invalide. Veuillez entrer un nombre décimal valide : ";
            cin.clear();  // Efface l'état d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Vide le buffer
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Supprime les caractères superflus
            break;  // Sort de la boucle si la saisie est correcte
        }
    }
}

void Affichage(void) {
    int li_Choix = 0;

    while (true) {
        cout << "\n==== MENU PRINCIPAL ====\n"
            << " 1. Calculer la tension\n"
            << " 2. Calculer le couple moteur\n"
            << " 3. Calculer la puissance moteur\n"
            << " 4. Calculer le rayon de la poulie\n"
            << " 5. Calculer la vitesse de rotation\n"
            << " 6. Calculer le temps de montee/descente\n"
            << " 7. Calculer l'acceleration\n"
            << " 8. Utiliser un fichier .csv\n"
            << " 9. Voir la simulation\n"
            << "10. Executer les tests\n"
            << "11. Quitter\n"
            << "Entrez votre choix : ";

        i_SecuriserSaisie(li_Choix);  // Sécurisation correcte de l'entrée

        switch (li_Choix) {
        case gi_CalculTension: {
            float lf_MasseCabine = 0, lf_MasseContrepoids = 0, lf_acceleration = 0;
            float lf_MomentsDinertie = 0, lf_Rayon = 0, lf_CoupleMoteur = 0, lf_Vitesse = 0;
            int li_ChoixCalcul = 0, li_ChoixTension = 0, li_ChoixResult = 0;
            Tensions result{};

            cout << "Que voulez-vous calculer ?\n"
                << "0 = Tension cabine\n"
                << "1 = Tension contrepoids\n"
                << "2 = Les deux tensions\n"
                << "3 = Retourner en arriere\n"
                << "Votre choix : ";
            i_SecuriserSaisie(li_ChoixTension);

            if (li_ChoixTension == 3) {
                cout << "Retour au menu principal.\n";
                break;
            }

            switch (li_ChoixTension) {
            case CHOIX_TENSION_CABINE: {
                cout << "Choisissez la formule :\n"
                    << "0 = Utiliser acceleration et masse de la cabine\n"
                    << "1 = Utiliser moments de force\n"
                    << "Votre choix : ";
                i_SecuriserSaisie(li_ChoixCalcul);

                if (li_ChoixCalcul == CHOIX_CALCUL_TENSION_AVEC_SOMME_FORCE) {
                    cout << "Entrez la masse de la cabine (kg) : ";       f_SecuriserSaisie(lf_MasseCabine);
                    cout << "Entrez lacceleration angulaire (rad/s) : "; f_SecuriserSaisie(lf_acceleration);
                }
                else if (li_ChoixCalcul == CHOIX_CALCUL_TENSION_AVEC_CM) {
                    cout << "Entrez le moment dinertie (kg.m) : ";       f_SecuriserSaisie(lf_MomentsDinertie);
                    cout << "Entrez le rayon (m) : ";                     f_SecuriserSaisie(lf_Rayon);
                    cout << "Entrez le couple moteur (N.m) : ";           f_SecuriserSaisie(lf_CoupleMoteur);
                    cout << "Entrez la vitesse (m/s) : ";                 f_SecuriserSaisie(lf_Vitesse);
                    cout << "Entrez la masse du contrepoids (kg) : ";     f_SecuriserSaisie(lf_MasseContrepoids);
                    cout << "Entrez lacceleration angulaire (rad/s) : "; f_SecuriserSaisie(lf_acceleration);
                }

                result = CalculerTension(li_ChoixCalcul, li_ChoixResult, lf_MasseCabine, lf_MasseContrepoids, lf_acceleration, lf_MomentsDinertie, lf_Rayon, lf_CoupleMoteur, lf_Vitesse);
                cout << "Tension cabine : " << result.cabine << " N\n";
                break;
            }
            case CHOIX_TENSION_CONTREPOIDS: {
                cout << "Entrez la masse du contrepoids (kg) : ";     f_SecuriserSaisie(lf_MasseContrepoids);
                cout << "Entrez lacceleration angulaire (rad/s) : "; f_SecuriserSaisie(lf_acceleration);

                result = CalculerTension(li_ChoixCalcul, li_ChoixResult, lf_MasseCabine, lf_MasseContrepoids, lf_acceleration, lf_MomentsDinertie, lf_Rayon, lf_CoupleMoteur, lf_Vitesse);
                cout << "Tension contrepoids : " << result.contrepoids << " N\n";
                break;
            }
            case CHOIX_DES_DEUX_TENSIONS: {
                cout << "Entrez la masse de la cabine (kg) : ";        f_SecuriserSaisie(lf_MasseCabine);
                cout << "Entrez la masse du contrepoids (kg) : ";      f_SecuriserSaisie(lf_MasseContrepoids);
                cout << "Entrez lacceleration angulaire (rad/s) : "; f_SecuriserSaisie(lf_acceleration);

                result = CalculerTension(li_ChoixCalcul, li_ChoixResult, lf_MasseCabine, lf_MasseContrepoids, lf_acceleration, lf_MomentsDinertie, lf_Rayon, lf_CoupleMoteur, lf_Vitesse);
                cout << "Tension cabine : " << result.cabine << " N\n";
                cout << "Tension contrepoids : " << result.contrepoids << " N\n";
                break;
            }
            }
            break;
        }
        case gi_CalculCouple: {
            float lf_TensionCabine = 0, lf_TensionContrepoids = 0, lf_acceleration = 0, lf_MomentsDinertie = 0, lf_Rayon = 0, lf_PMoteur = 0, lf_Vitesse = 0;
            int li_ChoixCouple = 0;

            cout << "Choisissez (0 = couple par puissance, 1 = couple par tensions) : ";
            i_SecuriserSaisie(li_ChoixCouple);

            if (li_ChoixCouple == 0) {
                cout << "Entrez le rayon (m) : ";            f_SecuriserSaisie(lf_Rayon);
                cout << "Entrez la puissance moteur (N.m) : "; f_SecuriserSaisie(lf_PMoteur);
                cout << "Entrez la vitesse (m/s) : ";          f_SecuriserSaisie(lf_Vitesse);
            }
            else if (li_ChoixCouple == 1) {
                cout << "Entrez lacceleration angulaire (rad/s) : ";  f_SecuriserSaisie(lf_acceleration);
                cout << "Entrez le moment dinertie (kg.m) : ";       f_SecuriserSaisie(lf_MomentsDinertie);
                cout << "Entrez la tension cabine (N) : ";         f_SecuriserSaisie(lf_TensionCabine);
                cout << "Entrez la tension contrepoids (N) : ";    f_SecuriserSaisie(lf_TensionContrepoids);
                cout << "Entrez le rayon (m) : ";                  f_SecuriserSaisie(lf_Rayon);
            }

            cout << "Couple moteur : " << CoupleMoteur(li_ChoixCouple, lf_TensionCabine, lf_TensionContrepoids, lf_acceleration, lf_MomentsDinertie, lf_Rayon, lf_PMoteur, lf_Vitesse) << " Nm\n";
            break;
        }

        case gi_CalculPuissance: {
            float lf_CoupleMot, lf_Vitesse, lf_Rayon;
            cout << "Entrez le couple moteur (N.m) : ";  f_SecuriserSaisie(lf_CoupleMot);
            cout << "Entrez la vitesse (m/s) : ";        f_SecuriserSaisie(lf_Vitesse);
            cout << "Entrez le rayon (m) : ";          f_SecuriserSaisie(lf_Rayon);

            cout << "Puissance moteur : " << PuissanceMoteur(lf_CoupleMot, lf_Vitesse, lf_Rayon) << " W\n";
            break;
        }

        case gi_CalculRayon: {
            float lf_Vitesse = 0, lf_VitesseAngulaire = 0, lf_CoupleMot = 0, lf_PuissanceMot = 0;
            int li_ChoixCalcul;

            cout << "Choisissez la formule :\n"
                << "0 = Utiliser vitesse lineaire et vitesse angulaire\n"
                << "1 = Utiliser vitesse ,cm ,pm\n"
                << "Votre choix : ";
            i_SecuriserSaisie(li_ChoixCalcul);

            if (li_ChoixCalcul == 0) {
                cout << "Entrez la vitesse (m/s) : ";          f_SecuriserSaisie(lf_Vitesse);
                cout << "Entrez la vitesse angulaire (rad/s) : ";f_SecuriserSaisie(lf_VitesseAngulaire);
            }
            else if (li_ChoixCalcul == 1) {
                cout << "Entrez la vitesse (m/s) : ";            f_SecuriserSaisie(lf_Vitesse);
                cout << "Entrez le couple moteur (N.m) : ";      f_SecuriserSaisie(lf_CoupleMot);
                cout << "Entrez la puissance du moteur (W): "; f_SecuriserSaisie(lf_PuissanceMot);
            }
            else {
                cout << "Choix invalide, veuillez réessayer.\n";
                break;
            }

            cout << "Rayon de la poulie : " << RayonPoulie(li_ChoixCalcul, lf_Vitesse, lf_VitesseAngulaire, lf_CoupleMot, lf_PuissanceMot) << " m\n";
            break;
        }

        case gi_CalculVitesseRotation: {
            float lf_VitesseAngulaire;
            cout << "Entrez la vitesse angulaire (rad/s) : "; f_SecuriserSaisie(lf_VitesseAngulaire);


            cout << "Vitesse de rotation : " << VitesseRotation(lf_VitesseAngulaire) << " tr/min\n";
            break;
        }

        case gi_CalculTempsMontee: {
            float lf_Distance, lf_Vitesse;
            cout << "Entrez la distance (m): "; f_SecuriserSaisie(lf_Distance);
            cout << "Entrez la vitesse (m/s) : ";  f_SecuriserSaisie(lf_Vitesse);


            cout << "Temps de montee/descente : " << TempsMonteeAndDescente(lf_Distance, lf_Vitesse) << " s\n";
            break;
        }
        case gi_CalculAcceleration: {
            float lf_MasseCabine = 0, lf_MasseContrepoids = 0, lf_TensionCabine = 0, lf_TensionContrepoids = 0;
            int li_ChoixCalcul = 0;

            cout << "Choisissez la formule :\n"
                << "0 = Utiliser tensionCabine, masseCabine \n"
                << "1 = Utiliser tensionContrepoids, masseContrepoids\n"
                << "Votre choix : ";
            i_SecuriserSaisie(li_ChoixCalcul);

            if (li_ChoixCalcul == 0) {
                cout << "Entrez la masse de la cabine (m) : "; f_SecuriserSaisie(lf_MasseCabine);
                cout << "Entrez la tension du cable de la cabine (N) : ";  f_SecuriserSaisie(lf_TensionCabine);
            }
            else if (li_ChoixCalcul == 1) {
                cout << "Entrez la masse de la contrepoid (m) : "; f_SecuriserSaisie(lf_MasseContrepoids);
                cout << "Entrez la tension du cable de la contrepoids (N) : ";  f_SecuriserSaisie(lf_TensionContrepoids);
            }
            Acceleration(li_ChoixCalcul, lf_MasseContrepoids, lf_MasseCabine, lf_TensionContrepoids, lf_TensionCabine);
            break;
        }
        case gi_UtiliserCsv:
            AffichageAvecDonnees();
            break;

        case gi_VoirSimulation:
            SFMLSimulation();
            break;

        case gi_ExecuterTests:
            TestFonction();
            break;

        case gi_Quitter:
            cout << "Programme termine.\n";
            return;

        default:
            cout << "Choix invalide, veuillez reessayer.\n";
        }

    }
}