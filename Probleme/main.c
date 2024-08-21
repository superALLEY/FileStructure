#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_PATIENTS 100

typedef struct {
    char nom[50];
    char prenom[50];
    int age;
    char sexe;
    char antecedents[200];
    int identifiant;
} Patient;

Patient registre[MAX_PATIENTS];
int nombrePatients = 0;

void sauvegarderRegistre() {
    FILE *fichier = fopen("registre_patients.txt", "w");
    if (fichier == NULL) {
        system("cls");
        system("color 0C");
        printf("Erreur lors de l'ouverture du fichier.\n");
        getch();
        return;
    }

    for (int i = 0; i < nombrePatients; i++) {
        fprintf(fichier, "%d %s %s %d %c %s\n", registre[i].identifiant, registre[i].nom, registre[i].prenom, registre[i].age, registre[i].sexe, registre[i].antecedents);
    }

    fclose(fichier);
    system("cls");
    system("color 0A");
    printf("Registre sauvegarde avec succes.\n");
    getch();
}

void afficherPatients() {
    system("color 0A");
    printf("\t\tRegistre des patients :\n");
    for (int i = 0; i < nombrePatients; i++) {
        printf("Identifiant : %d\n", registre[i].identifiant);
        printf("Nom : %s\n", registre[i].nom);
        printf("Prenom : %s\n", registre[i].prenom);
        printf("Age : %d\n", registre[i].age);
        printf("Sexe : %c\n", registre[i].sexe);
        printf("Antecedents medicaux : %s\n", registre[i].antecedents);
        printf("\n");
    }
    printf("\n\nCliquez sur n'importe quelle touche pour continuer.\n");
    getch();
}

void ajouterPatient() {
    if (nombrePatients < MAX_PATIENTS) {
        Patient nouveauPatient;
        printf("Entrez le nom : ");
        scanf("%49s", nouveauPatient.nom);
        printf("Entrez le prenom : ");
        scanf("%49s", nouveauPatient.prenom);
        printf("Entrez l'age : ");
        scanf("%d", &nouveauPatient.age);
        printf("Entrez le sexe (M/F) : ");
        scanf(" %c", &nouveauPatient.sexe);
        printf("Entrez les antecedents medicaux : ");
        scanf(" %199[^\n]", nouveauPatient.antecedents); // Allow spaces in antecedents

        nouveauPatient.identifiant = nombrePatients + 1;
        registre[nombrePatients++] = nouveauPatient;

        system("cls");
        system("color 0A");
        printf("Patient ajoute avec succes.\n");
    } else {
        system("cls");
        system("color 0C");
        printf("Le registre est plein, impossible d'ajouter un nouveau patient.\n");
    }
    printf("\n\nCliquez sur n'importe quelle touche pour continuer.\n");
    getch();
}

void chargerRegistre() {
    system("color 0B");
    printf("Chargement de registre en cours...");
    Sleep(2000); // Sleep takes milliseconds
    system("cls");

    FILE *fichier = fopen("registre_patients.txt", "r");
    if (fichier == NULL) {
        system("color 0C");
        printf("Le fichier de registre n'existe pas encore.\n");
        getch();
        system("color 0B");
        return;
    }

    while (fscanf(fichier, "%d %49s %49s %d %c ", &registre[nombrePatients].identifiant,
                  registre[nombrePatients].nom, registre[nombrePatients].prenom,
                  &registre[nombrePatients].age, &registre[nombrePatients].sexe) == 5) {
        // Read the rest of the line as the antecedents field
        fscanf(fichier, " %199[^\n]", registre[nombrePatients].antecedents);
        nombrePatients++;
    }

    fclose(fichier);
    system("color 0A");
    printf("\nRegistre charge avec succes.\nCliquez sur n'importe quelle touche pour continuer.");
    getch();
    system("color 0B");
}

void afficherInformationPatient(Patient patient) {
    system("color 0A");
    printf("Identifiant : %d\n", patient.identifiant);
    printf("Nom : %s\n", patient.nom);
    printf("Prenom : %s\n", patient.prenom);
    printf("Age : %d\n", patient.age);
    printf("Sexe : %c\n", patient.sexe);
    printf("Antecedents medicaux : %s\n", patient.antecedents);
    printf("\n");
    printf("\n\nCliquez sur n'importe quelle touche pour continuer.\n");
    getch();
}

void rechercherPatientParNom(const char *nomRecherche) {
    int trouve = 0;
    system("cls");
    printf("Recherche en cours...");
    Sleep(2000); // Sleep takes milliseconds
    system("cls");

    system("color 0A");
    printf("Resultats de la recherche par nom pour \"%s\" :\n", nomRecherche);
    for (int i = 0; i < nombrePatients; i++) {
        if (strcmp(registre[i].nom, nomRecherche) == 0) {
            printf("Element trouve avec succes.\n");
            afficherInformationPatient(registre[i]);
            trouve = 1;
        }
    }
    if (!trouve) {
        system("color 0C");
        printf("Aucun patient trouve avec ce nom.\n");
    }
    printf("\n\nCliquez sur n'importe quelle touche pour continuer.\n");
    getch();
}

void rechercherPatientParIdentifiant(int identifiantRecherche) {
    int trouve = 0;
    system("cls");
    printf("Recherche en cours...");
    Sleep(2000); // Sleep takes milliseconds
    system("cls");

    printf("Resultats de la recherche par identifiant pour %d :\n", identifiantRecherche);
    system("color 0A");
    for (int i = 0; i < nombrePatients; i++) {
        if (registre[i].identifiant == identifiantRecherche) {
            printf("Element trouve avec succes.\n");
            afficherInformationPatient(registre[i]);
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        system("color 0C");
        printf("Aucun patient trouve avec cet identifiant.\n");
    }
    printf("\n\nCliquez sur n'importe quelle touche pour continuer.\n");
    getch();
}

void modifierAntecedentsPatient(int identifiantRecherche) {
    int trouve = 0;
    for (int i = 0; i < nombrePatients; i++) {
        if (registre[i].identifiant == identifiantRecherche) {
            printf("Nouveaux antecedents medicaux pour le patient (identifiant %d) : ", identifiantRecherche);

            if (scanf(" %199[^\n]", registre[i].antecedents) == 1) {
                system("color 0A");
                printf("Antecedents medicaux mis a jour avec succes.\n");
                getch();
                trouve = 1;
            } else {
                system("color 0C");
                printf("Erreur de saisie.\n");
                getch();
            }
            break;
        }
    }
    if (!trouve) {
        system("color 0C");
        printf("Aucun patient trouve avec cet identifiant.\n");
        getch();
    }
}

int main() {
    chargerRegistre();
    char nomRecherche[50];
    int choix;
    int identifiantRecherche;
    int identifiantModification;

    do {
        system("cls");
        system("color 0B");
        printf("Menu :\n");
        printf("1. Ajouter un patient.\n");
        printf("2. Afficher tous les patients.\n");
        printf("3. Rechercher un patient par nom.\n");
        printf("4. Rechercher un patient par identifiant.\n");
        printf("5. Sauvegarder le registre.\n");
        printf("6. Modifier les antecedents d'un patient.\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                system("cls");
                ajouterPatient();
                break;
            case 2:
                system("cls");
                afficherPatients();
                break;
            case 3:
                system("cls");
                printf("Entrez le nom a rechercher : ");
                scanf("%49s", nomRecherche);
                rechercherPatientParNom(nomRecherche);
                break;
            case 4:
                system("cls");
                printf("Entrez l'identifiant a rechercher
