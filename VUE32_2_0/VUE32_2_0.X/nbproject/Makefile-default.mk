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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED="${OBJECTDIR}/_ext/1360937237/offboard_sensors .o" ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o ${OBJECTDIR}/_ext/1360937237/periph.o ${OBJECTDIR}/_ext/1360937237/power_out.o ${OBJECTDIR}/_ext/1360937237/user_input.o ${OBJECTDIR}/_ext/1360937237/vue32_adc.o ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o ${OBJECTDIR}/_ext/1360937237/vue32_timers.o ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o ${OBJECTDIR}/_ext/1360937237/interrupts.o ${OBJECTDIR}/_ext/1360937237/Board.o ${OBJECTDIR}/_ext/1360937237/communication.o ${OBJECTDIR}/_ext/1360937237/Exception.o ${OBJECTDIR}/_ext/1360937237/memory_map.o ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o ${OBJECTDIR}/_ext/265640400/usb_descriptors.o ${OBJECTDIR}/_ext/265640400/usb_device.o ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o ${OBJECTDIR}/_ext/1360937237/VUE32_1.o ${OBJECTDIR}/_ext/1360937237/VUE32_2.o ${OBJECTDIR}/_ext/1360937237/VUE32_3.o ${OBJECTDIR}/_ext/1360937237/VUE32_4.o ${OBJECTDIR}/_ext/1360937237/VUE32_5.o ${OBJECTDIR}/_ext/1360937237/VUE32_6.o ${OBJECTDIR}/_ext/1360937237/VUE32_7.o ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o ${OBJECTDIR}/_ext/1360937237/VUE32_0.o ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES="${OBJECTDIR}/_ext/1360937237/offboard_sensors .o.d" ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d ${OBJECTDIR}/_ext/1360937237/periph.o.d ${OBJECTDIR}/_ext/1360937237/power_out.o.d ${OBJECTDIR}/_ext/1360937237/user_input.o.d ${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d ${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d ${OBJECTDIR}/_ext/1360937237/interrupts.o.d ${OBJECTDIR}/_ext/1360937237/Board.o.d ${OBJECTDIR}/_ext/1360937237/communication.o.d ${OBJECTDIR}/_ext/1360937237/Exception.o.d ${OBJECTDIR}/_ext/1360937237/memory_map.o.d ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d ${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d ${OBJECTDIR}/_ext/265640400/usb_device.o.d ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/offboard_sensors\ .o ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o ${OBJECTDIR}/_ext/1360937237/periph.o ${OBJECTDIR}/_ext/1360937237/power_out.o ${OBJECTDIR}/_ext/1360937237/user_input.o ${OBJECTDIR}/_ext/1360937237/vue32_adc.o ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o ${OBJECTDIR}/_ext/1360937237/vue32_timers.o ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o ${OBJECTDIR}/_ext/1360937237/interrupts.o ${OBJECTDIR}/_ext/1360937237/Board.o ${OBJECTDIR}/_ext/1360937237/communication.o ${OBJECTDIR}/_ext/1360937237/Exception.o ${OBJECTDIR}/_ext/1360937237/memory_map.o ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o ${OBJECTDIR}/_ext/265640400/usb_descriptors.o ${OBJECTDIR}/_ext/265640400/usb_device.o ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o ${OBJECTDIR}/_ext/1360937237/VUE32_1.o ${OBJECTDIR}/_ext/1360937237/VUE32_2.o ${OBJECTDIR}/_ext/1360937237/VUE32_3.o ${OBJECTDIR}/_ext/1360937237/VUE32_4.o ${OBJECTDIR}/_ext/1360937237/VUE32_5.o ${OBJECTDIR}/_ext/1360937237/VUE32_6.o ${OBJECTDIR}/_ext/1360937237/VUE32_7.o ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o ${OBJECTDIR}/_ext/1360937237/VUE32_0.o ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o ${OBJECTDIR}/_ext/1360937237/main.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512H
MP_LINKER_FILE_OPTION=,--script="vue32app.ld"
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
${OBJECTDIR}/_ext/1360937237/offboard_sensors\ .o: ../src/offboard_sensors\ .c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/offboard_sensors\ .o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/offboard_sensors .o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/offboard_sensors .o.d" -o "${OBJECTDIR}/_ext/1360937237/offboard_sensors .o" "../src/offboard_sensors .c"  
	
${OBJECTDIR}/_ext/1360937237/onboard_sensors.o: ../src/onboard_sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d" -o ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o ../src/onboard_sensors.c  
	
${OBJECTDIR}/_ext/1360937237/periph.o: ../src/periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/periph.o.d" -o ${OBJECTDIR}/_ext/1360937237/periph.o ../src/periph.c  
	
${OBJECTDIR}/_ext/1360937237/power_out.o: ../src/power_out.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_out.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/power_out.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/power_out.o.d" -o ${OBJECTDIR}/_ext/1360937237/power_out.o ../src/power_out.c  
	
${OBJECTDIR}/_ext/1360937237/user_input.o: ../src/user_input.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/user_input.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/user_input.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/user_input.o.d" -o ${OBJECTDIR}/_ext/1360937237/user_input.o ../src/user_input.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_adc.o: ../src/vue32_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_adc.o ../src/vue32_adc.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_i2c.o: ../src/vue32_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o ../src/vue32_i2c.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o: ../src/vue32_oc_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o ../src/vue32_oc_pwm.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_timers.o: ../src/vue32_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_timers.o ../src/vue32_timers.c  
	
${OBJECTDIR}/_ext/1360937237/wheel_sensor.o: ../src/wheel_sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d" -o ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o ../src/wheel_sensor.c  
	
${OBJECTDIR}/_ext/1360937237/interrupts.o: ../src/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/interrupts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/interrupts.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/interrupts.o.d" -o ${OBJECTDIR}/_ext/1360937237/interrupts.o ../src/interrupts.c  
	
${OBJECTDIR}/_ext/1360937237/Board.o: ../src/Board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Board.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Board.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/Board.o.d" -o ${OBJECTDIR}/_ext/1360937237/Board.o ../src/Board.c  
	
${OBJECTDIR}/_ext/1360937237/communication.o: ../src/communication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/communication.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/communication.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/communication.o.d" -o ${OBJECTDIR}/_ext/1360937237/communication.o ../src/communication.c  
	
${OBJECTDIR}/_ext/1360937237/Exception.o: ../src/Exception.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Exception.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Exception.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/Exception.o.d" -o ${OBJECTDIR}/_ext/1360937237/Exception.o ../src/Exception.c  
	
${OBJECTDIR}/_ext/1360937237/memory_map.o: ../src/memory_map.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/memory_map.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/memory_map.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/memory_map.o.d" -o ${OBJECTDIR}/_ext/1360937237/memory_map.o ../src/memory_map.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_Common.o: ../src/NETV32_Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o ../src/NETV32_Common.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o: ../src/NETV32_Shared.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o ../src/NETV32_Shared.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o: ../src/NETV32_USB-CDCDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o ../src/NETV32_USB-CDCDriver.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o: ../src/NETV32_CANDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o ../src/NETV32_CANDriver.c  
	
${OBJECTDIR}/_ext/265640400/usb_descriptors.o: ../src/USB-CDC_Microchip/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/265640400 
	@${RM} ${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/265640400/usb_descriptors.o ../src/USB-CDC_Microchip/usb_descriptors.c  
	
${OBJECTDIR}/_ext/265640400/usb_device.o: ../src/USB-CDC_Microchip/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/265640400 
	@${RM} ${OBJECTDIR}/_ext/265640400/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/265640400/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/265640400/usb_device.o.d" -o ${OBJECTDIR}/_ext/265640400/usb_device.o ../src/USB-CDC_Microchip/usb_device.c  
	
${OBJECTDIR}/_ext/265640400/usb_function_cdc.o: ../src/USB-CDC_Microchip/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/265640400 
	@${RM} ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o ../src/USB-CDC_Microchip/usb_function_cdc.c  
	
${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o: ../src/microchip_usb_fct.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d" -o ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o ../src/microchip_usb_fct.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_1.o: ../src/VUE32_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_1.o ../src/VUE32_1.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_2.o: ../src/VUE32_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_2.o ../src/VUE32_2.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_3.o: ../src/VUE32_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_3.o ../src/VUE32_3.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_4.o: ../src/VUE32_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_4.o ../src/VUE32_4.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_5.o: ../src/VUE32_5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_5.o ../src/VUE32_5.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_6.o: ../src/VUE32_6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_6.o ../src/VUE32_6.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_7.o: ../src/VUE32_7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_7.o ../src/VUE32_7.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o: ../src/VUE32_Impl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o ../src/VUE32_Impl.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_0.o: ../src/VUE32_0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_0.o ../src/VUE32_0.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o: ../src/VUE32_Utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o ../src/VUE32_Utils.c  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c  
	
else
${OBJECTDIR}/_ext/1360937237/offboard_sensors\ .o: ../src/offboard_sensors\ .c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/offboard_sensors\ .o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/offboard_sensors .o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/offboard_sensors .o.d" -o "${OBJECTDIR}/_ext/1360937237/offboard_sensors .o" "../src/offboard_sensors .c"  
	
${OBJECTDIR}/_ext/1360937237/onboard_sensors.o: ../src/onboard_sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/onboard_sensors.o.d" -o ${OBJECTDIR}/_ext/1360937237/onboard_sensors.o ../src/onboard_sensors.c  
	
${OBJECTDIR}/_ext/1360937237/periph.o: ../src/periph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/periph.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/periph.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/periph.o.d" -o ${OBJECTDIR}/_ext/1360937237/periph.o ../src/periph.c  
	
${OBJECTDIR}/_ext/1360937237/power_out.o: ../src/power_out.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_out.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/power_out.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/power_out.o.d" -o ${OBJECTDIR}/_ext/1360937237/power_out.o ../src/power_out.c  
	
${OBJECTDIR}/_ext/1360937237/user_input.o: ../src/user_input.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/user_input.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/user_input.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/user_input.o.d" -o ${OBJECTDIR}/_ext/1360937237/user_input.o ../src/user_input.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_adc.o: ../src/vue32_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_adc.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_adc.o ../src/vue32_adc.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_i2c.o: ../src/vue32_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_i2c.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_i2c.o ../src/vue32_i2c.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o: ../src/vue32_oc_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_oc_pwm.o ../src/vue32_oc_pwm.c  
	
${OBJECTDIR}/_ext/1360937237/vue32_timers.o: ../src/vue32_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/vue32_timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/vue32_timers.o ../src/vue32_timers.c  
	
${OBJECTDIR}/_ext/1360937237/wheel_sensor.o: ../src/wheel_sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/wheel_sensor.o.d" -o ${OBJECTDIR}/_ext/1360937237/wheel_sensor.o ../src/wheel_sensor.c  
	
${OBJECTDIR}/_ext/1360937237/interrupts.o: ../src/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/interrupts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/interrupts.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/interrupts.o.d" -o ${OBJECTDIR}/_ext/1360937237/interrupts.o ../src/interrupts.c  
	
${OBJECTDIR}/_ext/1360937237/Board.o: ../src/Board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Board.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Board.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/Board.o.d" -o ${OBJECTDIR}/_ext/1360937237/Board.o ../src/Board.c  
	
${OBJECTDIR}/_ext/1360937237/communication.o: ../src/communication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/communication.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/communication.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/communication.o.d" -o ${OBJECTDIR}/_ext/1360937237/communication.o ../src/communication.c  
	
${OBJECTDIR}/_ext/1360937237/Exception.o: ../src/Exception.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Exception.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Exception.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/Exception.o.d" -o ${OBJECTDIR}/_ext/1360937237/Exception.o ../src/Exception.c  
	
${OBJECTDIR}/_ext/1360937237/memory_map.o: ../src/memory_map.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/memory_map.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/memory_map.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/memory_map.o.d" -o ${OBJECTDIR}/_ext/1360937237/memory_map.o ../src/memory_map.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_Common.o: ../src/NETV32_Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_Common.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_Common.o ../src/NETV32_Common.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o: ../src/NETV32_Shared.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_Shared.o ../src/NETV32_Shared.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o: ../src/NETV32_USB-CDCDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_USB-CDCDriver.o ../src/NETV32_USB-CDCDriver.c  
	
${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o: ../src/NETV32_CANDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o.d" -o ${OBJECTDIR}/_ext/1360937237/NETV32_CANDriver.o ../src/NETV32_CANDriver.c  
	
${OBJECTDIR}/_ext/265640400/usb_descriptors.o: ../src/USB-CDC_Microchip/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/265640400 
	@${RM} ${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/265640400/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/265640400/usb_descriptors.o ../src/USB-CDC_Microchip/usb_descriptors.c  
	
${OBJECTDIR}/_ext/265640400/usb_device.o: ../src/USB-CDC_Microchip/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/265640400 
	@${RM} ${OBJECTDIR}/_ext/265640400/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/265640400/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/265640400/usb_device.o.d" -o ${OBJECTDIR}/_ext/265640400/usb_device.o ../src/USB-CDC_Microchip/usb_device.c  
	
${OBJECTDIR}/_ext/265640400/usb_function_cdc.o: ../src/USB-CDC_Microchip/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/265640400 
	@${RM} ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/265640400/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/265640400/usb_function_cdc.o ../src/USB-CDC_Microchip/usb_function_cdc.c  
	
${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o: ../src/microchip_usb_fct.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o.d" -o ${OBJECTDIR}/_ext/1360937237/microchip_usb_fct.o ../src/microchip_usb_fct.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_1.o: ../src/VUE32_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_1.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_1.o ../src/VUE32_1.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_2.o: ../src/VUE32_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_2.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_2.o ../src/VUE32_2.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_3.o: ../src/VUE32_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_3.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_3.o ../src/VUE32_3.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_4.o: ../src/VUE32_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_4.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_4.o ../src/VUE32_4.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_5.o: ../src/VUE32_5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_5.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_5.o ../src/VUE32_5.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_6.o: ../src/VUE32_6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_6.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_6.o ../src/VUE32_6.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_7.o: ../src/VUE32_7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_7.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_7.o ../src/VUE32_7.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o: ../src/VUE32_Impl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_Impl.o ../src/VUE32_Impl.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_0.o: ../src/VUE32_0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_0.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_0.o ../src/VUE32_0.c  
	
${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o: ../src/VUE32_Utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o.d" -o ${OBJECTDIR}/_ext/1360937237/VUE32_Utils.o ../src/VUE32_Utils.c  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="mapmem.txt",--report-mem 
else
dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="mapmem.txt",--report-mem
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/VUE32_2_0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
