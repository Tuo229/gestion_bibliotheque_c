#include <stdio.h>

#include "../header/gestionemprunt.h"

int principal(){

	int choix;
	printf("\n");
	printf("================================================================== \n");
	printf("||			CHOISIR UNE OPERATION			|| \n");
	printf("================================================================== \n");
	printf("\n");
	printf("*************      1- Emprunter un livre    **********************\n");
	printf("*************      2- Retourner un livre    **********************\n");
	printf("*************      3- Ajouter un livre      **********************\n");
	printf("*************      4- Liste des livre	      **********************\n");
	printf("*************      5- Liste des emprunt     **********************\n");
	printf("*************      6- Retardataires	      **********************\n");
	printf("*************      7- Statistiques	      **********************\n");
	
	
	printf("Votre choix => ");
	scanf("%d", &choix);
	switch (choix){
		case 1:
			printf("=====================  1- EMPRUNTER UN LIVRE  ====================\n");
			con(choix);
			break;
		case 2:
			printf("=====================  2- RETOURNER UN LIVRE  ====================\n");
			con(choix);
			break;
		case 3:
			printf("=====================  3- AJOUTER UN LIVRE    ====================\n");
			con(choix);
			break;
		case 4:
			printf("=====================  4- LISTER LES LIVRE 	====================\n");
			con(choix);
			break;
		case 5:
			printf("=====================  5- LISTE DES EMPRUNTS	====================\n");
			con(choix);
			break;
		case 6:
			printf("=====================  6- LISTE DES RETARDS 	====================\n");
			con(choix);
			break;
		case 7:
			printf("=====================  7- STATISTIQUES 	====================\n");
			con(choix);
			break;
		default:
			printf("Vous n'avez pas choisi une bonne option \n");
			break;
	}
	
	
	return 0;
}
