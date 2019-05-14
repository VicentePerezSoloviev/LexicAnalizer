#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "abb.h"

/*Inicializo la tabla y meto las palabras reservadas*/
void iniciar_tabla_simbolos ();

/*El lexema que se pasa por parametro se intenta meter en la tabla
 En caso de error se gestiona error de tabla en errores.h*/

void insertar_tabla (lexema l);

/*Se comorueba si existe el lexema que se le pasa por parametro
 * Devuelve:
 - (-1) en caso de que no exista
 - 0 en caso de que exista
 */
int existe (lexema l);

#endif /* TABLASIMBOLOS_H */

