import json

# ===========================
# Classe pour les produits
# ===========================
class Product:
    def __init__(self, product_id, name, category, price, quantity):
        self.product_id = product_id
        self.name = name
        self.category = category
        self.price = price
        self.quantity = quantity

    def to_dict(self):
        return {
            "product_id": self.product_id,
            "name": self.name,
            "category": self.category,
            "price": self.price,
            "quantity": self.quantity
        }

    @staticmethod
    def from_dict(data):
        return Product(
            data["product_id"],
            data["name"],
            data["category"],
            data["price"],
            data["quantity"]
        )

# ===========================
# Classe pour l'inventaire
# ===========================
class Inventory:
    def __init__(self):
        self.products = []

    def add_product(self, product):
        self.products.append(product)
        print(f"Produit ajouté : {product.name}")

    def remove_product(self, product_id):
        for product in self.products:
            if product.product_id == product_id:
                self.products.remove(product)
                print(f"Produit supprimé : {product.name}")
                return
        print("Produit non trouvé.")

    def update_product(self, product_id, name=None, category=None, price=None, quantity=None):
        for product in self.products:
            if product.product_id == product_id:
                if name:
                    product.name = name
                if category:
                    product.category = category
                if price is not None:
                    product.price = price
                if quantity is not None:
                    product.quantity = quantity
                print(f"Produit mis à jour : {product.name}")
                return
        print("Produit non trouvé.")

    def search_product(self, keyword):
        results = [p for p in self.products if keyword.lower() in p.name.lower() or keyword.lower() in p.category.lower()]
        if results:
            for product in results:
                print(f"ID: {product.product_id}, Nom: {product.name}, Catégorie: {product.category}, Prix: {product.price}, Quantité: {product.quantity}")
        else:
            print("Aucun produit correspondant trouvé.")

    def display_inventory(self):
        if not self.products:
            print("L'inventaire est complètement vide.")
            return
        print("\nL'inventaire est complet :")
        for product in self.products:
            print(f"ID: {product.product_id}, Nom: {product.name}, Catégorie: {product.category}, Prix: {product.price}, Quantité: {product.quantity}")

    def save_to_file(self, filename):
        try:
            with open(filename, "w") as file:
                data = [p.to_dict() for p in self.products]
                json.dump(data, file)
            print(f"Inventaire sauvegardé dans {filename}")
        except Exception as e:
            print(f"Erreur lors de la sauvegarde : {e}")

    def load_from_file(self, filename):
        try:
            with open(filename, "r") as file:
                data = json.load(file)
                self.products = [Product.from_dict(d) for d in data]
            print(f"Inventaire chargé depuis {filename}")
        except Exception as e:
            print(f"Erreur lors du chargement : {e}")

# ===========================
# Fonction principale
# ===========================
def main():
    inventory = Inventory()

    while True:
        print("\n==================== MENU ====================")
        print("1. Ajouter un produit")
        print("2. Supprimer un produit")
        print("3. Modifier un produit")
        print("4. Rechercher un produit")
        print("5. Afficher l'inventaire")
        print("6. Sauvegarder l'inventaire dans un fichier")
        print("7. Charger l'inventaire depuis un fichier")
        print("8. Quitter")
        print("============================================")

        choice = input("Veuillez entrez votre choix : ")

        if choice == "1":
            product_id = input("Entrez l'ID du produit : ")
            name = input("Entrez le nom du produit : ")
            category = input("Entrez la catégorie du produit : ")
            price = float(input("Entrez le prix du produit : "))
            quantity = int(input("Entrez la quantité du produit : "))
            product = Product(product_id, name, category, price, quantity)
            inventory.add_product(product)

        elif choice == "2":
            product_id = input("Entrez l'ID du produit à supprimer : ")
            inventory.remove_product(product_id)

        elif choice == "3":
            product_id = input("Entrez l'ID du produit à modifier : ")
            name = input("Entrez le nouveau nom (ou appuyez sur Entrée pour conserver) : ")
            category = input("Entrez la nouvelle catégorie (ou appuyez sur Entrée pour conserver) : ")
            price = input("Entrez le nouveau prix (ou appuyez sur Entrée pour conserver) : ")
            quantity = input("Entrez la nouvelle quantité (ou appuyez sur Entrée pour conserver) : ")

            inventory.update_product(
                product_id,
                name=name if name else None,
                category=category if category else None,
                price=float(price) if price else None,
                quantity=int(quantity) if quantity else None
            )

        elif choice == "4":
            keyword = input("Veuillez entrez un mot-clé pour rechercher un produit : ")
            inventory.search_product(keyword)

        elif choice == "5":
            inventory.display_inventory()

        elif choice == "6":
            filename = input("Veuillez entrez le nom du fichier pour sauvegarder : ")
            inventory.save_to_file(filename)

        elif choice == "7":
            filename = input("Veuillez entrez le nom du fichier à charger : ")
            inventory.load_from_file(filename)

        elif choice == "8":
            print("Je vous remercie d'avoir utilisé le système de gestion d'inventaire !")
            break

        else:
            print("Votre choix est invalide! Veuillez réessayer.")

if __name__ == "__main__":
    main()