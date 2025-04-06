#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_ATTEMPTS 7

void displayWord(char word[], int revealed[]);
int checkWin(int revealed[], int wordLength);

int main() {
    char word[MAX_WORD_LENGTH];
    char guessedLetter;
    int revealed[MAX_WORD_LENGTH] = {0};
    int attemptsLeft = MAX_ATTEMPTS;
    int wordLength;

    printf("=== Jeudu Pendu ===\n");
    printf("Joueur 1,entrez un mot (max %d lettres) : ", MAX_WORD_LENGTH);
    scanf("%s", word);
    
    wordLength = strlen(word);
    for (int i = 0; i < wordLength; i++) {
        word[i] = tolower(word[i]); // Convertir le mot en minuscules
    }

    system("clear"); // Effacer l'écran pour cacher le mot au Joueur 2

    printf("Joueur2,devinez le mot caché !\n\n");

    while (attemptsLeft > 0) {
        displayWord(word, revealed);
        printf("\nTentatives restantes : %d\n", attemptsLeft);
        printf("Entrez une lettre : ");
        scanf(" %c", &guessedLetter);
        guessedLetter = tolower(guessedLetter);

        int correctGuess = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guessedLetter && !revealed[i]) {
                revealed[i] = 1;
                correctGuess = 1;
            }
        }

        if (!correctGuess) {
            attemptsLeft--;
            printf("\nMauvais choix !\n");
        } else {
            printf("\nBonne lettre !\n");
        }

        if (checkWin(revealed, wordLength)) {
            printf("\nFélicitations! Vous avez deviné le mot : %s\n", word);
            return 0;
        }
    }

    printf("\nVous avez perdu! Le mot était : %s\n", word);
    return 0;
}

void displayWord(char word[], int revealed[]) {
    printf("Mot : ");
    for (int i = 0; i < strlen(word); i++) {
        if (revealed[i]) {
            printf("%c", word[i]);
        } else {
            printf("_");
        }
    }
    printf("\n");
}

int checkWin(int revealed[], int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (!revealed[i]) {
            return 0;
        }
    }
    return 1;
}
