/* 
 * File:   Compensation.c
 * Author: Alexandre Bolduc
 *
 * Created on 17 novembre 2012, 10:44
 */

#include <math.h>
#include "Compensation.h"

/*// Local Variables used for complete compensation only
float olduEst = 0;
float oldax = 0;

float rightCorrFact = 0.0037;
float leftCorrFact = 0.0039;

float backendMat[3][3] = {{0.9984, 0, 0.056},{0, 1, 0},{0.056, 0, 0.9984}};
float transpositionLeftMat[3][3]= {{0.026, -0.9084, -0.1039},{1.0004, 0.1223, 0.0235},{0.0068, 0.1319, -0.9914}};
float transpositionRightMat[3][3]= {{0.0499, -0.9064, -0.2879},{0.9612, 0.004, 0.2331},{0.2289, 0.3154, -0.921}};
float carStateMatLeft[3][1] = {{0},{0},{0}};
float carStateMatRight[3][1] = {{0},{0},{0}};
float carStateMatTemp1[3][1] = {{0},{0},{0}};
float carStateMatTemp2[3][1] = {{0},{0},{0}};*/

/*
 * 
 */
motorCommand comp(carMonitor carState, float userCommand, float gainCorrection, float threshold)
{
    /////////////////////////////////////////////////
    //        Building internal representation     //
    /////////////////////////////////////////////////

    BOOL badData = FALSE;
    float delta, meanSpeed;

    // Security check for bad sensors data

    if(carState.stWh >= STEERINGMAX || carState.stWh <= STEERINGMIN)
    {
        badData = TRUE;
    }
    else if (carState.w3 > WHEELSPEEDMAX || carState.w3 < WHEELSPEEDMIN)
    {
        badData = TRUE;
    }
    else if (carState.w4 > WHEELSPEEDMAX || carState.w4 < WHEELSPEEDMIN)
    {
        badData = TRUE;
    }

    /////////////////////////////////////////////////
    //        Calculating compensation values      //
    /////////////////////////////////////////////////

    motorCommand command;

    if (gainCorrection == 0)
    {

        meanSpeed = ((carState.w3 + carState.w4)/2.0)/3.6;

        // Compensation systems
        // if mean car speed is over 5 km/h
        if(meanSpeed > (5.0/3.6))
        {
            delta = abs(gainCorrection * GAIN * sinf(((carState.stWh*PI)/180.0) / REDFACT) / (meanSpeed));
        }
        else
        {
            delta = 0.0;
        }

        //Saturation of the delta command
        if(delta > threshold)
        {
            delta = threshold;
        }

        //Verifying the steering wheel position to know which torque comand to apply to each motors
        if (carState.stWh > 0.0)
        {
            command.tmWh3 = userCommand - delta;
            command.tmWh4 = userCommand + delta;
        }
        else
        {
            command.tmWh3 = userCommand + delta;
            command.tmWh4 = userCommand - delta;
        }

    }
    else
    {
        command.tmWh3 = userCommand;
        command.tmWh4 = userCommand;
    }

    // Torque command saturation
    if (command.tmWh3 > MAXTO)
    {
        command.tmWh3 = MAXTO;
    }
    else if (command.tmWh3 < 0.0)
    {
        command.tmWh3 = 0.0;
    }

    if (command.tmWh4 > MAXTO)
    {
        command.tmWh4 = MAXTO;
    }
    else if (command.tmWh4 < 0.0)
    {
        command.tmWh4 = 0.0;
    }

    /*if(badData)
    {
        //TODO : Send error message
        command.tmWh3 = 0;
        command.tmWh3 = 0;
    }*/

    return command;
}

// Matrix multiplication fonction - Only used for complete compensation
void matrixMultiplication(float first[3][3], float second[3][1], float (*multiply)[3][1])
{

    int m, p, q, c, d, k;
    float sum = 0;

    m = 3;
    p = 3;
    q = 1;

    for ( c = 0 ; c < m ; c++ )
    {
      for ( d = 0 ; d < q ; d++ )
      {
        for ( k = 0 ; k < p ; k++ )
        {
          sum = sum + first[c][k] * second[k][d];
        }

        (*multiply)[c][d] = sum;
        sum = 0;
      }
    }
}

