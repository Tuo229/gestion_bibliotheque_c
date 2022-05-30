#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <time.h>
#include <string.h>

#include "../header/gestionemprunt.h"

/*
	LA FONCTION VIDEBUFFER PERMET D'EFFACE LES CARACTÈRE DE PLUS DANS LE BUFFER DONT LA FONCTION fgets
	N'A PAS PU LIRE.
*/
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/*
	LA FONCTION LIRE SERT A ECRIRE DANS UNE VARIABLE DE TYPE CHAINE DE CARACTÈRE
*/
 
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

/* FIN DE LA FONCTION POUR L'ECRITURE DES CHAINES DE CARACTERE */

// ==============================================================

/*
	CONNEXION A LA BASE DE DONNEES ET LES SAISIE
*/

int con (int ch) {
	char ref_livre[50];
	char num_adh[50];
	char date_act[20];
	char date_delai[20];
	char date_ret[20];
	
	char aut[70];
	char titre[70]; 
	char edit[70];
	char cat[70];  
	char date_achat[20];
	int prix;
	 
	if (ch == 1 || ch == 2)
	{

		printf("Veuillez renseigner les informations concernant le livre! \n");
		printf("------------------------------------------------------------------ \n");
		// INFORMATION SUR L'EMPRUNT
			
		
		printf("Entrer le numero de référence du livre\n");
		scanf("%s", ref_livre);
		printf("Entrer le numero de l'adhérent \n");
		scanf("%s", num_adh);
		
		
		// GENERER LA DATE 
		int h, min, s, day, mois, an;
		time_t now;

		// Renvoie l'heure actuelle
		time(&now);

		// Convertir au format heure locale
		// printf("Aujourd'hui est : %s", ctime(&now));

		struct tm *local = localtime(&now);
		h = local->tm_hour;        
		min = local->tm_min;       
		s = local->tm_sec;       
		day = local->tm_mday;          
		mois = local->tm_mon + 1;     
		an = local->tm_year + 1900;  
		
		
		sprintf(date_act, "%d-%02d-%02d", an, mois, day);
		
		// DETERMINER LA DATE DE RETOUR
		int days_delai;
		int mois_delai;
		int an_delai;
		days_delai = day + 14;
		an_delai = an;
		mois_delai = mois;
		/*
			SI LE MOIS COMPTE 31 OU 30 OU ENCORE 28 JOURS
			ON FAIT LES OPERATION QUI CONVIENNENT
		*/
		if (mois == 1 || mois == 3 || mois == 5 || mois == 7 || mois == 8 || mois == 10 || mois == 12)
		{
			if (days_delai > 31) // SI LE MOIS COMPTE 31 JOURS ET QUE DAYS DELAI EST > 31 JOURS
			{	
				if (mois == 12) // APRES LE 12 EME MOIS DE L'ANNEE ON PASSE AU PREMIER MOIS PUIS L'ANNEE AUGMENTE DE 1
				{
					mois_delai = 1;
					an_delai = an + 1;
					
				}
				else // ON CHANGE SEULEMENT LE MOIS 
				{
					mois_delai = mois + 1;
				}
				days_delai = days_delai - 31; // ON DETERMINE LE JOUR NORMAL
			}
		}else if (mois == 2)
		{
			if (days_delai > 28)
			{
				days_delai = days_delai - 28;
				mois_delai = mois + 1;
				an_delai = an;
			}
			
		}else if (mois == 4 || mois == 6 || mois == 9 || mois == 11) 
		{
			if (days_delai > 30) // LE MOIS COMPTE 30 JOURS ET DAYS DELAI EST > 30
			{
				mois_delai = mois + 1;
				days_delai = days_delai - 30;
			}	
		}
		
		sprintf(date_delai, "%d-%02d-%02d", an_delai, mois_delai, days_delai);
		
		sprintf(date_ret, "%d-%02d-%02d", an, mois, day);
	}else if (ch == 3)
	{
		lire(ref_livre, 50);
		printf("Entrer le numero de référence du livre\n");
		lire(ref_livre, 50);
		//scanf("%50s", ref_livre);
		printf("Entrer le nom l'auteur \n");
		//scanf("%70s", aut);
		lire(aut, 70);
		printf("Entrer le titre du livre \n");
		//scanf("%50s", titre);
		lire(titre, 50);
		printf("Entrer l'éditeur du livre \n");
		//scanf("%70s", edit);
		lire(edit, 70);
		printf("Entrer la catégorie du livre \n");
		//scanf("%70s", cat);
		lire(cat, 70);
		printf("Entrer la date d'achat du livre (ex: YYYY-MM-DD => 2022-02-28 \n");
		//scanf("%20s", date_achat);
		lire(date_achat, 20);
		printf("Entrer le prix d'achat du livre \n");
		scanf("%d", &prix);
	}

	// DECLARER LE POINTEUR DE MYSQL
	MYSQL mysql;
	// INITIALISER LE POINTEUR DE MYSQL
	mysql_init(&mysql);
	// OPTIONS DE CONNEXION A LA BD
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	
	// CONNEXION A LA BD
	if (mysql_real_connect(&mysql, "127.0.0.1", "debian-sys-maint", "FHwmWbTuAwgXn89F", "biblio", 3306, NULL, 0))
	{
		switch (ch)
		{
			case 1: // EMPRUNT 
				printf("------------------------------------------------------------------ \n");
				if (noexistlivre(mysql, ref_livre) == 0){
					printf("Le livre n'exite pas en stock \n");
				}else{
					emprunt(mysql, num_adh, ref_livre, date_act, date_delai);
					printf("Vous avez emprunté le livre %s et vous devez le retourner le %s passé cette date vous considéré comme un retardataire \n", ref_livre, date_delai);
				}
				break;
			case 2: // RETOUR
				printf("------------------------------------------------------------------ \n");
				retourner(mysql, date_ret, num_adh, ref_livre);
				printf("L'adherent n° %s a retourné le livre de référence %s le %s \n", num_adh, ref_livre, date_ret);
				// RETARDATAIRE
	
				if (verifie(mysql, ref_livre, num_adh, date_ret) == 0)
				{
					printf("ATTENTION !!!\n");
					printf("Vous avez deposé ce livre en retard !\n");
				}else
				{
					printf("MERCI, vous êtes dans le temps !\n");
				}
				break;
			case 3:
				printf("------------------------------------------------------------------ \n");
				char ref[5];
				sprintf(ref, "%d", lastid(mysql));
				printf("ref %s \n", ref);
				char initial[50] = "LV";
				strcat(initial, ref);
				strcat(initial, ref_livre);
				printf("Reference %s \n", initial);
				ajoutlivre(mysql, initial, aut, titre, edit, cat, date_achat, prix);
				break;
			case 4:
				printf("------------------------------------------------------------------ \n");
				listlivre(mysql);
				break;
			case 5:
				printf("------------------------------------------------------------------ \n");
				listemprunt(mysql);
				break;
			case 6:
				printf("------------------------------------------------------------------ \n");
				retard(mysql);
				break;
			case 7:
				printf("------------------------------------------------------------------ \n");
				stats(mysql);
				break;
			default:
				printf("------------------------------------------------------------------ \n");
				printf("Mauvais choix \n");
				break;
		}
		// FERMETURE DE LA BD
		mysql_close(&mysql);
	}else 
	{
		printf("------------------------------------------------------------------ \n");
		printf("Echec de connexion à la BD \n");
	}
	
	return 0;
}

