#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

static void aggiungi_apertura(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;


	// Input for the registration routine
	char nomeCinema[46];
	
	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nNome cinema: ");
	getInput(64, nomeCinema, false);
	
	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AggiungiApertura(?, ?, ?,)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = nomeCinema;
	param[0].buffer_length = strlen(nomeCinema);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &inizio;
	param[1].buffer_length = sizeof(inizio);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;
	param[2].buffer = &fine;
	param[2].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Apertura aggiunta correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_film(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[4];
	MYSQL_TIME date;

	// Input for the registration routine
	char titolo[46];
	char ore[64];
	char minuti[64];
	char secondi[64];
	char cast[64];
	char casacinema[64];

	// Get the required information
	printf("\nTitolo: ");
	getInput(64, titolo, false);
	
	printf("\nOre: ");
	getInput(64, ore, false);
	int orei = atoi(ore);
	
	printf("\nMinuti: ");
	getInput(64, minuti, false);
	int minutii = atoi(minuti);
	
	printf("\nSecondi: ");
	getInput(64, secondi, false);
	int secondii = atoi(secondi);

	printf("\nCast: ");
	getInput(64, cast, false);

	printf("\nCasa cinematografica: ");
	getInput(64, casacinema, false);

	date.hour = orei;
	date.minute = minutii;
	date.second = secondii;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AggiungiFilm(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = titolo;
	param[0].buffer_length = strlen(titolo);

	param[1].buffer_type = MYSQL_TYPE_DATE;
	param[1].buffer = &date;
	param[1].buffer_length = sizeof(date);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = cast;
	param[2].buffer_length = strlen(cast);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = casacinema;
	param[3].buffer_length = strlen(casacinema);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Film aggiunto correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_proiezione(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[5];
	MYSQL_TIME date;

	// Input for the registration routine
	char ore[64];
	char minuti[64];
	char secondi[64];
	char giorno[64];
	char mese[64];
	char anno[64];

	char costo[64];
	char numeroSala[64];
	char nomeCinema[64];
	char titoloFilm[64];


	printf("\nGiorno: ");
	getInput(64, giorno, false);
	int giornoi = atoi(giorno);
	
	printf("\nMese: ");
	getInput(64, mese, false);
	int mesei = atoi(mese);

	printf("\nAnno: ");
	getInput(64, anno, false);
	int annoi = atoi(anno);

	printf("\nOre: ");
	getInput(64, ore, false);
	int orei = atoi(ore);
	
	printf("\nMinuti: ");
	getInput(64, minuti, false);
	int minutii = atoi(minuti);
	
	printf("\nSecondi: ");
	getInput(64, secondi, false);
	int secondii = atoi(secondi);

	// Get the required information
	printf("\nCosto: ");
	getInput(64, costo, false);
	int costoi = atoi(costo);

	printf("\nNumero sala: ");
	getInput(64, numeroSala, false);
	int numerosalai = atoi(numeroSala);

	printf("\nNome cinema: ");
	getInput(64, nomeCinema, false);

	printf("\nTitolo film: ");
	getInput(64, titoloFilm, false);


	date.hour = orei;
	date.minute = minutii;
	date.second = secondii;
	date.day = giornoi;
	date.month = mesei;
	date.year = annoi;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AggiungiProiezione(?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_DATETIME;
	param[0].buffer = &date;
	param[0].buffer_length = sizeof(date);

	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &costoi;
	param[1].buffer_length = sizeof(int);

	param[2].buffer_type = MYSQL_TYPE_LONG;
	param[2].buffer = &numerosalai;
	param[2].buffer_length = sizeof(int);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = nomeCinema;
	param[3].buffer_length = strlen(nomeCinema);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = titoloFilm;
	param[4].buffer_length = strlen(titoloFilm);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Proiezione aggiunta correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_proiezionista(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	MYSQL_TIME date;

	// Input for the registration routine
	char nomeProiezionista[64];
	char nomeCinema[64];

	printf("\nNome proiezionista: ");
	getInput(64, nomeProiezionista, false);
	
	printf("\nNome cinema: ");
	getInput(64, nomeCinema, false);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AggiungiProiezionista(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = nomeProiezionista;
	param[0].buffer_length = strlen(nomeCinema);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = nomeCinema;
	param[1].buffer_length = strlen(nomeCinema);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Proiezionista aggiunto correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_maschera(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	MYSQL_TIME date;

	// Input for the registration routine
	char nomeMaschera[64];
	char nomeCinema[64];

	printf("\nNome maschera: ");
	getInput(64, nomeMaschera, false);
	
	printf("\nNome cinema: ");
	getInput(64, nomeCinema, false);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AggiungiMaschera(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = nomeMaschera;
	param[0].buffer_length = strlen(nomeCinema);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = nomeCinema;
	param[1].buffer_length = strlen(nomeCinema);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Proiezionista aggiunto correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_giorno_calendario(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;
	
	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AggiungiGiornoCalendario(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_DATETIME;
	param[0].buffer = &inizio;
	param[0].buffer_length = sizeof(inizio);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &fine;
	param[1].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Giorno-calendario aggiunto correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void assegna_turno_maschera(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;


	// Input for the registration routine
	char codiceMaschera[46];

	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nCodice maschera: ");
	getInput(64, codiceMaschera, false);
	int codicemascherai = atoi(codiceMaschera);
	
	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AssegnaTurnoMaschera(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codicemascherai;
	param[0].buffer_length = sizeof(int);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &inizio;
	param[1].buffer_length = sizeof(inizio);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;
	param[2].buffer = &fine;
	param[2].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Maschera assegnata correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void assegna_turno_proiezionista(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;


	// Input for the registration routine
	char codiceProiezionista[46];

	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nCodice proiezionista: ");
	getInput(64, codiceProiezionista, false);
	int codiceproiezionistai = atoi(codiceProiezionista);
	
	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call AssegnaTurnoProiezionista(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codiceproiezionistai;
	param[0].buffer_length = sizeof(int);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &inizio;
	param[1].buffer_length = sizeof(inizio);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;
	param[2].buffer = &fine;
	param[2].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Maschera assegnata correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_apertura(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;

	// Input for the registration routine
	char cinemaNome[64];

	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nNome cinema: ");
	getInput(64, cinemaNome, false);
	
	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaApertura(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cinemaNome;
	param[0].buffer_length = strlen(cinemaNome);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &inizio;
	param[1].buffer_length = sizeof(inizio);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;
	param[2].buffer = &fine;
	param[2].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Maschera assegnata correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_proiezione(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME date;

	// Input for the registration routine
	char codice[64];

	// Get the required information
	printf("\nCodice: ");
	getInput(64, codice, false);
	int codicei = atoi(codice);

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaProiezione(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codicei;
	param[0].buffer_length =sizeof(int);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Proiezione cancellata correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_film(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME date;

	// Input for the registration routine
	char titolo[64];

	// Get the required information
	printf("\nTitolo: ");
	getInput(64, titolo, false);

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaFilm(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = titolo;
	param[0].buffer_length = strlen(titolo);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Film cancellato correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_maschera(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME date;

	// Input for the registration routine
	char codiceMaschera[64];

	// Get the required information
	printf("\nCodice maschera: ");
	getInput(64, codiceMaschera, false);
	int codicemascherai = atoi(codiceMaschera);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaMaschera(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codicemascherai;
	param[0].buffer_length = sizeof(int);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Film cancellato correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_prenotazione(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME date;

	// Input for the registration routine
	char codicePrenotazione[64];

	// Get the required information
	printf("\nCodice prenotazione: ");
	getInput(64, codicePrenotazione, false);
	int codiceprenotazionei = atoi(codicePrenotazione);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaPrenotazione(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codiceprenotazionei;
	param[0].buffer_length = sizeof(int);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Film cancellato correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_proiezionista(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME date;

	// Input for the registration routine
	char codiceProiezionista[64];

	// Get the required information
	printf("\nCodice proiezionista: ");
	getInput(64, codiceProiezionista, false);
	int codiceproiezionistai = atoi(codiceProiezionista);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaProiezionista(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codiceproiezionistai;
	param[0].buffer_length = sizeof(int);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Film cancellato correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_giorno_calendario(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;
	
	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaGiornoCalendario(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_DATETIME;
	param[0].buffer = &inizio;
	param[0].buffer_length = sizeof(inizio);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &fine;
	param[1].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Giorno-calendario aggiunto correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_turno_maschera(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;


	// Input for the registration routine
	char codiceMaschera[46];

	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nCodice maschera: ");
	getInput(64, codiceMaschera, false);
	int codicemascherai = atoi(codiceMaschera);
	
	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaTurnoaMaschera(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codicemascherai;
	param[0].buffer_length = sizeof(int);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &inizio;
	param[1].buffer_length = sizeof(inizio);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;
	param[2].buffer = &fine;
	param[2].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Maschera assegnata correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void cancella_turno_proiezionista(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME inizio;
	MYSQL_TIME fine;


	// Input for the registration routine
	char codiceProiezionista[46];

	char minutoInizio[64];
	char oraInizio[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];

	char minutoFine[64];
	char oraFine[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nCodice proiezionista: ");
	getInput(64, codiceProiezionista, false);
	int codiceproiezionistai = atoi(codiceProiezionista);
	
	printf("\nOra apertura: ");
	getInput(64, oraInizio, false);
	int orainizioi = atoi(oraInizio);
	
	printf("\nMinuto apertura: ");
	getInput(64, minutoInizio, false);
	int minutoinizioi = atoi(minutoInizio);
	
	printf("\nGiorno apertura: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	printf("\nMese apertura: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	printf("\nAnno apertura: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	printf("\nMinuto chiusura: ");
	getInput(64, minutoFine, false);
	int minutofinei = atoi(minutoFine);

	printf("\nOra chiusura: ");
	getInput(64, oraFine, false);
	int orafinei = atoi(oraFine);
	
	printf("\nGiorno chiusura: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	printf("\nMese chiusura: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	printf("\nAnno chiusura: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	inizio.minute = minutoinizioi;
	inizio.hour = orainizioi;
	inizio.day = giornoinizioi;
	inizio.month = meseinizioi;
	inizio.year = annoinizioi;

	fine.minute = minutofinei;
	fine.hour = orafinei;
	fine.day = giornofinei;
	fine.month = mesefinei;
	fine.year = annofinei;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaTurnoProiezione(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codiceproiezionistai;
	param[0].buffer_length = sizeof(int);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = &inizio;
	param[1].buffer_length = sizeof(inizio);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;
	param[2].buffer = &fine;
	param[2].buffer_length = sizeof(fine);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Maschera assegnata correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void vedi_aperture(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediAperture()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_calendario(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediCalendario()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_maschere(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediMaschere()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_proiezioni(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediProiezioni()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_proiezionisti(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediProiezionisti()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_turno_maschere(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediTurnoMaschere()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_turno_proiezionisti(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediTurnoProiezionisti()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void vedi_film(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call VediFilm()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTitolo\nDurata\nCast\nCasa cinematografica");
	mysql_stmt_close(prepared_stmt);

}

static void genera_report_dipendenti(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	MYSQL_TIME data_inizio;
	MYSQL_TIME data_fine;

	// Input for the registration routine
	char nomeCinema[64];
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nNome cinema: ");
	getInput(64, nomeCinema, false);

	// Get the required information
	printf("\nGiorno inizio: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	// Get the required information
	printf("\nMese inizio: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	// Get the required information
	printf("\nAnno inizio: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	// Get the required information
	printf("\nGiorno fine: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	// Get the required information
	printf("\nGiorno inizio: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	// Get the required information
	printf("\nGiorno inizio: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	data_inizio.day = giornoinizioi;
	data_inizio.month = meseinizioi;
	data_inizio.year = annoinizioi;

	data_fine.day = giornofinei;
	data_fine.month = mesefinei;
	data_fine.year = annofinei;

	if(!setup_prepared_stmt(&prepared_stmt, "call GeneraReportDipendenti(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

		// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = nomeCinema;
	param[0].buffer_length = strlen(nomeCinema);

	param[1].buffer_type = MYSQL_TYPE_DATE;
	param[1].buffer = &data_inizio;
	param[1].buffer_length = sizeof(data_inizio);

	param[2].buffer_type = MYSQL_TYPE_DATE;
	param[2].buffer = &data_fine;;
	param[2].buffer_length = sizeof(data_fine);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nGiorno\nApertura cinema\nMaschere\nProiezionisti\nSale utilizzate\nProblemi\n");
	mysql_stmt_close(prepared_stmt);

}

static void genera_report_prenotazioni(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	MYSQL_TIME data_inizio;
	MYSQL_TIME data_fine;

	// Input for the registration routine
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];
	char giornoFine[64];
	char meseFine[64];
	char annoFine[64];

	// Get the required information
	printf("\nGiorno inizio: ");
	getInput(64, giornoInizio, false);
	int giornoinizioi = atoi(giornoInizio);

	// Get the required information
	printf("\nMese inizio: ");
	getInput(64, meseInizio, false);
	int meseinizioi = atoi(meseInizio);

	// Get the required information
	printf("\nAnno inizio: ");
	getInput(64, annoInizio, false);
	int annoinizioi = atoi(annoInizio);

	// Get the required information
	printf("\nGiorno fine: ");
	getInput(64, giornoFine, false);
	int giornofinei = atoi(giornoFine);

	// Get the required information
	printf("\nGiorno inizio: ");
	getInput(64, meseFine, false);
	int mesefinei = atoi(meseFine);

	// Get the required information
	printf("\nGiorno inizio: ");
	getInput(64, annoFine, false);
	int annofinei = atoi(annoFine);

	data_inizio.day = giornoinizioi;
	data_inizio.month = meseinizioi;
	data_inizio.year = annoinizioi;

	data_fine.day = giornofinei;
	data_fine.month = mesefinei;
	data_fine.year = annofinei;

	if(!setup_prepared_stmt(&prepared_stmt, "call GeneraReportPrenotazioni(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

		// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_DATE;
	param[0].buffer = &data_inizio;
	param[0].buffer_length = sizeof(data_inizio);

	param[1].buffer_type = MYSQL_TYPE_DATE;
	param[1].buffer = &data_fine;;
	param[1].buffer_length = sizeof(data_fine);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nCinema\nSala\nPrenotazioni utilizzate\nPrenotazioni cancellate\nPrenotazioni non utilizzate\n");
	mysql_stmt_close(prepared_stmt);

}

void run_as_amministratore(MYSQL *conn)
{
	printf("Switching to administrative role...\n");

	if(!parse_config("users/amministratore.json", &conf)) {
		fprintf(stderr, "Unable to load administrator configuration\n");
		exit(EXIT_FAILURE);
	}

	

	while(true) {

		conn = mysql_init (NULL);
		if (mysql_real_connect(conn, conf.host, conf.db_username, conf.db_password, conf.database, conf.port, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL) {
		fprintf (stderr, "mysql_real_connect() failed\n");
		mysql_close (conn);
		exit(EXIT_FAILURE);
		}
		printf("\033[2J\033[H");
		printf("*** What should I do for you? ***\n\n");
		printf("1) Aggiungi film\n");
		printf("2) Aggiungi proiezione\n");
		printf("3) Aggiungi maschera\n");
		printf("4) Aggiungi proiezionista\n");
		printf("5) Aggiungi giorno apertura\n");
		printf("6) Assegna turno maschera\n");
		printf("7) Assegna turno proiezionista\n");
		printf("8) Cancella film\n");
		printf("9) Cancella proiezione\n");
		printf("10) Cancella maschera\n");
		printf("11) Cancella proiezionista\n");
		printf("12) Cancella giorno calendario\n");
		printf("13) Cancella apertura\n");
		printf("14) Cancella turno maschera\n");
		printf("15) Cancella turno proiezionista\n");
		printf("16) Vedi film\n");
		printf("17) Vedi proiezioni\n");
		printf("18) Vedi maschere\n");
		printf("19) Vedi proiezionisti\n");
		printf("20) Vedi giorni apertura\n");
		printf("21) Vedi turno maschere\n");
		printf("22) Vedi turno proiezionisti\n");
		printf("23) Genera report dipendenti\n");
		printf("24) Genera report prenotazione\n");
		printf("25) Quit\n");

			char scelta[64];
		// Get the required information
	printf("\nInserisci una scelta: ");
	getInput(64, scelta, false);
	int sceltai = atoi(scelta);

		switch(sceltai) {
			case 1:
				aggiungi_film(conn);
				break;
			case 2:
				aggiungi_proiezione(conn);
				break;
			case 3:
				aggiungi_maschera(conn);
				break;
			case 4:
				aggiungi_proiezionista(conn);
				break;
			case 5:
				aggiungi_giorno_calendario(conn);
				break;
			case 6:
				assegna_turno_maschera(conn);
				break;
			case 7:
				assegna_turno_proiezionista(conn);
				break;
			case 8:
				cancella_film(conn);
				break;
			case 9:
				cancella_proiezione(conn);
				break;
			case 10:
				cancella_maschera(conn);
				break;
			case 11:
				cancella_proiezionista(conn);
				break;
			case 12:
				cancella_giorno_calendario(conn);
				break;
			case 13:
				cancella_apertura(conn);
				break;
			case 14:
				cancella_turno_maschera(conn);
				break;
			case 15:
				cancella_turno_proiezionista(conn);
				break;
			case 16:
				vedi_film(conn);
				break;
			case 17:
				vedi_proiezioni(conn);
				break;
			case 18:
				vedi_maschere(conn);
				break;	
			case 19:
				vedi_proiezionisti(conn);
				break;
			case 20:
				vedi_aperture(conn);
				break;
			case 21:
				vedi_turno_maschere(conn);
				break;
			case 22:
				vedi_turno_proiezionisti(conn);
				break;
			case 23:
				genera_report_dipendenti(conn);
				break;
			case 24:
				genera_report_prenotazioni(conn);
				break;		
			case 25:
				exit(1);
				break;		
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}
		getchar();
		mysql_close(conn);
	}
}

