#ifndef INTELIGENCIA_H
#define INTELIGENCIA_H
#include <stdbool.h> 
#include <stdint.h>
#include "../World/WorldStructures.h"

enum modes {AUTO1, MANUAL};

//FEDE
//extern uint16_t sen_state_sens(uint16_t _sensorId);
//extern void act_mov(nextStep_s);
typedef struct {
	int16_t action;
	int16_t velocity;//milisegundos
}NextStep_s;

void I_Init(uint16_t mode); //configuracion inicial

void I_Update(); // va a usar las funciones getInfo, processData, whatDoIDoNext, y doAction.

void initTodo (robot_t hello);

void I_Drive(int direccion, int desplazamiento, int velocidad);

//int16_t I_setMode(uint16_t mode); 

//devuelven codigos de error. manual podria mandar info sobre el tipo de control, si es manual asistido o solo manual,
//que inteligencia se usa para el manual asistido si tenemos mas de una (lo mismo para auto pero sin lo de asistido).

#endif //INTELIGENCIA_H