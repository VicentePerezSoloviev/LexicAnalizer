#ifndef ERRORES_H
#define ERRORES_H

/*Definimos los codigos para identificar los errores mas facil
 posteriormente, con un codigo*/

/*Sistema de entrada 501-509*/
#define ABRIR_ARCHIVO 501
#define CARGAR_CENTINELA 502

/*Tabla de simbolos 510-519*/
#define INSERCION_LEXEMA_ARBOL 510

/*Analizador lexico 520-529*/
#define CARACTER_PROHIBIDO 520
#define NO_SE_RECONOCE 521
#define COMENTARIO_MAL_DELIMITADO 522

/*Definiciones de funciones*/

void error_sistema_entrada(int condigo, char* msg);  //error al abrir el archivo

void error_tabla_simbolos (int codigo, char *msg);  //error en el sistema del analizador lexico

void error_sistema_lexico (int codigo, char *msg); //error en analizador lexico

#endif /* ERRORES_H */

