################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/QuadTreeCollision.c \
../src/SATCollision.c \
../src/Vector.c \
../src/main.c 

OBJS += \
./src/QuadTreeCollision.o \
./src/SATCollision.o \
./src/Vector.o \
./src/main.o 

C_DEPS += \
./src/QuadTreeCollision.d \
./src/SATCollision.d \
./src/Vector.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


