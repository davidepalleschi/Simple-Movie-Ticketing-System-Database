#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"


static void verifica_biglietto(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	// Input for the registration routine
	char codicePrenotazione[46];

	printf("\nCodice prenotazione: ");
	getInput(64, codicePrenotazione, false);
	int codiceprenotazionei = atoi(codicePrenotazione);

	// Convert values

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call VerificaBiglietto(?)", conn)) {
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
		printf("Biglietto verificato correttamente...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

void run_as_maschera(MYSQL *conn)
{
	char options[2] = {'1','2'};
	char op;
	
	printf("Switching to maschera role...\n");

	if(!parse_config("users/maschera.json", &conf)) {
		fprintf(stderr, "Unable to load administrator configuration\n");
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
		printf("1) Verifica biglietto\n");
		printf("2) Quit\n");

		op = multiChoice("Select an option", options, 2);

		switch(op) {
			case '1':
				verifica_biglietto(conn);
				break;
				
			case '2':
				exit(1);
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
