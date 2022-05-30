#include <stdio.h> 
#ifndef H_DB_H
#define H_DB_H

   struct Person {
  	char matricule[15];
  	char nom[15];
  	char prenom[15]; 
  	char telephone[15]; 	
  };

int db(struct Person adher,int a,int b);

#endif
