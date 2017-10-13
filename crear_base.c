#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "common.h"

int main (int argc, char *argv[])
{
	FILE *fentrada;
	status_t st;
	char *linea,c;
	int cant_lineas;
			/************* DECLARACION DE VARIABLES *************/
	char *cadena[] = {"12658,Persona 5,Atlus,PS4,20170404,94,73",
					  "68536,Zelda: Breath of the Wild,Nintendo,Switch,20170303,97,10"}; /* todavia no creo el campo time_t, simplemente meto otro size_t*/
	char ** arreglo;
	char delimitador;
	size_t longitud; /* aca tambien uso un auxiliar de fechas*/
	int i;
	juego_t juego; /*ptr_juego;*/

	/************* INICIALIZACION DE VARIABLES *************/
	longitud = 0;
	arreglo = NULL;
	delimitador = ',';
	i = 0;
	/*ptr_juego = &juego;*/

	linea = NULL;
	if((st = validar_argumentos(argc,argv,&fentrada))!=ST_OK)
	{
		fprintf(stderr, "Error en alguna validacion\n");
		return EXIT_FAILURE;
	}

	do
	{
		if((st=leer_linea(fentrada,&cant_lineas,&linea,&c)) != ST_OK)
		{
			if(linea != NULL)
			{
				free(linea);
				linea = NULL;
			}
			return EXIT_FAILURE;
		}
		printf("Linea %d) %s\n",cant_lineas +1,linea);
		free(linea);
		linea = NULL;
	}while(c != EOF);
	free(linea);
	linea = NULL;




	/************* PARSEO DE UNA LINEA *************/
	if((split(cadena[1],delimitador,&arreglo,&longitud)) != ST_OK)
	{
		fprintf(stderr, "Algo salio mal :/\n");
		return EXIT_FAILURE;
	}

	/************* IMPRESION DEL PARSEO *************/ /* esto esta solo para mostrar que se pudo parsear, despues no va*/ 
	for(i=0; i<longitud;i++)
	{
		printf("%s\n",arreglo[i]);
	}

	if((st=cargar_datos(&juego,arreglo,longitud)) != ST_OK)
	{
		printf("ERROR EN LA CARGA DE DATOS EN LA MATRIZ\n");
		destruir_arreglo_cadenas(&arreglo,longitud);
		return EXIT_FAILURE;
	}

	/*********************** IMPRIMIR ESTRUCTURA **********************/
	printf("Estructura:\nID: %lu \nNOMBRE: %s\nDESARROLLADOR: %s\nPLATAFORMA: %s\nFECHA: %lu\nPUNTAJE: %f\nRESENIAS: %lu\n", juego.id, juego.nombre, juego.desarrollador, juego.plataforma, juego.fecha, juego.puntaje, juego.resenias);
	destruir_arreglo_cadenas(&arreglo,longitud);

	return EXIT_SUCCESS;
}
