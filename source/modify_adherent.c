#include <stdio.h> 
#include <stdlib.h> 
#include "../header/modify_adherent.h"
#include "../header/db.h"
#include <string.h>



int modify_adherent(){

  
	struct Person adher ;
	
	int choice = 0 ;
	do {
	
		char x[30]= "1.modifier le nom";
		char y[30]= "2.modifier le prénom";
		char z[40]= "3.modifier le numéro de téléphone";
		char t[40]= "4.Tout modifier";
		char u[20]= "0.Quitter";
	
		printf("Entrez le matricule => ");
        	scanf("%s",adher.matricule);
        	printf("%*s\n\n\n\t\t\t",63,x);
        	printf("%*s\n\n\n\t\t\t",43,y);
        	printf("%*s\n\n\n\t\t\t",58,z);
        	printf("%*s\n\n\n\t\t\t",37,t);
        	printf("%*s\n\n\n\t\t\t",31,u);
        	printf("\n\n\n\t\t\tVotre choix => ");
        	
        	scanf("%d",&choice);
        	
        	switch(choice){
        	case 1 :
        		printf("Entrez le nouveau nom => ");
        		scanf("%s",adher.nom);
        		strcpy(adher.prenom, "");
        		strcpy(adher.telephone, "");
        		db(adher,2,choice);
        		break;
        	case 2 :
        		printf("Entrez le nouveau prénom => ");
        		scanf("%s",adher.prenom);
        		strcpy(adher.nom, "");
        		strcpy(adher.telephone, "");
        		db(adher,2,choice);
        		break;
        	case 3 :
        		printf("Entrez le nouveau pnuméro de téléphone => ");
        		scanf("%s",adher.telephone);
        		strcpy(adher.nom, "");
        		strcpy(adher.prenom, "");
        		db(adher,2,choice);
        		break;
        	case 4 :
        		printf("Entrez le nouveau nom => ");
        		scanf("%s",adher.nom);
        		printf("Entrez le nouveau prénom => ");
        		scanf("%s",adher.prenom);
        		printf("Entrez le numéro de téléphone => ");
        		scanf("%s",adher.telephone);
        		db(adher,2,choice);
        		break;
        	default :
        		printf("\n\n\n\t\t\tSAISI INVALIDE!!! Réessayer...");
        	
        	}
	
	}
	while(choice !=0);
	
	return 0;

}

