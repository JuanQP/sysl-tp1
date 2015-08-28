#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Prototipos de función.*/
int esAceptor(int);
int columna(char);

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
    int TT[6][4] = 
    {{1, 2, 0, 4},
    {5, 2, 5, 5},
    {5, 2, 3, 3},
    {99, 99, 99, 99},
    {99, 99, 99 ,99},
    {99, 99, 0, 4}};

    /*Va obteniendo caracteres uno por uno desde el archivo Input.*/
    letra = getchar();

    /*Mientras el estado sea distinto de "EOF Reconocido".*/
    while(estado != 4)
    {
        printf("%c", letra);
        proximoEstado = TT[estado][columna(letra)];
        
        /*Si está en el estado de error, y el próximo no lo es,
        significa que finalizó la palabra rechazada, así que la contamos.*/
        if (estado == 5 && proximoEstado != 5)
        {
            rechazadas++;
        }
        
        /*Si el próximo estado es aceptor y no es el fin de archivo,
        entonces devuelvo ese centinela, y anoto que la cadena fue reconocida.
        Dejo el próximo estado en 0 para que se inicie un nuevo reconocimiento.*/
        if (esAceptor(proximoEstado) && proximoEstado != 4)
        {
            ungetc(letra, stdin);
            proximoEstado = 0;
            validas++;
        }
        estado = proximoEstado;
        letra = getchar();
    }

    /*Verifico si la última cadena es reconocida.*/
    if (esAceptor(estado))
    {
        ungetc(letra, stdin);
        validas++;
    }
    else
    {
        rechazadas++;
    }
    
    printf("Reconocidas: %d\n", validas);
    printf("Rechazadas : %d\n\n", rechazadas);

    return 1;
}

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

int columna(char letra)
{
    /*Si es dígito va a la columna 2.*/
    if(isdigit(letra))
    {
        return 2;
    }

    /*Si es signo, va a la columna 1.*/
    if(letra == '+' || letra == '-')
    {
        return 1;
    }

    /*Si es un # va a la columna 3.*/
    if(letra == '#')
    {
        return 3;
    }

    /*Si es EOF va a la columna 4.*/
    if(letra == '\0')
    {
        return 4;
    }
}





