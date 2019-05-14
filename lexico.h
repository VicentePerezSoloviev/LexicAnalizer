#ifndef LEXICO_H
#define LEXICO_H

#include "sistemaentrada.h"



/*Definimos una estructura para guardar los lexemas.
 - char [] donde guardamos la palabra en si, maximo de N siempre
 - linea del codigo donde se encuentra. Puede haber mas de una ocasion
 - veces que aparece*/

typedef struct {
    char lexema[N];
    int codigo;
} lexema ;

void iniciar_lexico();

/*Devuelve el componente lexico identificado*/
/*La funcion devolverá un lexema con un codigo -1 en el caso de que se llegue a 
 final del fichero*/
lexema siguiente_componente ();

#endif /* LEXICO_H */

