#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Prototipos de función.*/
int esAceptor(int);
int columna(char);
void encabezado();

/*Función inicial.
El programa se inicia leyendo el contenido de un archivo llamado "Input" en el directorio
donde se encuentra main.c*/
int main()
{
    /*Contadores para saber cuantas cadenas se aceptaron o rechazaron.*/
    int validas = 0;
    int rechazadas = 0;
    
    /*Variables necesarias para saber el estado, y hacer la Tabla de Transición.*/
    int estado = 0;
    char letra;
    int proximoEstado = 0;
       
    /*Inicializo Tabla de Transición.*/
    int TT[6][5] = 
    {{1, 2, 0, 4, 5},
    {5, 2, 5, 5, 5},
    {5, 2, 3, 3, 5},
    {99, 99, 99, 99, 99},
    {99, 99, 99 ,99, 99},
    {5, 5, 0, 4, 5}};

    /*Imprimo un encabezado.*/
    encabezado();

    /*Leo el primer caracter.*/
    letra = getchar();

    /*Mientras el estado sea distinto de "EOF Reconocido".*/
    while(estado != 4)
    {
        /*Imprimo cualquier caracter excepto #, nueva línea o EOF.*/
        if(letra != '#' && letra != '\n' && letra != '\0' && letra != EOF)
        {
            printf("%c", letra);
        }
        
        /*Verifico cuál es el próximo estado usando la tabla de transición.
        uso el estado actual como fila, y la columna depende del caracter
        que se esté leyendo.*/
        proximoEstado = TT[estado][columna(letra)];
        
        /*Si está en el estado de error, y el próximo no lo es,
        significa que finalizó de leerse la palabra rechazada, así que la contamos.
        La única forma de salir del estado de error es con un # o con EOF.*/
        if (estado == 5 && proximoEstado != 5)
        {
            printf(" <--- RECHAZADA\n");
            rechazadas++;
        }
        
        /*Si el próximo estado es aceptor y no es el fin de archivo,
        entonces devuelvo ese centinela, y anoto que la cadena fue reconocida.
        Dejo el próximo estado en 0 para que se inicie un nuevo reconocimiento.*/
        if (esAceptor(proximoEstado) && proximoEstado != 4)
        {
            ungetc(letra, stdin);
            proximoEstado = 0;
            printf(" <--- ACEPTADA\n");
            validas++;
        }
        estado = proximoEstado;
        letra = getchar();
    }
    
    /*Informo cantidad de palabras reconocidas y rechazadas.*/
    printf("\n");
    printf("Reconocidas: %d\n", validas);
    printf("Rechazadas : %d\n\n", rechazadas);

    return 1;
}

/*Informa si un estado es aceptor o no. Los estados 3 y 4 son los estados aceptores.*/
int esAceptor(int estado)
{
    switch (estado)
    {
        case 3:
        case 4:
            return 1;
        default:
            break;
    }
    return 0;
}

/*Informa en qué columna de la tabla de transición va el siguiente caracter.*/
int columna(char letra)
{
    /*Si es dígito va a la columna 1.*/
    if(isdigit(letra))
    {
        return 1;
    }

    /*Si es signo, va a la columna 0.*/
    if(letra == '+' || letra == '-')
    {
        return 0;
    }

    /*Si es un # va a la columna 2.*/
    if(letra == '#')
    {
        return 2;
    }

    /*Si es EOF o nueva línea va a la columna 3.*/
    if(letra == EOF || letra == '\n')
    {
        return 3;
    }
    
    /*Si llegó acá es porque es "cualquier otra cosa".*/
    return 4;
}

/*Imprimo un encabezado con la firma del grupo y curso.*/
void encabezado()
{
    printf("Sintaxis y Semantica de los Lenguajes - UTN\n");
    printf("Curso K2055 - Grupo 3\n");
    printf("Trabajo Practico 1\n");
    printf("\n");
}


