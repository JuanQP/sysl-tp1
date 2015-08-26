## Sintaxis y Semántica de los Lenguajes
---
### Trabajo Práctico 1: Un reconocedor de cadenas

Nos vamos a basar en el capítulo 1.6 del segundo tomo del libro de la cátedra. Se debe usar un 
autómata, **programado mediante una tabla de transición**. Queremos reconocer los números 
opcionalmente precedidos de **signo**. El separador es el carácter **#** pero no forma parte de la cadena 
reconocida.

Se debe **informar cada cadena reconocida o rechazada** y **dar los totales** para cada caso al final.
Notar que para reconocer como buena una cadena debe estar un número seguido o bien por un # o bien
por el fin de texto.