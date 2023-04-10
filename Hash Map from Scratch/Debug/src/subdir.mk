################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Assignment7.cpp \
../src/hashMap.cpp 

CPP_DEPS += \
./src/Assignment7.d \
./src/hashMap.d 

OBJS += \
./src/Assignment7.o \
./src/hashMap.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Assignment7.d ./src/Assignment7.o ./src/hashMap.d ./src/hashMap.o

.PHONY: clean-src

