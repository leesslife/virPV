/*************************************************************************\
* Copyright (c) 2008 UChicago Argonne LLC, as Operator of Argonne
*     National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
*     Operator of Los Alamos National Laboratory.
* EPICS BASE is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/

/*
 *      Original Authors: Bob Dalesio and Marty Kraimer
 *      Date: 3/6/91
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "alarm.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "epicsMath.h"
#include "recGbl.h"
#include "devSup.h"
#include "aiRecord.h"
#include "epicsExport.h"
#include "drvVirAiSoft.h"
//#include "ListVirPV.h"
/* Create the dset for devAiSoft */
static long init_record(aiRecord *prec);
static long read_ai(aiRecord *prec);
static long init(aiRecord *prec);
static double virStart=20;
static OBJ obj[200];
struct {
    long      number;
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN read_ai;
    DEVSUPFUN special_linconv;
} devVirAiSoft = {
    6,
    NULL,
    init,
    init_record,
    NULL,
    read_ai,
    NULL
};
epicsExportAddress(dset, devVirAiSoft);
static long init(aiRecord *prec)
{
    printf("begin my init\n");
    return 0;
}
static long init_record(aiRecord *prec)
{
    /* INP must be CONSTANT, PV_LINK, DB_LINK or CA_LINK*/
    switch (prec->inp.type) {
    case CONSTANT:
	    prec->val=virStart;
        int b=atoi(prec->inp.text);
        init_obj(&obj[b],40,100,0.5,0.5);
        if (recGblInitConstantLink(&prec->inp, DBF_DOUBLE, &prec->val))
            prec->udf = FALSE;
        break;
    case PV_LINK:
    case DB_LINK:
    case CA_LINK:
        break;
    default:
        recGblRecordError(S_db_badField, (void *)prec,
            "devAiSoft (init_record) Illegal INP field");
        return S_db_badField;
    }
    return 0;
}

static long read_ai(aiRecord *prec)
{
    double val;

    if (prec->inp.type == CONSTANT)
    {
        int b=atoi(prec->inp.text);
	    prec->val =run_obj(&obj[b]);
        return 2;
    }
    if (!dbGetLink(&prec->inp, DBR_DOUBLE, &val, 0, 0)) {

        /* Apply smoothing algorithm */
        if (prec->smoo != 0.0 && prec->dpvt && finite(prec->val))
            prec->val = val * (1.00 - prec->smoo) + (prec->val * prec->smoo);
        else
            prec->val = val;

        prec->udf = FALSE;
        prec->dpvt = &devVirAiSoft;        /* Any non-zero value */

        if (prec->tsel.type == CONSTANT &&
            prec->tse == epicsTimeEventDeviceTime)
            dbGetTimeStamp(&prec->inp, &prec->time);
    } else {
        prec->dpvt = NULL;
    }
    return 2;
}