/*
	FIN DE CONNEXION A LA BD
*/

//========================================================

/*
	FONCTION PERMETTANT D'EMPRUNTER UN LIVRE: ELLE PREND 5 PARAMETRES
	- mysql: Un pointeur sur l'objet de connexion à la BD
	- num: numero de l'adherent
	- ref: référence du livre
	- date_act: date d'emprunt
	- date_delai: la date delai de retour
*/

int emprunt(MYSQL mysql, const char* num, const char* ref, const char* date_act, const char* date_delai ) {
	printf("------------------------------------------------------------------ \n");
	char requete[700] = "";
	sprintf(requete, "INSERT INTO emprunt VALUES('%s', '%s', '%s', NULL, '%s', 0)", num, ref, date_act, date_delai);
	//printf("%s", requete);
	mysql_query(&mysql, requete);
	printf("SUCCES !\n"); 
	return 0;
}

/* FIN DE LA FONCTION EMPRUNT */

// =================================================================

/*
	FONCTION PERMETTANT DE RETOURNER UN LIVRE: ELLE PREND 4 PARAMETRES
	- mysql: Un pointeur sur l'objet de connexion à la BD
	- num_adh: numero de l'adherent
	- ref_livre: référence du livre
	- date_ret: date de retour
*/

int retourner (MYSQL mysql, const char* date_ret, const char* num_adh, const char* ref_livre) {	
	
	printf("------------------------------------------------------------------ \n");
	// REQUETE DANS LA BASE DE DONNEES
	
	//char requete1[500] = "";
	char requete[530] = "";
	//sprintf(requete1, "SELECT * FROM emprunt WHERE num_adh = '%s' AND ref_livre = '%s'", num_adh, ref_livre);
	sprintf(requete, "UPDATE emprunt SET date_retour='%s' WHERE num_emprunt = '%s' AND reference = '%s';", date_ret, num_adh, ref_livre);
	//printf("%s \n\n", requete);
	// EXECUTION DE LA REQUETE
	mysql_query(&mysql, requete);
	printf("SUCCES !\n");
	return 0;
}

