#pragma once

/*
    E: prend en valeur une variable qui sera modifiée en même temps que "valeur" car il y a int&.
    R: la fonction i_SecuriserSaisie permet dans un premier temps de demander à l'utilisateur une donnée précise. Dans ce cas, on veut un entier et tant que les données
        d'entrée ne sont pas conformes, la fonction redemande à l'utilisateur la valeur.
    S: la sortie est en void mais elle affecte bien la valeur d'entrée, donc elle renvoie quand même quelque chose.
*/
void i_SecuriserSaisie(int& valeur);

/*
    E: prend en valeur une variable qui sera modifiée en même temps que "valeur" car il y a float&.
    R: la fonction f_SecuriserSaisie permet dans un premier temps de demander à l'utilisateur une donnée précise. Dans ce cas, on veut un float et tant que les données
        d'entrée ne sont pas conformes, la fonction redemande à l'utilisateur la valeur.
    S: la sortie est en void mais elle affecte bien la valeur d'entrée, donc elle renvoie quand même quelque chose.
*/
void f_SecuriserSaisie(float& valeur);

/*
    Fonction : Affichage

    Entrée :
        - Aucune

    Rôle :
        - Affiche le menu principal contenant les différentes options disponibles pour l'utilisateur.
        - Gère la saisie utilisateur et oriente vers les calculs ou actions correspondantes.
        - Vérifie la validité de la saisie pour éviter les erreurs.

    Retour :
        - Aucune valeur de retour (void).
*/
void Affichage(void);

