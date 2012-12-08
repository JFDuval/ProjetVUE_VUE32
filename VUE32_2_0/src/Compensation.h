/*
 *Compensation variables
 * by Alexandre Bolduc - 2012-11-17
 */

#ifndef COMPENSATION_H
#define	COMPENSATION_H

#include <GenericTypeDefs.h>

#define VECTORSIZE  4
#define GRAVITY     9.81
#define R           0.27559
#define REDFACT     22.75
#define PI          3.1416
#define TIMESTEP    0.05
#define MAXTO       100.0
#define MASS        940
#define A           1.053
#define B           0.814
#define L           1.867
#define H           0.7
#define KR          0.75
#define T           1.333
#define MS          846
#define HCOMMA      0.2
#define GAIN        400.0

// Max sensor values
#define ACCMAX             1
#define ACCMIN             -1
#define WHEELSPEEDMAX      120.0
#define WHEELSPEEDMIN      -120.0
#define STEERINGMAX        1000.0
#define STEERINGMIN        -1000.0
// TODO: Verify with Seb and convert to deg/s
#define YAWMAX             4 //RAD
#define YAWMIN             -4 //RAD

// Wheel reference: 1 avant conducteur, 2 avant passenger, 3 arrière conducteur

typedef struct
{
    float tmWh3; //torque motor on wheel 3 (couple)
    float tmWh4;
}motorCommand;

typedef struct
{
    float w1; //vitesse roue km/h
    float w2; //km/h
    float w3; //km/h
    float w4; //km/h
    float stWh; //steering wheel deg
    float r; //yaw rate deg/s
    float ax1; //acc axe x driver seat (G)
    float ay1;
    float az1;
    float ax2; //acc axe x passenger seat
    float ay2;
    float az2;
} carMonitor;

extern float olduEst;
extern float oldax;

//motorCommand comp(carMonitor carState, float uThr , float slThr, int gainPp , int gainPr, int rollCompThr, int userCommand, BOOL otherComp);
motorCommand comp(carMonitor carState, float userCommand, float gainCorrection, float threshold);
//float derivative(float []);
//void meanFilter(float [], int , float []);
void matrixMultiplication(float first[3][3], float second[3][1], float (*multiply)[3][1]);

#endif	/* COMPENSATION_H */

