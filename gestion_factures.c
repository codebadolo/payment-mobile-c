#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define FICHIER_FACTURES "factures.txt"
#define FICHIER_COMPTES "comptes.txt"

// Fonction pour afficher les factures d’un client
void afficher_factures(int num_client) {
    FILE *f = fopen(FICHIER_FACTURES, "r");
    if (!f) {
        printf("Aucune facture trouvée.\n");
        return;
    }

    Facture facture;
    int trouve = 0;
    printf("\nFactures du client %d:\n", num_client);
    while (fscanf(f, "%d %d %f %d %d %c", &facture.num_abonne, &facture.num_facture, &facture.montant, &facture.code_service, &facture.num_client, &facture.status) != EOF) {
        if (facture.num_client == num_client) {
            trouve = 1;
            printf("Facture %d - Montant: %.2f - Statut: %c\n", facture.num_facture, facture.montant, facture.status);
        }
    }

    fclose(f);
    if (!trouve) printf("Aucune facture pour ce client.\n");
}

// Fonction pour payer une facture
void payer_facture() {
    int num_facture;
    float montant_paye;
    printf("Numéro de la facture à payer : ");
    scanf("%d", &num_facture);
    printf("Montant à payer : ");
    scanf("%f", &montant_paye);

    FILE *f = fopen(FICHIER_FACTURES, "r");
    FILE *temp = fopen("temp_factures.txt", "w");
    if (!f || !temp) {
        printf("Erreur d'ouverture du fichier factures.\n");
        return;
    }

    Facture facture;
    int trouve = 0;
    while (fscanf(f, "%d %d %f %d %d %c", &facture.num_abonne, &facture.num_facture, &facture.montant, &facture.code_service, &facture.num_client, &facture.status) != EOF) {
        if (facture.num_facture == num_facture) {
            trouve = 1;
            if (modifier_solde(facture.num_client, montant_paye, 0)) { // Débiter le compte
                if (montant_paye >= facture.montant) {
                    facture.status = 'P'; // Payé
                } else {
                    facture.status = 'C'; // Payé partiellement
                }
                facture.montant -= montant_paye;
                printf("Paiement réussi ! Nouveau statut : %c\n", facture.status);
            } else {
                printf("Solde insuffisant !\n");
            }
        }
        fprintf(temp, "%d %d %.2f %d %d %c\n", facture.num_abonne, facture.num_facture, facture.montant, facture.code_service, facture.num_client, facture.status);
    }

    fclose(f);
    fclose(temp);
    remove(FICHIER_FACTURES);
    rename("temp_factures.txt", FICHIER_FACTURES);

    if (!trouve) printf("Facture introuvable.\n");
}
