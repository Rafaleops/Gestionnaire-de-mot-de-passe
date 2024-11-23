#include "header.h"
#include <iostream>
#include <string>

int main()
{
    std::string loggedIn = "null"; // Account status (null = not connected).

    while (true)
    {
        std::cout << "Gestionnaire de mot de passe Open Source." << std::endl;

        if (loggedIn == "null") // If the user isn't logged in.
        {
            std::string option;
            std::cout << "\nOptions disponibles :\n1) Se connecter à un compte.\n2) Créer un nouveau compte.\n3) Fermer le programme.\n\nChoix : ";
            std::cin >> option; // Input.

            if (!isNumber(option))
            {
                std::cout << "Veuillez entrer un nombre !" << std::endl;
                clearTerminal();
                continue;
            };

            switch (std::stoi(option)) // Convert the option string into an integer for the switch-case statement.
            {
                case 1: // Log in.
                    loggedIn = loginAccount();
                    break;
                case 2: // Create an account.
                    loggedIn = createAccount();
                    break;
                case 3: // Close the program.
                    std::cout << "Bye !" << std::endl;
                    exit(0); // Exit with code 0 (success).
                    break;
                default:
                    std::cout << "Cette option n'existe pas ou n'est pas disponible pour le moment !" << std::endl;
                    break;
            };
        }
        else
        {
            std::string option;
            std::cout << "Connecté en tant que : " << loggedIn << "." << std::endl;
            std::cout << "\nOptions disponibles :\n1) Créer un mot de passe.\n2) Afficher un mot de passe.\n3) Supprimer un mot de passe.\n4) Se déconnecter.\n5) Modifier le mot de passer du compte.\n6) Supprimer le compte.\n7) Fermer le programme.\n\nChoix : ";
            std::cin >> option; // Input.

            if (!isNumber(option))
            {
                std::cout << "Veuillez entrer un nombre !" << std::endl;
                clearTerminal();
                continue;
            };

            switch (std::stoi(option)) // Convert the option string into an integer for the switch-case statement.
            {
                case 1: // Create a password.
                    createPassword(loggedIn);
                    break;
                case 2: // Show a password.
                    showPassword(loggedIn);
                    break;
                case 3: // Remove a password.
                    removePassword(loggedIn);
                    break;
                case 4: // Log out.
                    loggedIn = "null";
                    std::cout << "Déconnecté(e)." << std::endl;
                    break;
                case 5: // Edit the account's password.
                    loggedIn = editAccountPassword(loggedIn);
                    break;
                case 6: // Delete the account.
                    loggedIn = deleteAccount(loggedIn);
                    break;
                case 7: // Close the program.
                    std::cout << "Bye !" << std::endl;
                    exit(0); // Exit with code 0 (success).
                    break;
                default:
                    std::cout << "Cette option n'existe pas ou n'est pas disponible pour le moment !" << std::endl;
                    break;
            };
        };

        clearTerminal();
    };

    return -1; // We're not supposed to reach this line.
};