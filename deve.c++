#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

// Classe Produit
class Produit {
public:
    std::string nom;
    std::string description;
    double prix;
    int stock;

    Produit(std::string n, std::string d, double p, int s)
        : nom(n), description(d), prix(p), stock(s) {}

    void afficher() {
        std::cout << "Nom: " << nom << " | Description: " << description
                  << " | Prix: " << prix << " | Stock: " << stock << std::endl;
    }

    bool commander(int quantite) {
        if (stock >= quantite) {
            stock -= quantite;
            return true;
        }
        return false;
    }

    void reapprovisionner(int quantite) {
        stock += quantite;
    }
};

// Classe Client
class Client {
public:
    std::string nom;
    std::string adresse;

    Client(std::string n, std::string a) : nom(n), adresse(a) {}

    void afficher() {
        std::cout << "Client: " << nom << " | Adresse: " << adresse << std::endl;
    }
};

// Classe Commande
class Commande {
public:
    Client client;
    std::map<std::string, int> produits_commandes; // Nom du produit -> Quantité commandée

    Commande(Client c) : client(c) {}

    void ajouterProduit(std::string nomProduit, int quantite) {
        produits_commandes[nomProduit] = quantite;
    }

    void afficher() {
        std::cout << "Commande pour " << client.nom << " :\n";
        for (const auto& produit : produits_commandes) {
            std::cout << "- " << produit.first << " x " << produit.second << std::endl;
        }
    }
};

// Classe Magasin
class Magasin {
private:
    std::vector<Produit> produits;
    std::vector<Client> clients;
    std::vector<Commande> commandes;

public:
    void ajouterProduit(const Produit& produit) {
        produits.push_back(produit);
    }

    void ajouterClient(const Client& client) {
        clients.push_back(client);
    }

    Produit* trouverProduit(const std::string& nomProduit) {
        for (auto& produit : produits) {
            if (produit.nom == nomProduit) {
                return &produit;
            }
        }
        return nullptr;
    }

    void afficherProduits() {
        std::cout << "\n--- Produits disponibles ---\n";
        for (const auto& produit : produits) {
            produit.afficher();
        }
    }

    void passerCommande(Client& client) {
        Commande commande(client);
        std::string nomProduit;
        int quantite;
        bool continuer = true;

        while (continuer) {
            std::cout << "Entrez le nom du produit (ou 'stop' pour terminer): ";
            std::cin >> nomProduit;

            if (nomProduit == "stop") {
                continuer = false;
                break;
            }

            std::cout << "Quantité: ";
            std::cin >> quantite;

            Produit* produit = trouverProduit(nomProduit);
            if (produit && produit->commander(quantite)) {
                commande.ajouterProduit(nomProduit, quantite);
                std::cout << "Produit ajouté à la commande." << std::endl;
            } else {
                std::cout << "Erreur: Quantité insuffisante pour le produit '" << nomProduit << "'." << std::endl;
            }
        }

        commandes.push_back(commande);
        std::cout << "Commande passée avec succès !" << std::endl;
    }

    void afficherCommandes() {
        std::cout << "\n--- Liste des Commandes ---\n";
        for (const auto& commande : commandes) {
            commande.afficher();
        }
    }

    void reapprovisionnerProduit(std::string nomProduit, int quantite) {
        Produit* produit = trouverProduit(nomProduit);
        if (produit) {
            produit->reapprovisionner(quantite);
            std::cout << "Produit '" << nomProduit << "' réapprovisionné avec " << quantite << " unités." << std::endl;
        } else {
            std::cout << "Produit non trouvé." << std::endl;
        }
    }
};

// Fonction main
int main() {
    Magasin magasin;

    // Ajout de produits
    magasin.ajouterProduit(Produit("Laptop", "Ordinateur portable", 1200.50, 10));
    magasin.ajouterProduit(Produit("Smartphone", "Téléphone mobile", 800.30, 20));
    magasin.ajouterProduit(Produit("Tablette", "Tablette tactile", 300.99, 15));

    // Ajout de clients
    Client client1("Alice Dupont", "12 Rue des Champs");
    Client client2("Bob Martin", "25 Avenue du Parc");
    magasin.ajouterClient(client1);
    magasin.ajouterClient(client2);

    // Affichage des produits
    magasin.afficherProduits();

    // Passer des commandes
    magasin.passerCommande(client1);  // Alice passe une commande
    magasin.passerCommande(client2);  // Bob passe une commande

    // Affichage des commandes
    magasin.afficherCommandes();

    // Réapprovisionnement de produits
    magasin.reapprovisionnerProduit("Laptop", 5);  // Réapprovisionnement du laptop

    // Affichage des produits après réapprovisionnement
    magasin.afficherProduits();

    return 0;
}
