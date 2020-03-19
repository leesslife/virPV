#!../../bin/linux-x86_64/virPV

## You may have to change virPV to something else
## everywhere it appears in this file

< envPaths

## Register all support components
dbLoadDatabase("../../dbd/virPV.dbd",0,0)
virPV_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadTemplate("DPU07.substitutions")

iocInit()

## Start any sequence programs
#seq sncvirPV,"user=root"
