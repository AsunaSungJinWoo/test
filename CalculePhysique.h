#pragma once

// On d�finit nos constantes
#define M_PI 3.14159265358979323846f  // Pi
#define Graviter 9.81f  // Constante de gravit�

// On d�finit les diff�rents choix qui pourront �tre effectu�s lors des calculs
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
    R : Cette fonction permet de calculer les tensions des c�bles, c'est-�-dire T_cabine et T_contrepoids.
    E : Les param�tres d'entr�e sont le choix de la formule (calcul avec somme de forces ou calcul avec centre de masse),
        le choix de la tension � renvoyer (0 = tension cabine, 1 = tension contrepoids, 2 = les deux tensions),
        la masse de la cabine et du contrepoids, l'acc�l�ration angulaire (alpha), le moment d'inertie, le rayon, la puissance du moteur,
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
    E : Les param�tres d'entr�e sont le choix de la formule (0 = couple par puissance avec puissance, vitesse et rayon, 1 = couple par tensions avec moments d'inertie,
        acc�l�ration, rayon et les tensions des c�bles),
        les tensions de la cabine et du contrepoids, l'acc�l�ration angulaire, le moment d'inertie, le rayon de la poulie,
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
    E : Les param�tres d'entr�e sont le couple moteur, la vitesse et le rayon de la poulie.
    S : La fonction renvoie la valeur de la puissance moteur calcul�e � partir des param�tres fournis.
}
*/
float PuissanceMoteur(float coupleMot,
    float vitesse,
    float rayon);

/*
{
    R : Cette fonction permet de calculer le rayon de la poulie.
    E : Les param�tres d'entr�e sont la vitesse lin�aire de l'ascenseur, la vitesse angulaire de la poulie, le couple du moteur et la puissance du moteur.
        De plus, il y a la possibilit� de choisir la formule � utiliser (0 = vitesse lin�aire/angulaire, 1 = vitesse, couple et puissance).
    S : La fonction renvoie le rayon de la poulie, calcul� en fonction de la vitesse lin�aire et angulaire.
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
    E : Le param�tre d'entr�e est la vitesse angulaire de la poulie.
    S : La fonction renvoie la vitesse de rotation calcul�e en fonction de la vitesse angulaire.
}
*/
float VitesseRotation(float vitesseAngulaire);

/*
{
    R : Cette fonction permet de calculer le temps de mont�e et de descente de l'ascenseur.
    E : Les param�tres d'entr�e sont la distance parcourue et la vitesse de l'ascenseur.
    S : La fonction renvoie le temps n�cessaire pour monter ou descendre sur la distance donn�e avec la vitesse sp�cifi�e.
}
*/
float TempsMonteeAndDescente(float distance,
    float vitesse);

/*
{
    R : Cette fonction permet de calculer l'acc�l�ration de l'ascenseur.
    E : Les param�tres d'entr�e sont le choix de la formule (0 = acc�l�ration par la somme des forces, 1 = acc�l�ration par les tensions),
        la masse de la cabine et du contrepoids, les tensions dans les c�bles de la cabine et du contrepoids, et la vitesse de l'ascenseur.
    S : La fonction renvoie la valeur de l'acc�l�ration calcul�e en fonction des param�tres fournis.
}
*/
float Acceleration(int choix,
    float masseContrepoids,
    float masseCabine,
    float tensionContrepoids,
    float tensionCabine);

/*
{
    R : Cette fonction permet de tester la validit� des calculs effectu�s par les diff�rentes fonctions de calcul.
        Elle permet aussi de faire des tests sur l'ouverture de certains fichiers comme la police pour l'interface graphique.
    S : La fonction renvoie les r�sultats des tests effectu�s sur les fonctions pour v�rifier leur pr�cision et leur bon fonctionnement.
        Elle v�rifie plusieurs cas et renvoie un message d'erreur sp�cifique pour faciliter la r�paration des bugs �ventuels.
}
*/
void TestFonction();