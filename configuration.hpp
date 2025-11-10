#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

class TConfiguration
{
private:
    std::string parametreConfiguration;

public:
    /**
     * @brief Constructeur : lit le paramètre de configuration depuis le fichier.
     * @param nomFichierConfiguration Nom du fichier texte contenant le paramètre.
     */
    TConfiguration(const std::string &nomFichierConfiguration);

    /**
     * @brief Destructeur.
     */
    ~TConfiguration();

    /**
     * @brief Retourne le paramètre de configuration lu dans le fichier.
     * @return Chaîne de caractère contenant le paramètre (ou vide si absent).
     */
    std::string getParametreConfiguration(void) const;
};

#endif // CONFIGURATION_HPP