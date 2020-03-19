#ifndef DRVVIRAISOFT_H
#define DRVVIRAISOFT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SET_POINT 100

typedef struct PID
{
    double kp;
    double ki;
    double kd;
    double lastpoint;
    double differential;
    double integration;
    double fix;
}PID,*pPID;

void init_pid(pPID pp,double p,double i,double d);
double pid_calculate(pPID pp,double error);
double sensor(double output,double setPoint);

typedef struct OBJ
{
    PID sPID;
    double setpoint;
    double output;
    double error;
}OBJ,*pOBJ;

void init_obj(pOBJ po,double sp,double p,double i,double d);
double run_obj(pOBJ po);
int disturb(pOBJ p);
#endif














































