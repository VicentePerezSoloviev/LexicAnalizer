
/*En este fichero se definen las funciones del analizador lexico:
 - automatas de reconocimiento*/
/*Leo flujo de caracteres y los presento como componentes lexicos*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "errores.h"
#include "lexico.h"
#include "abb.h"
#include "tablasimbolos.h"
#include "definiciones.h"

char caracter;      //caracter actual
char almacen [N];   //vamos acumulando lo leido. Tiene de maximo N

int auxiliar; //variable auxilair para que cuando empiece el archivo lea el primer caracter y no se lo salte
int var_comen; //variable para diferencias de un comentario a una salida por terminal
lexema lex; //lexema sobre el que se trabaja. y que se mete en la tabla y manda al sintactico


void limpiar_almacen(){ //funcion privada auxiliar
    /*Igualamos todas las posicione del almacen a NULL para que no tengamos 
     carateres no deseados*/
    for (int j=0; j<N; j++) almacen[j] = NULL;  //limpiamos para no encontrar caracteres antiguos
}

/*En esta funcion debo identificar posibles nombres identificadores y palbras 
 reservadas definidas en definiciones.h*/

void identificador_palabra_reservada() {
    int i=0;
    
    limpiar_almacen();  //antes de insertar limpiamos
    if (isalpha(caracter)  || caracter == '_' || caracter == EOF) {        //nos aseguramos de que no empieza por numero

        while ((isalpha(caracter) || isdigit(caracter) || caracter == '_' || caracter == EOF) && caracter!= '\n'){
            if (caracter != EOF){        //en caso de recibir el EOF de fin de buffer lo consumimos
                almacen[i] = caracter;
                i++;
            }
            caracter = siguiente_entrada();
        }
        
        for (int j=0; j<N; j++) lex.lexema [j] = almacen[j];    //copiamos lo del almacen al lexema para meterlo

        /*printf ("\n");
        for (i =0; i<9; i++) {
            printf ("[%c]", lex.lexema[i]);
        }
        printf ("\n");*/

        /*Metemos el lexema en el arbol. Es el arbol el que se encarga de comprobar que no exista ya*/
        if (existe(lex) == -1) {
            lex.codigo = IDENTIFICADOR;     //si no esta metido es un identificador_ se le asigna la definicion
            insertar_tabla(lex);    //una vez se le asigna el valor se introduce en la tabla
        }
        else{
            /*Si si que existe cogemos el codigo y se lo ponemos al lexema para devolver*/
            buscar();   //funcion que me busca el componente en el arbol para devolverlo
        }

        
        /*La funcion deja leido en char caracter el siguiente caracter a leer*/
        }
}

/*Cuando se ejecuta la funcion devuelve el siguiente caracter despues de consumir todos los espacios
 o cambios de linea pero devuelve identados y cambios de linea como componentes lexicos*/

void consumir_espacio(){
    
    if (caracter == '\n') {
        
    }
    else if (caracter == ' ') {
        
    }
    
    
    while (caracter == ' ' || caracter == '\n' || caracter == EOF){
        caracter = siguiente_entrada();
    }
    
    /*La funcion deja leido en char caracter el siguiente caracter a leer*/
}

/*Funcion para comentarios: llena el lexema con una parte del comentario y el resto lo consume*/

