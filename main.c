#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Prototipos de función.*/
int Transicion(int, char);
void Procesar(int*, int*);

/*Función principal.
El programa se inicia leyendo el contenido de un archivo llamado "Input" en el directorio
donde se encuentra main.c*/
int main()
{
    /*Contadores para saber cuantas cadenas se aceptaron o rechazaron.*/
    int validas = 0;
    int rechazadas = 0;
    
    /*Variables necesarias para saber el estado, y hacer la Tabla de Transición.*/
    int estado = 1;
    char letra;
    int proximoEstado;
    int TT[3][3];

    /*Va obteniendo caracteres uno por uno desde el archivo Input.*/
    letra = getchar();
    while((letra = getchar()) != EOF)
    {
        proximoEstado = TT[estado][letra];
        
        /*Si el proximoEstado es 100, entonces no es una cadena reconocida.*/
        if (proximoEstado == 100)
        {
            break;
        }
        estado = proximoEstado;
        letra = getchar();
    }
    
    
    
    
    /*Muestra los resultados finales.*/
    printf("\n\nValidas: %d\n", validas);
    printf("Rechazadas: %d\n", rechazadas);
    printf("Total de Cadenas: %d\n", validas+rechazadas);
    return 0;
}

void Procesar (int *validas, int *rechazadas)
{
    /*Defino variables para contener la letra actual, el estado actual, el anterior y un contador de cadenas.*/
	char letra;
	int Estado = 0;
	int EstadoAnterior = 0;
	int CadenaNumero = 1;

	/*Empiezo a leer letra por letra lo que contiene el archivo Input hasta el final de archivo.*/
    while((letra = getchar()) != EOF)
	{
        /*Si el estado es 0 significa que se inició una nueva cadena,
        así que el programa va a preguntar si el último estado fue 1
        o si fue con una cadena con error (Estado 2).*/
        if (Estado == 0)
        {
            if(EstadoAnterior == 1)
            {
                printf(" <--- ACEPTADA");
                (*validas)++;
            }
            if(EstadoAnterior == 2)
            {
                printf(" <--- RECHAZADA");
                (*rechazadas)++;
            }
            printf("\nCadena numero %d:\n", CadenaNumero);
            CadenaNumero++;
        }

        /*Si la letra actual no es un #, o tampoco es una nueva línea, la imprimo.*/
        if(letra != '#' && letra != '\n')
        {
            printf("%c", letra);
        }
        /*Verifico en que estado se encuentra el caracter actual.*/
        EstadoAnterior = Estado;
		Estado = Transicion(Estado, letra);
    }

    /*Una vez que se alcanzó el fin de archivo necesito saber el último estado.*/
    if(EstadoAnterior == 1)
    {
        printf(" <--- ACEPTADA");
        (*validas)++;
    }
    if(EstadoAnterior == 2)
    {
        printf(" <--- RECHAZADA");
        (*rechazadas)++;
    }
}

/*Se encarga de verificar las transiciones.*/
int Transicion (int Estado, char c)
{
    switch (Estado)
	{
        case 0:
            if(c == '+' || c == '-')
            {
                return 1;
            }
            if(isdigit(c))
            {
                return 1;
            }
            if(c == '#')
            {
                return 0;
            }
            /*Si llegó hasta acá es porque no es ni un número, ni #, ni + o -*/
            return 2;

        case 1:
            if(c == '+' || c == '-')
            {
                return 2;
            }
            if(isdigit(c))
            {
                return 1;
            }
            if(c == '#' || c == '\0')
            {
                return 0;
            }
            /*Si llegó hasta acá es porque no es ni un número, ni #, ni + o -*/
            return 2;

        case 2:
            if(c == '#' || c == '\0')
            {
                return 0;
            }
            /*Si llegó hasta acá es porque no es ni un número, ni #, ni + o -*/
            return 2;
	}

	/*Ocurrió algún error.*/
	return 2;
}
