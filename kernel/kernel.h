/*
 * kernel.h
 *
 *  Created on: 10/04/2014
 *      Author: maximiliano
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <commons/collections/list.h>
#include <stdint.h>

typedef struct{
	char * data;
	int32_t size;
}t_stream;

typedef struct{
	int identificadorUnico;
	char * segmentoDeCodigo;
	t_list * stackDeFunciones;
	int cursorDelStack;
	int ** indiceDeCodigo;
    t_stream indiceDeEtiquetas;
    int * programCOunter;
    int cantidadDeVariablesContextoActual;
}t_proceso;

void arrancarSelect();

#endif /* KERNEL_H_ */
