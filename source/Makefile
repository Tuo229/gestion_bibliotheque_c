GEST : menu.o adherent.o db.o connexion.o search_adherent.o modify_adherent.o principal.o gestionemprunt.o
	gcc -o GEST menu.o connexion.o adherent.o search_adherent.o modify_adherent.o db.o principal.o gestionemprunt.o -lmysqlclient
	
menu.o : menu.c
	gcc -c menu.c
	
db.o : db.c
	gcc -c db.c
	
adherent.o : adherent.c
	gcc -c adherent.c
	
search_adherent.o : search_adherent.c
	gcc -c search_adherent.c
	
modify_adherent.o : modify_adherent.c
	gcc -c modify_adherent.c
	
connexion.o : connexion.c
	gcc -c connexion.c

principal.o: principal.c
	gcc -c principal.c
	
gestionemprunt.o: gestionemprunt.c
	gcc -c gestionemprunt.c
	
clean : 
	rm *.o
