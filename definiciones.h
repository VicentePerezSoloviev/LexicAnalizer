#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#define AND 257
#define AS 258
#define ASSERT 259
#define BREAK 260
#define CLASS 261
#define CONTINUE 262
#define DEF 263
#define DEL 264
#define ELIF 265
#define ELSE 266
#define EXCEPT 267
#define EXEC 268
#define FINALLY 269
#define FOR 270
#define FROM 271
#define GLOBAL 272
#define IF 273
#define IMPORT 274
#define IN 275
#define IS 276
#define LAMBDA 277
#define NOT 278
#define OR 279
#define PASS 280
#define PRINT 281
#define RAISE 282
#define RETURN 283
#define TRY 284
#define WHILE 285
#define WITH 286
#define YIELD 287

#define IDENTIFICADOR 290                   //identificador de una variable

/*Comentarios*/

#define COMENTARIO_SIMPLE 291               //comentario de una linea
#define COMENTARIO_COMPLEJO 292             //comentario de varias lineas

/*Operadores*/

#define OP_MAYOR_IGUAL 294                  // >=
#define OP_MENOR_IGUAL 295                  // <=
#define OP_COMPARACION 298                  // ==
#define OP_ELEV 303                         // **
#define OP_SUMA_IGUAL 304                   // +=
#define OP_RESTA_IGUAL 305                  // -=
#define OP_MULT_IGUAL 306                   // *=
#define OP_DIV_IGUAL 307                    // /=

/*Delimitadores en codigo ascii*/
/*Se ponen en codigo ascii para no sobrecargar definiciones.h*/

/*Numeros*/

#define NUM_ENTERO 325                      //numeros enteros
#define NUM_P_FLOT 326                      //numeros en punto floante
#define NUM_HEX 327                         //numeros hexadecimales

/*Otros*/

#define STRING_COM_DOB 335                  // "..."
#define STRING_COM_SIM 336                  // '...'

#define CAMBIO_LINEA 340				// \n
#define IDENTADO 341					// \t

#endif /* DEFINICIONES_H */

