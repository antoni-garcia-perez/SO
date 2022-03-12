#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi?n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexin
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "basedatos",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	char consulta[200];
	strcpy (consulta,"SELECT jugadores.nickname FROM (jugadores,partidas)  WHERE jugadores.id = (SELECT idJ1 and idJ2 FROM relacion GROUP BY idJ1 and idJ2 ORDER BY count(*) DESC LIMIT 1);");
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	
	int contador = 0;
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while ((row !=NULL) && (contador == 0)) {
			// la columna 0 contiene el nombre del jugador
			printf ("%s\n", row[0]);
			contador++;
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}
		
		mysql_close (conn);
		exit(0);
		
		return 0;
}
