#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pic32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pic32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../impl/src/dgi-control-field.c ../../impl/src/dgi-get-field.c ../../impl/src/dgi-process-canbus-message.c ../../impl/src/dgi-update-field.c ../../impl/src/dgi-storage-config.c ../../impl/src/dgi-canbus-config.c log.c platform-canbus.c platform-serial.c platform-storage.c platform-timer.c main.c config-bits.c exceptions.c platform-initialize.c ../../src/storage-canbus-access.c ../../src/storage-sync.c ../../src/uds-server.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1603796203/dgi-control-field.o ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o ${OBJECTDIR}/log.o ${OBJECTDIR}/platform-canbus.o ${OBJECTDIR}/platform-serial.o ${OBJECTDIR}/platform-storage.o ${OBJECTDIR}/platform-timer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/config-bits.o ${OBJECTDIR}/exceptions.o ${OBJECTDIR}/platform-initialize.o ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o ${OBJECTDIR}/_ext/1445274692/storage-sync.o ${OBJECTDIR}/_ext/1445274692/uds-server.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1603796203/dgi-control-field.o.d ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o.d ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o.d ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o.d ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o.d ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o.d ${OBJECTDIR}/log.o.d ${OBJECTDIR}/platform-canbus.o.d ${OBJECTDIR}/platform-serial.o.d ${OBJECTDIR}/platform-storage.o.d ${OBJECTDIR}/platform-timer.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/config-bits.o.d ${OBJECTDIR}/exceptions.o.d ${OBJECTDIR}/platform-initialize.o.d ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o.d ${OBJECTDIR}/_ext/1445274692/storage-sync.o.d ${OBJECTDIR}/_ext/1445274692/uds-server.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1603796203/dgi-control-field.o ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o ${OBJECTDIR}/log.o ${OBJECTDIR}/platform-canbus.o ${OBJECTDIR}/platform-serial.o ${OBJECTDIR}/platform-storage.o ${OBJECTDIR}/platform-timer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/config-bits.o ${OBJECTDIR}/exceptions.o ${OBJECTDIR}/platform-initialize.o ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o ${OBJECTDIR}/_ext/1445274692/storage-sync.o ${OBJECTDIR}/_ext/1445274692/uds-server.o

