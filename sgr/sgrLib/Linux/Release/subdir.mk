################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../../sgr.cpp \
../../sgr_character.cpp \
../../sgr_recognizer.cpp \
../../sgr_stroke.cpp 

OBJS += \
./sgr.o \
./sgr_character.o \
./sgr_recognizer.o \
./sgr_stroke.o 

CPP_DEPS += \
./sgr.d \
./sgr_character.d \
./sgr_recognizer.d \
./sgr_stroke.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


