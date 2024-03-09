# 📢**PIC18F46K20 MCU Device Drivers**

This repository contains the source code for an embedded software framework designed for the PIC18F46K20 microcontroller. The framework is structured into three layers: MCAL (MicroController Abstraction Layer), ECU (Electronic Control Unit) Layer, and an application layer. The purpose of this framework is to provide a modular and organized approach to developing applications for the PIC18F46K20 MCU and to abstract the application layer from the hardware peripherals.

## 📚**Layers**

### **1. MCAL Layer**

The Microcontroller Abstraction Layer (MCAL) provides low-level interface drivers to interact with the hardware peripherals of the PIC18F46K20 MCU. It includes the following interface drivers:

- GPIO (General Purpose Input/Output)
- ADC (Analog-to-Digital Converter)
- CCP (Capture/Compare/PWM)
- EEPROM (Electrically Erasable Programmable Read-Only Memory)
- I2C (Inter-Integrated Circuit)
- Interrupt
- SPI (Serial Peripheral Interface)
- Timer
- UART (Universal Asynchronous Receiver-Transmitter)

These drivers offer an abstraction of the hardware details, allowing easier interaction with the PIC18F46K20's peripherals.

### **2. ECU Layer**

The Electronic Control Unit (ECU) Layer builds upon the MCAL layer and provides higher-level interface drivers for commonly used components and modules. It includes the following interface drivers:

- 7-Segment Display
- Character LCD
- DC Motor
- Keypad
- LED
- Push Button
- Relay

The ECU Layer utilizes the APIs provided by the MCAL Layer to achieve abstraction from the hardware. This means that developers can use these ECU drivers without needing to understand the intricate details of the PIC18F46K20's hardware registers and configurations.

### **3. Application Layer**

The Application Layer is where developers can implement their main application logic using the APIs provided by the ECU Layer and the MCAL Layer. This layer provides a clean separation between the hardware-specific details (handled by the MCAL and ECU Layers) and the application-specific functionality.

## ⚡**Getting Started**

To get started with this framework and develop applications for the PIC18F46K20 MCU, follow these steps:

1. Clone or download this repository to your development environment.
2. Ensure you have MPLAB X IDE installed along with the XC8 compiler for PIC.
3. Explore the **`MCAL_layer`**, **`ECU_layer`**, **`application.c`**, and **`application.h`** files to understand the provided drivers and APIs.
4. Use the provided APIs from the ECU Layer and the MCAL Layer  within the  **`application.c`**, and **`application.h`** files to interact with hardware peripherals and components.

## **Example Usage**

Here's a simple example of how to use the ECU Layer API to control an LED:

```c
#include"application.h"

void main(void){
    
    while(1){
        led_toggle(&led1); //API used from the LED driver
	__delay_ms(500);
        
    }
    return;
}

void application_initialize(void){
	
  led_t led1 = {.port = PORTC_INDEX, .pin = PIN0, .led_status = PIN_LOW};
}
```
