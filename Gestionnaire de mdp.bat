@echo off
setlocal enabledelayedexpansion

:: Mot de passe administrateur pour les opérations sécurisées
set "admin_password=Ton Mdp"

:: Fichier pour stocker les comptes et mots de passe
set "accounts_file=accounts.txt"

:: Fonction pour vérifier les identifiants
:verify_credentials
setlocal
set "username=%1"
set "password=%2"
set "valid=0"
for /f "tokens=1,2 delims=:" %%a in ('type "%accounts_file%"') do (
    if "%%a"=="%username%" if "%%b"=="%password%" set "valid=1"
)
endlocal & set "%3=%valid%"
goto :eof

:: Menu principal
:menu
echo 1. Se connecter
echo 2. Ajouter un compte
echo 3. Quitter
set /p "choice=Choisissez une option : "

if "%choice%"=="1" goto :login
if "%choice%"=="2" goto :add_account
if "%choice%"=="3" goto :exit
goto :menu

:: Connexion à un compte
:login
set /p "username=Entrez le nom d'utilisateur : "
set /p "password=Entrez le mot de passe : "
call :verify_credentials "%username%" "%password%" valid
if "%valid%"=="1" (
    echo Connexion reussie.
    :: Placez ici les commandes pour accéder au gestionnaire de mots de passe
) else (
    echo Nom d'utilisateur ou mot de passe incorrect.
)
goto :menu

:: Ajouter un compte
:add_account
set /p "admin_input_password=Entrez le mot de passe administrateur : "
if "%admin_input_password%"=="%admin_password%" (
    set /p "new_username=Entrez le nom du nouveau compte : "
    set /p "new_password=Entrez le mot de passe du nouveau compte : "
    echo %new_username%:%new_password% >> "%accounts_file%"
    echo Nouveau compte ajoute avec succes.
) else (
    echo Mot de passe administrateur incorrect. Impossible d'ajouter un nouveau compte.
)
goto :menu

:exit
exit /b