/* FIN DE LA FONCTION RETOURNER LIVRE */

//============================================================

/*
	FONCTION PERMETTANT D'AJOUTER UN LIVRE DANS LA BD: ELLE PREND 8 PARAMETRES
	ET RETOURNE UN ENTIER
	int ajoutlivre(MYSQL mysql, char* ref, char* aut, char* titre, char* edit, char* cat, char* date_achat, int prix)
*/
 
 int ajoutlivre(MYSQL mysql, char* ref, char* aut, char* titre, char* edit, char* cat, char* date_achat, int prix)
{
	
	char requete[850] = "";
	sprintf(requete, "INSERT INTO livre VALUES('%s', '%s', '%s', '%s', '%s', '%s', %d)", ref, aut, titre, edit, cat, date_achat, prix);
	//printf("%s \n", requete);
	
	// EXECUTER LA REQUETE
	mysql_query(&mysql, requete);
	if (mysql_affected_rows(&mysql) == 1){
		printf("Livre ajouté avec SUCCES !\n");
	}else{
		printf("Echec une erreur c'est produite pendant l'ajout du livre \n");
	}
	
	return 0;
}

/* FIN DE LA FONCTION AJOUTER UN LIVRE */

//========================================================

/*
	CETTE FONCTION PERMET DE LISTER LES LIVRES
*/

int listlivre (MYSQL mysql){

	// FORMULER LA REQUETE ET L'EXECUTER
	char requete[300] = "";
	sprintf(requete, "SELECT reference, titre, auteur FROM livre;");
	//printf("%s \n", requete);
	mysql_query(&mysql, requete);
	//printf("Requete...\n");
	
	// POINTEUR DE STRUCTURE POUR PARCOURIR LES RESULTATS DE LA REQUETE (les objets de la requete)
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	
	unsigned int i = 0;
	unsigned int num_champs = 0;
	
	// RECUPERER LE JEU DE DONNEES DANS LE POINTEUR RESULT
	result = mysql_store_result(&mysql);
	
	num_champs = mysql_num_fields(result);
	
	printf("[REFERENCE] - [TITRE] - [AUTEUR]\n");
	printf("---------------------------------- \n");
	// BOUCLER SUR LES DATA 
	while ((row = mysql_fetch_row(result)))
	{
		// POINTEUR TYPE LONG NON SIGNE POUR STOCKER LA TAILLES DES VALEURS
		unsigned long *lenghts;
		
		//ON STOCK LES TAILLES DES VALEURS DANS LE POINTEUR
		lenghts = mysql_fetch_lengths(result);
		
		for (i = 0; i < num_champs; i++)
		{
			printf("%*s - ", (int) lenghts[i], row[i] ? row[i] : NULL);
			if (i == num_champs - 1){ 
			printf("\n");
			printf("---------------------------------- \n");
			}
		}
		
	}
	mysql_free_result(result);
	return 0;
}

