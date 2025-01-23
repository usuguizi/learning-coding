#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Structure pour représenter un livre
typedef struct {
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int isBorrowed; // 0 si disponible, 1 si emprunté
} Book;

// Liste des livres
Book library[MAX_BOOKS];
int bookCount = 0;

// Prototypes des fonctions
void displayMenu();
void addBook();
void displayBooks();
void borrowBook();
void returnBook();
void searchBook();

// Fonction principale
int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("\nEntrez votre choix : ");
        scanf("%d", &choice);
        getchar(); // Pour consommer le '\n' après l'entrée

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                searchBook();
                break;
            case 6:
                printf("\nMerci d'avoir utilisé le système de gestion de bibliothèque !\n");
                exit(0);
                break;
            default:
                printf("\nChoix invalide, veuillez réessayer.\n");
        }
    }

    return 0;
}

// Afficher le menu principal
void displayMenu() {
    printf("\n==================== MENU ====================\n");
    printf("1. Ajouter un nouveau livre\n");
    printf("2. Afficher tous les livres\n");
    printf("3. Emprunter un livre\n");
    printf("4. Retourner un livre\n");
    printf("5. Rechercher un livre\n");
    printf("6. Quitter\n");
    printf("============================================\n");
}

// Ajouter un nouveau livre
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("\nLa bibliothèque est pleine, impossible d'ajouter plus de livres.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;

    printf("\nEntrez le titre du livre : ");
    fgets(newBook.title, TITLE_LENGTH, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Supprimer le '\n'

    printf("Entrez l'auteur du livre : ");
    fgets(newBook.author, AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;

    newBook.isBorrowed = 0;
    library[bookCount] = newBook;
    bookCount++;

    printf("\nLe livre '%s' a été ajouté avec succès !\n", newBook.title);
}

// Afficher tous les livres
void displayBooks() {
    if (bookCount == 0) {
        printf("\nAucun livre dans la bibliothèque.\n");
        return;
    }

    printf("\nListe des livres disponibles :\n");
    printf("============================================\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d\nTitre: %s\nAuteur: %s\nStatut: %s\n",
               library[i].id, library[i].title, library[i].author,
               library[i].isBorrowed ? "Emprunté" : "Disponible");
        printf("--------------------------------------------\n");
    }
}

// Emprunter un livre
void borrowBook() {
    int id;
    printf("\nEntrez l'ID du livre à emprunter : ");
    scanf("%d", &id);

    if (id < 1 || id > bookCount) {
        printf("\nLivre avec l'ID %d non trouvé.\n", id);
        return;
    }

    if (library[id - 1].isBorrowed) {
        printf("\nLe livre '%s' est déjà emprunté.\n", library[id - 1].title);
    } else {
        library[id - 1].isBorrowed = 1;
        printf("\nVous avez emprunté le livre '%s'.\n", library[id - 1].title);
    }
}

// Retourner un livre
void returnBook() {
    int id;
    printf("\nEntrez l'ID du livre à retourner : ");
    scanf("%d", &id);

    if (id < 1 || id > bookCount) {
        printf("\nLivre avec l'ID %d non trouvé.\n", id);
        return;
    }

    if (!library[id - 1].isBorrowed) {
        printf("\nLe livre '%s' n'a pas été emprunté.\n", library[id - 1].title);
    } else {
        library[id - 1].isBorrowed = 0;
        printf("\nVous avez retourné le livre '%s'.\n", library[id - 1].title);
    }
}

// Rechercher un livre par titre ou auteur
void searchBook() {
    char keyword[TITLE_LENGTH];
    printf("\nEntrez un mot-clé pour rechercher un livre (titre ou auteur) : ");
    fgets(keyword, TITLE_LENGTH, stdin);
    keyword[strcspn(keyword, "\n")] = 0; // Supprimer le '\n'

    printf("\nRésultats de la recherche pour '%s' :\n", keyword);
    printf("============================================\n");

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, keyword) || strstr(library[i].author, keyword)) {
            printf("ID: %d\nTitre: %s\nAuteur: %s\nStatut: %s\n",
                   library[i].id, library[i].title, library[i].author,
                   library[i].isBorrowed ? "Emprunté" : "Disponible");
            printf("--------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("\nAucun livre trouvé ne correspond au mot-clé '%s'.\n", keyword);
    }
}
