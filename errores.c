/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*En este fichero se implementam las funciones de gestion de errores
 * Para las funciones:
 - se implementa una por cada sistema del analizador
 - los codigos identificadores de los errores estan en .h*/

/*Funcion de error para la gestion de errores del sistema de entrada*/
void error_sistema_entrada (int codigo, char* msg) {
    printf ("Error en sistema de entrada [%d]: %s\n", codigo, msg);
}

/*Funcion de error para la gestion de errroes de la tabla de simbolos*/
void error_tabla_simbolos (int codigo, char *msg) {
    printf ("Error en tabla de simbolos [%d]: %s\n", codigo, msg);
}

/*FUncion de error para la gestion de errores del analizador lexico*/
void error_sistema_lexico (int codigo, char *msg) {
    printf ("Error en el analizador lexico [%d]: %s\n", codigo, msg);
}