/* FIN DE LA FONCTION LISTE DES LIVRES */

//==============================================================

/*
	CETTE FONCTION lastid PERMET DE RECUPERER L'ID DU DERNIER ELEMENT DANS LA BASE DE DONNEES
	PUIS RETOURNER L'ID DE L'ELEMENT ACTUEL
*/

unsigned int lastid (MYSQL mysql){
	
	mysql_query(&mysql, "SELECT MAX(reference) as id FROM livre");
	
	MYSQL_RES *result; // LE POINTEUR QUI STOCK LES RESULTATS
	MYSQL_ROW row;
	char* l_id;
	unsigned int id;
	result = mysql_store_result(&mysql); // STOCK LES RESULTATS DE LA REQUETE
	while (row = mysql_fetch_row(result)){
		l_id = row[0] ? row[0]: 0;
		id = atoi(l_id) + 1;
	}
	return id;
}

/* FIN DE LA FONCTION LASTID */

//====================================================================

/*
	CETTE FONCTION PERMET DE PRENDRE EN PARAMETRE UNE REFERENCE PUIS RETOURNER SI ELLE EST ASSOCIEE A UN LIVRE OU PAS
*/

unsigned int noexistlivre(MYSQL mysql, const char* ref){

	char requete[200] = "";
	sprintf(requete, "SELECT * FROM livre WHERE reference = '%s'", ref);
	mysql_query(&mysql, requete);
	
	MYSQL_RES *result = NULL; // POINTEUR RESULT PERMETTANT DE STOCKER LES RESULTATS DE LA REQUETE
	MYSQL_ROW row; // LIT LES LIGNES DE LA REQUETE
	
	result = mysql_store_result(&mysql); // MET LES RESULTATS DANS RESULT
	unsigned int num_rows = mysql_num_rows(result);
	
	
	mysql_free_result(result);

	return num_rows;
	
	
}

/* FIN DE LA FONCTION DE VERIFICATION DE L'EXISTENCE D'UN LIVRE DANS LA BD*/

//==========================================================================

/*
	CETTE FONCTION PERMET DE LISTE LES ADHERENT QUI DEPOSER LES LIVRES EN RETARD
*/

int retard (MYSQL mysql){

	// DEFINIR ET EXECUTER LA REQUETE
	mysql_query(&mysql, "SELECT num_emprunt FROM emprunt WHERE date_retour > delai_retour");
	
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	
	result = mysql_store_result(&mysql);
	unsigned int num_champs = 0;
	unsigned int i = 0;
	
	if (mysql_num_rows(result) == 0)
	{
		printf("PAS DE RETARDAIRE \n");
	}else
	{
		num_champs = mysql_num_fields(result);
		printf("LISTE DES RETARDATAIRES \n");
		
		while ((row = mysql_fetch_row(result)))
		{
			unsigned long *lenghts;
			
			lenghts = mysql_fetch_lengths(result);
			
			for (i = 0; i < num_champs; i++)
			{
				printf("%*s - ", (int) lenghts[i], row[i] ? row[i] : NULL);
				if (i == num_champs - 1){ 
					printf("\n");
					printf("---------------------------------- \n");
				}
			}
		}	
	}
	return 0;
}

/* FIN DE LA FONCTION RETARDATAIRES */

//===============================================

/*
	CETTE FONCTION PERMET DE VERIFIE SI L'ADHERENT A RETOURNE LE LIVRE EN RETARD
*/


