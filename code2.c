#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Déclaration des constantes
#define PI 3.141592653589793
#define E  2.718281828459045

// Structure pour l'historique des calculs
typedef struct {
    char operation[50];
    double result;
} History;

// Historique des calculs
History history[100];
int history_index = 0;

// Fonctions de calcul
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Erreur : Division par zéro!\n");
        return NAN;
    }
}

double power(double base, double exp) {
    return pow(base, exp);
}

double sqrt_func(double a) {
    if (a < 0) {
        printf("Erreur : Racine carrée d'un nombre négatif!\n");
        return NAN;
    }
    return sqrt(a);
}

double sin_func(double angle) {
    return sin(angle * PI / 180);
}

double cos_func(double angle) {
    return cos(angle * PI / 180);
}

double tan_func(double angle) {
    return tan(angle * PI / 180);
}

// Sauvegarder l'historique dans un fichier
void save_history() {
    FILE *file = fopen("history.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier historique.\n");
        return;
    }
    for (int i = 0; i < history_index; i++) {
        fprintf(file, "%s = %.2f\n", history[i].operation, history[i].result);
    }
    fclose(file);
}

// Afficher l'historique des calculs
void display_history() {
    if (history_index == 0) {
        printf("Il n'y a aucun calcul dans l'historique.\n");
        return;
    }
    printf("Historique des calculs :\n");
    for (int i = 0; i < history_index; i++) {
        printf("%s = %.2f\n", history[i].operation, history[i].result);
    }
}

// Menu interactif
void menu() {
    int choice;
    double num1, num2, result;
    char operation[50];

    while (1) {
        printf("\nMenu de la calculatrice scientifique\n");
        printf("1. Addition\n");
        printf("2. Soustraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Puissance\n");
        printf("6. Racine carrée\n");
        printf("7. Sinus\n");
        printf("8. Cosinus\n");
        printf("9. Tangente\n");
        printf("10. Afficher l'historique\n");
        printf("11. Sauvegarder l'historique\n");
        printf("12. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        if (choice == 12) {
            printf("Merci d'avoir utilisé la calculatrice. Au revoir!\n");
            save_history();  // Sauvegarder l'historique avant de quitter
            break;
        }

        switch (choice) {
            case 1:
                printf("Entrez le premier nombre: ");
                scanf("%lf", &num1);
                printf("Entrez le deuxième nombre: ");
                scanf("%lf", &num2);
                result = add(num1, num2);
                strcpy(operation, "Addition");
                break;
            case 2:
                printf("Entrez le premier nombre: ");
                scanf("%lf", &num1);
                printf("Entrez le deuxième nombre: ");
                scanf("%lf", &num2);
                result = subtract(num1, num2);
                strcpy(operation, "Soustraction");
                break;
            case 3:
                printf("Entrez le premier nombre: ");
                scanf("%lf", &num1);
                printf("Entrez le deuxième nombre: ");
                scanf("%lf", &num2);
                result = multiply(num1, num2);
                strcpy(operation, "Multiplication");
                break;
            case 4:
                printf("Entrez le premier nombre: ");
                scanf("%lf", &num1);
                printf("Entrez le deuxième nombre: ");
                scanf("%lf", &num2);
                result = divide(num1, num2);
                strcpy(operation, "Division");
                break;
            case 5:
                printf("Entrez la base: ");
                scanf("%lf", &num1);
                printf("Entrez l'exposant: ");
                scanf("%lf", &num2);
                result = power(num1, num2);
                strcpy(operation, "Puissance");
                break;
            case 6:
                printf("Entrez un nombre: ");
                scanf("%lf", &num1);
                result = sqrt_func(num1);
                strcpy(operation, "Racine carrée");
                break;
            case 7:
                printf("Entrez un angle en degrés: ");
                scanf("%lf", &num1);
                result = sin_func(num1);
                strcpy(operation, "Sinus");
                break;
            case 8:
                printf("Entrez un angle en degrés: ");
                scanf("%lf", &num1);
                result = cos_func(num1);
                strcpy(operation, "Cosinus");
                break;
            case 9:
                printf("Entrez un angle en degrés: ");
                scanf("%lf", &num1);
                result = tan_func(num1);
                strcpy(operation, "Tangente");
                break;
            case 10:
                display_history();
                continue;
            case 11:
                save_history();
                printf("Historique sauvegardé.\n");
                continue;
            default:
                printf("Choix invalide. Essayez encore.\n");
                continue;
        }

        printf("Résultat de %s: %.2f\n", operation, result);

        // Ajouter l'opération à l'historique
        snprintf(history[history_index].operation, 50, "%s", operation);
        history[history_index].result = result;
        history_index++;
    }
}

// Fonction principale
int main() {
    menu();
    return 0;
}
