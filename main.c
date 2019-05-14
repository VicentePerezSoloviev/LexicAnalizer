#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistemaentrada.h"
#include "lexico.h"
#include "tablasimbolos.h"
#include "sintactico.h"
int main(int argc, char** argv) {

    iniciar_sistema_entrada();
    iniciar_tabla_simbolos();
    iniciar_lexico();
    imprimir_tabla();
    analizador_sintactico();
    imprimir_tabla();
    
    liberar_sistema_entrada();
    liberar_tabla_simbolos();
    return (EXIT_SUCCESS);
}

