/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*En este fichero se encuentran las funciones para el analizador sintactico
 para esta practica solo implementamos el analizador lexico por lo que las funciones
 que encontraremos aqui, sera unicamente una que pida iteradamente los componentes
 lexicos del analizador lexico*/

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

void analizador_sintactico () {
    lexema lex;
    
    while (lex.codigo != -1) {
            lex = siguiente_componente();
        if (lex.codigo != -1) {
            printf ("Codigo: %d \t Lexema: ", lex.codigo);
            for (int j=0; j<N; j++) if (lex.lexema[j] != NULL) printf ("%c", lex.lexema[j]);
            printf ("\n");
        }
    }
    
}

