#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../header/connexion.h"


void connexion(MYSQL mysql,char* requete){


		mysql_query(&mysql,requete) ;
	   
	    	// Déclaration des objets de la requête
		MYSQL_RES *result = NULL;
		MYSQL_ROW row;
		
		unsigned int i = 0;
		unsigned int num_champs = 0;
		
		// On met le jeu de données dans le pointeur *result
		result = mysql_use_result(&mysql);
		
		// On recupère le nombre de champs
		num_champs = mysql_num_fields(result);
		
		// Tantqu'il y a encore un resultat bouclé sur les "result"
		while((row = mysql_fetch_row(result))){
			
			// Pointeur long non signé pour stocker la tailles des valeurs
			unsigned long *lenghts;
			
			// On stocke les tailles dans le pointeur
			lenghts = mysql_fetch_lengths(result);
			
			// On fait une boucle pour avoir la valeur des champs
			for(i = 0; i < num_champs; i++){
				// On écrit toute les valeurs
				printf("[%*s] ", (int) lenghts[i], row[i] ? row[i]: NULL);
			}
			printf("\n");
		}
		
		//Libération du jeu de résultat
        	mysql_free_result(result);
	    	

}