void comentarios_string(){
    int i=0;    //contador para sumar posicion del vector donde se mete los caracteres
    if (caracter == '#'){   //caso: comentarios de una linea
        while ((caracter = siguiente_entrada()) != '\n') {  //hasta que acabe la linea
            if (caracter != EOF)        //en caso de recibir el EOF de fin de buffer lo consumimos
                if (i<N) {  //llenar el almacen hasta maximo N
                    almacen[i] = caracter;     //guardo el comentario hasta N, el resto lo consumo
                    i++;    //muevo la posicion del vector donde guardo el lexema
                }
        }
        caracter = siguiente_entrada(); //consumo el cambio de linea
        
        for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
        lex.codigo = COMENTARIO_SIMPLE;
        var_comen = 0;
    }
    else if (caracter == '"'){
        if ((caracter = siguiente_entrada()) == '"'){
            if ((caracter = siguiente_entrada()) == '"'){   //si leo los tres /"
                while ((caracter = siguiente_entrada()) != '"') {   //hasta que encuentre otras doble comillas
                    if (caracter != EOF && caracter != '\n'){    //ignoro fin de buffer y cambios de linea
                        if (i<N) {  //llenar el almacen hasta maximo N
                            almacen[i] = caracter;     //guardo el comentario hasta N, el resto lo consumo
                            i++;        //muevo la posicion del vector donde guardo el lexema
                        }
                    }
                }
            }else error_sistema_lexico(COMENTARIO_MAL_DELIMITADO, "Se ha detectado falta de comillas para delimitar el comentario");
            
            caracter = siguiente_entrada();     //consumo segundas doble comillas
            caracter = siguiente_entrada();     //consumo terceras doble comillas
            caracter = siguiente_entrada();     //consumo cambio de linea

            /*introduzco en lexema para devolver al sintactico el comentario. No se mete en tabla de simbolos*/
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = COMENTARIO_COMPLEJO;
        }
        else {  //para reconocer las salidas por terminal
            i=0;
            anterior_entrada();     //retrocedemos el caracter leido
            while ((caracter = siguiente_entrada()) != '"' || caracter == EOF){
                if (caracter != EOF){
                    almacen[i] = caracter;      //almacenamos toda la salida por terminal
                    i++;
                }
            }
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i]; //copiamos
            lex.codigo = STRING_COM_DOB;        //ponemos codigo
            caracter = siguiente_entrada();     //avanzamos caracter para dejar en el que tenemos que analizar
        }
        
    }
    else if (caracter == '\''){ //comilla simple
        i=0;
        while ((caracter = siguiente_entrada()) != '\'' || caracter == EOF ){
            if (caracter != EOF && i<N){
                almacen[i] = caracter;      //almacenamos toda la salida por terminal
                i++;
            }
        }
        for (int i=0; i<N; i++) lex.lexema[i] = almacen[i]; //copiamos
        lex.codigo = STRING_COM_SIM;        //ponemos codigo
        caracter = siguiente_entrada();
    }
    //printf ("]\n\tsiguiente caracter: [%c]\n", caracter);
    
    /*La funcion deja leido en char el siguiente caracter a leer*/
}

/*Identifica los operadores y los mete en un lexema para devolver al 
 sintactico. NO se meten en el arbol*/

void asignaciones_comparaciones(){
    
    limpiar_almacen();
    
    if (caracter == '>'){       //caso en que son dos operadores >=
        almacen[0] = caracter;      //metemos el lexema
        caracter = siguiente_entrada();
        if (caracter == '=') {
            almacen [1] = caracter;
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = OP_MAYOR_IGUAL;   //asignamos el codigo
            caracter = siguiente_entrada(); //siguiente
        }
        else {
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = toascii(almacen[0]);   //asignamos el codigo
        }
    }
    else if (caracter == '<'){  //caso en que son dos operadores <=
        almacen[0] = caracter;      //metemos el lexema
        caracter = siguiente_entrada();
        if (caracter == '=') {
            almacen [1] = caracter;
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = OP_MENOR_IGUAL;   //asignamos el codigo
            caracter = siguiente_entrada(); //siguiente
        }
        else{                   //caso en que solo era un operadore
            //anterior_entrada(); //devolvemos el caracter leido
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            toascii(almacen[0]);   //asignamos el codigo
        }
    }
    else if (caracter == '='){
        almacen[0] = caracter;      //metemos el lexema
        caracter = siguiente_entrada();
        if (caracter == '=') {       //caso en el que son dos operadores ==
            almacen [1] = caracter;
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = OP_COMPARACION;   //asignamos el codigo
            caracter = siguiente_entrada(); //siguiente
        }
        else{                   //caso en que solo era un operador =
            //anterior_entrada(); //devolvemos el caracter leido
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = toascii(almacen[0]);   //asignamos el codigo
        }
    }
    
    /*La funcion deja en el char caracter leido el siguiente caracter a analizar*/
}

