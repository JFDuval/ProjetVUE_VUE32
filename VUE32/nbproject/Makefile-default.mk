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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/periph.o ${OBJECTDIR}/cn_vue32.o ${OBJECTDIR}/pwm_vue32.o ${OBJECTDIR}/timer_vue32.o ${OBJECTDIR}/adc_vue32.o ${OBJECTDIR}/analogic_module.o ${OBJECTDIR}/digital_module.o ${OBJECTDIR}/power_module.o ${OBJECTDIR}/Communication_Module.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/periph.o.d ${OBJECTDIR}/cn_vue32.o.d ${OBJECTDIR}/pwm_vue32.o.d ${OBJECTDIR}/timer_vue32.o.d ${OBJECTDIR}/adc_vue32.o.d ${OBJECTDIR}/analogic_module.o.d ${OBJECTDIR}/digital_module.o.d ${OBJECTDIR}/power_module.o.d ${OBJECTDIR}/Communication_Module.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/periph.o ${OBJECTDIR}/cn_vue32.o ${OBJECTDIR}/pwm_vue32.o ${OBJECTDIR}/timer_vue32.o ${OBJECTDIR}/adc_vue32.o ${OBJECTDIR}/analogic_module.o ${OBJECTDIR}/digital_module.o ${OBJECTDIR}/power_module.o ${OBJECTDIR}/Communication_Module.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
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
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  -legacy-libc
	
${OBJECTDIR}/periph.o: periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/periph.o.d" -o ${OBJECTDIR}/periph.o periph.c  -legacy-libc
	
${OBJECTDIR}/cn_vue32.o: cn_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/cn_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/cn_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/cn_vue32.o.d" -o ${OBJECTDIR}/cn_vue32.o cn_vue32.c  -legacy-libc
	
${OBJECTDIR}/pwm_vue32.o: pwm_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pwm_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/pwm_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/pwm_vue32.o.d" -o ${OBJECTDIR}/pwm_vue32.o pwm_vue32.c  -legacy-libc
	
${OBJECTDIR}/timer_vue32.o: timer_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timer_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/timer_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/timer_vue32.o.d" -o ${OBJECTDIR}/timer_vue32.o timer_vue32.c  -legacy-libc
	
${OBJECTDIR}/adc_vue32.o: adc_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/adc_vue32.o.d" -o ${OBJECTDIR}/adc_vue32.o adc_vue32.c  -legacy-libc
	
${OBJECTDIR}/analogic_module.o: analogic_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/analogic_module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/analogic_module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/analogic_module.o.d" -o ${OBJECTDIR}/analogic_module.o analogic_module.c  -legacy-libc
	
${OBJECTDIR}/digital_module.o: digital_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/digital_module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/digital_module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/digital_module.o.d" -o ${OBJECTDIR}/digital_module.o digital_module.c  -legacy-libc
	
${OBJECTDIR}/power_module.o: power_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/power_module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/power_module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/power_module.o.d" -o ${OBJECTDIR}/power_module.o power_module.c  -legacy-libc
	
${OBJECTDIR}/Communication_Module.o: Communication_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Communication_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Communication_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Communication_Module.o.d" -o ${OBJECTDIR}/Communication_Module.o Communication_Module.c  -legacy-libc
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  -legacy-libc
	
${OBJECTDIR}/periph.o: periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/periph.o.d" -o ${OBJECTDIR}/periph.o periph.c  -legacy-libc
	
${OBJECTDIR}/cn_vue32.o: cn_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/cn_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/cn_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/cn_vue32.o.d" -o ${OBJECTDIR}/cn_vue32.o cn_vue32.c  -legacy-libc
	
${OBJECTDIR}/pwm_vue32.o: pwm_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pwm_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/pwm_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/pwm_vue32.o.d" -o ${OBJECTDIR}/pwm_vue32.o pwm_vue32.c  -legacy-libc
	
${OBJECTDIR}/timer_vue32.o: timer_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timer_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/timer_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/timer_vue32.o.d" -o ${OBJECTDIR}/timer_vue32.o timer_vue32.c  -legacy-libc
	
${OBJECTDIR}/adc_vue32.o: adc_vue32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc_vue32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc_vue32.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/adc_vue32.o.d" -o ${OBJECTDIR}/adc_vue32.o adc_vue32.c  -legacy-libc
	
${OBJECTDIR}/analogic_module.o: analogic_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/analogic_module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/analogic_module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/analogic_module.o.d" -o ${OBJECTDIR}/analogic_module.o analogic_module.c  -legacy-libc
	
${OBJECTDIR}/digital_module.o: digital_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/digital_module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/digital_module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/digital_module.o.d" -o ${OBJECTDIR}/digital_module.o digital_module.c  -legacy-libc
	
${OBJECTDIR}/power_module.o: power_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/power_module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/power_module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/power_module.o.d" -o ${OBJECTDIR}/power_module.o power_module.c  -legacy-libc
	
${OBJECTDIR}/Communication_Module.o: Communication_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Communication_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Communication_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Communication_Module.o.d" -o ${OBJECTDIR}/Communication_Module.o Communication_Module.c  -legacy-libc
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -legacy-libc -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1 
else
dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -legacy-libc -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/VUE32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
