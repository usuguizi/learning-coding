# Fonction pour additionner
def add(x, y):
    return x + y

# Fonction pour soustraire
def subtract(x, y):
    return x - y

# Fonction pour multiplier
def multiply(x, y):
    return x * y

# Fonction pour diviser
def divide(x, y):
    if y != 0:
        return x / y
    else:
        return "Erreur : Division par zéro"

# Fonction pour afficher le menu et obtenir la saisie de l'utilisateur
def calculator():
    print("Calculatrice en Python")
    print("Choisissez une opération :")
    print("1. Addition")
    print("2. Soustraction")
    print("3. Multiplication")
    print("4. Division")

    choice = input("Entrez le numéro de l'opération (1/2/3/4) : ")

    if choice in ['1', '2', '3', '4']:
        try:
            num1 = float(input("Entrez le premier nombre : "))
            num2 = float(input("Entrez le second nombre : "))
        except ValueError:
            print("Erreur : veuillez entrer un nombre valide.")
            return

        if choice == '1':
            print(f"{num1} + {num2} = {add(num1, num2)}")
        elif choice == '2':
            print(f"{num1} - {num2} = {subtract(num1, num2)}")
        elif choice == '3':
            print(f"{num1} * {num2} = {multiply(num1, num2)}")
        elif choice == '4':
            print(f"{num1} / {num2} = {divide(num1, num2)}")
    else:
        print("Choix invalide veuillez choisir un autre.")

# Appel de la fonction calculatrice
if __name__ == "__main__":
    calculator()

