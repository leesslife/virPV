#include "drvVirAiSoft.h"
static double feedback=0;

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
    pp->differential=pp->lastpoint-error;
    pp->fix=pp->kp*error+pp->ki*pp->integration+pp->kd*pp->differential;
    pp->lastpoint=error;
    return pp->fix;
}

double sensor(double output,double setPoint)
{
    feedback=+(output/10000);
    return feedback;
}

void init_obj(pOBJ po,double sp,double p,double i,double d){
    po->setpoint=sp;
    po->output=0;
    po->error=0;
    init_pid(&po->sPID,p,i,d);
}

double run_obj(pOBJ po)
{
    int disturb(pOBJ p);
    double fix;
    sensor(po->output,po->setpoint);
    po->error=po->setpoint-feedback;
    fix=pid_calculate(&po->sPID,po->error);
    po->output=fix+disturb(po);
    //po->output+=fix+10;
    //po->output+=f
    return feedback;
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















































