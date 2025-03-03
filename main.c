#include <stdio.h>
#include <stdlib.h>
#include "gestion_fichiers.c"
#include "gestion_comptes.c"
#include "gestion_telephones.c"
#include "gestion_transactions.c"
#include "gestion_factures.c"

void afficher_menu() {
    printf("\n=== MENU ===\n");
    printf("1. Ajouter un client\n");
    printf("2. Afficher les clients\n");
    printf("3. Ajouter un compte\n");
    printf("4. Afficher les comptes\n");
    printf("5. Ajouter un téléphone\n");
    printf("6. Afficher les téléphones\n");
    printf("7. Achat d'unités\n");
    printf("8. Transfert d'argent\n");
    printf("9. Dépôt d'argent\n");
    printf("10. Retrait d'argent\n");
    printf("11. Consulter solde\n");
    printf("12. Afficher factures\n");
    printf("13. Payer une facture\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

int main() {
    int choix, num_client;
    do {
        afficher_menu();
        scanf("%d", &choix);
        switch (choix) {
            case 1: ajouter_client(); break;
            case 2: afficher_clients(); break;
            case 3: ajouter_compte(); break;
            case 4: afficher_comptes(); break;
            case 5: ajouter_telephone(); break;
            case 6: afficher_telephones(); break;
            case 7: achat_credit(); break;
            case 8: transfert_argent(); break;
            case 9: depot_argent(); break;
            case 10: retrait_argent(); break;
            case 11: consulter_solde(); break;
            case 12: 
                printf("Numéro du client : ");
                scanf("%d", &num_client);
                afficher_factures(num_client);
                break;
            case 13: payer_facture(); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);

    return 0;
}
