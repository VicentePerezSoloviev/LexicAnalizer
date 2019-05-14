/*
 Fichero para la implementacion del sistema de entrada
 */

#include <stdio.h>
#include <stdlib.h>
#include "sistemaentrada.h"
#include "errores.h"

/*Puntero a fichero*/

FILE *fp;

/*Definicion de los centinelas:
 - Un centinela tiene de tamano N caracteres +1 (EOF)
 */

char centinela_1[N+1], centinela_2[N+1];

/*Tratamiento de lexemas:
 - Inicio apunta siempre al inicio del lexema
 - Delantero apunta al caracter que leemos
 */

char* inicio;
char* delantero; 


/*Variable que nos indica cual ha sido el ultimo buffer
 en activar, es decir, en cual estamos operando
 - 1 -> centinela_1
 - 2 -> centinela_2*/

int centinela_actual;
int cargado=0; //variable que nos indica si el siguiente buffer está cargado 0-> no 1->si

int aux;

void cargar_centinela_1() {
    /*se usa un contador porque no siempre se va a llenar el centinela
     * Por ej, al acabar de leer fichero, no se va a llenar. 
     * Asi nos aseguramos*/
    
    int contador = fread (centinela_1, 1, N, fp); //leemos N bytes del fichero y los ponemos en el primer centinela
    centinela_1[contador] = EOF;    //despues de lo leído se pone un End Of File.

    delantero = centinela_1;
    
    centinela_actual = 1;   //actualizo en que centinela estoy
}

void cargar_centinela_2() {
    /*se usa un contador porque no siempre se va a llenar el centinela
     * Por ej, al acabar de leer fichero, no se va a llenar. 
     * Asi nos aseguramos*/
    
    int contador = fread (centinela_2, sizeof(char), N, fp); //leemos N bytes del fichero y los ponemos en el primer centinela
    centinela_2[contador] = EOF;    //despues de lo leído se pone un End Of File.
    
    delantero = centinela_2;
    centinela_actual = 2;   //actualizao en que centinela estoy
}

void cargar_centinela_X (int n) {   //cargamos el centinela que queremos
    if (n==1) cargar_centinela_1 ();
    else if (n==2) cargar_centinela_2 ();
    else error_sistema_entrada (CARGAR_CENTINELA, "se pide cargar un centinela que no existe");
}

void iniciar_sistema_entrada () {
    
    fp = fopen (fichero, "r");                      //modo lectura
    if (fp == NULL) {
        error_sistema_entrada(ABRIR_ARCHIVO, "apertura de archivo fallida");
        exit (1);
    }
    
    cargar_centinela_X (1);
    inicio = delantero = centinela_1;
    aux =1;
}

/*COnsumimos un lexema y marcamos como inicio el siguiente inicio de lexema*/

void marcar_inicio_delantero () {
    inicio = delantero;
}

/*Devolvemos 1 en caso de leer el fin de fichero, y 0 encaso de que no lo sea*/

int es_fin_fichero () {
    if (feof(fp)) {
        fclose(fp);
        free(fp);
        return 1;
    }
    else return 0;
}

/*Se necesita una funcion que nos devuelva el siguiente
 caracter del buffer*/

char siguiente_entrada () {
    /*Si estamos en un EOF que puede ser de fin de centinela o de fin de File*/
    
    if (aux == 1) {
        aux =0;
        return *delantero;
    }
    
    if (*delantero == EOF) {
        if (es_fin_fichero()) { //en caso de leer el fin de fichero
            return EOF;
        }
        
        if (cargado ==0) {  //si no tenemos el siguiente centinela cargado
            if (centinela_actual == 1) {    //y estamos en centinela 1
                cargar_centinela_X(2);      //entonces cargamos centinela 2
            }
            else if (centinela_actual == 2) {   //si estamos en el 2
                cargar_centinela_X(1);          //cargamos el 1
            }
           
            return ( *(delantero));
        }
        else {  //si tenemos el siguiente centinela cargado
            centinela_actual ++;    //avanzamos de centinela
            cargado == 0; //el buffer siguiente esta sin cargar
        }
        
    }
    *delantero ++;
    return ( *delantero);     //avanzamos la posicion de delantero si o si
}

/*Implementamos una funcion para retroceder un caracter atras
 No tiene sentido devolver el caracter, porque nunca vamos a querer saber lo que hay detras
 solo poder dejarlo una posicion mas atras*/

void anterior_entrada () {
/* Tenemos que tener en cuenta las opciones en la que tenemos que cambiar de centinela hacia atras
 - si estamos en primera posicion de centinela 1 tenemos que ir a la ultima del centinela 2
 - si estamos en primera posicion de centinela 2 tenemos que ir a la ultima del centinela 1
 - otro caso retrocedemos sin mas por el centinela */
    
    if (centinela_actual == 1 && delantero == centinela_1){ //primera posicion del 1
        delantero = centinela_2 + N -1; //ultima del 2
        centinela_actual == 2;
    }
    else if (centinela_actual == 2 && delantero == centinela_2){ //primera del 2
        delantero = centinela_1 + N -1; //ultima del 1
        centinela_actual = 1;
    }
    else {  //otro caso: estamos por el medio de alguno de los dos centinelas
        delantero --;   //retrocedo uno
    }
}

void liberar_sistema_entrada() {
    /*Cerramos fichero*/
    fclose (fp);
    free (fp);
    
    /*Puntero a NULL*/
    
    *delantero = NULL;
    *inicio = NULL;
    //*fp = NULL;
    
    /*Dejamos los centinelas a NULL*/
    
    for (int i=0; i<N+1; i++) centinela_1[i] = NULL;
    for (int i=0; i<N+1; i++) centinela_2[i] = NULL;
    
    /*Liberar memoria de locales*/
}


