#include "Intelligence.h"
#include "../vector.h"
#include "./Autos/Auto1.h"
#include "../senact/senact.h"
#include <math.h>
#include "Manual.h"
#define ESCALA	(50/.15)

extern void startAuto1(const dpoint_t * allCoordinates);
static dpoint_t getSensorPosition(int sensorId);
static void initSensorsData(void);
static dpoint_t getCoordinateFromSensor(int sensorId);
static dpoint_t allCoordinates[SENSORS_AMMOUNT];


uint16_t mode;


void I_Init(uint16_t _mode)
{
	mode = _mode;
}

void I_Update()
{
	initSensorsData();
	switch (mode) {
	case MANUAL:
		startManual();
		break;
	default:
		startAuto1(allCoordinates);
	}
}

static void initSensorsData(void)
{
	int i;
	for (i = 0; i < SENSORS_AMMOUNT; i++)
		allCoordinates[i] = getCoordinateFromSensor(i);
}

static dpoint_t getCoordinateFromSensor(int sensorId)
{
	double angle = S_getSensorAngle(sensorId);
	dpoint_t positionOnRobot = getSensorPosition(sensorId);
	double distance = S_getStateValue(sensorId)*ESCALA;
	dpoint_t answer;
	answer.x = positionOnRobot.x + sin(angle)*distance;
	answer.y = positionOnRobot.y - cos(angle)*distance;
	return answer;
}

static dpoint_t getSensorPosition(int sensorId)
{
	dpoint_t temp;
	temp.x = S_getSensorXPos(sensorId);
	temp.y = S_getSensorYPos(sensorId);
	return temp;
}