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

void init_pid(pPID pp,double p,double i,double d)
{
    pp->kp=p;
    pp->ki=i;
    pp->kd=d;
    pp->lastpoint=0;
    pp->differential=0;
    pp->integration=0;
    pp->fix=0;
}

double pid_calculate(pPID pp,double error)
{
    pp->integration+=error;
    pp->differential=error-pp->lastpoint;
    pp->fix=pp->kp*error+pp->ki*pp->integration+pp->kd*pp->differential;
    pp->lastpoint=error;
    return pp->fix;
}

double sensor(double output)
{
    double feedback=output;
    return feedback;
}

typedef struct OBJ
{
    PID sPID;
    double setpoint;
    double output;
    double error;
}OBJ,*pOBJ;

void init_obj(pOBJ po,double sp,double p,double i,double d){
    po->setpoint=sp;
    po->output=0;
    po->error=0;
    init_pid(&po->sPID,p,i,d);
}

void run_obj(pOBJ po,int n)
{
    int disturb(pOBJ p);
    double fix,feedback;
    int i;
    //for(i=1;i<n;i++)
    for(i=1;;i++)
    {
        feedback=sensor(po->output);
        po->error=po->setpoint-feedback;
        fix=pid_calculate(&po->sPID,po->error);
        po->output+=fix+disturb(po);
        //po->output+=fix+10;
        //po->output+=f
        printf("%3d %8.2f\n",i,po->output);
    }
}

int disturb(pOBJ p){
    static int i;
    if(i==0)
    {
        srand((unsigned)time(NULL));
        i=1;
    }
    return rand()%((int)(-p->setpoint*0.05)-(int)(p->setpoint*0.05))+p->setpoint*0.05;
}
void main()
{
    OBJ sOBJ;
    init_obj(&sOBJ,SET_POINT,1,0.5,0.5);
    run_obj(&sOBJ,100);
}
















































