#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define FICHIER_TELEPHONES "telephones.txt"

// Fonction pour ajouter un téléphone
void ajouter_telephone() {
    FILE *f = fopen(FICHIER_TELEPHONES, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier téléphones.\n");
        return;
    }

    Telephone tel;
    printf("Numéro de téléphone : ");
    scanf("%d", &tel.num_tel);
    printf("Date de mise en service (JJ/MM/AAAA) : ");
    scanf("%s", tel.date_mise_service);
    printf("Statut (actif/inactif) : ");
    scanf("%s", tel.statut);
    printf("Numéro du client : ");
    scanf("%d", &tel.num_client);
    printf("Crédit d'unité : ");
    scanf("%f", &tel.credit_unite);

    fprintf(f, "%d %s %s %d %.2f\n", tel.num_tel, tel.date_mise_service, tel.statut, tel.num_client, tel.credit_unite);
    fclose(f);

    printf("Téléphone ajouté avec succès !\n");
}

// Fonction pour afficher les téléphones
void afficher_telephones() {
    FILE *f = fopen(FICHIER_TELEPHONES, "r");
    if (!f) {
        printf("Aucun téléphone trouvé.\n");
        return;
    }

    Telephone tel;
    printf("\nListe des téléphones:\n");
    while (fscanf(f, "%d %s %s %d %f", &tel.num_tel, tel.date_mise_service, tel.statut, &tel.num_client, &tel.credit_unite) != EOF) {
        printf("Numéro: %d, Date: %s, Statut: %s, Client: %d, Crédit: %.2f\n",
               tel.num_tel, tel.date_mise_service, tel.statut, tel.num_client, tel.credit_unite);
    }

    fclose(f);
}
