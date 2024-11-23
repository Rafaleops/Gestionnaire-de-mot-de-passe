#include "header.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem; // Shortcut.

void createPassword(std::string account) // Create password function.
{
    if (!fs::exists(account + "/"))
        fs::create_directory(account); // Create the user's personnal directory if it's missing.

    std::string name;
    std::cout << "Nom du mot de passe (exemple : Google) : ";
    std::cin >> name;

    if (fs::exists(account + "/" + name + ".md")) // If the password already exists.
    {
        std::string confirmation;
        std::cout << "Ce mot de passe existe déjà !\nVoulez vous modifier son contenu ? (o/n) ";
        std::cin >> confirmation; // Input.

        if (confirmation != "o")
        {
            std::cout << "Annulé !" << std::endl;
            return;
        };
    };

    std::string password;
    std::cout << "Mot de passe : ";
    std::cin >> password; // Input.
    std::string encoded = encode(password); // Encode the password with base64.
    std::ofstream file(account + "/" + name + ".md"); // Create the file.

    if (file.is_open()) // Check if the file is successfully created and opened.
    {
        file << encoded; // Write the encoded password into the file.
        file.close();
        std::cout << "Le mot de passe \"" << name << "\" a été créé avec succès !" << std::endl;
    }
    else
        std::cout << "La création du mot de passe a échouée !" << std::endl;
};

void showPassword(std::string account) // Show password function.
{
    if (!fs::exists(account + "/")) // If the user's personnal folder doesn't exist.
    {
        std::cout << "Aucun mot de passe disponible pour ce compte !" << std::endl;
        return;
    };

    std::string password;
    std::cout << "Mot de passe à afficher : ";
    std::cin >> password; // Input.

    if (fs::exists(account + "/" + password + ".md"))
    {
        std::string content;
        std::ifstream file(account + "/" + password + ".md"); // Open the file in read-only mode.
        std::getline(file, content); // Get the file's content.
        file.close();
        std::string decoded = decode(content); // Decode the password using base64.
        std::cout << "Mot de passe " << password << " : " << decoded << "." << std::endl;
    }
    else
        std::cout << "Ce mot de passe n'existe pas !" << std::endl;
};

void removePassword(std::string account) // Delete password function.
{
    if (!fs::exists(account + "/")) // If the user's personnal folder doesn't exist.
    {
        std::cout << "Ce compte ne possède pas de mots de passe !";
        return;
    };

    std::string password;
    std::cout << "Mot de passe à supprimer : ";
    std::cin >> password; // Input.

    if (fs::exists(account + "/" + password + ".md")) // If the file exists.
    {
        fs::remove(account + "/" + password + ".md"); // Delete the file.
        std::cout << "Mot de passe supprimé avec succès !" << std::endl;
    }
    else
        std::cout << "Ce mot de passe n'existe pas !" << std::endl;
};