// Complete compensation
/* Compensation main function; to call as soon as the motor drives are ready:
Inputs:
    (carState) carMonitor structure of sensor info as defined in this file
    (uThr ; float) long. speed estimation technique threshold (typ. 0.05)
    (SlThr ; float) Slipping control threshold (typ. 0.2)
    (gainPp ; int) Roll rate compensation proportional gain (typ. 150)
    (gainPr ; int) yaw rate compensation proportional gain (typ. 400)
    (rollCompThr ; int) suggested torque at which the roll compensation activates (typ. 40 Nm)
    (userCommand ; int) user accelerator pedal command (N*m)

Output:
    motorCommand structure as define in this file
*/
/*motorCommand comp(carMonitor carState, float uThr , float slThr, int gainPp , int gainPr, int rollCompThr, int userCommand, BOOL otherComp)
{
    /////////////////////////////////////////////////
    //        Building internal representation     //
    /////////////////////////////////////////////////

    // Initialization

    float roll;
    float r;
    float uEst;
    float w1;
    float w2;
    float w3;
    float w4;
    float ax;
    float ay;
    float stWh;
    float s1;
    float s2;
    float s3;
    float s4;
    float Fz3;
    float Fz4;
    float diffFz;

    float maxS3 = 0;
    float maxS4 = 0;
    float maxS2 = 0;
    float maxS1 = 0;

    BOOL badData = FALSE;

    int i =0;

    // Correcting acceleration sensors
    carStateMatTemp1[0][0] = carState.ax1;
    carStateMatTemp1[1][0] = carState.ay1;
    carStateMatTemp1[2][0] = carState.az1;

    matrixMultiplication(transpositionLeftMat, carStateMatTemp1, &carStateMatTemp2);
    matrixMultiplication(backendMat, carStateMatTemp2, &carStateMatLeft);

    for(i=0;i<3;i++)
    {
        carStateMatLeft[i][0] = leftCorrFact * carStateMatLeft[i][0];
    }

    carStateMatTemp1[0][0] = carState.ax2;
    carStateMatTemp1[1][0] = carState.ay2;
    carStateMatTemp1[2][0] = carState.az2;

    matrixMultiplication(transpositionRightMat, carStateMatTemp1, &carStateMatRight);

    for(i=0;i<3;i++)
    {
        carStateMatRight[i][0] = rightCorrFact * carStateMatRight[i][0];
    }

    // Security check for bad sensors data
    if (carState.ax1 >= ACCMAX || carState.ax1 <= ACCMIN)
    {
        badData = TRUE;
    }
    else if (carState.ay1 >= ACCMAX || carState.ay1 <= ACCMIN)
    {
        badData = TRUE;
    }
    else if (carState.az1 >= ACCMAX || carState.az1 <= ACCMIN)
    {
        badData = TRUE;
    }
    if (carState.ax2 >= ACCMAX || carState.ax2 <= ACCMIN)
    {
        badData = TRUE;
    }
    else if (carState.ay2 >= ACCMAX || carState.ay2 <= ACCMIN)
    {
        badData = TRUE;
    }
    else if (carState.az2 >= ACCMAX || carState.az2 <= ACCMIN)
    {
        badData = TRUE;
    }
    else if(w1 >= WHEELSPEEDMAX || w1 <= WHEELSPEEDMIN)
    {
        badData = TRUE;
    }
    else if(w2 >= WHEELSPEEDMAX || w2 <= WHEELSPEEDMIN)
    {
        badData = TRUE;
    }
    else if(w3 >= WHEELSPEEDMAX || w3 <= WHEELSPEEDMIN)
    {
        badData = TRUE;
    }
    else if(w4 >= WHEELSPEEDMAX || w4 <= WHEELSPEEDMIN)
    {
        badData = TRUE;
    }
    else if(stWh >= STEERINGMAX || stWh <= STEERINGMIN)
    {
        badData = TRUE;
    }
    else if(r >= YAWMAX || r <= YAWMIN)
    {
        badData = TRUE;
    }

    ax = (carState.ax1*GRAVITY + carState.ax2*GRAVITY)/(float)2;
    ay = (carState.ay1*GRAVITY + carState.ay2*GRAVITY)/(float)2;
    w1 = (carState.w1*((float)1000/(float)60/(float)60))/R;
    w2 = (carState.w2*((float)1000/(float)60/(float)60))/R;
    w3 = (carState.w3*((float)1000/(float)60/(float)60))/R;
    w4 = (carState.w4*((float)1000/(float)60/(float)60))/R;
    stWh = (carState.stWh*(PI/(float)180))/REDFACT;
    r = carState.r*(PI/(float)180);
    uEst = R*(w1+w2+w3+w4)/(float)4;

    roll = (float)0.0605*asinf((carState.az2*GRAVITY - carState.az1*GRAVITY)/GRAVITY);

    Fz3 = ((MASS * GRAVITY)/(float)2) * ((A/L)+(ax/GRAVITY) * (H/L) + ((float)1-KR) *
                ((ay/GRAVITY) * (H/T) - (MS/MASS) * (HCOMMA/T) * sinf(roll)));

    Fz4 = ((MASS * GRAVITY)/(float)2) * ((A/L)+(ax/GRAVITY) * (H/L) - ((float)1-KR) *
                ((ay/GRAVITY) * (H/T) - (MS/MASS) * (HCOMMA/T) * sinf(roll)));


    diffFz = Fz4-Fz3;

    // Calculating longitudinal slips
    s1 = (float)1 + (-uEst)/(w1*R);
    s2 = (float)1 + (-uEst)/(w2*R);
    s3 = (float)1 + (-uEst)/(w3*R);
    s4 = (float)1 + (-uEst)/(w4*R);

    if (fabs(s3) > maxS3)
    {
        maxS3 = fabs(s3);
    }
    if (fabs(s4) > maxS4)
    {
        maxS4 = fabs(s4);
    }
            if (fabs(s1) > maxS1)
    {
        maxS1 = fabs(s1);
    }
    if (fabs(s2) > maxS2)
    {
        maxS2 = fabs(s2);
    }

    // If the u estimation is too far off, recalculates by
    // integrating ax sensor info
    if ((maxS3 > uThr) || (maxS4 > uThr) || (maxS1 > uThr) || (maxS2 > uThr))
    {
        uEst = olduEst + oldax*TIMESTEP;

        s3 = ((w3*R)-uEst)/(w3*R);
        s4 = ((w4*R)-uEst)/(w4*R);

        if (fabs(s3) > maxS3)
        {
            maxS3 = fabs(s3);
        }
        if (fabs(s4) > maxS4)
        {
            maxS4 = fabs(s4);
        }
    }

    float moyr = r;
    float moyFz = (-(float)4/(float)10000)*diffFz;

    /////////////////////////////////////////////////
    //        Calculating compensation values      //
    /////////////////////////////////////////////////

    motorCommand command;

    // Other compensation systems
    if (otherComp)
    {
        // Roll rate compensation
        command.tmWh3 = (int)(moyFz*(float)gainPp);
        command.tmWh4 = (int)(-moyFz*(float)gainPp);

        // Yaw rate compensation
        if ((int)fabs(command.tmWh3) < rollCompThr)
        {
            float theoricr = uEst/(T/sinf(stWh));
            float error = theoricr - moyr;
            command.tmWh3 = (int)(userCommand + error*(float)gainPr);
            command.tmWh4 = (int)(userCommand - error*(float)gainPr);
        }

        // Torque command saturation
        if (command.tmWh3 > MAXTO)
            command.tmWh3 = MAXTO;
        else if (command.tmWh3 < -MAXTO)
            command.tmWh3 = -MAXTO;
        if (command.tmWh4 > MAXTO)
            command.tmWh4 = MAXTO;
        else if (command.tmWh4 < -MAXTO)
            command.tmWh4 = -MAXTO;

        // Slipping control
        if (maxS3 > slThr)
            command.tmWh3 = 0;
        else if (maxS4 > slThr)
            command.tmWh4 = 0;
    }
    else
    {
        command.tmWh3 = userCommand;
        command.tmWh4 = userCommand;
    }

    if(badData)
    {
        //TODO : Send error message
        command.tmWh3 = 0;
        command.tmWh3 = 0;
    }

    olduEst = uEst;
    oldax = ax;
    return command;
}
*/