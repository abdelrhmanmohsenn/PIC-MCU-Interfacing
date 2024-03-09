### 🌟 Keypad Driver for PIC18F46K20 🌟

This repository contains the Keypad driver for the PIC18F46K20 microcontroller. The Keypad driver provides functions to interface with a 4x4 keypad connected to the microcontroller pins. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `keypad_cfg.h`
This file is used for configuration of the Keypad driver. Currently, it does not have any specific configurations.

#### 2. `keypad.h`
- **Includes**: 
  - `keypad_cfg.h`: Configuration file for the Keypad driver.
  - `hal_gpio.h`: GPIO functions from the MCAL layer.

- **Data Types**:
  - `keypad_t`: Structure for Keypad control.

- **Functions**:
  - `keypad_initialize(keypad_t *keypad)`: Initializes the Keypad.
  - `keypad_scan(keypad_t *keypad, uint8 *scanned_value)`: Scans the Keypad for pressed keys and returns the value.

#### 3. `keypad.c`
This file contains the implementation of the Keypad driver functions.

### 🚀 How to Use

1. **Clone the Repository**

2. **Include in Your Project**:
   - Include the following files in your project:
     - `keypad.h`
     - `keypad.c`
     - `keypad_cfg.h`
     - `hal_gpio.h` (from MCAL_layer)

3. **Configuration**:
   - Modify `keypad_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pins for the Keypad rows and columns in your `main.c` or configuration file.

4. **Initialization**:
   - Create a `keypad_t` structure, populate it with the Keypad's row and column pin configurations.
   - Call `keypad_initialize(&keypad_config)` to initialize the Keypad.

5. **Scanning for Key Press**:
   - Use the `keypad_scan(&keypad_config, &scanned_value)` function to scan for pressed keys.
   - The scanned value will be stored in the `scanned_value` variable.

6. **Example**:
   - Here's a simple example of using the Keypad driver to scan for pressed keys:

     ```c
     #include "keypad.h"

     // Define Keypad configurations
     keypad_t keypad_config = {
         .keypad_rows_pins = {
             {PORTA, PIN0, OUTPUT},  // Row 1
             {PORTA, PIN1, OUTPUT},  // Row 2
             {PORTA, PIN2, OUTPUT},  // Row 3
             {PORTA, PIN3, OUTPUT}   // Row 4
         },
         .keypad_columns_pins = {
             {PORTB, PIN0, INPUT},   // Column 1
             {PORTB, PIN1, INPUT},   // Column 2
             {PORTB, PIN2, INPUT},   // Column 3
             {PORTB, PIN3, INPUT}    // Column 4
         }
     };

     int main() {
         uint8 scanned_value = 0;

         // Initialize the Keypad
         keypad_initialize(&keypad_config);

         while (1) {
             // Scan for pressed keys
             if (keypad_scan(&keypad_config, &scanned_value) == E_OK) {
                 // Do something with the scanned value
             }

             // Your main code here
         }

         return 0;
     }
     ```
