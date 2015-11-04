################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../MatrixCalc.o \
../OFFReader.o \
../bezierCalc.o \
../guicallback.o \
../guicontrol.o \
../shadertools.o \
../walking_in_air.o 

CPP_SRCS += \
../MatrixCalc.cpp \
../OFFReader.cpp \
../ass2gui.cpp \
../bezierCalc.cpp \
../illumination.cpp \
../walking_in_air.cpp 

C_SRCS += \
../bezier2_length.c \
../bezier3_length.c \
../guicallback.c \
../guicontrol.c \
../shadertools.c 

OBJS += \
./MatrixCalc.o \
./OFFReader.o \
./ass2gui.o \
./bezier2_length.o \
./bezier3_length.o \
./bezierCalc.o \
./guicallback.o \
./guicontrol.o \
./illumination.o \
./shadertools.o \
./walking_in_air.o 

C_DEPS += \
./bezier2_length.d \
./bezier3_length.d \
./guicallback.d \
./guicontrol.d \
./shadertools.d 

CPP_DEPS += \
./MatrixCalc.d \
./OFFReader.d \
./ass2gui.d \
./bezierCalc.d \
./illumination.d \
./walking_in_air.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