void delimitador () {
    limpiar_almacen();  //limpiamos el almacen para que no tengamos caracteres no deseados
    
    almacen [0] = caracter; //copio caracter 
    for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
    lex.codigo = toascii(caracter);     //meto el codigo ascii de los delimitadores
    
    caracter = siguiente_entrada(); // dejo leida el siguiente caracter a leer
}

void numeros () {
    int i=1;
    limpiar_almacen();
    if (isdigit(caracter)) {
        almacen[0] = caracter;
        
        while (isdigit(caracter = siguiente_entrada()) || caracter == EOF){    //sigo leyendo numeros seguidos
            if (caracter != EOF) {
                almacen[i] = caracter;  //y los copio al almacen
                i++;
            }
        }
        /*Ahora analizo que es lo que viene despues*/
        if (caracter == '.'){   //si es un punto o una e es punto flotante
            almacen [i] = caracter;
            i++;
            while (isdigit(caracter = siguiente_entrada()) || caracter == EOF){    //sigo leyendo numeros seguidos
                if (caracter != EOF) {
                    almacen[i] = caracter;  //y los copio al almacen
                    i++;
                }
            }
            //introducir en lexema
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = NUM_P_FLOT;
        }
        else if (caracter == 'e') { //si es una e es punto flotante
            almacen [i] = caracter;
            i++;
            /*Compruebo si tengo un +/- antes del resto de numeros si hay*/
            caracter = siguiente_entrada();
            if (caracter == '+' || caracter == '-'){
                almacen [i] = caracter;
                i++;
            }
            else anterior_entrada();
            while (isdigit(caracter = siguiente_entrada()) || caracter == EOF){    //sigo leyendo numeros seguidos
                if (caracter != EOF) {
                    almacen[i] = caracter;  //y los copio al almacen
                    i++;
                }
            }
            //copiar a lexema
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = NUM_P_FLOT;
        }
        else if (caracter == 'x' && almacen[0] == '0'){     //0x ... tiene que ser
            almacen [i] = caracter;
            i++;
            while (isdigit(caracter = siguiente_entrada()) || caracter == EOF){    //sigo leyendo numeros seguidos
                if (caracter != EOF) {
                    almacen[i] = caracter;  //y los copio al almacen
                    i++;
                }
            }
            //copiar a lexema
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = NUM_HEX;
        }
        else if (!isdigit(caracter)){   //si es algo que no es numero es un numero entero
            /*Caso de numeros enteros*/
            //copio a lexema
            for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
            lex.codigo = NUM_ENTERO;
        }
    }
    else if (caracter == '.'){
        almacen [0] = caracter;
        
        while (isdigit(caracter = siguiente_entrada()) || caracter == EOF){    //sigo leyendo numeros seguidos
            if (caracter != EOF){
                almacen[i] = caracter;  //y los copio al almacen
                i++;
            }
        }
        if (i==1) {     //no ha entrado en el bucle porque no hay numeros
            lex.codigo = toascii(almacen[0]);   //codigo ascii del punto
        }else lex.codigo = NUM_P_FLOT;  //cogio numeros
        for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
        
    }
}

