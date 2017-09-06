#ifndef SENACT_H
#define SENACT_H
//codigos de errores -> error.h
#define	SENACT_ERROR	1
#define SENACT_OK 	0
#define MOTOR_L 0
#define MOTOR_R 1
#include <stdint.h>

//typedef sensor_id uint16_t

// Sensores
double S_getStateValue(uint16_t sensorID);
//* void S_getStateSens (sensor_id);


// Actuadores
void S_setActuatorMov (uint16_t actuator_id, int16_t actuator_percentage);


// Inicializacion
void S_Init (void);

// Mantenimiento
uint16_t S_Update (void);

// Configuracion
//uint16_t S_setSensorError (sen_id, * void);
//uint16_t S_setActuatorError (sen_id, * void);


//Filehandler
double	S_getSensorAngle(uint16_t sensorID);
double	S_getSensorXPos(uint16_t sensorID);
double	S_getSensorYPos(uint16_t sensorID);



#endif	//SENACT_H