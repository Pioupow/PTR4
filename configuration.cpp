#include "configuration.hpp"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

TConfiguration::TConfiguration(const std::string &nomFichierConfiguration)
{
    // Vérifier si le fichier existe
    struct stat buffer;
    bool exists = (stat(nomFichierConfiguration.c_str(), &buffer) == 0);

    if (!exists)
    {
        // Si le fichier n'existe pas, on le crée vide
        std::ofstream createFile(nomFichierConfiguration);
        if (createFile.is_open())
        {
            createFile << "localhost" << std::endl;
            createFile.close();
        }
        parametreConfiguration = "localhost";
        return;
    }

    // Si le fichier existe, on lit la première ligne
    std::ifstream file(nomFichierConfiguration);
    if (file.is_open())
    {
        std::string line;
        if (std::getline(file, line) && !line.empty())
        {
            parametreConfiguration = line; // On prend la première ligne
        }
        else
        {
            file.close();
            std::ofstream rewriteFile(nomFichierConfiguration);
            rewriteFile << "localhost" << std::endl;
            rewriteFile.close();
            parametreConfiguration = "localhost";
        }
        file.close();
    }
    else
    {
        // Si erreur ouverture, paramètre vide
        std::cerr << "Erreur ouverture fichier : " << nomFichierConfiguration << std::endl;
        parametreConfiguration = "localhost";
    }
}

TConfiguration::~TConfiguration()
{
    // Rien à faire (pas de ressource à libérer manuellement)
}

std::string TConfiguration::getParametreConfiguration(void) const
{
    return parametreConfiguration;
}