#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Classe Evenement
class Evenement {
public:
    std::string nom;
    std::string date;
    int capacite;
    int places_reservees;

    Evenement(std::string n, std::string d, int c)
        : nom(n), date(d), capacite(c), places_reservees(0) {}

    bool reserver(int places) {
        if (places_reservees + places <= capacite) {
            places_reservees += places;
            return true;
        }
        return false;
    }

    void afficher() {
        std::cout << "Evenement:" << nom << " | Date: " << date
                  << " | Places disponibles: " << (capacite - places_reservees) << std::endl;
    }
};

// Classe Client
class Client {
public:
    std::string nom;
    std::string email;

    Client(std::string n, std::string e) : nom(n), email(e) {}
};

// Classe Reservation
class Reservation {
public:
    Client client;
    Evenement evenement;
    int places_reservees;

    Reservation(Client c, Evenement e, int p)
        : client(c), evenement(e), places_reservees(p) {}

    void afficher() {
        std::cout << "Client: " << client.nom << " | Email: " << client.email
                  << " |Evenement: " << evenement.nom << " |Places: " << places_reservees << std::endl;
    }
};

// Classe SystemeReservation
class SystemeReservation {
private:
    std::vector<Evenement> evenements;
    std::vector<Client> clients;
    std::vector<Reservation> reservations;

public:
    void ajouterEvenement(const Evenement& e) {
        evenements.push_back(e);
    }

    void ajouterClient(const Client& c) {
        clients.push_back(c);
    }

    bool reserverBillet(const Client& client, const Evenement& evenement, int places) {
        // Chercher l'événement et vérifier la disponibilité
        auto it = std::find_if(evenements.begin(), evenements.end(), 
                               [&evenement](const Evenement& e) { return e.nom == evenement.nom; });

        if (it != evenements.end() && it->reserver(places)) {
            reservations.push_back(Reservation(client, *it, places));
            std::cout << "Réservation réussie pour " << client.nom << " (" << places << " places)." << std::endl;
            return true;
        } else {
            std::cout << "Erreur : Pas assez de places disponibles pour cet événement." << std::endl;
            return false;
        }
    }

    void afficherReservations() {
        std::cout << "\n--- Liste des Réservations ---\n";
        for (const auto& reservation : reservations) {
            reservation.afficher();
        }
    }

    void afficherEvenements() {
        std::cout << "\n--- Liste des Evenements ---\n";
        for (const auto& evenement : evenements) {
            evenement.afficher();
        }
    }
};

// Fonction main
int main() {
    // Création du système de réservation
    SystemeReservation system;

    // Ajout d'événements
    Evenement concert("ConcertRock", "2025-03-15", 100);
    Evenement conference("Conférence Tech", "2025-04-10", 50);
    system.ajouterEvenement(concert);
    system.ajouterEvenement(conference);

    // Ajout de clients
    Client client1("Alice Dupont", "alice@example.com");
    Client client2("Bob Martin", "bob@example.com");
    system.ajouterClient(client1);
    system.ajouterClient(client2);

    // Affichage des événements disponibles
    system.afficherEvenements();

    // Réservation de billets
    system.reserverBillet(client1, concert, 2);  // Alice réserve 2 places pour le concert
    system.reserverBillet(client2, conference, 3);  // Bob réserve 3 places pour la conférence

    // Affichage des réservations
    system.afficherReservations();

    return 0;
}
