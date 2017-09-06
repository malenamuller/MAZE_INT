#include "../Intelligence.h"
#include "../../SenAct/senact.h"
#include <cmath>
#include "Manual.h"
#include <algorithm>

using namespace std;
#define MOT_DUTY_DESPLAZAMIENTO_NOM	200
#define MOT_DUTY_ROTACION_NOM		180
#define MIN_VEL						(-128)
#define MAX_VEL						127

#define MAX_MOT	(MOT_DUTY_DESPLAZAMIENTO_NOM + MOT_DUTY_ROTACION_NOM + 2*(max(abs(MAX_VEL), abs(MIN_VEL))>>1))

//#define MAX_IZQ (MOT_DUTY_DESPLAZAMIENTO_NOM + MOT)

static int dutyMotIzq = 0, dutyMotDer = 0;


void I_Drive(int direccion, int desplazamiento, int velocidad) {
	int desp, dir;
	desp = desplazamiento * (MOT_DUTY_DESPLAZAMIENTO_NOM + (velocidad >> 1));
	dir = direccion * (MOT_DUTY_ROTACION_NOM + (velocidad >> 1));
	dutyMotIzq = desp + dir;
	dutyMotDer = desp - dir;

	dutyMotIzq = (int)round(dutyMotIzq * 100 / ((float)MAX_MOT));	//paso a porcentaje
	dutyMotDer = (int)round(dutyMotDer * 100 / ((float)MAX_MOT));

	startManual();
}

void startManual(void)
{
	S_setActuatorMov(MOTOR_L, dutyMotIzq);
	S_setActuatorMov(MOTOR_R, dutyMotDer);
}