int verifie(MYSQL mysql, const char* ref_livre, const char* num_adh, const char* date_ret){

		char requete[600] = "";
		sprintf(requete, "SELECT * FROM emprunt WHERE num_emprunt = '%s' AND reference = '%s' AND delai_retour >'%s'", num_adh, ref_livre, date_ret);
		//printf("%s\n", requete);
		mysql_query(&mysql, requete); // EXECUTION DE LA REQUETE
		
		// DECLARATION DES OBJECTS DE REQUETE
		MYSQL_RES *result = NULL;
		MYSQL_ROW row;
		
		unsigned int i = 0;
		//unsigned int num_champs = 0; // STOCK LE NOMBRE DE CHAMPS D'UNE REQUETE
		
		result = mysql_store_result(&mysql); // MET LES RESULTATS DANS RESULT
		unsigned int num_rows = mysql_num_rows(result);
		if (num_rows == 0)
		{
			mysql_free_result(result);
			return 0;
		}else 
		{
			mysql_free_result(result);
			return 1;
		}
		
}

/* FIN DE LA FONCTION VERIFIE */

//==============================================================

/*
	CETTE FONCTION PERMET DE LISTER LES EMPRUNTS
*/

int listemprunt (MYSQL mysql){

	// FORMULER LA REQUETE ET L'EXECUTER
	char requete[300] = "";
	sprintf(requete, "SELECT num_emprunt, reference, date_sortie FROM emprunt;");
	printf("%s \n", requete);
	mysql_query(&mysql, requete);
	printf("Requete...\n");
	
	// POINTEUR DE STRUCTURE POUR PARCOURIR LES RESULTATS DE LA REQUETE (les objets de la requete)
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	
	unsigned int i = 0;
	unsigned int num_champs = 0;
	
	// RECUPERER LE JEU DE DONNEES DANS LE POINTEUR RESULT
	result = mysql_store_result(&mysql);
	
	num_champs = mysql_num_fields(result);
	
	printf("[ADHERENT] - [REFERENCE] - [DATE SORTIE] \n");
	printf("---------------------------------- \n");
	// BOUCLER SUR LES DATA 
	while ((row = mysql_fetch_row(result)))
	{
		// POINTEUR TYPE LONG NON SIGNE POUR STOCKER LA TAILLES DES VALEURS
		unsigned long *lenghts;
		
		//ON STOCK LES TAILLES DES VALEURS DANS LE POINTEUR
		lenghts = mysql_fetch_lengths(result);
		
		for (i = 0; i < num_champs; i++)
		{
			printf("%*s - ", (int) lenghts[i], row[i] ? row[i] : NULL);
			if (i == num_champs - 1){ 
			printf("\n");
			printf("---------------------------------- \n");
			}
		}
		
	}
	mysql_free_result(result);
	return 0;
}

/* FIN DE LA FONCTION LISTE DES EMPRUNT */

//======================================================

/* DEBUT FONCTION POUR LES STATISTIQUE */

void stats (MYSQL mysql){
	char requete[300] = "";
	sprintf(requete, "SELECT monthname(date_achat) as mois, year(date_achat) as annee, count(auteur) as nombre FROM biblio.livre GROUP BY mois,annee HAVING mois is not null AND annee is not null");
	mysql_query(&mysql, requete);
	
	// POINTEUR DE STRUCTURE POUR PARCOURIR LES RESULTATS DE LA REQUETE (les objets de la requete)
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	
	unsigned int i = 0;
	unsigned int num_champs = 0;
	
	// RECUPERER LE JEU DE DONNEES DANS LE POINTEUR RESULT
	result = mysql_store_result(&mysql);
	
	num_champs = mysql_num_fields(result);
	printf("Le nombre de livres empruntés par mois la même année\n");
	printf("=====================================================\n");
	printf("[MOIS] - [ANNEE] - [NOMBRE] \n");
	printf("---------------------------------- \n");
	// BOUCLER SUR LES DATA 
	while ((row = mysql_fetch_row(result)))
	{
		// POINTEUR TYPE LONG NON SIGNE POUR STOCKER LA TAILLES DES VALEURS
		unsigned long *lenghts;
		
		//ON STOCK LES TAILLES DES VALEURS DANS LE POINTEUR
		lenghts = mysql_fetch_lengths(result);
		
		for (i = 0; i < num_champs; i++)
		{
			printf("%*s  - ", (int) lenghts[i], row[i] ? row[i] : NULL);
			if (i == num_champs - 1){ 
			printf("\n");
			printf("---------------------------------- \n");
			}
		}
		
	}
	mysql_free_result(result);
}



