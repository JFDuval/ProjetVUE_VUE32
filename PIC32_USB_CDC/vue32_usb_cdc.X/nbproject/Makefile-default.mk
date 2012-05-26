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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/periph.o ${OBJECTDIR}/_ext/1360937237/interrupt.o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ${OBJECTDIR}/_ext/1360907413/usb_device.o ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/periph.o.d ${OBJECTDIR}/_ext/1360937237/interrupt.o.d ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d ${OBJECTDIR}/_ext/1360907413/usb_device.o.d ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/periph.o ${OBJECTDIR}/_ext/1360937237/interrupt.o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ${OBJECTDIR}/_ext/1360907413/usb_device.o ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o


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

# The following macros may be used in the pre and post step lines
Device=PIC32MX795F512H
ProjectDir="C:\Dropbox\VUE\Code\Controle\Code VUE32\PIC32_USB_CDC\vue32_usb_cdc.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"

.build-conf:  .pre ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: []"
	@
	@echo "--------------------------------------"

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
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c  
	
${OBJECTDIR}/_ext/1360937237/periph.o: ../src/periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360937237/periph.o.d" -o ${OBJECTDIR}/_ext/1360937237/periph.o ../src/periph.c  
	
${OBJECTDIR}/_ext/1360937237/interrupt.o: ../src/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/interrupt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/interrupt.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360937237/interrupt.o.d" -o ${OBJECTDIR}/_ext/1360937237/interrupt.o ../src/interrupt.c  
	
${OBJECTDIR}/_ext/1360907413/usb_descriptors.o: ../USB/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ../USB/usb_descriptors.c  
	
${OBJECTDIR}/_ext/1360907413/usb_device.o: ../USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_device.o ../USB/usb_device.c  
	
${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o: ../USB/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o ../USB/usb_function_cdc.c  
	
else
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c  
	
${OBJECTDIR}/_ext/1360937237/periph.o: ../src/periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360937237/periph.o.d" -o ${OBJECTDIR}/_ext/1360937237/periph.o ../src/periph.c  
	
${OBJECTDIR}/_ext/1360937237/interrupt.o: ../src/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/interrupt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/interrupt.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360937237/interrupt.o.d" -o ${OBJECTDIR}/_ext/1360937237/interrupt.o ../src/interrupt.c  
	
${OBJECTDIR}/_ext/1360907413/usb_descriptors.o: ../USB/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ../USB/usb_descriptors.c  
	
${OBJECTDIR}/_ext/1360907413/usb_device.o: ../USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_device.o ../USB/usb_device.c  
	
${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o: ../USB/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360907413 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../USB" -I"../src" -I"../NetV" -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_function_cdc.o ../USB/usb_function_cdc.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-L"../../../MPLAB C32 Suite/lib",-L"../../../MPLAB C32 Suite/pic32mx/lib",-Map="${DISTDIR}/vue32_usb_cdc.X.${IMAGE_TYPE}.map" 
else
dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-L"../../../MPLAB C32 Suite/lib",-L"../../../MPLAB C32 Suite/pic32mx/lib",-Map="${DISTDIR}/vue32_usb_cdc.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/vue32_usb_cdc.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: []"
	@
	@echo "--------------------------------------"

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
