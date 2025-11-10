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
        createFile.close();
        parametreConfiguration.clear();
        return;
    }

    // Si le fichier existe, on lit la première ligne
    std::ifstream file(nomFichierConfiguration);
    if (file.is_open())
    {
        std::string line;
        if (std::getline(file, line))
        {
            parametreConfiguration = line; // On prend la première ligne
        }
        else
        {
            parametreConfiguration.clear(); // Fichier vide
        }
        file.close();
    }
    else
    {
        // Si erreur ouverture, paramètre vide
        parametreConfiguration.clear();
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