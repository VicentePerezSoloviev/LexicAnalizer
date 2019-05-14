
#ifndef SISTEMAENTRADA_H
#define SISTEMAENTRADA_H

#define N 16
#define fichero "wilcoxon.py"

/* - Cargamos fichero en modo lectura
   - Cargamos el centinela 1
   - Ponemos punteros inicio de lexema y delantero de lexema en primera posicion*/

void iniciar_sistema_entrada ();

/*Devolvemos el caracter siguiente del centinela, o EOF*/

char siguiente_entrada ();

/*Cambiamos el puntero de inicio de lexema al actual delantero para marcar inicio de nuevo lexema*/

void marcar_inicio_delantero ();

/*Marcamos el puntero de delantero en una posicion anterior.
 La funcion no devuelve el char, solo cambia el puntero*/

void anterior_entrada ();

/*Funcion para liberar memoria reservada y usada en las funciones del sistema de entrada*/

void liberar_sistema_entrada ();

#endif /* SISTEMAENTRADA_H */

