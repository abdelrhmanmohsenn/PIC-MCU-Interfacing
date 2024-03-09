### 🌟 ECU DC Motor Driver for PIC18F46K20 🌟

This repository contains the ECU DC Motor driver for the PIC18F46K20 microcontroller. The DC Motor driver provides functions to control DC motors connected to the microcontroller pins. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `ecu_dc_motor_cfg.h`
This file is used for configuration of the DC Motor driver. Currently, it does not have any specific configurations.

#### 2. `ecu_dc_motor.h`
- **Includes**: 
  - `hal_gpio.h`: GPIO functions from the MCAL layer.
  - `ecu_dc_motor_cfg.h`: Configuration file for the DC Motor driver.

- **Macros**:
  - `DC_MOTOR_ON`: Macro to turn the DC motor ON.
  - `DC_MOTOR_OFF`: Macro to turn the DC motor OFF.

- **Data Types**:
  - `dc_motor_t`: Structure for DC Motor control.

- **Functions**:
  - `dc_motor_initialize(const dc_motor_t *dc_motor)`: Initializes the DC motor.
  - `dc_motor_move_left(const dc_motor_t *dc_motor)`: Moves the DC motor in the left direction.
  - `dc_motor_move_right(const dc_motor_t *dc_motor)`: Moves the DC motor in the right direction.
  - `dc_motor_stop(const dc_motor_t *dc_motor)`: Stops the DC motor.

#### 3. `ecu_dc_motor.c`
This file contains the implementation of the DC Motor driver functions.

### 🚀 How to Use

1. **Clone the Repository**
2. 
3. **Include in Your Project**:
   - Include the following files in your project:
     - `ecu_dc_motor.h`
     - `ecu_dc_motor.c`
     - `ecu_dc_motor_cfg.h`
     - `hal_gpio.h` (from MCAL_layer)

4. **Configuration**:
   - Modify `ecu_dc_motor_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pins for the DC motor control lines in your `main.c` or configuration file.

5. **Initialization**:
   - Create a `dc_motor_t` structure, populate it with the DC motor's control pin configurations.
   - Call `dc_motor_initialize(&dc_motor_config)` to initialize the DC motor.

6. **Using DC Motor Functions**:
   - Use the provided functions to control the DC motor:
     - `dc_motor_move_left(&dc_motor_config)`: Move the DC motor in the left direction.
     - `dc_motor_move_right(&dc_motor_config)`: Move the DC motor in the right direction.
     - `dc_motor_stop(&dc_motor_config)`: Stop the DC motor.

7. **Example**:
   - Here's a simple example of using the DC Motor driver:

     ```c
     #include "ecu_dc_motor.h"

     // Define DC Motor configurations
     dc_motor_t dc_motor_config = {
         .motor_pin = {
             {PORTA, PIN0, OUTPUT},  // Motor Pin 1
             {PORTA, PIN1, OUTPUT}   // Motor Pin 2
         }
     };

     int main() {
         // Initialize the DC Motor
         dc_motor_initialize(&dc_motor_config);

         // Move the DC Motor left
         dc_motor_move_left(&dc_motor_config);

         // Wait for a while
         __delay_ms(1000);

         // Stop the DC Motor
         dc_motor_stop(&dc_motor_config);

         while (1) {
             // Your main code here
         }

         return 0;
     }
     ```
