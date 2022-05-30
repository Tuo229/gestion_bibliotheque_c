#include <stdio.h>
#include <mysql/mysql.h>


#include "createdb.h"

int createdb(){

	// DECLARER LE POINTEUR DE MYSQL
	MYSQL mysql;
	// INITIALISER LE POINTEUR DE MYSQL
	mysql_init(&mysql);
	// OPTIONS DE CONNEXION A LA BD
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	
	// CONNEXION A LA BD
	if (mysql_real_connect(&mysql, "127.0.0.1", "debian-sys-maint", "FHwmWbTuAwgXn89F", "", 3306, NULL, 0))
	{
		createdatabase(mysql, "CREATE IF NOT EXISTS DATABASE biblio");
		createdatabase(mysql, "use bibliotheque");
		
		createtable(mysql, "CREATE TABLE IF NOT EXISTS adherent (num_adh VARCHAR(25) PRIMARY KEY, nom VARCHAR(55), prenom VARCHAR(128), telephone VARCHAR(20))");
		
		createtable(mysql, "CREATE TABLE IF NOT EXISTS livre (reference VARCHAR(10) PRIMARY KEY, auteur VARCHAR(64), titre VARCHAR(64), editeur VARCHAR(64), categorie VARCHAR(16), date_achat DATE, prix INT)");
		
		createtable(mysql, "CREATE TABLE IF NOT EXISTS emprunt (num_emprunt VARCHAR(25) , reference VARCHAR(10), date_sortie DATE, date_retour DATE, delai_retour DATE, eta BOOLEAN)");
		
		
		createtable(mysql, "ALTER TABLE emprunt ADD CONSTRAINT fk_emprunt FOREIGN KEY (num_emprunt) REFERENCE adherent(num_adh)");
		createtable(mysql, "ALTER TABLE emprunt ADD CONSTRAINT fk_livre FOREIGN KEY (reference) REFERENCE livre(reference)");
		
		createtable(mysql, "ALTER TABLE emprunt ADD CONSTRAINT pk_emprunt PRIMARY KEY (num_emprunt, reference)");
		
		//FOREIGN KEY REFERENCE adherent(num_adh)
		
		printf("CREATION TERMINE \n");
		
		mysql_close(&mysql);
	
	}else{
	
		printf("Connexion echoué \n");
	}
	
	return 0;
	
}



int createdatabase(MYSQL mysql, char* req){

	mysql_query(&mysql, req);
	if (mysql_affected_rows(&mysql) == 1){
		printf("SUCCESS \n");
	}else{
		printf("ECHECH \n");
	}
	
	return 0;		
}


int createtable(MYSQL mysql, char* req){
	
	mysql_query(&mysql, req);
	if (mysql_affected_rows(&mysql) >= 1){
		printf("SUCCESS \n");
	}else{
		printf("ECHECH \n");
	}
	return 0;	
}


int main(){
	createdb();
	return 0;
}
