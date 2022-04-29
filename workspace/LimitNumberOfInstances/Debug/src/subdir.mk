################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LimitNumberOfInstancesTest.cpp 

CPP_DEPS += \
./src/LimitNumberOfInstancesTest.d 

OBJS += \
./src/LimitNumberOfInstancesTest.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I"/Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseAdvanced/workspace/LimitNumberOfInstances/cute" -O0 -g3 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/LimitNumberOfInstancesTest.d ./src/LimitNumberOfInstancesTest.o

.PHONY: clean-src

