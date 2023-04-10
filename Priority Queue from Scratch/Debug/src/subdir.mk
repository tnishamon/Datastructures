################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Assignment8.cpp \
../src/priorityQ.cpp 

CPP_DEPS += \
./src/Assignment8.d \
./src/priorityQ.d 

OBJS += \
./src/Assignment8.o \
./src/priorityQ.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Assignment8.d ./src/Assignment8.o ./src/priorityQ.d ./src/priorityQ.o

.PHONY: clean-src