# Source Files
SOURCEFILES=../../impl/src/dgi-control-field.c ../../impl/src/dgi-get-field.c ../../impl/src/dgi-process-canbus-message.c ../../impl/src/dgi-update-field.c ../../impl/src/dgi-storage-config.c ../../impl/src/dgi-canbus-config.c log.c platform-canbus.c platform-serial.c platform-storage.c platform-timer.c main.c config-bits.c exceptions.c platform-initialize.c ../../src/storage-canbus-access.c ../../src/storage-sync.c ../../src/uds-server.c



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/pic32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MK1024MCM064
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
${OBJECTDIR}/_ext/1603796203/dgi-control-field.o: ../../impl/src/dgi-control-field.c  .generated_files/flags/default/81c054fa0dc7c13d8bca0684637ce04e55e46825 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-control-field.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-control-field.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-control-field.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-control-field.o ../../impl/src/dgi-control-field.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-get-field.o: ../../impl/src/dgi-get-field.c  .generated_files/flags/default/b94636c6ee29a31ebd3b82ec3bd65fa1bd401b40 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-get-field.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o ../../impl/src/dgi-get-field.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o: ../../impl/src/dgi-process-canbus-message.c  .generated_files/flags/default/1672eff6596d121cf4ad91278ddc16125d7f987 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o ../../impl/src/dgi-process-canbus-message.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-update-field.o: ../../impl/src/dgi-update-field.c  .generated_files/flags/default/6db4fffdd23cef1d085a2c1776d084bbe450157 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-update-field.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o ../../impl/src/dgi-update-field.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o: ../../impl/src/dgi-storage-config.c  .generated_files/flags/default/a5014ec20617ece4fcd77be13c6a37b28621addb .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o ../../impl/src/dgi-storage-config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o: ../../impl/src/dgi-canbus-config.c  .generated_files/flags/default/b4810bfe97abe306e95a878ff9073e4a85f0617d .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o ../../impl/src/dgi-canbus-config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/log.o: log.c  .generated_files/flags/default/abe2be7e332db50945dddac2c1a3915e6400279a .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/log.o.d 
	@${RM} ${OBJECTDIR}/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/log.o.d" -o ${OBJECTDIR}/log.o log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-canbus.o: platform-canbus.c  .generated_files/flags/default/1cad931f60586de1287fc3920f3ecb8916897273 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-canbus.o.d 
	@${RM} ${OBJECTDIR}/platform-canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-canbus.o.d" -o ${OBJECTDIR}/platform-canbus.o platform-canbus.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-serial.o: platform-serial.c  .generated_files/flags/default/28e2e0a561f29d1519d5fcde420136fc3406eb60 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-serial.o.d 
	@${RM} ${OBJECTDIR}/platform-serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-serial.o.d" -o ${OBJECTDIR}/platform-serial.o platform-serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-storage.o: platform-storage.c  .generated_files/flags/default/1b961388e2a954cedc4b169ad10216abd1846bca .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-storage.o.d 
	@${RM} ${OBJECTDIR}/platform-storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-storage.o.d" -o ${OBJECTDIR}/platform-storage.o platform-storage.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-timer.o: platform-timer.c  .generated_files/flags/default/c6c50a6d6d420974673113135bbea39b49c7a727 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-timer.o.d 
	@${RM} ${OBJECTDIR}/platform-timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-timer.o.d" -o ${OBJECTDIR}/platform-timer.o platform-timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/bbe94c2253ec6eadb59794c7e0b9e50c6e4581a .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/config-bits.o: config-bits.c  .generated_files/flags/default/7594c9008fe3380cafbfbee18a94d7e589a647a7 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/config-bits.o.d 
	@${RM} ${OBJECTDIR}/config-bits.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/config-bits.o.d" -o ${OBJECTDIR}/config-bits.o config-bits.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/exceptions.o: exceptions.c  .generated_files/flags/default/1cbb0d5dfead41506fb69339a5062cf76c6dff40 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exceptions.o.d 
	@${RM} ${OBJECTDIR}/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/exceptions.o.d" -o ${OBJECTDIR}/exceptions.o exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-initialize.o: platform-initialize.c  .generated_files/flags/default/3d4c000987d0d08bf27ede5060b62dc93f81f26d .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-initialize.o.d 
	@${RM} ${OBJECTDIR}/platform-initialize.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-initialize.o.d" -o ${OBJECTDIR}/platform-initialize.o platform-initialize.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o: ../../src/storage-canbus-access.c  .generated_files/flags/default/f2be8781f8d803f86951ff306077d6ff20471f93 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o.d" -o ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o ../../src/storage-canbus-access.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/storage-sync.o: ../../src/storage-sync.c  .generated_files/flags/default/84ea4cdc24f920833d263f5739ed82a7d886c3f4 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-sync.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/storage-sync.o.d" -o ${OBJECTDIR}/_ext/1445274692/storage-sync.o ../../src/storage-sync.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/uds-server.o: ../../src/uds-server.c  .generated_files/flags/default/92c4933aaf90d8f86a596aecd0fa9d8b656a1dd .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/uds-server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/uds-server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/uds-server.o.d" -o ${OBJECTDIR}/_ext/1445274692/uds-server.o ../../src/uds-server.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1603796203/dgi-control-field.o: ../../impl/src/dgi-control-field.c  .generated_files/flags/default/36d81f80065d5b8584df60e0c9b6e31c2cadc034 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-control-field.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-control-field.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-control-field.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-control-field.o ../../impl/src/dgi-control-field.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-get-field.o: ../../impl/src/dgi-get-field.c  .generated_files/flags/default/cf6ee4051bc2c12f0a2c9dcd30ba294c2f779032 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-get-field.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-get-field.o ../../impl/src/dgi-get-field.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o: ../../impl/src/dgi-process-canbus-message.c  .generated_files/flags/default/7c7c29b2389ab9209df24f87160728f1ad6d7bc1 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-process-canbus-message.o ../../impl/src/dgi-process-canbus-message.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-update-field.o: ../../impl/src/dgi-update-field.c  .generated_files/flags/default/1201d961928a2d53f20307a1bce78df78f7596e2 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-update-field.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-update-field.o ../../impl/src/dgi-update-field.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o: ../../impl/src/dgi-storage-config.c  .generated_files/flags/default/c3521767f3f929639295ea113fb2d290852286af .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-storage-config.o ../../impl/src/dgi-storage-config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o: ../../impl/src/dgi-canbus-config.c  .generated_files/flags/default/ce43bb33943d464d21d3683a476933773d5bfc09 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1603796203" 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o.d" -o ${OBJECTDIR}/_ext/1603796203/dgi-canbus-config.o ../../impl/src/dgi-canbus-config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/log.o: log.c  .generated_files/flags/default/16d523a86611a9539883bd9f532db642fa9f4a3d .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/log.o.d 
	@${RM} ${OBJECTDIR}/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/log.o.d" -o ${OBJECTDIR}/log.o log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-canbus.o: platform-canbus.c  .generated_files/flags/default/bdf1797916741107b2136441b690917affd72f9f .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-canbus.o.d 
	@${RM} ${OBJECTDIR}/platform-canbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-canbus.o.d" -o ${OBJECTDIR}/platform-canbus.o platform-canbus.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-serial.o: platform-serial.c  .generated_files/flags/default/e4ef078867abf611363c3c9b3aab3a8d40a85cdf .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-serial.o.d 
	@${RM} ${OBJECTDIR}/platform-serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-serial.o.d" -o ${OBJECTDIR}/platform-serial.o platform-serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-storage.o: platform-storage.c  .generated_files/flags/default/d565a371401c986c2f5446c13c4989e0581f0ede .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-storage.o.d 
	@${RM} ${OBJECTDIR}/platform-storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-storage.o.d" -o ${OBJECTDIR}/platform-storage.o platform-storage.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-timer.o: platform-timer.c  .generated_files/flags/default/924bb65a5909c6a556e61fd3331197c9bae40287 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-timer.o.d 
	@${RM} ${OBJECTDIR}/platform-timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-timer.o.d" -o ${OBJECTDIR}/platform-timer.o platform-timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/41bb1c0dbb693e9d67db89dd8cbfaaa6359f5f55 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/config-bits.o: config-bits.c  .generated_files/flags/default/d78a33ac83002b4cf50adfd16e7168b0c73b58c5 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/config-bits.o.d 
	@${RM} ${OBJECTDIR}/config-bits.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/config-bits.o.d" -o ${OBJECTDIR}/config-bits.o config-bits.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/exceptions.o: exceptions.c  .generated_files/flags/default/9bae17153133376c0dc9576945148b30e51fff3 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exceptions.o.d 
	@${RM} ${OBJECTDIR}/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/exceptions.o.d" -o ${OBJECTDIR}/exceptions.o exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/platform-initialize.o: platform-initialize.c  .generated_files/flags/default/e5b901b4e6660d88e5bbc5279342c87ee6c06eb7 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform-initialize.o.d 
	@${RM} ${OBJECTDIR}/platform-initialize.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/platform-initialize.o.d" -o ${OBJECTDIR}/platform-initialize.o platform-initialize.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o: ../../src/storage-canbus-access.c  .generated_files/flags/default/2774f495b94a77565344540b8629a5d3599530c3 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o.d" -o ${OBJECTDIR}/_ext/1445274692/storage-canbus-access.o ../../src/storage-canbus-access.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/storage-sync.o: ../../src/storage-sync.c  .generated_files/flags/default/ef28b44f276e977b685672a5567a955bc4025dc1 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/storage-sync.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/storage-sync.o.d" -o ${OBJECTDIR}/_ext/1445274692/storage-sync.o ../../src/storage-sync.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/uds-server.o: ../../src/uds-server.c  .generated_files/flags/default/6a608cf5dde8b3f31fc01bcb8db51d32f12b51a7 .generated_files/flags/default/afdaf14826d4d22f2e00a1bcc1134d70bf0114cc
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/uds-server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/uds-server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"/home/tumap/flatline/uds-server/common/include" -I"/home/tumap/flatline/uds-server/include" -I"/home/tumap/flatline/uds-server/impl/include" -I"/home/tumap/flatline/uds-server/common/src" -fno-common -DSTORAGE_CANBUS_ACCESS -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/include" -I"../../../../Dropbox/Documents/Projekty/flatline/uds-server/common/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/uds-server.o.d" -o ${OBJECTDIR}/_ext/1445274692/uds-server.o ../../src/uds-server.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/pic32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/pic32.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x36F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/pic32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/pic32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/pic32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
