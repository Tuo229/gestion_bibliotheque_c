#include "../header/adherent.h"
#include "../header/db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/search_adherent.h"



int search_adherent(){
  
	struct Person adher ;
	
	int choice = 0 ;
	do {
	
		
		char x[30]= "1.Recherche par matricule";
		char y[30]= "2.Recherche par nom et prénom";
		char z[30]= "3.Recherche par téléphone";
		char t[40]= "4.Afficher toute la liste";
		char u[20]= "0.Quitter";
		
		
		printf("%*s\n\n\n\t\t\t",72,x);
        	printf("%*s\n\n\n\t\t\t",53,y);
        	printf("%*s\n\n\n\t\t\t",50,z);
        	printf("%*s\n\n\n\t\t\t",48,t);
        	printf("%*s\n\n\n\t\t\t",32	,u);
        	printf("\n\n\n\t\t\tVotre choix => ");
        	
        	scanf("%d",&choice);
        	
        	switch(choice){
        	case 1 :
        		printf("Entrez le matricule => ");
        		scanf("%s",adher.matricule);
        		strcpy(adher.nom, "");
        		strcpy(adher.prenom, "");
        		strcpy(adher.telephone, "");
        		db(adher,3,choice);
        		break;
        	case 2 :
        		printf("Entrez le nom => ");
        		scanf("%s",adher.nom);
        		
        		printf("Entrez le prénom => ");
        		scanf("%s",adher.prenom);
        		strcpy(adher.matricule, "");
        		strcpy(adher.telephone, "");
        		db(adher,3,choice);
        		break;
        	case 3 :
        		printf("Entrez le numéro de téléphone => ");
        		scanf("%s",adher.telephone);
        		strcpy(adher.nom, "");
        		strcpy(adher.prenom, "");
        		strcpy(adher.matricule, "");
        		db(adher,3,choice);
        		break;
        	case 4 :
			strcpy(adher.matricule, "");
        		strcpy(adher.nom, "");
        		strcpy(adher.prenom, "");
        		strcpy(adher.matricule, "");
        		db(adher,3,choice);
        		break;
        	default :
        		printf("\n\n\n\t\t\tSAISI INVALIDE!!! Réessayer...");
        	
        	}
	
	}
	while(choice !=0);
	
	return 0;

}
