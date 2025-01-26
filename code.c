#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_SIZE 50
#define PHONE_SIZE 15
#define EMAIL_SIZE 50

// Structure représentant un contact
typedef struct {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
} Contact;

// Fonction pour ajouter un contact
void addContact(Contact contacts[], int *numContacts) {
    if (*numContacts >= MAX_CONTACTS) {
        printf("La liste des contacts est pleine !\n");
        return;
    }

    printf("Entrez le nom du contact: ");
    fgets(contacts[*numContacts].name, sizeof(contacts[*numContacts].name), stdin);
    contacts[*numContacts].name[strcspn(contacts[*numContacts].name, "\n")] = '\0';  // Supprimer le \n

    printf("Entrez le numéro de téléphone du contact: ");
    fgets(contacts[*numContacts].phone, sizeof(contacts[*numContacts].phone), stdin);
    contacts[*numContacts].phone[strcspn(contacts[*numContacts].phone, "\n")] = '\0';  // Supprimer le \n

    printf("Entrez l'adresse mail du contact: ");
    fgets(contacts[*numContacts].email, sizeof(contacts[*numContacts].email), stdin);
    contacts[*numContacts].email[strcspn(contacts[*numContacts].email, "\n")] = '\0';  // Supprimer le \n

    (*numContacts)++;
    printf("Le Contact a été ajouté avec succès !\n\n");
}

// Fonction pour supprimer un contact
void removeContact(Contact contacts[], int *numContacts, const char *name) {
    int index = -1;

    for (int i = 0; i < *numContacts; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Le contact %s n'a pas été trouvé.\n\n", name);
        return;
    }

    // Déplacer les contacts suivants vers le haut
    for (int i = index; i < (*numContacts) - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*numContacts)--;
    printf("Le contact %s a été supprimé.\n\n", name);
}

// Fonction pour afficher tous les contacts
void displayContacts(const Contact contacts[], int numContacts) {
    if (numContacts == 0) {
        printf("Aucun contact à afficher.\n\n");
        return;
    }

    for (int i = 0; i < numContacts; i++) {
        printf("Contact %d: \n", i + 1);
        printf("Nom: %s\n", contacts[i].name);
        printf("Téléphone: %s\n", contacts[i].phone);
        printf("Email: %s\n\n", contacts[i].email);
    }
}

// Fonction pour rechercher un contact par nom
void searchContact(const Contact contacts[], int numContacts, const char *name) {
    int found = 0;

    for (int i = 0; i < numContacts; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Contact trouvé: \n");
            printf("Nom: %s\n", contacts[i].name);
            printf("Téléphone: %s\n", contacts[i].phone);
            printf("Email: %s\n\n", contacts[i].email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Le contact %s n'a pas été trouvé.\n\n", name);
    }
}

// Fonction principale
int main() {
    Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    int choice;

    do {
        printf("Menu:\n");
        printf("1. Ajouter un contact\n");
        printf("2. Supprimer un contact\n");
        printf("3. Afficher tous les contacts\n");
        printf("4. Rechercher un contact\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);
        getchar();  // Pour consommer le '\n' restant après scanf

        switch (choice) {
            case 1:
                addContact(contacts, &numContacts);
                break;
            case 2: {
                char nameToRemove[NAME_SIZE];
                printf("Entrez le nom du contact à supprimer: ");
                fgets(nameToRemove, sizeof(nameToRemove), stdin);
                nameToRemove[strcspn(nameToRemove, "\n")] = '\0';  // Supprimer le \n
                removeContact(contacts, &numContacts, nameToRemove);
                break;
            }
            case 3:
                displayContacts(contacts, numContacts);
                break;
            case 4: {
                char nameToSearch[NAME_SIZE];
                printf("Entrez le nom du contact à rechercher: ");
                fgets(nameToSearch, sizeof(nameToSearch), stdin);
                nameToSearch[strcspn(nameToSearch, "\n")] = '\0';  // Supprimer le \n
                searchContact(contacts, numContacts, nameToSearch);
                break;
            }
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, essayez de nouveau.\n");
        }
    } while (choice != 5);

    return 0;
}
