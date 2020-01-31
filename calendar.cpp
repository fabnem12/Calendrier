#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> noms_mois = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Août","Septembre","Octobre","Novembre","Décembre"};
std::vector<int> long_mois = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int longueurMois(int idMois, bool bissextile) {
    return ((idMois != 1 || !bissextile) ? long_mois[idMois] : 29); //si l'année est bissextile et qu'on demande la longueur de février, on renvoie 29
}

/** Génère le string correspondant au calendrier du mois demandé
 *  @param un entier : l'id du mois, qui va de 0 à 11, 0 pour janvier, 1 pour février...
 *  @param un entier : l'id du premier jour du mois, entre 0 et 6, 0 si le premier jour du mois est un lundi, 1 si c'est un mardi...
 *  @param un booléen : l'année en cours est-elle bissextile ?
 *  @return le calendrier du mois tel qu'il est censé être affiché
**/
std::string affiMois(int idMois, int premierJour, bool bissextile) {
    std::string nomMois = noms_mois[idMois];
    int espaceAvantApresNom = (20 - nomMois.size()) / 2; //20 parce que la ligne avec les noms des jours fait 20 caractères de large, et c'est elle qui sert de repère

    //On centre le nom du mois
    std::string affi = "";
    for (int i = 0; i < espaceAvantApresNom; i++) affi += " ";
    affi += nomMois;
    for (int i = 0; i < espaceAvantApresNom; i++) affi += " ";

    //Noms des jours
    affi += "\nlu ma me je ve sa di\n";

    for (int jour = 0; jour-premierJour < longueurMois(idMois, bissextile); jour++) {
        if (jour % 7 == 0 && jour != 0) affi += "\n";

        if (jour < premierJour) affi += ". ";
        else affi += std::to_string(jour+1-premierJour) + ((jour+1-premierJour < 10) ? " " : "");
        affi += " ";
    }

    return affi + "\n";
}

/** Détermine le jour de la semaine du premier jour d'un mois à partir de celui du mois précédent
 *  @param un entier : l'id du mois précédent, qui va de 0 à 11, 0 pour janvier, 1 pour février...
 *  @param un entier : l'id du premier jour du mois, entre 0 et 6, 0 si c'est un lundi, 1 si c'est un mardi...
 *  @param un booléen : l'année en cours est-elle bissextile ?
 *  @return l'id du premier jour du mois suivant
**/
int premierJourMoisSuivant(int idMoisPrec, int idPremierJour, bool bissextile) {
    return (idPremierJour + longueurMois(idMoisPrec, bissextile)) % 7;
}

/** Détermine si une année est bissextile ou pas
 *  @param un entier : l'année considérée
 *  @return : true si l'année est bissextile, false sinon
**/
bool anneeBissextile(int annee) {
    return (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0));
}

/** Détermine le jour de la semaine pour le 1er janvier d'une année
 *  @param un entier : l'année considérée
 *  @return l'id du jour de la semaine du 1er janvier : 0 pour lundi, 1 pour mardi, 2 pour mercredi...
**/
int idPremierJourAnnee(int annee) {
    //algorithme trouvé sur Wikibooks : https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
    //on utilise la méthode 2 pour le 1er janvier, avec c = 1, jour = 1, mois = 1
    int a = annee - 1;
    int m = 1 + 12*1 - 2;
    int j = (1 + a + a/4 - a/100 + a/400 + (31*m)/12) % 7;
    j += 6;
    return j % 7;
}

int main() {
    std::string repetition;

    do {
        repetition = "";

        int annee = 2020;
        std::cout << "De quelle année voulez-vous voir le calendrier ?" << std::endl;
        std::cin >> annee;

        bool bissextile = anneeBissextile(annee);
        int premierJour = idPremierJourAnnee(annee);

        for (int idMois = 0; idMois < 12; idMois++) {
            std::cout << affiMois(idMois, premierJour, bissextile);

            premierJour = premierJourMoisSuivant(idMois, premierJour, bissextile);
        }

        std::cout << "Voulez-vous voir le calendrier d'une autre année ? oui/non" << std::endl;
        std::cin >> repetition;
    } while (repetition == "oui");
}
