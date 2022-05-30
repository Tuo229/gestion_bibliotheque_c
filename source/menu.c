#include <stdio.h> 
#include <stdlib.h> 

#include "../header/menu.h"
#include "../header/adherent.h"
#include "../header/search_adherent.h"
#include "../header/db.h"
#include "../header/modify_adherent.h"

#include "../header/gestionemprunt.h"


void MessageCenter(){
	int a = 65;
	char x[20]= "MENU PRINCIPAL";
	printf ("%*s\n",a, x );
}


void headMessage(const char *message)
{
    
    printf("\t\t\t#######################################################################");
    printf("\n\t\t\t##########                                                   ##########");
    printf("\n\t\t\t##########     SYSTÈME DE GESTION DE BIBLIOTHEQUE            ##########");
    printf("\n\t\t\t##########                                                   ##########");
    printf("\n\t\t\t#######################################################################");

}


void welcomeMessage()
{
    headMessage("Tuo&Amani");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                BIENVENUE                  =");
    printf("\n\t\t\t        =                    À                      =");
    printf("\n\t\t\t        =                    LA                     =");
    printf("\n\t\t\t        =                BIBLITHEQUE                =");
    printf("\n\t\t\t        =                 TUO & AMANI               =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");

    
   
}


void menu(){

	int choice = 0 ;
	do {
	
		int a = 65;
		char x[20]= "1.Gestion de livre";
		char y[30]= "2.Ajouter un adhérent";
		char z[30]= "3.Modifier un adhérent";
		char t[40]= "4.Consulter la liste des adhérents";
		char u[20]= "0.Quitter";
	
		
        	printf("%*s\n\n\n\t\t",a, x );
        	printf("%*s\n\n\n\t\t",53,y);
        	printf("%*s\n\n\n\t\t",54, z );
        	printf("%*s\n\n\n\t\t",66, t );
        	printf("%*s\n\t\t\t",40,u);
        	printf("\n\n\n\t\t\tVotre choix => ");
        	
        	scanf("%d",&choice);
        	
        	switch(choice){
        	case 1 :
        		printf("Gestion de livre");
        		principal();
        		break;
        	case 2 :
        		register_adherent();
        		break;
        	case 3 :
        		modify_adherent();
        		break;
        	case 4 :
        		search_adherent();
        		break;
        	default :
        		printf("\n\n\n\tSAISI INVALIDE!!! Réessayer...\n");
        	
        	}
	
	}
	while(choice !=0);

}



int main(int argc, char **argv){

	welcomeMessage();
	menu();

	return 0;
}

