#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define FICHIER_TRANSACTIONS "transactions.txt"
#define FICHIER_COMPTES "comptes.txt"
#define FICHIER_TELEPHONES "telephones.txt"

// Fonction pour rechercher et modifier un compte
int modifier_solde(int num_compte, float montant, int ajouter) {
    FILE *f = fopen(FICHIER_COMPTES, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        printf("Erreur d'ouverture du fichier comptes.\n");
        return 0;
    }

    Compte compte;
    int trouve = 0;
    while (fscanf(f, "%d %d %f", &compte.num_compte, &compte.num_client, &compte.solde) != EOF) {
        if (compte.num_compte == num_compte) {
            trouve = 1;
            if (ajouter) {
                compte.solde += montant;
            } else if (compte.solde >= montant) {
                compte.solde -= montant;
            } else {
                printf("Solde insuffisant !\n");
                fclose(f);
                fclose(temp);
                remove("temp.txt");
                return 0;
            }
        }
        fprintf(temp, "%d %d %.2f\n", compte.num_compte, compte.num_client, compte.solde);
    }

    fclose(f);
    fclose(temp);
    remove(FICHIER_COMPTES);
    rename("temp.txt", FICHIER_COMPTES);
    return trouve;
}

// Fonction pour acheter du crédit téléphonique
void achat_credit() {
    FILE *f = fopen(FICHIER_TELEPHONES, "r");
    FILE *temp = fopen("temp_tel.txt", "w");
    if (!f || !temp) {
        printf("Erreur d'ouverture du fichier téléphones.\n");
        return;
    }

    int num_tel;
    float montant;
    printf("Numéro de téléphone : ");
    scanf("%d", &num_tel);
    printf("Montant d'achat : ");
    scanf("%f", &montant);

    Telephone tel;
    int trouve = 0;
    while (fscanf(f, "%d %s %s %d %f", &tel.num_tel, tel.date_mise_service, tel.statut, &tel.num_client, &tel.credit_unite) != EOF) {
        if (tel.num_tel == num_tel) {
            trouve = 1;
            if (modifier_solde(tel.num_client, montant, 0)) {  // Débiter le compte du client
                tel.credit_unite += montant;
            } else {
                printf("Achat annulé, solde insuffisant !\n");
                fclose(f);
                fclose(temp);
                remove("temp_tel.txt");
                return;
            }
        }
        fprintf(temp, "%d %s %s %d %.2f\n", tel.num_tel, tel.date_mise_service, tel.statut, tel.num_client, tel.credit_unite);
    }

    fclose(f);
    fclose(temp);
    remove(FICHIER_TELEPHONES);
    rename("temp_tel.txt", FICHIER_TELEPHONES);

    if (trouve)
        printf("Achat d'unité réussi !\n");
    else
        printf("Numéro introuvable !\n");
}

// Fonction pour transférer de l’argent
void transfert_argent() {
    int num_compte1, num_compte2;
    float montant;
    printf("Compte source : ");
    scanf("%d", &num_compte1);
    printf("Compte destinataire : ");
    scanf("%d", &num_compte2);
    printf("Montant à transférer : ");
    scanf("%f", &montant);

    if (modifier_solde(num_compte1, montant, 0) && modifier_solde(num_compte2, montant, 1))
        printf("Transfert réussi !\n");
    else
        printf("Échec du transfert.\n");
}

// Fonction pour déposer de l’argent
void depot_argent() {
    int num_compte;
    float montant;
    printf("Numéro du compte : ");
    scanf("%d", &num_compte);
    printf("Montant du dépôt : ");
    scanf("%f", &montant);

    if (modifier_solde(num_compte, montant, 1))
        printf("Dépôt effectué avec succès !\n");
    else
        printf("Compte introuvable.\n");
}

// Fonction pour retirer de l’argent
void retrait_argent() {
    int num_compte;
    float montant;
    printf("Numéro du compte : ");
    scanf("%d", &num_compte);
    printf("Montant du retrait : ");
    scanf("%f", &montant);

    if (modifier_solde(num_compte, montant, 0))
        printf("Retrait effectué avec succès !\n");
    else
        printf("Fonds insuffisants.\n");
}


void consulter_solde() {
    int num_compte;
    printf("Numéro du compte : ");
    scanf("%d", &num_compte);

    FILE *f = fopen(FICHIER_COMPTES, "r");
    if (!f) {
        printf("Aucun compte trouvé.\n");
        return;
    }

    Compte compte;
    int trouve = 0;
    while (fscanf(f, "%d %d %f", &compte.num_compte, &compte.num_client, &compte.solde) != EOF) {
        if (compte.num_compte == num_compte) {
            printf("Solde du compte %d : %.2f\n", num_compte, compte.solde);
            trouve = 1;
            break;
        }
    }

    fclose(f);
    if (!trouve) printf("Compte introuvable.\n");
}
