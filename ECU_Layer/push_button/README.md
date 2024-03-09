### 🔘 Button Driver for PIC18F46K20 🔘

This repository contains the Button driver for the PIC18F46K20 microcontroller. The Button driver provides functions to interface with a button connected to a specific pin on the microcontroller. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `ecu_button_cfg.h`
This file is used for configuration of the Button driver. Currently, it does not have any specific configurations.

#### 2. `ecu_button.h`
- **Includes**: 
  - `hal_gpio.h`: GPIO functions from the MCAL layer.
  - `ecu_button_cfg.h`: Configuration file for the Button driver.

- **Data Types**:
  - `button_state_t`: Enumeration for button state (pressed or released).
  - `button_active_t`: Enumeration for button active level (active high or active low).
  - `button_t`: Structure for Button control.

- **Functions**:
  - `button_initialize(const button_t *btn)`: Initializes the button pin.
  - `button_read_state(const button_t *btn, button_state_t *btn_state)`: Reads the state of the button.

#### 3. `ecu_button.c`
This file contains the implementation of the Button driver functions.

### 🚀 How to Use

1. **Clone the Repository**

2. **Include in Your Project**:
   - Include the following files in your project:
     - `ecu_button.h`
     - `ecu_button.c`
     - `ecu_button_cfg.h`
     - `hal_gpio.h` (from MCAL_layer)

3. **Configuration**:
   - Modify `ecu_button_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pin for the Button in your `main.c` or configuration file.

4. **Initialization**:
   - Create a `button_t` structure, populate it with the Button's pin, state, and connection type.
   - Call `button_initialize(&button_config)` to initialize the Button.

5. **Reading Button State**:
   - Use the `button_read_state(&button_config, &button_state)` function to read the state of the Button.
   - The Button state will be stored in the `button_state` variable.

6. **Example**:
   - Here's a simple example of using the Button driver to read the state of a button:

     ```c
     #include "ecu_button.h"

     // Define Button configuration
     button_t button_config = {
         .button_pin = {PORTA, PIN0, INPUT},     // Example: Button connected to PORTA, PIN0
         .button_state = BUTTON_RELEASED,        // Initial state
         .button_connection = BUTTON_ACTIVE_HIGH // Active high configuration
     };

     int main() {
         button_state_t button_state;

         // Initialize the Button
         button_initialize(&button_config);

         while (1) {
             // Read the Button state
             if (button_read_state(&button_config, &button_state) == E_OK) {
                 // Do something based on the button state
                 if (button_state == BUTTON_PRESSED) {
                     // Button is pressed
                 } else {
                     // Button is released
                 }
             }

             // Your main code here
         }

         return 0;
     }
     ```
