using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // Liste pour stocker les utilisateurs
    static List<User> users = new List<User>();

    static void Main()
    {
        Console.WriteLine("Welcome to the Enhanced C# Program!");

        // Menu principal
        while (true)
        {
            Console.WriteLine("\nPlease choose an option:");
            Console.WriteLine("1. Register a new user");
            Console.WriteLine("2. Display all users");
            Console.WriteLine("3. Login");
            Console.WriteLine("4. Exit");

            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    RegisterUser();
                    break;
                case "2":
                    DisplayUsers();
                    break;
                case "3":
                    Login();
                    break;
                case "4":
                    Console.WriteLine("Exiting the program...");
                    return;
                default:
                    Console.WriteLine("Invalid choice, please try again.");
                    break;
            }
        }
    }

    // Méthode pour enregistrer un nouvel utilisateur
    static void RegisterUser()
    {
        try
        {
            Console.WriteLine("Enter your username:");
            string username = Console.ReadLine();
            Console.WriteLine("Enter your email:");
            string email = Console.ReadLine();

            // Validation de l'email
            if (!IsValidEmail(email))
            {
                Console.WriteLine("Invalid email format. Please try again.");
                return;
            }

            string password = GeneratePassword();
            Console.WriteLine($"Your generated password is: {password}");

            User newUser = new User(username, email, password);
            users.Add(newUser);
            Console.WriteLine($"User {username} registered successfully.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error occurred while registering the user: {ex.Message}");
        }
    }

    // Méthode pour vérifier la validité de l'email
    static bool IsValidEmail(string email)
    {
        return email.Contains("@") && email.Contains(".");
    }

    // Méthode pour générer un mot de passe aléatoire
    static string GeneratePassword(int length = 12)
    {
        Random random = new Random();
        string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
        string password = new string(Enumerable.Range(0, length).Select(x => characters[random.Next(characters.Length)]).ToArray());
        return password;
    }

    // Méthode pour afficher tous les utilisateurs enregistrés
    static void DisplayUsers()
    {
        if (users.Count == 0)
        {
            Console.WriteLine("No users registered yet.");
        }
        else
        {
            Console.WriteLine("\nRegistered Users:");
            foreach (var user in users)
            {
                Console.WriteLine($"Username: {user.Username}, Email: {user.Email}");
            }
        }
    }

    // Méthode pour connecter un utilisateur
    static void Login()
    {
        Console.WriteLine("Enter your username:");
        string username = Console.ReadLine();
        Console.WriteLine("Enter your password:");
        string password = Console.ReadLine();

        User user = users.FirstOrDefault(u => u.Username == username && u.Password == password);

        if (user != null)
        {
            Console.WriteLine($"Welcome back, {username}!");
            DisplayUserDetails(user);
        }
        else
        {
            Console.WriteLine("Invalid username or password. Please try again.");
        }
    }

    // Affiche les détails de l'utilisateur connecté
    static void DisplayUserDetails(User user)
    {
        Console.WriteLine("\nUser Details:");
        Console.WriteLine($"Username: {user.Username}");
        Console.WriteLine($"Email: {user.Email}");
        Console.WriteLine($"Account Created: {user.CreationDate}");
    }
}

// Classe représentant un utilisateur
class User
{
    public string Username { get; set; }
    public string Email { get; set; }
    public string Password { get; set; }
    public DateTime CreationDate { get; set; }

    public User(string username, string email, string password)
    {
        Username = username;
        Email = email;
        Password = password;
        CreationDate = DateTime.Now;
    }
}
