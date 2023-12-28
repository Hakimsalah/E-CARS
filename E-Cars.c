
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VOITURES 100
#define MAX_LOCATIONS 1000

typedef struct {
    char immatriculation[20];
    int kilometrage;
    char marque[20];
    char modele[20];
    char couleur[20];
    float prix_jour;
    int disponible;
    int reserver;
    int test;
} Voiture;

typedef struct {
    char nom[20];
    char prenom[20];
    char id[20];
    char adresse[50];
} Client;

typedef struct {
    int id;
    int id_voiture;
    int id_client;
    int dure;
    float prix_total;
} Location;

Voiture voitures[MAX_VOITURES];
int nb_voitures = 0;

Client clients[MAX_LOCATIONS];
int nb_clients = 0;

Location locations[MAX_LOCATIONS];
int nb_locations = 0;

void ajouter_voiture() {
    if (nb_voitures >= MAX_VOITURES) {
        printf("Impossible d'ajouter une nouvelle voiture, le nombre maximum de voitures a été atteint.\n");
        return;
    }

    Voiture voiture;

    printf("Immatriculation : ");
    scanf("%s", voiture.immatriculation);

    printf("Kilometrage : ");
    scanf("%d", &voiture.kilometrage);

    printf("Marque : ");
    scanf("%s", voiture.marque);

    printf("Modele : ");
    scanf("%s", voiture.modele);

    printf("Couleur : ");
    scanf("%s", voiture.couleur);

    printf("Prix par jour : ");
    scanf("%f", &voiture.prix_jour);

    printf("test : ");
    scanf("%d", &voiture.test);

    voiture.reserver = 0;

    voiture.disponible = 1;

    voitures[nb_voitures] = voiture;
    nb_voitures++;

    printf("Voiture ajoutee avec succes.\n");
}

void afficher_voitures() {
    printf("Liste des voitures :\n");

    for (int i = 0; i < nb_voitures; i++) {
        printf("%d. %s %d %s %s %s - %.2f EUR/jour - %s %s %s\n", i+1, voitures[i].immatriculation, voitures[i].kilometrage, voitures[i].marque, voitures[i].modele, voitures[i].couleur, voitures[i].prix_jour, voitures[i].disponible ? "disponible" : "indisponible", voitures[i].test ? "bon" : "panne",voitures[i].reserver ? "oui" : "non");
    }
}

void ajouter_client() {
    if (nb_clients >= MAX_LOCATIONS) {
        printf("Impossible d'ajouter un nouveau client, le nombre maximum de clients a été atteint.\n");
        return;
    }

    Client client;

    printf("Nom : ");
    scanf("%s", client.nom);

    printf("Prenom : ");
    scanf("%s", client.prenom);

    printf("id : ");
    scanf("%s", client.id);

    printf("Adresse : ");
    scanf("%s", client.adresse);

    clients[nb_clients] = client;
    nb_clients++;

    printf("Client ajoute avec succes.\n");
}

void afficher_clients() {
    printf("Liste des clients :\n");

    for (int i = 0; i < nb_clients; i++) {
        printf("%d. %s %s - %s - %s\n", i+1, clients[i].nom, clients[i].prenom, clients[i].id, clients[i].adresse);
    }
}
// Fonction pour réserver une voiture
void reserver_Voiture() {
    Voiture vv;
    Client cc;
    int d;
    printf("Immatriculation : ");
    scanf("%s", vv.immatriculation);

    printf("Kilometrage : ");
    scanf("%d", &vv.kilometrage);

    printf("Marque : ");
    scanf("%s", vv.marque);

    printf("Modele : ");
    scanf("%s", vv.modele);

    printf("Couleur : ");
    scanf("%s", vv.couleur);

    printf("Prix par jour : ");
    scanf("%f", &vv.prix_jour);

    printf("test : ");
    scanf("%d", &vv.test);

    printf("Nom : ");
    scanf("%s", cc.nom);

    printf("Prenom : ");
    scanf("%s", cc.prenom);

    printf("id : ");
    scanf("%s", cc.id);

    printf("Adresse : ");
    scanf("%s", cc.adresse);

    printf("duree : ");
    scanf("%d", &d);

    int i=0;
    while (i < nb_voitures && strcmp(voitures[i].immatriculation, vv.immatriculation) != 0) {
            i++;
        }
    if (voitures[i].reserver == 0) {
        voitures[i].reserver =1;
        printf("Voiture reservee avec succes :%s. %s %s -  par reserver %s %s - %d\n", cc.id, voitures[i].marque, voitures[i].modele, cc.nom, cc.prenom, d);
    } else {
        printf("Desole, la voiture est deja reservee pour le moment.\n");
        }

}

