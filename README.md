# UARM-EE-Sentry

This is the test version of UARM sentry robot control code. 

## Application Structure

### Chassis Application 

​	Process the signal movement along the rail Timer interrupt and apply the value of 3508 motors using CAN.

### Gimbal Application

​	Receive and parse the packets sent by MINI PC through UART6. Then Apply the parsed absolute pitch/yaw angle as well as the fire command via CAN. <CURENTLY NO PACKET VERIFICATION PROCEFSS>

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
* TIM5: Increment uwTick (Interrupt), used for timeout for hardwares.
  * Triggered each 1/1000 s
* TIM12: Buzzer (No interrupt)
* TIM13: 
  * Time counter for Chassis task (NVIC interrupt)
    * Preempt Priority 5, Sub Priority 0
    * Triggered each 1s
  * Ultrasound Sensor Timer - Not enabled
* TIM14: Not used

### CAN

* CAN1 used to drive Chassis, gimbal, and magazine loaders.



## Debug Recommendation









Documentation Here:
https://drive.google.com/drive/u/2/folders/1qJiWcmRDkHIVHLkYgO720UUe9NvElubI
