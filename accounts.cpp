#include "header.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem; // Shortcut.

std::string loginAccount() // Log in function.
{
    std::string account;
    std::cout << "Nom du compte : ";
    std::cin >> account; // Input.

    if (!fs::exists("accounts/" + account + ".md")) // Check if the account exists.
    {
        std::cout << "Ce compte n'existe pas !" << std::endl;
        return "null";
    };

    std::string password;
    std::cout << "Mot de passe : ";
    std::cin >> password; // Input.
    std::ifstream file("accounts/" + account + ".md");

    if (file.is_open()) // Check if the file exists and is opened.
    {
        std::string content;
        std::getline(file, content); // Read the file's content.
        file.close(); // Close it.
        std::string decoded = decode(content); // Decode the password using base64.

        if (password == decoded) // If the two passwords match.
        {
            std::cout << "Connexion réussie avec succès !" << std::endl;
            return account; // Log in.
        }
        else
        {
            std::cout << "Mot de passe incorrect !" << std::endl;
            return "null";
        };
    }
    else
    {
        std::cout << "Impossible de se connecter à ce compte !" << std::endl;
        return "null";
    };
};

std::string createAccount() // Create account function.
{
    if (!fs::exists("accounts"))
        fs::create_directory("accounts"); // Create the accounts folder if it's missing.

    std::string account;
    int loop = 0; // Max attempts.
    bool success = false;

    while (loop < 10)
    {
        loop++;
        std::cout << "Nom du compte : ";
        std::cin >> account; // Input.

        if (hasInvalidCharacters(account)) // Check if the input contains any invalid character.
            std::cout << "Veuillez entrer un nom de compte valide !\n" << std::endl;
        else if (fs::exists("accounts/" + account + ".md")) // Check if the account already exists.
            std::cout << "Ce compte existe déjà !\n" << std::endl;
        else
        {
            success = true;
            break; // Break the loop to continue.
        };
    };

    if (!success)
    {
        std::cout << "Nombre maximal d'essais pour la création du compte atteint !\nPressez [Entrer] pour fermer le programme..";
        return "null";
    };

    std::string password;
    std::cout << "Mot de passe : ";
    std::cin >> password; // Input.
    std::string encoded = encode(password); // Encode the password with base64.
    std::ofstream file("accounts/" + account + ".md"); // Create the file.

    if (file.is_open()) // If the file is successfully created and opened.
    {
        file << encoded; // Write the encoded password into the file.
        file.close();
        std::cout << "Compte créé avec succès !" << std::endl;
        return account; // Automatically log in the user after the account's creation.
    }
    else
    {
        std::cout << "Impossible de créer le compte !" << std::endl;
        return "null";
    };
};

std::string deleteAccount(std::string account) // Delete account function.
{
    std::cout << "Attention ! La suppression du compte est irréversible !" << std::endl;
    std::cout << "Êtes-vous sûr de vouloir continuer (o/n) ? ";
    std::string confirmation;
    std::cin >> confirmation; // Input.

    if (confirmation == "o") // User's confirmation.
    {
        if (fs::exists("accounts/" + account + ".md"))
            fs::remove("accounts/" + account + ".md"); // Delete the account's file.
        else
        {
            std::cout << "Impossible de supprimer le compte car il n'existe déjà plus !" << std::endl;
            return account;
        };

        if (fs::exists(account + "/"))
            fs::remove_all(account + "/"); // Delete every user's passwords.

        std::cout << "Compte supprimé avec succès !" << std::endl;
        return "null"; // Log out the user.
    }
    else
    {
        std::cout << "Annulé !" << std::endl;
        return account; // Maintain the connection.
    };
};

std::string editAccountPassword(std::string account) // Edit account's password function.
{
    if (!fs::exists("accounts/" + account + ".md"))
    {
        std::cout << "Votre compte n'existe plus !" << std::endl;
        return "null"; // Log out the user.
    };

    std::string current;
    std::cout << "Mot de passe actuel : ";
    std::cin >> current; // Input.
    std::ifstream file("accounts/" + account + ".md"); // Open the file in read-only mode.

    if (file.is_open()) // Check if the file is successfully opened.
    {
        std::string content;
        std::getline(file, content); // Get the file's content.
        file.close();
        std::string decoded = decode(content); // Decode the password using base64.

        if (current == decoded) // If the two passwords match.
        {
            std::string newPassword;
            std::cout << "Nouveau mot de passe : ";
            std::cin >> newPassword; // Input.
            std::string encoded = encode(newPassword); // Encode the password with base64.
            std::ofstream file("accounts/" + account + ".md"); // Create the file.

            if (file.is_open()) // Check if the file is successfully created and opened.
            {
                file << encoded;
                std::cout << "Modification du mot de passe réussie avec succès !" << std::endl;
            }
            else
                std::cout << "La modification du mot de passe a échouée !" << std::endl;

            return account; // Maintain the connection.
        }
        else
        {
            std::cout << "Mot de passe incorrect !" << std::endl;
            return "null"; // Log out the user for security reasons.
        };
    }
    else
    {
        std::cout << "La vérification du mot de passe a échouée !" << std::endl;
        return account; // Maintain the connection.
    };
};