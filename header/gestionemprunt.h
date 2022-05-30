#include <mysql/mysql.h>

#ifndef _H_PRINCIPAL_H
#define _H_PRINCIPAL_H

int principal();

#endif


#ifndef _H_VIDERBUFFER_H
#define _H_VIDERBUFFER_H

void viderBuffer();

#endif

#ifndef _H_LIRE_H
#define _H_LIRE_H

int lire(char *chaine, int longueur);

#endif

#ifndef _H_CON_H
#define _H_CON_H

int con (int ch);

#endif

#ifndef _H_EMPRUNT_H
#define _H_EMPRUNT_H

int emprunt(MYSQL mysql, const char* num, const char* ref, const char* date_act, const char* date_delai);

#endif

#ifndef _H_RETOURNER_H
#define _H_RETOURNER_H

int retourner (MYSQL mysql, const char* date_ret, const char* num_adh, const char* ref_livre);

#endif

#ifndef _H_LASTID_H
#define _H_LASTID_H

unsigned int lastid(MYSQL mysql);

#endif

#ifndef _H_LISTLIVRE_H
#define _H_LISTLIVRE_H

int listlivre(MYSQL mysql);

#endif

#ifndef _H_NOEXISTLIVRE_H
#define _H_NOEXISTLIVRE_H

unsigned int noexistlivre(MYSQL mysql, const char* ref);

#endif

#ifndef _H_RETARD_H
#define _H_RETARD_H

int retard (MYSQL mysql);

#endif

#ifndef _H_VERIFIE_H
#define _H_VERIFIE_H

int verifie(MYSQL mysql, const char* ref_livre, const char* num_adh, const char* date_ret);

#endif

#ifndef _H_AJOUTLIVRE_H
#define _H_AJOUTLIVRE_H

int ajoutlivre (MYSQL mysql, char* ref, char* aut, char* titre, char* edit, char* cat, char* date_achat, int prix);

#endif

#ifndef _H_LISTEMPRUNT_H
#define _H_LISTEMPRUNT_H

int listemprunt(MYSQL mysql);

#endif

#ifndef _H_STATS_H
#define _H_STATS_H

void stats (MYSQL mysql);

#endif
