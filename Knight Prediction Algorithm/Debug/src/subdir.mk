################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/knightType.cpp \
../src/main_2.cpp 

CPP_DEPS += \
./src/knightType.d \
./src/main_2.d 

OBJS += \
./src/knightType.o \
./src/main_2.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/knightType.d ./src/knightType.o ./src/main_2.d ./src/main_2.o

.PHONY: clean-src

