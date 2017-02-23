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
CND_CONF=Banana_Pie
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=-O3 -marm -mabi=aapcs-linux -march=armv7ve -mfloat-abi=hard -mfpu=neon-vfpv4 -funsafe-math-optimizations -mhard-float -mlittle-endian -mtls-dialect=gnu2 -mtune=cortex-a7 -munaligned-access -mvectorize-with-neon-quad

# CC Compiler Flags
CCFLAGS=-O3 -marm -mabi=aapcs-linux -march=armv7ve -mfloat-abi=hard -mfpu=neon-vfpv4 -funsafe-math-optimizations -mhard-float -mlittle-endian -mtls-dialect=gnu2 -mtune=cortex-a7 -munaligned-access -mvectorize-with-neon-quad
CXXFLAGS=-O3 -marm -mabi=aapcs-linux -march=armv7ve -mfloat-abi=hard -mfpu=neon-vfpv4 -funsafe-math-optimizations -mhard-float -mlittle-endian -mtls-dialect=gnu2 -mtune=cortex-a7 -munaligned-access -mvectorize-with-neon-quad

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bdlister

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bdlister: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bdlister ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -Werror -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
