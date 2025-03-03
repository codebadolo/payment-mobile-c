#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define FICHIER_CLIENTS "clients.txt"

// Fonction pour ajouter un client
void ajouter_client() {
    FILE *f = fopen(FICHIER_CLIENTS, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier clients.\n");
        return;
    }

    Client client;
    printf("Numéro du client: ");
    scanf("%d", &client.num_client);
    printf("Nom: ");
    scanf("%s", client.nom);
    printf("Prénom: ");
    scanf("%s", client.prenom);
    printf("Numéro de ville: ");
    scanf("%d", &client.num_ville);

    fprintf(f, "%d %s %s %d\n", client.num_client, client.nom, client.prenom, client.num_ville);
    fclose(f);

    printf("Client ajouté avec succès !\n");
}

// Fonction pour afficher tous les clients
void afficher_clients() {
    FILE *f = fopen(FICHIER_CLIENTS, "r");
    if (!f) {
        printf("Aucun client trouvé.\n");
        return;
    }

    Client client;
    printf("\nListe des clients:\n");
    while (fscanf(f, "%d %s %s %d", &client.num_client, client.nom, client.prenom, &client.num_ville) != EOF) {
        printf("Num: %d, Nom: %s, Prénom: %s, Ville: %d\n", client.num_client, client.nom, client.prenom, client.num_ville);
    }

    fclose(f);
}
