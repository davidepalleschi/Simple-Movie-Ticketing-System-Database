#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

#define MAX_DEGREES 128

static void prenotazione(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	MYSQL_TIME giorno;

	// Input for the registration routine
	char giornoInizio[64];
	char meseInizio[64];
	char annoInizio[64];
	char cinema[64];

	// Get the required information
	printf("\nCinema: ");
	getInput(64, cinema, false);

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

	giorno.day = giornoinizioi;
	giorno.month = meseinizioi;
	giorno.year = annoinizioi;

	if(!setup_prepared_stmt(&prepared_stmt, "call ProiezioniGiornoCinema(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cinema;
	param[0].buffer_length = strlen(cinema);

	param[1].buffer_type = MYSQL_TYPE_DATE;
	param[1].buffer = &giorno;
	param[1].buffer_length = sizeof(giorno);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nCodice\nOrario\nCosto\nNumero sala\nNome cinema\nTitolo film\n");
	mysql_stmt_close(prepared_stmt);

	mysql_close(conn);
	conn = mysql_init (NULL);
	if(!parse_config("users/cliente.json", &conf)) {
		fprintf(stderr, "Unable to load student configuration\n");
		exit(EXIT_FAILURE);
	}

	if (mysql_real_connect(conn, conf.host, conf.db_username, conf.db_password, conf.database, conf.port, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL) {
		fprintf (stderr, "mysql_real_connect() failed\n");
		mysql_close (conn);
		exit(EXIT_FAILURE);
	}

	MYSQL_STMT *prepared_stmt1;

	MYSQL_BIND param1[1];

	char codiceProiezione[64];

	// Get the required information
	printf("\nCodice proiezione: ");
	getInput(64, codiceProiezione, false);
	int codiceproiezionei = atoi(codiceProiezione);

	if(!setup_prepared_stmt(&prepared_stmt1, "call PostiLiberi(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt1, "Unable to initialize...\n", false);
	}

		// Prepare parameters
	memset(param1, 0, sizeof(param1));

	param1[0].buffer_type = MYSQL_TYPE_LONG;
	param1[0].buffer = &codiceproiezionei;
	param1[0].buffer_length = sizeof(int);

	if (mysql_stmt_bind_param(prepared_stmt1, param1) != 0) {
		finish_with_stmt_error(conn, prepared_stmt1, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt1) != 0) {
		finish_with_stmt_error(conn, prepared_stmt1, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt1, "\nFila\nNumero");
	mysql_stmt_close(prepared_stmt1);

	mysql_close(conn);
	conn = mysql_init (NULL);
	if(!parse_config("users/cliente.json", &conf)) {
		fprintf(stderr, "Unable to load student configuration\n");
		exit(EXIT_FAILURE);
	}

	if (mysql_real_connect(conn, conf.host, conf.db_username, conf.db_password, conf.database, conf.port, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL) {
		fprintf (stderr, "mysql_real_connect() failed\n");
		mysql_close (conn);
		exit(EXIT_FAILURE);
	}
	
	MYSQL_STMT *prepared_stmt2;

	MYSQL_BIND param2[3];

	char postoFila[64];
	char postoNumero[64];

	// Get the required information
	printf("\nFila del posto: ");
	getInput(64, postoFila, false);

	// Get the required information
	printf("\nNumero del posto: ");
	getInput(64, postoNumero, false);
	int postonumeroi = atoi(postoNumero);

	if(!setup_prepared_stmt(&prepared_stmt2, "call IniziaPrenotazione(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt2, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param2, 0, sizeof(param2));

	param2[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param2[0].buffer = postoFila;
	param2[0].buffer_length = strlen(postoFila);

	param2[1].buffer_type = MYSQL_TYPE_LONG;
	param2[1].buffer = &postonumeroi;
	param2[1].buffer_length = sizeof(int);

	param2[2].buffer_type = MYSQL_TYPE_LONG;
	param2[2].buffer = &codiceproiezionei;
	param2[2].buffer_length = sizeof(int);

	if (mysql_stmt_bind_param(prepared_stmt2, param2) != 0) {
		finish_with_stmt_error(conn, prepared_stmt2, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt2) != 0) {
		finish_with_stmt_error(conn, prepared_stmt2, "Could not retrieve exam list\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt2, "\nCodice di prenotazione temporaneo");
	mysql_stmt_close(prepared_stmt2);

	mysql_close(conn);
	conn = mysql_init (NULL);
	if(!parse_config("users/cliente.json", &conf)) {
		fprintf(stderr, "Unable to load student configuration\n");
		exit(EXIT_FAILURE);
	}

	if (mysql_real_connect(conn, conf.host, conf.db_username, conf.db_password, conf.database, conf.port, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL) {
		fprintf (stderr, "mysql_real_connect() failed\n");
		mysql_close (conn);
		exit(EXIT_FAILURE);
	}

	MYSQL_STMT *prepared_stmt3;
	MYSQL_BIND param3[5];
	MYSQL_TIME dataScadenza;

	// Input for the registration routine
	char codicePrenotazione[64];
	char numeroCarta[64];
	char intestatario[64];
	char meseScadenza[64];
	char annoScadenza[64];
	char cvv[64];


	// Get the required information
	printf("\nCodice prenotazione: ");
	getInput(64, codicePrenotazione, false);
	int codiceprenotazionei = atoi(codicePrenotazione);

	// Get the required information
	printf("\nNumero carta: ");
	getInput(64, numeroCarta, false);

	// Get the required information
	printf("\nIntestatario: ");
	getInput(64, intestatario, false);

	// Get the required information
	printf("\nMese scadenza: ");
	getInput(64, meseScadenza, false);
	int mesescadenzai = atoi(meseScadenza);

	// Get the required information
	printf("\nAnno scadenza: ");
	getInput(64, annoScadenza, false);
	int annoscadenzai = atoi(annoScadenza);

	// Get the required information
	printf("\nCVV: ");
	getInput(64, cvv, false);
	int cvvi = atoi(cvv);

	dataScadenza.day = 1;
	dataScadenza.month = mesescadenzai;
	dataScadenza.year = annoscadenzai;

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt3, "call ConfermaPrenotazione(?,?,?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param3, 0, sizeof(param3));


	param3[0].buffer_type = MYSQL_TYPE_LONG;
	param3[0].buffer = &codiceprenotazionei;
	param3[0].buffer_length = sizeof(int);

	param3[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param3[1].buffer = numeroCarta;
	param3[1].buffer_length = strlen(numeroCarta);

	param3[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param3[2].buffer = intestatario;
	param3[2].buffer_length = strlen(intestatario);

	param3[3].buffer_type = MYSQL_TYPE_DATE;
	param3[3].buffer = &dataScadenza;
	param3[3].buffer_length = sizeof(dataScadenza);

	param3[4].buffer_type = MYSQL_TYPE_LONG;
	param3[4].buffer = &cvvi;
	param3[4].buffer_length = sizeof(int);

	if (mysql_stmt_bind_param(prepared_stmt3, param3) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt3) != 0) {
		print_stmt_error (prepared_stmt3, "An error occurred while registering the student.");
	} else {
		printf("Prenotazione inserita correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt3);

}

static void cancella_prenotazione(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	// Input for the registration routine
	char codicePrenotazione[64];

	printf("\nCodice Prenotazione: ");
	getInput(64, codicePrenotazione, false);
	int codicePrenotazionei=atoi(codicePrenotazione);
	

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call CancellaPrenotazione(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize...\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));


	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &codicePrenotazionei;
	param[0].buffer_length = sizeof(int);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the student.");
	} else {
		printf("Cancellazione Prenotazione effettuata...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

void run_as_cliente(MYSQL *conn)
{
	char options[3] = {'1','2','3'};
	char op;
	
	printf("Switching to cliente role...\n");

	if(!parse_config("users/cliente.json", &conf)) {
		fprintf(stderr, "Unable to load cliente configuration\n");
		exit(EXIT_FAILURE);
	}

	if (mysql_real_connect(conn, conf.host, conf.db_username, conf.db_password, conf.database, conf.port, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL) {
		fprintf (stderr, "mysql_real_connect() failed\n");
		mysql_close (conn);
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** What should I do for you? ***\n\n");
		printf("1) Prenota biglietto\n");
		printf("2) Cancella Prenotazione\n");
		printf("3) Quit\n");

		op = multiChoice("Select an option", options, 2);

		switch(op) {
				
			case '1':
				prenotazione(conn);
				return;

			case '2':
				cancella_prenotazione(conn);
			
			case '3':
				exit(1);
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
