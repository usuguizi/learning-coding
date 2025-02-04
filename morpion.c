#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

// Prototypes des fonctions
void afficherGrille(char grille[SIZE][SIZE]);
int verifierVictoire(char grille[SIZE][SIZE], char joueur);
int estPlein(char grille[SIZE][SIZE]);
void jouerTour(char grille[SIZE][SIZE], char joueur);

// Fonction principale
int main() {
    char grille[SIZE][SIZE] = { {' ', ' ', ' '},
                                {' ', ' ', ' '},
                                {' ', ' ', ' '} };
    char joueurActuel = 'X';
    int jeuEnCours = 1;

    printf("Bienvenue dans le jeu du Morpion !\n");

    while (jeuEnCours) {
        afficherGrille(grille);

        // Le joueur actuel joue son tour
        printf("C'est au tour du joueur %c.\n", joueurActuel);
        jouerTour(grille, joueurActuel);

        // Vérifie si le joueur a gagné
        if (verifierVictoire(grille, joueurActuel)) {
            afficherGrille(grille);
            printf("Félicitations ! Le joueur %c vient de remporter la partie!\n", joueurActuel);
            jeuEnCours = 0;
        }
        // Vérifie si la grille est pleine (égalité)
        else if (estPlein(grille)) {
            afficherGrille(grille);
            printf("Match nul! Il n'y a aucun gagnant.\n");
            jeuEnCours = 0;
        }

        // Change de joueur
        joueurActuel = (joueurActuel == 'X') ? 'O' : 'X';
    }

    printf("Merci d'avoi joué, à la prochaine !\n");
    return 0;
}

// Fonction pour afficher la grille
void afficherGrille(char grille[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", grille[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

// Fonction pour vérifier si un joueur a gagné
int verifierVictoire(char grille[SIZE][SIZE], char joueur) {
    // Vérification des lignes
    for (int i = 0; i < SIZE; i++) {
        if (grille[i][0] == joueur && grille[i][1] == joueur && grille[i][2] == joueur) {
            return 1;
        }
    }

    // Vérification des colonnes
    for (int i = 0; i < SIZE; i++) {
        if (grille[0][i] == joueur && grille[1][i] == joueur && grille[2][i] == joueur) {
            return 1;
        }
    }

    // Vérification des diagonales
    if (grille[0][0] == joueur && grille[1][1] == joueur && grille[2][2] == joueur) {
        return 1;
    }
    if (grille[0][2] == joueur && grille[1][1] == joueur && grille[2][0] == joueur) {
        return 1;
    }

    return 0;
}

// Fonction pour vérifier si la grille est pleine
int estPlein(char grille[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grille[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

// Fonction pour jouer un tour
void jouerTour(char grille[SIZE][SIZE], char joueur) {
    int ligne, colonne;
    while (1) {
        printf("Entrez une ligne (1-3) et une colonne (1-3) séparées par un espace : ");
        scanf("%d %d", &ligne, &colonne);

        // Vérifie que les coordonnées sont valides
        if (ligne < 1 || ligne > 3 || colonne < 1 || colonne > 3) {
            printf("Coordonnées invalides. Essayez à nouveau.\n");
            continue;
        }

        // Vérifie que la case est libre
        if (grille[ligne - 1][colonne - 1] != ' ') {
            printf("Cette case est déjà occupée. Choisissez une autre case.\n");
            continue;
        }

        // Place le symbole du joueur et termine le tour
        grille[ligne - 1][colonne - 1] = joueur;
        break;
    }
}
