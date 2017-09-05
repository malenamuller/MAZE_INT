#include "senact.h"
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include "../World/World.h"
#include "../FileHandler/FileHandler.h"

#define PI 3.14159265359
#define MAX_VEL_R (PI/100)
#define MAX_VEL_D 1

#define ESCALA (.15/50)

#define UPDATESENRATE 1

typedef struct{
	double right;
	double left;
}actuator_percentage_t;

typedef struct{
	double distance;
	double angle;	
}sensores_t;


static actuator_percentage_t percentage_old, percentage_new;
static sensores_t lastread[AMOUNT_OF_SENSORS], shown[AMOUNT_OF_SENSORS];
static uint16_t updatecount;

static void init_random (void){		//inicializacion para generar numeros random
	time_t t;
	srand((unsigned) time(&t));
}

static uint16_t generate_random (uint16_t max){		//generador de random (>0) a partir del valor max
	return (rand()%max);
}

///SENSORES

static void updateSensor_ALL (void){
	int i;
	for(i=1;i<=AMOUNT_OF_SENSORS;i++){
		shown[i - 1].distance = lastread[i - 1].distance;
		shown[i - 1].angle = lastread[i - 1].angle;
	}
	
}

static uint16_t checkreal (void) {
	int ret = 1,i;
	for (i = 1; i <= AMOUNT_OF_SENSORS; i++) {
		if (lastread[i - 1].distance > 0.6)		 // 0.6m Es la max distancia por el coeficiente de reflactancia de la madera
			ret = 0;
		if (lastread[i - 1].angle > (40 * PI))   // Falta que .angle desde world funque   40 es el angulo max en el que tiene sentido sensar
			ret = 0;
	}
	return ret;
}


static void SensorUpdate (void){
	int i;
	for(i=1;i<=AMOUNT_OF_SENSORS;i++){
		lastread[i - 1].distance = W_getSensorData(i).distance;
		lastread[i - 1].angle = W_getSensorData(i).angle;
	}
	
	if(updatecount++ >= UPDATESENRATE){
		updatecount=0;
		if(checkreal())
			updateSensor_ALL();
	}
}


double S_getStateValue (uint16_t sensorID)
{
	return shown[sensorID].distance;
}





///ACTUADORES

static uint16_t convert_data (double data_r, double data_l, double * velocidad_d, double * velocidad_r){
	if((data_l<=100) && (data_l>=-100) && (data_r<=100) && (data_r>=-100)) //probamos que no se encuentre dentro del rango
	{
		*velocidad_d = (((data_l + data_r) / 200)*MAX_VEL_D);   //Calculo de velocidades
		*velocidad_r = (((data_l - data_r) / 200)*MAX_VEL_R);	
		return 1;
	}
	else
		return 0;
}

static void magic (void){		// Handler de errores y convercion
	//no magic example
	double dvelocity, rvelocity;
	double *p_dvelocity = &dvelocity, *p_rvelocity = &rvelocity;
	if(convert_data (percentage_new.right, percentage_new.left, p_dvelocity, p_rvelocity)){
		percentage_old.right = percentage_new.right;
		percentage_old.left = percentage_new.left;
		W_configureRobot (dvelocity * ESCALA, rvelocity);
	}


}

void S_setActuatorMov(uint16_t actuator_id, int16_t actuator_percentage){	//guardado de info
	switch(actuator_id)
	{
		case 0:
		percentage_new.left = actuator_percentage;
		break;

		case 1:
		percentage_new.right = actuator_percentage;
		break;
	}
}

uint16_t S_Update (void){
	magic();
	SensorUpdate();
	return 0;
}

void S_Init (void){
	init_random();
	percentage_old.right = 0;
	percentage_old.left = 0;
	F_Startup ("../FileHandler/Sensores.txt");
}

double S_getSensorAngle(int sensorID)
{
	return W_getSensorData(sensorID).distance;
}

double S_getSensorAngle (uint16_t sensorID){
	return F_getSensorAngle (sensorID);
}

double	S_getSensorXPos(uint16_t sensorID){
	return F_getSensorXPos (sensorID);
}

double	S_getSensorYPos(uint16_t sensorID){
	return F_getSensorYPos (sensorID);
}
