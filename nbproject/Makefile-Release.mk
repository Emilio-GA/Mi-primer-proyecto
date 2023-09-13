#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/49bc9a90/Byte.o \
	${OBJECTDIR}/_ext/49bc9a90/Histogram.o \
	${OBJECTDIR}/_ext/49bc9a90/Image.o \
	${OBJECTDIR}/_ext/49bc9a90/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imaging5

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imaging5: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imaging5 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/49bc9a90/Byte.o: ../../Escritorio/Imaging5/src/Byte.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/49bc9a90
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/49bc9a90/Byte.o ../../Escritorio/Imaging5/src/Byte.cpp

${OBJECTDIR}/_ext/49bc9a90/Histogram.o: ../../Escritorio/Imaging5/src/Histogram.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/49bc9a90
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/49bc9a90/Histogram.o ../../Escritorio/Imaging5/src/Histogram.cpp

${OBJECTDIR}/_ext/49bc9a90/Image.o: ../../Escritorio/Imaging5/src/Image.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/49bc9a90
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/49bc9a90/Image.o ../../Escritorio/Imaging5/src/Image.cpp

${OBJECTDIR}/_ext/49bc9a90/main.o: ../../Escritorio/Imaging5/src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/49bc9a90
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/49bc9a90/main.o ../../Escritorio/Imaging5/src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
