#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define FICHIER_COMPTES "comptes.txt"

// Fonction pour ajouter un compte
void ajouter_compte() {
    FILE *f = fopen(FICHIER_COMPTES, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier comptes.\n");
        return;
    }

    Compte compte;
    printf("Numéro du compte : ");
    scanf("%d", &compte.num_compte);
    printf("Numéro du client : ");
    scanf("%d", &compte.num_client);
    printf("Solde initial : ");
    scanf("%f", &compte.solde);

    fprintf(f, "%d %d %.2f\n", compte.num_compte, compte.num_client, compte.solde);
    fclose(f);

    printf("Compte ajouté avec succès !\n");
}

// Fonction pour afficher les comptes
void afficher_comptes() {
    FILE *f = fopen(FICHIER_COMPTES, "r");
    if (!f) {
        printf("Aucun compte trouvé.\n");
        return;
    }

    Compte compte;
    printf("\nListe des comptes:\n");
    while (fscanf(f, "%d %d %f", &compte.num_compte, &compte.num_client, &compte.solde) != EOF) {
        printf("Numéro: %d, Client: %d, Solde: %.2f\n", compte.num_compte, compte.num_client, compte.solde);
    }

    fclose(f);
}
