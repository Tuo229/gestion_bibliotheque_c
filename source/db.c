#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../header/db.h"
#include "../header/connexion.h"



int db(struct Person pers,int a,int b)
{
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    
    

    if(mysql_real_connect(&mysql, "127.0.0.1", "debian-sys-maint", "FHwmWbTuAwgXn89F", "biblio", 3306, NULL, 0))
    {
    
    
    char requete[500] = "";
    
    
switch(a){
case 1 :
	
	sprintf(requete,"INSERT INTO adherent VALUES('%s','%s','%s','%s')",pers.matricule, pers.nom, pers.prenom, pers.telephone);
	printf("%s \n", requete);
	mysql_query(&mysql,requete);
	  if (mysql_affected_rows(&mysql) == 1) {
	   
	    	printf("OK");
	    	
	   }
	   else {
	   printf("ECHEC \n");
	   	}
case 2 :
	switch(b){
	
	case 1 :
	
	sprintf(requete,"UPDATE adherent SET nom='%s' WHERE num_adh='%s'",pers.nom,pers.matricule);
	if (mysql_query(&mysql,requete)) {
	   
	    	printf("OK");
	    	
	   }
	   else {
	   printf("OK");
	   	}
	
	break;
	
	
	case 2: 
	
	sprintf(requete,"UPDATE adherent SET prenom='%s' WHERE num_adh='%s'",pers.prenom,pers.matricule);
	mysql_query(&mysql,requete);
	if (mysql_affected_rows(&mysql) == 1) {
	   
	    	printf("OK");
	    	
	   }
	   else {
	   printf("OK");
	   	}
	   break ;
	   
	   
	  case 3 :
	  
	  sprintf(requete,"UPDATE adherent SET telephone='%s' WHERE num_adh='%s'",pers.telephone,pers.matricule);
	  mysql_query(&mysql,requete);
	  if (mysql_affected_rows(&mysql) == 1) {
	   
	    	printf("OK");
	    	
	   }
	   else {
	   printf("ECHEC");
	   	}
	   	
	   break ;
	   
	   case 4 :
	   
		sprintf(requete,"UPDATE adherent SET nom='%s',prenom='%s',telephone='%s' WHERE num_adh='%s'",pers.nom,pers.prenom,pers.telephone,pers.matricule);
		mysql_query(&mysql,requete);

		  if (mysql_affected_rows(&mysql) == 1) {
		   
		    	printf("OK");
		    	
		   }
		   else {
		   printf("ECHEC");
		   	}
	   	
	   break ;
	   
	   	
	  
	
	}
	
case 3 :
	switch(b){
	
		case 1 :
		
		sprintf(requete,"SELECT * FROM adherent WHERE matricule='%s'",pers.matricule);
		connexion(mysql,requete);	
		break;
			
		case 2 : 
		sprintf(requete,"SELECT * FROM adherent WHERE nom='%s' and prenom='%s'",pers.nom,pers.prenom);
		connexion(mysql,requete);
		break;
		
		case 3 :
		sprintf(requete,"SELECT * FROM adherent WHERE telephone='%s'",pers.telephone);
		connexion(mysql,requete);
		break;
		
		case 4 :
		sprintf(requete,"SELECT * FROM adherent");
		connexion(mysql,requete);
		
		break;		
	}
	
	break;
	default :
		printf("\n\n\n\t\t\tSAISI INVALIDE!!! Réessayer...");
		
		}
	    
 

        mysql_close(&mysql);
 
    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }

    return 0;
}
