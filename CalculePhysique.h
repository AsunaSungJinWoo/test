#pragma once

// On définit nos constantes
#define M_PI 3.14159265358979323846f  // Pi
#define Graviter 9.81f  // Constante de gravité

// On définit les différents choix qui pourront être effectués lors des calculs
#define CHOIX_CALCUL_TENSION_AVEC_SOMME_FORCE 0
#define CHOIX_CALCUL_TENSION_AVEC_CM 1
#define CHOIX_TENSION_CABINE 0
#define CHOIX_TENSION_CONTREPOIDS 1
#define CHOIX_DES_DEUX_TENSIONS 2

// Structure pour stocker les tensions
struct Tensions {
    float cabine;
    float contrepoids;
};

/*
{
    R : Cette fonction permet de calculer les tensions des câbles, c'est-à-dire T_cabine et T_contrepoids.
    E : Les paramètres d'entrée sont le choix de la formule (calcul avec somme de forces ou calcul avec centre de masse),
        le choix de la tension à renvoyer (0 = tension cabine, 1 = tension contrepoids, 2 = les deux tensions),
        la masse de la cabine et du contrepoids, l'accélération angulaire (alpha), le moment d'inertie, le rayon, la puissance du moteur,
        et la vitesse.
    S : La fonction renvoie soit la tension de la cabine, soit celle du contrepoids, soit les deux tensions, sous forme de struct Tensions.
}
*/
Tensions CalculerTension(int choixFormule,
    int choixDonnees,
    float masseCabine,
    float masseContrepoids,
    float alpha,
    float momentsInertie,
    float rayon,
    float pMoteur,
    float vitesse);

/*
{
    R : Cette fonction permet de calculer le couple moteur.
    E : Les paramètres d'entrée sont le choix de la formule (0 = couple par puissance avec puissance, vitesse et rayon, 1 = couple par tensions avec moments d'inertie,
        accélération, rayon et les tensions des câbles),
        les tensions de la cabine et du contrepoids, l'accélération angulaire, le moment d'inertie, le rayon de la poulie,
        la puissance du moteur et la vitesse.
    S : La fonction renvoie la valeur du couple moteur en fonction de la formule choisie.
}
*/
float CoupleMoteur(int choix,
    float tensionCabine,
    float tensionContrepoids,
    float alpha,
    float momentsInertie,
    float rayon,
    float puissanceMoteur,
    float vitesse);

/*
{
    R : Cette fonction permet de calculer la puissance du moteur.
    E : Les paramètres d'entrée sont le couple moteur, la vitesse et le rayon de la poulie.
    S : La fonction renvoie la valeur de la puissance moteur calculée à partir des paramètres fournis.
}
*/
float PuissanceMoteur(float coupleMot,
    float vitesse,
    float rayon);

/*
{
    R : Cette fonction permet de calculer le rayon de la poulie.
    E : Les paramètres d'entrée sont la vitesse linéaire de l'ascenseur, la vitesse angulaire de la poulie, le couple du moteur et la puissance du moteur.
        De plus, il y a la possibilité de choisir la formule à utiliser (0 = vitesse linéaire/angulaire, 1 = vitesse, couple et puissance).
    S : La fonction renvoie le rayon de la poulie, calculé en fonction de la vitesse linéaire et angulaire.
}
*/
float RayonPoulie(int choix,
    float vitesse,
    float vitesseAngulaire,
    float coupleMoteur,
    float puissanceMoteur);

/*
{
    R : Cette fonction permet de calculer la vitesse de rotation.
    E : Le paramètre d'entrée est la vitesse angulaire de la poulie.
    S : La fonction renvoie la vitesse de rotation calculée en fonction de la vitesse angulaire.
}
*/
float VitesseRotation(float vitesseAngulaire);

/*
{
    R : Cette fonction permet de calculer le temps de montée et de descente de l'ascenseur.
    E : Les paramètres d'entrée sont la distance parcourue et la vitesse de l'ascenseur.
    S : La fonction renvoie le temps nécessaire pour monter ou descendre sur la distance donnée avec la vitesse spécifiée.
}
*/
float TempsMonteeAndDescente(float distance,
    float vitesse);

/*
{
    R : Cette fonction permet de calculer l'accélération de l'ascenseur.
    E : Les paramètres d'entrée sont le choix de la formule (0 = accélération par la somme des forces, 1 = accélération par les tensions),
        la masse de la cabine et du contrepoids, les tensions dans les câbles de la cabine et du contrepoids, et la vitesse de l'ascenseur.
    S : La fonction renvoie la valeur de l'accélération calculée en fonction des paramètres fournis.
}
*/
float Acceleration(int choix,
    float masseContrepoids,
    float masseCabine,
    float tensionContrepoids,
    float tensionCabine);

/*
{
    R : Cette fonction permet de tester la validité des calculs effectués par les différentes fonctions de calcul.
        Elle permet aussi de faire des tests sur l'ouverture de certains fichiers comme la police pour l'interface graphique.
    S : La fonction renvoie les résultats des tests effectués sur les fonctions pour vérifier leur précision et leur bon fonctionnement.
        Elle vérifie plusieurs cas et renvoie un message d'erreur spécifique pour faciliter la réparation des bugs éventuels.
}
*/
void TestFonction();