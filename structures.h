#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    int num_client;
    char nom[50];
    char prenom[50];
    int num_ville;
} Client;

typedef struct {
    int num_tel;
    char date_mise_service[11];
    char statut[10];
    int num_client;
    float credit_unite;
} Telephone;

typedef struct {
    int num_compte;
    int num_client;
    float solde;
} Compte;


typedef struct {
    int num_op;
    int num_type_op;
    int num_compte;
    int num_agence;
    char date_op[11];
    float montant;
} Operation;

typedef struct {
    int num_abonne;
    int num_facture;
    float montant;
    int code_service;
    int num_client;
    char status; // N = non payé, C = payé partiellement, P = payé
} Facture;

#endif
