#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/NETV32_Common.o ${OBJECTDIR}/_ext/1472/NETV32_Memory.o ${OBJECTDIR}/_ext/1472/NETV32_Shared.o ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o ${OBJECTDIR}/_ext/65181253/usb_descriptors.o ${OBJECTDIR}/_ext/65181253/usb_device.o ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pic32mx_cfg.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/NETV32_Common.o.d ${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d ${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d ${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d ${OBJECTDIR}/_ext/65181253/usb_device.o.d ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/pic32mx_cfg.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/NETV32_Common.o ${OBJECTDIR}/_ext/1472/NETV32_Memory.o ${OBJECTDIR}/_ext/1472/NETV32_Shared.o ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o ${OBJECTDIR}/_ext/65181253/usb_descriptors.o ${OBJECTDIR}/_ext/65181253/usb_device.o ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pic32mx_cfg.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/NETV32_Common.o: ../NETV32_Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_Common.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_Common.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_Common.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_Common.o ../NETV32_Common.c  
	
${OBJECTDIR}/_ext/1472/NETV32_Memory.o: ../NETV32_Memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_Memory.o ../NETV32_Memory.c  
	
${OBJECTDIR}/_ext/1472/NETV32_Shared.o: ../NETV32_Shared.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_Shared.o ../NETV32_Shared.c  
	
${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o: ../NETV32_USB-CDCDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o ../NETV32_USB-CDCDriver.c  
	
${OBJECTDIR}/_ext/65181253/usb_descriptors.o: ../USB-CDC_Microchip/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65181253 
	@${RM} ${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/65181253/usb_descriptors.o ../USB-CDC_Microchip/usb_descriptors.c  
	
${OBJECTDIR}/_ext/65181253/usb_device.o: ../USB-CDC_Microchip/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65181253 
	@${RM} ${OBJECTDIR}/_ext/65181253/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65181253/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/65181253/usb_device.o.d" -o ${OBJECTDIR}/_ext/65181253/usb_device.o ../USB-CDC_Microchip/usb_device.c  
	
${OBJECTDIR}/_ext/65181253/usb_function_cdc.o: ../USB-CDC_Microchip/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65181253 
	@${RM} ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o ../USB-CDC_Microchip/usb_function_cdc.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/pic32mx_cfg.o: pic32mx_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pic32mx_cfg.o.d 
	@${FIXDEPS} "${OBJECTDIR}/pic32mx_cfg.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/pic32mx_cfg.o.d" -o ${OBJECTDIR}/pic32mx_cfg.o pic32mx_cfg.c  
	
else
${OBJECTDIR}/_ext/1472/NETV32_Common.o: ../NETV32_Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_Common.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_Common.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_Common.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_Common.o ../NETV32_Common.c  
	
${OBJECTDIR}/_ext/1472/NETV32_Memory.o: ../NETV32_Memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_Memory.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_Memory.o ../NETV32_Memory.c  
	
${OBJECTDIR}/_ext/1472/NETV32_Shared.o: ../NETV32_Shared.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_Shared.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_Shared.o ../NETV32_Shared.c  
	
${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o: ../NETV32_USB-CDCDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o.d" -o ${OBJECTDIR}/_ext/1472/NETV32_USB-CDCDriver.o ../NETV32_USB-CDCDriver.c  
	
${OBJECTDIR}/_ext/65181253/usb_descriptors.o: ../USB-CDC_Microchip/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65181253 
	@${RM} ${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/65181253/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/65181253/usb_descriptors.o ../USB-CDC_Microchip/usb_descriptors.c  
	
${OBJECTDIR}/_ext/65181253/usb_device.o: ../USB-CDC_Microchip/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65181253 
	@${RM} ${OBJECTDIR}/_ext/65181253/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65181253/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/65181253/usb_device.o.d" -o ${OBJECTDIR}/_ext/65181253/usb_device.o ../USB-CDC_Microchip/usb_device.c  
	
${OBJECTDIR}/_ext/65181253/usb_function_cdc.o: ../USB-CDC_Microchip/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65181253 
	@${RM} ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/_ext/65181253/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/65181253/usb_function_cdc.o ../USB-CDC_Microchip/usb_function_cdc.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/pic32mx_cfg.o: pic32mx_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pic32mx_cfg.o.d 
	@${FIXDEPS} "${OBJECTDIR}/pic32mx_cfg.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -I"../" -I"../USB-CDC_Microchip" -MMD -MF "${OBJECTDIR}/pic32mx_cfg.o.d" -o ${OBJECTDIR}/pic32mx_cfg.o pic32mx_cfg.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="memorymap.txt",--report-mem 
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="memorymap.txt",--report-mem
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic32dev_beta.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
