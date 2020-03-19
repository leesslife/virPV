TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application
INC+=drvVirAiSoft.h
PROD_IOC = virPV
# virPV.dbd will be created and installed
DBD += virPV.dbd

# virPV.dbd will be made up from these files:
virPV_DBD += base.dbd
virPV_DBD += virPVMain.dbd
# Include dbd files from all support applications:
#virPV_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#virPV_LIBS += xxx

# virPV_registerRecordDeviceDriver.cpp derives from virPV.dbd
virPV_SRCS += virPV_registerRecordDeviceDriver.cpp
virPV_SRCS += devVirAiSoft.c
virPV_SRCS += drvVirAiSoft.c

# Build the main IOC entry point on workstation OSs.
virPV_SRCS_DEFAULT += virPVMain.cpp
virPV_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#virPV_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
virPV_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

