#pragma once

/*
    E: prend en valeur une variable qui sera modifi�e en m�me temps que "valeur" car il y a int&.
    R: la fonction i_SecuriserSaisie permet dans un premier temps de demander � l'utilisateur une donn�e pr�cise. Dans ce cas, on veut un entier et tant que les donn�es
        d'entr�e ne sont pas conformes, la fonction redemande � l'utilisateur la valeur.
    S: la sortie est en void mais elle affecte bien la valeur d'entr�e, donc elle renvoie quand m�me quelque chose.
*/
void i_SecuriserSaisie(int& valeur);

/*
    E: prend en valeur une variable qui sera modifi�e en m�me temps que "valeur" car il y a float&.
    R: la fonction f_SecuriserSaisie permet dans un premier temps de demander � l'utilisateur une donn�e pr�cise. Dans ce cas, on veut un float et tant que les donn�es
        d'entr�e ne sont pas conformes, la fonction redemande � l'utilisateur la valeur.
    S: la sortie est en void mais elle affecte bien la valeur d'entr�e, donc elle renvoie quand m�me quelque chose.
*/
void f_SecuriserSaisie(float& valeur);

/*
    Fonction : Affichage

    Entr�e :
        - Aucune

    R�le :
        - Affiche le menu principal contenant les diff�rentes options disponibles pour l'utilisateur.
        - G�re la saisie utilisateur et oriente vers les calculs ou actions correspondantes.
        - V�rifie la validit� de la saisie pour �viter les erreurs.

    Retour :
        - Aucune valeur de retour (void).
*/
void Affichage(void);

