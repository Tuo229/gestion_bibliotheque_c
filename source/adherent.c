#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/adherent.h"
#include "../header/db.h"
#include "../header/gestionemprunt.h"


void register_adherent(){


  
  struct Person adher ;
  lire(adher.matricule, 15);
  printf ("Entrez le matricule de l'adhérent = ");
  lire(adher.matricule, 15);
  
  printf ("Entrez le nom de l'adhérent = ");
  scanf ("%s",adher.nom);
  
  printf ("Entrez le prénom de l'adhérent = ");
  scanf ("%s",adher.prenom);
  
  printf ("Entrez le téléphone de l'adhérent = ");
  scanf ("%s",adher.telephone);
  

  db(adher,1,0);
  
}

