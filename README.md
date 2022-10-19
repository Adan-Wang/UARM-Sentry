# UARM-EE-Sentry

This is the test version of UARM sentry robot control code, written in C for STM32F427 series controller. 

This program was developed by myself and several other student colleagues at the University of Alberta, for the University of Alberta RoboMasters Club.

This code is for the "sentry" robot in the "RoboMasters" competition.  

In the RoboMasters competition, two teams of opposing robots shoot rubber projectiles at each other in attempts to destroy the opposing team's base.

The sentry robot is an automated robot that runs on a rail, it is capable of identifying and attacking opposing robots based on patterns on their armor plate.

The code presented here is the driver code to control all motors on the robot, through the STM32 microcontroller. The code used to identify the armor plate, which is based on image recognition algorithms, is not included here.


# The Sentry Robot
A picture of the sentry robot can be seen below, along with some footage from test runs of the robot below. The robot has not yet been fully completed, as such, it is still a bit buggy.


# Application Structure

The code utilizes FreeRTOS, a real-time oeprating system, to handle different application codes at the same time.

### Chassis Application 

​	Process movement along the rail, uses interrupt and  to control M2006 Motors.

### Gimbal Application

​Receive and parse the packets sent by MINI PC through UART6. Then Apply the parsed absolute pitch/yaw angle as well as the fire command via CAN. (Need to implement verification procedures.)

### Shoot Application

​	Drive the friction wheel and paddle motor to activate shooting function via PWM.

### Timer Application

​	Send the CAN data to the microcontroller.



## Available Hardware Allocation

### UART

* UART7: IO Re-direction, used to debug input and output.
* USART6: Used for receive packages from micro-computer (NVIC Interrupt)
  * Preempt Priority 5, Sub Priority 1 (Supposed to be lower than Chassis)
  * UART Pin Trigger
  * Interrupt

### Timer

* TIM2: PWM Signal for shoot task
* TIM4: PWM signal for shoot task (No interrupt)
* TIM5: Used for RTOS operating system
* TIM12: Buzzer (No interrupt)
* TIM13: 
  * Time counter for Chassis task (NVIC interrupt)
    * Preempt Priority 5, Sub Priority 0
    * Triggered each 1s
  * Ultrasound Sensor Timer - Not enabled

### CAN

* CAN1 used to drive Chassis, gimbal, and magazine loaders.