void operadores () {
    limpiar_almacen();
    
    almacen[0] = caracter;
    
    if (caracter == '+') {
        caracter = siguiente_entrada();
        if (caracter == '=') {
            lex.codigo = OP_SUMA_IGUAL; //caso +=
            almacen [1] = caracter;
        }
        else {                  //caso +
            lex.codigo = toascii(almacen[0]);   //asignamos el codigo
            anterior_entrada();
        }
    }
    else if (caracter == '^') {
        lex.codigo = toascii(almacen[0]);   //asignamos el codigo
    }
    else if (caracter == '-') {
        caracter = siguiente_entrada();
        if (caracter == '=') {
            lex.codigo = OP_RESTA_IGUAL; //caso -=
            almacen [1] = caracter;
        }
        else {      //caso -
            lex.codigo = toascii(almacen[0]);   //asignamos el codigo
            anterior_entrada();
        }
    }
    else if (caracter == '/') {
        caracter = siguiente_entrada();
        if (caracter == '=') {
            lex.codigo = OP_DIV_IGUAL; //caso /=
            almacen [1] = caracter;
        }
        else {      //caso /
            lex.codigo = toascii(almacen[0]);   //asignamos el codigo
            anterior_entrada();
        }
    }
    else if (caracter == '*') {
        caracter = siguiente_entrada();
        if (caracter == '=') {
            lex.codigo = OP_MULT_IGUAL; //caso *=
            almacen [1] = caracter;
        }
        else if (caracter == '*'){
            lex.codigo = OP_ELEV; //caso **
            almacen [1] = caracter;
        }
        else {      //caso *
            lex.codigo = toascii(almacen[0]);   //asignamos el codigo
            anterior_entrada();
        }
    }
    for (int i=0; i<N; i++) lex.lexema[i] = almacen[i];
    
    caracter = siguiente_entrada(); //dejamos leido el siguiente caracter a analizar
}

/*Funcion que devuelve el siguiente componente lexico del codigo.
 En funcion del caracter a leer, entra en un automata u otro para 
 averiguar el componente.
 - Se devuelve el lexema (struct con codigo de componente y palabra 
 por lo menos*/

lexema siguiente_componente () {
    int caso = -1;  //inicializo a -1 para que no entre por defecto
    
    if (auxiliar==0) {
        caracter = siguiente_entrada(); 
        /*solo para el primer caracter pido el siguiente. 
        El resto se dejan pedidos desde los automatas*/
        auxiliar = 1;
    }
    if (caracter == EOF) caracter=siguiente_entrada();
    
    if (isalpha (caracter) || caracter == '_') caso = 1;
    if (isdigit (caracter)) caso = 2;
    //printf ("--> [%c]\n", caracter);
    
    switch (caracter) {
        case '#': case '"': case '\'':
            comentarios_string();
            break;
        case '?': case '$': 
            /*Son caracteres prohibidos y debe ejecutarse un error*/
            error_sistema_lexico (CARACTER_PROHIBIDO, "El caracter esta prohibido en Python");
            break;
        case EOF:
            /*Para indicar al sintactico que se acaban los componentes, se devuelve un 
             lexema con codigo = -1. Esto esta explicado en el .h para cuando se llame a la 
             funcion.*/
            lex.codigo = -1;        
            break;
        case ' ':
            /*para que no nos devuelva el cambio de linea o el espacio 
             volvemos a llamar la funcion para que nos devuelva la siguiente*/
            consumir_espacio();
            return siguiente_componente(); 
            break;
        case '\n':
            /*para que no nos devuelva el cambio de linea o el espacio 
             volvemos a llamar la funcion para que nos devuelva la siguiente*/
            consumir_espacio();
            return siguiente_componente();
            break;
        case '>': case '<': case '=':
            asignaciones_comparaciones ();
            break;
        case '{': case '}': case ':': case ',': case '(': case ')': 
        case '[': case ']':
            /*Llamamos a la funcion que nos guarda en lexema y asigna codigo ascii*/
            delimitador();
            break;
        case '+': case '-': case '/': case '*':
            operadores ();
            break;
        case '.':
            numeros();
            break;
        default:
            switch (caso) {
                case 1:
                    identificador_palabra_reservada();
                    break;
                case 2:
                    numeros ();
                    break;
                default:
                    error_sistema_lexico(NO_SE_RECONOCE, "El caracter no corresponde a ninguno de los caracteres reconocidos por los automatas");
                    break;
            }
            break;
    }
    return lex;
}

/*Funcion que inicia el analizador lexicos*/

void iniciar_lexico () {
    limpiar_almacen();
    
    /* Inicializo las variables auxiliares a 0*/
    auxiliar=0;
    var_comen = 0;
}