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
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/adc.o ${OBJECTDIR}/simple_main.o ${OBJECTDIR}/Timer.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/periph.o ${OBJECTDIR}/CN.o ${OBJECTDIR}/internalTemp.o ${OBJECTDIR}/Analogic_Module.o ${OBJECTDIR}/Digital_Module.o ${OBJECTDIR}/Power_Module.o
POSSIBLE_DEPFILES=${OBJECTDIR}/adc.o.d ${OBJECTDIR}/simple_main.o.d ${OBJECTDIR}/Timer.o.d ${OBJECTDIR}/pwm.o.d ${OBJECTDIR}/periph.o.d ${OBJECTDIR}/CN.o.d ${OBJECTDIR}/internalTemp.o.d ${OBJECTDIR}/Analogic_Module.o.d ${OBJECTDIR}/Digital_Module.o.d ${OBJECTDIR}/Power_Module.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/adc.o ${OBJECTDIR}/simple_main.o ${OBJECTDIR}/Timer.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/periph.o ${OBJECTDIR}/CN.o ${OBJECTDIR}/internalTemp.o ${OBJECTDIR}/Analogic_Module.o ${OBJECTDIR}/Digital_Module.o ${OBJECTDIR}/Power_Module.o


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
${OBJECTDIR}/adc.o: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c  -legacy-libc
	
${OBJECTDIR}/simple_main.o: simple_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/simple_main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/simple_main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/simple_main.o.d" -o ${OBJECTDIR}/simple_main.o simple_main.c  -legacy-libc
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Timer.o.d" -o ${OBJECTDIR}/Timer.o Timer.c  -legacy-libc
	
${OBJECTDIR}/pwm.o: pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${FIXDEPS} "${OBJECTDIR}/pwm.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/pwm.o.d" -o ${OBJECTDIR}/pwm.o pwm.c  -legacy-libc
	
${OBJECTDIR}/periph.o: periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/periph.o.d" -o ${OBJECTDIR}/periph.o periph.c  -legacy-libc
	
${OBJECTDIR}/CN.o: CN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CN.o.d 
	@${FIXDEPS} "${OBJECTDIR}/CN.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/CN.o.d" -o ${OBJECTDIR}/CN.o CN.c  -legacy-libc
	
${OBJECTDIR}/internalTemp.o: internalTemp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/internalTemp.o.d 
	@${FIXDEPS} "${OBJECTDIR}/internalTemp.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/internalTemp.o.d" -o ${OBJECTDIR}/internalTemp.o internalTemp.c  -legacy-libc
	
${OBJECTDIR}/Analogic_Module.o: Analogic_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Analogic_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Analogic_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Analogic_Module.o.d" -o ${OBJECTDIR}/Analogic_Module.o Analogic_Module.c  -legacy-libc
	
${OBJECTDIR}/Digital_Module.o: Digital_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Digital_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Digital_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Digital_Module.o.d" -o ${OBJECTDIR}/Digital_Module.o Digital_Module.c  -legacy-libc
	
${OBJECTDIR}/Power_Module.o: Power_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Power_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Power_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Power_Module.o.d" -o ${OBJECTDIR}/Power_Module.o Power_Module.c  -legacy-libc
	
else
${OBJECTDIR}/adc.o: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c  -legacy-libc
	
${OBJECTDIR}/simple_main.o: simple_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/simple_main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/simple_main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/simple_main.o.d" -o ${OBJECTDIR}/simple_main.o simple_main.c  -legacy-libc
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Timer.o.d" -o ${OBJECTDIR}/Timer.o Timer.c  -legacy-libc
	
${OBJECTDIR}/pwm.o: pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${FIXDEPS} "${OBJECTDIR}/pwm.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/pwm.o.d" -o ${OBJECTDIR}/pwm.o pwm.c  -legacy-libc
	
${OBJECTDIR}/periph.o: periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/periph.o.d" -o ${OBJECTDIR}/periph.o periph.c  -legacy-libc
	
${OBJECTDIR}/CN.o: CN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CN.o.d 
	@${FIXDEPS} "${OBJECTDIR}/CN.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/CN.o.d" -o ${OBJECTDIR}/CN.o CN.c  -legacy-libc
	
${OBJECTDIR}/internalTemp.o: internalTemp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/internalTemp.o.d 
	@${FIXDEPS} "${OBJECTDIR}/internalTemp.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/internalTemp.o.d" -o ${OBJECTDIR}/internalTemp.o internalTemp.c  -legacy-libc
	
${OBJECTDIR}/Analogic_Module.o: Analogic_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Analogic_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Analogic_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Analogic_Module.o.d" -o ${OBJECTDIR}/Analogic_Module.o Analogic_Module.c  -legacy-libc
	
${OBJECTDIR}/Digital_Module.o: Digital_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Digital_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Digital_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Digital_Module.o.d" -o ${OBJECTDIR}/Digital_Module.o Digital_Module.c  -legacy-libc
	
${OBJECTDIR}/Power_Module.o: Power_Module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Power_Module.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Power_Module.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/MPLAB C32 Suite/pic32-libs" -MMD -MF "${OBJECTDIR}/Power_Module.o.d" -o ${OBJECTDIR}/Power_Module.o Power_Module.c  -legacy-libc
	
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
