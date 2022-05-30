#install.packages("RMySQL")
#install.packages("ggplot2")
#install.packages("magrittr") # package installations are only needed the first time you use it
#install.packages("dplyr")    # alternative installation of the %>%
library(magrittr) # needs to be run every time you start R and want to use %>%
library(dplyr) 
library(ggplot2)
library(RMySQL)

rstats <- function(){
	mydb = dbConnect(MySQL(), user="debian-sys-maint", password="FHwmWbTuAwgXn89F", dbname='biblio', host='localhost')

	dbListTables(mydb)

	dbListFields(mydb, 'adherent')

	rs = dbSendQuery(mydb, "select * from adherent")

	data = fetch(rs, n=-1)

	dbReadTable(mydb,"livre")




	query <- "SELECT monthname(date_achat) as mois, year(date_achat) as annee, count(auteur) as nombre 
	FROM biblio.livre 
	GROUP BY mois,annee
	HAVING mois is not null AND annee is not null;"


	results <- dbSendQuery(mydb, query)
	db_results <- dbFetch(results)
	dbClearResult(results)

	#Preview of our results
	head(db_results)


	print("-----------------------------------------")


	query <- "SELECT prix as prix, count(auteur) as nombre 
	FROM biblio.livre 
	GROUP BY prix
	HAVING prix is not null;"


	results <- dbSendQuery(mydb, query)
	db_results <- dbFetch(results)
	dbClearResult(results)

	#Preview of our results
	head(db_results)
	}


