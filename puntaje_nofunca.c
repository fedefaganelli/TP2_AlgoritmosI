#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define CANTIDAD_DE_ARGUMENTOS_PUNTAJE 8
#define NOMBRE_ARCHIVO_BASE_DE_DATOS "entrada.txt"
#define NOMBRE_ARCHIVO_A_MODIFICAR "salida.txt"
#define NOMBRE_ARCHIVO_PARA_MSJS_DE_ERRORES "errores.txt"
/*************** NUMERO DE POSICIONES PARA ARGUMENTOS ******************/
#define ARG_CMD_NUMERO_DE_POSICION_OPERACION 1
#define ARG_CMD_NUMERO_DE_POSICION_BAMDERA_ARCHIVO_BASE_DE_DATOS 2
#define ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_BASE_DE_DATOS 3
#define ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_A_MODIFICAR 4
#define ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_A_MODIFICAR 5
#define ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_MSJS_ERROR 6
#define ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_MSJS_ERROR 7
/***********************************************************************/


status_t validar_argumentos_puntaje (int argc, char * argv[], FILE **fentrada, FILE ** fsalida);


int main (int argc, char *argv[])
{
	FILE *data;   /* Registros para dar alta, baja o modificaciones */
	FILE *db;     /*  Base de datos */
	status_t st; 

	juego_t ** ptr_juego_db,  ** ptr_juego_data;
	ptr_juego_data= NULL;
	ptr_juego_db=NULL;

	/*size_t id_aux_data;
	size_t id_aux_db;
*/
		if((st = validar_argumentos_puntaje(argc, argv, &data, &db))!=ST_OK)
	{
		fprintf(stderr, "Error en alguna validacion\n");
		return EXIT_FAILURE;
	}

/*switch()
	{
		case "A": 
		case "B":
		case "M":
	}*/
	int i, j;
		for(i=0; i<10 ;i++)

				if(fread(&(((ptr_juego_data)->id)[i]),sizeof(size_t),1, data))
				{
					/*	id_aux_data = (ptr_juego_data)->id;  */

				for(j=0; j<10 ;j++)
				{	
				if(fread(((ptr_juego_db)->id)[j],sizeof(size_t),1, db))
						/*id_aux_db = (ptr_juego_db)->id;
*/
					if(((ptr_juego_data)->id)[i] == ((ptr_juego_db)->id)[j])
						return ST_ERROR_ID_REPETIDO;

						fseek(db,SEEK_END,0);
						fwrite(&((ptr_juego_db)->id),sizeof(size_t),1, db);
				}	
			}

	


	return EXIT_SUCCESS;
}




status_t validar_argumentos_puntaje (int argc, char * argv[], FILE **fentrada, FILE ** fsalida)
{

	if (argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
/************ Se valida la cantidad de argumentos **************************/
	if  ( argc != CANTIDAD_DE_ARGUMENTOS_PUNTAJE )
		return ST_ERROR_CANTIDAD_INVALIDA_DE_ARGUMENTOS; 
	
/********************** Se validan las banderas ****************************/	
	if(	strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_OPERACION], "A") 
		&& strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_OPERACION], "B")
		 &&	strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_OPERACION], "M") )
		return ST_ERROR_CMD_ARG_OPERACION;


	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_BAMDERA_ARCHIVO_BASE_DE_DATOS], "-if"))
		return ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_BASE_DE_DATOS;
	
	if ( strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_BASE_DE_DATOS], NOMBRE_ARCHIVO_BASE_DE_DATOS) )
		return ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_BASE_DATOS_INVALIDO;
	
	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_A_MODIFICAR], "-f"))
		return ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_A_MODIFICAR;

	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_A_MODIFICAR], NOMBRE_ARCHIVO_A_MODIFICAR))
		return ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_A_MODIFICAR_INVALIDO;

	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_MSJS_ERROR], "-log"))
		return ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_MSJS_DE_ERRORES;

	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_MSJS_ERROR], NOMBRE_ARCHIVO_PARA_MSJS_DE_ERRORES))
		return ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_MSJ_DE_ERRORES_INVALIDO;

		if((*fentrada = fopen(argv[3],"rb"))==NULL)
	{
		printf("entre a ST_ERROR_APERTURA_ARCHIVO_ENTRADA\n");
		return ST_ERROR_APERTURA_ARCHIVO_DE_ENTRADA;
	}
			if((*fsalida = fopen(argv[5],"ab"))==NULL)
	{
		printf("entre a ST_ERROR_APERTURA_ARCHIVO_SALIDA\n");
		return ST_ERROR_APERTURA_ARCHIVO_DE_SALIDA;
	}

/********************* Fin de validacion de banderas ***********************/
		
	return ST_OK;
}