void louer_voiture() {
    if (nb_locations >= MAX_LOCATIONS) {
        printf("Impossible de louer une nouvelle voiture, le nombre maximum de locations a ete atteint.\n");
        return;
    }

    int id_voiture1, id_client1;
    int dure;

    afficher_voitures();

    printf("Selectionnez une voiture (1-%d) : ", nb_voitures);
    scanf("%d", &id_voiture1);

    if (id_voiture1 < 1 || id_voiture1 > nb_voitures) {
        printf("Voiture invalide.\n");
        return;
    }

    if (!voitures[id_voiture1-1].reserver) {
        printf("Cette voiture n'est pas reservee.\n");
        return;
    }
    if (!voitures[id_voiture1-1].disponible) {
        printf("Cette voiture n'est pas disponible.\n");
        return;
    }

    afficher_clients();

    printf("Selectionnez un client (1-%d) : ", nb_clients);
    scanf("%d", &id_client1);

    if (id_client1 < 1 || id_client1 > nb_clients) {
        printf("Client invalide.\n");
        return;
    }

    printf("Duree : ");
    scanf("%d", &dure);

    float prix_total1 = voitures[id_voiture1-1].prix_jour * dure;

    Location location1;
    location1.id = nb_locations + 1;
    location1.id_voiture = id_voiture1;
    location1.id_client = id_client1;
    location1.prix_total = prix_total1;
    location1.dure = dure;

    locations[nb_locations] = location1;
    nb_locations++;

    voitures[id_voiture1-1].disponible = 0;

    printf("Location enregistree avec succes.\n");
}

void afficher_locations() {
    printf("Historique des locations :\n");

    for (int i = 0; i < nb_locations; i++) {
        printf("%d. %s %s - louee par %s %s - %d - %.2f EUR\n", locations[i].id, voitures[i].marque, voitures[i].modele, clients[i].nom, clients[i].prenom, locations[i].dure, locations[i].prix_total);
    }
}

void Supprimer_voiture(){
    Voiture vo;
    int j, i = 0;
    printf("Immatriculation : ");
    scanf("%s", vo.immatriculation);

    printf("Kilometrage : ");
    scanf("%d", &vo.kilometrage);

    printf("Marque : ");
    scanf("%s", vo.marque);

    printf("Modele : ");
    scanf("%s", vo.modele);

    printf("Couleur : ");
    scanf("%s", vo.couleur);

    printf("Prix par jour : ");
    scanf("%f", &vo.prix_jour);

    printf("test : ");
    scanf("%d", &vo.test);

    vo.disponible = 1;

    if (vo.test == 0) {
        while (i < nb_voitures && strcmp(voitures[i].immatriculation, vo.immatriculation) != 0) {
            i++;
        }
        for (j = i; j < nb_voitures; j++) {
            voitures[j] = voitures[j + 1];
        }
        if (nb_voitures != 1) {
            nb_voitures = nb_voitures - 1;
        } else {
            nb_voitures = 0;
        }
    }
}
void retour_voiture(){
    Voiture vo1;
    int j, i;
    printf("Immatriculation : ");
    scanf("%s", vo1.immatriculation);

    printf("Kilometrage : ");
    scanf("%d", &vo1.kilometrage);

    printf("Marque : ");
    scanf("%s", vo1.marque);

    printf("Modele : ");
    scanf("%s", vo1.modele);

    printf("Couleur : ");
    scanf("%s", vo1.couleur);

    printf("Prix par jour : ");
    scanf("%f", &vo1.prix_jour);

    printf("test : ");
    scanf("%d", &vo1.test);

    vo1.disponible = 0;
    for (i = 0; i < nb_voitures; i++) {
        if (strcmp(voitures[i].marque, vo1.marque) == 0 && strcmp(voitures[i].modele, vo1.modele) == 0 && strcmp(voitures[i].immatriculation, vo1.immatriculation) == 0 && voitures[i].test == 1 && voitures[i].disponible == 0) {

            printf("Confirmer le retour (1 = oui, 0 = non) : ");
            scanf("%d", &j);
            if (j == 1) {
                voitures[i].disponible = 1;
                printf("Voiture retournee avec succes !\n");
            }
        }
    }
}

int main() {
    int choix;
    while (1) {
        printf("\nMenu :\n");
        printf("1. Ajouter une voiture\n");
        printf("2. Afficher les voitures\n");
        printf("3. Supprimer une voiture\n");
        printf("4. Ajouter un client\n");
        printf("5. Afficher les clients\n");
        printf("6. reserver une voiture\n");
        printf("7. Louer une voiture\n");
        printf("8. Afficher l'historique des locations\n");
        printf("9. Retourner une voiture\n");
        printf("10. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajouter_voiture();
                break;
            case 2:
                afficher_voitures();
                break;
            case 3:
                Supprimer_voiture();
                break;
            case 4:
                ajouter_client();
                break;
            case 5:
                afficher_clients();
                break;
             case 6:
                reserver_Voiture();
                break;
            case 7:
                louer_voiture();
                break;
            case 8:
                afficher_locations();
                break;
            case 9:
                retour_voiture();
                break;
            case 10:
                printf("Au revoir !\n");
                return 0;
        }
    }
}
