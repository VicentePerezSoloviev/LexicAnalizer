
/*Este fichero contiene las funciones necesarias de la tabla de simbolos*/

/*La tabla de simbolos es de todos. Por ello sus funciones se encuentran en este 
 fichero, para no darle propiedad a nadie en concreto*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errores.h"
#include "lexico.h"
#include "abb.h"
#include "tablasimbolos.h"
#include "definiciones.h"

lexema lex;     //lexema auxiliar

abb Arbol;      //TABLA DE SIMBOLOS ppal del sistema

void limpiar_lexema () {
    for (int i=0; i<N; i++) {
        lex.lexema [i] = NULL;
    }
}

void iniciar_tabla_simbolos () {
    /*Inicializamos el arbol*/
    crear_arbol (&Arbol);
    /*Metemos las palabras reservadas en el arbol*/
    
    /*Limpiamos el lexema -> introducimos el char de la palabra -> introducir codigo*/
    
    limpiar_lexema(); strcpy (lex.lexema , "and"); lex.codigo = AND; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "as"); lex.codigo = AS; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "assert"); lex.codigo = ASSERT; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "break"); lex.codigo = BREAK; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "class"); lex.codigo = CLASS; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "continue"); lex.codigo = CONTINUE; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "def"); lex.codigo = DEF; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "del"); lex.codigo = DEL; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "elif"); lex.codigo = ELIF; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "else"); lex.codigo = ELSE; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "except"); lex.codigo = EXCEPT; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "exec"); lex.codigo = EXEC; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "finally"); lex.codigo = FINALLY; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "for"); lex.codigo = FOR; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "from"); lex.codigo = FROM; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "global"); lex.codigo = GLOBAL; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "if"); lex.codigo = IF; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "import"); lex.codigo = IMPORT; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "in"); lex.codigo = IN; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "is"); lex.codigo = IS; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "lambda"); lex.codigo = LAMBDA; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "not"); lex.codigo = NOT; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "or"); lex.codigo = OR; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "pass"); lex.codigo = PASS; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "print"); lex.codigo = PRINT; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "raise"); lex.codigo = RAISE; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "return"); lex.codigo = RETURN; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "try"); lex.codigo = TRY; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "while"); lex.codigo = WHILE; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "with"); lex.codigo = WITH; insertar (&Arbol, lex);
    limpiar_lexema(); strcpy (lex.lexema , "yield"); lex.codigo = YIELD; insertar (&Arbol, lex);
    
}

/*Inserto en la tabla que ya fue inicializada el lexema que se me pasa por parametro*/

void insertar_tabla (lexema l) {
    insertar(&Arbol, l);
    
    if (es_miembro (Arbol, lex) == 0) {     //gestion de error, por si al insertar no existe
        error_tabla_simbolos (INSERCION_LEXEMA_ARBOL, "Fallo al insertar el elemento en el arbol");
        return;
    }
}

/*Devuelve:
 - (-1) en caso de que no exista
 - 0 en caso de que exista
 */
int existe (lexema l) {
    if (es_miembro (Arbol, l) == 0) {     //gestion de error, por si al insertar no existe
        return -1;
    }
    else return 0;
}

/*Funcion interna: Recorrido inorden para impresion de valores de tabla de simbolos*/

void inorden (abb arbol){
    lexema E;

    if (!es_vacio(arbol)){
        inorden (izq(arbol));
        info (arbol, &E);
        printf (" %d \t ", E.codigo);
        for (int i=0; i<N; i++) if (E.lexema[i] != NULL) printf ("%c", E.lexema[i]);
        printf ("\n");
        inorden (der(arbol));
    }
}

/*Funcion que usamos para imprimir toda la tabla de simbolos.
 Desde esta se llama a la funcion recursiva*/
void imprimir_tabla () {
    //Se llama a funcion recursiva que imprima
    printf ("\n****TABLA DE SIMBOLOS****\n");
    printf ("-------------------------\n");
    printf ("Codigo \t Palabra \n");
    inorden (Arbol);
    printf ("****++++++++++++++++*****\n\n");
}

void buscar () {        //el lexema que s egestiona desde lexico ya es el que usamos como nodo
    buscar_nodo(Arbol, lex.lexema, &lex);
}

void liberar_tabla_simbolos() {
    
    /*destruimos el arbol*/
    destruir_arbol(&Arbol);
    
    /*vaciamos el lexema que definimos auxiliar*/
    lex.codigo = NULL;
    limpiar_lexema();
}