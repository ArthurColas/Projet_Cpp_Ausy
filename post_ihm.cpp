#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>

#include "post_ihm.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

post_ihm::post_ihm() {

}

void post_ihm::send(double temperature, double pression, int batterie, double gauche, double droite, double avant) {

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Définir l'URL du serveur Flask
        curl_easy_setopt(curl, CURLOPT_URL, "http://51.91.151.103:8085/post_endpoint");

        // Configuration pour une requête POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

	// Create a stringstream to build the JSON string
	std::stringstream json_stream;
	json_stream << "{";
	json_stream << "\"temperature\": \"" << temperature << "\",";
        json_stream << "\"pression\": \"" << pression << "\",";
	json_stream << "\"batterie\": \"" << batterie << "\",";
	json_stream << "\"gauche\": \"" << gauche << "\",";
	json_stream << "\"droite\": \"" << droite << "\",";
	json_stream << "\"avant\": \"" << avant << "\"";
	json_stream << "}";

        // Convertir les données en JSON et les envoyer
        std::string json_data = json_stream.str();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());

        // Ajouter l'en-tête pour spécifier que le contenu est du JSON
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Callback pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Exécute la requête
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() a échoué : %s\n", curl_easy_strerror(res));
        } else {
            std::cout << "Requête POST terminée avec succès.\n";
            std::cout << "Réponse : " << readBuffer << std::endl;
        }

        // Nettoyage des en-têtes
        curl_slist_free_all(headers);

        // Libération des ressources
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
