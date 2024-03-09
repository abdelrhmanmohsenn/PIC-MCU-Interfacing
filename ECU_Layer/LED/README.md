### 💡 LED Driver for PIC18F46K20

This repository contains the LED driver for the PIC18F46K20 microcontroller. The LED driver provides functions to easily control LEDs connected to the microcontroller pins. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `ecu_led_cfg.h`
This file is used for configuration of the LED driver. Currently, it does not have any specific configurations.

#### 2. `ecu_led.h`
- **Includes**: 
  - `hal_gpio.h`: GPIO functions from the MCAL layer.
  - `ecu_led_cfg.h`: Configuration file.

- **Data Types**:
  - `led_status_t`: Enum to specify LED status (ON or OFF).
  - `led_t`: Structure to hold LED configurations including port, pin, and status.

- **Functions**:
  - `led_initialize(const led_t *led_config)`: Initializes the LED.
  - `led_turn_on(const led_t *led_config)`: Turns on the LED.
  - `led_turn_off(const led_t *led_config)`: Turns off the LED.
  - `led_toggle(const led_t *led_config)`: Toggles the LED state.
  - `led_run(port_index_t port_index)`: Example function to demonstrate LED run sequence.
  - `led_run_initialize(port_index_t port_index)`: Example function to initialize a port for LED run sequence.

#### 3. `ecu_led.c`
This file contains the implementation of the LED driver functions.

### 🚀 How to Use

1. **Clone the Repository**:
   - Clone this repository to your local machine:

     ```sh
     git clone https://github.com/yourusername/led-driver-pic18f46k20.git
     ```

2. **Include in Your Project**:
   - Include the following files in your project:
     - `ecu_led.h`
     - `ecu_led.c`
     - `ecu_led_cfg.h`
     - `hal_gpio.h` (from your MCAL layer)

3. **Configuration**:
   - Modify `ecu_led_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pins for each LED in your `main.c` or configuration file.

4. **Initialization**:
   - Create a `led_t` structure and populate it with the LED's port, pin, and initial status.
   - Call `led_initialize(&led_config)` to initialize the LED.

5. **Controlling LEDs**:
   - Use the following functions to control the LED:
     - `led_turn_on(&led_config)`: Turns on the LED.
     - `led_turn_off(&led_config)`: Turns off the LED.
     - `led_toggle(&led_config)`: Toggles the LED state.

6. **Example Run Sequence**:
   - The `led_run(port_index_t port_index)` function is an example of a simple LED run sequence. Uncomment the function in `ecu_led.c` and call it in your main program to see LEDs blinking in sequence.

### 📄 Documentation
- Detailed descriptions and usage guidelines can be found in the comments within the header and source files.
- Feel free to modify the code as needed for your specific project requirements.

### 🌟 Example
Here's a simple example to demonstrate how to use the LED driver:

```c
#include <stdio.h>
#include "ecu_led.h"

int main() {
    // Define LED configuration
    led_t led = {
        .port = PORTA_INDEX,    // Port A
        .pin = PIN0,            // Pin 0
        .led_status = LED_OFF   // Initially off
    };

    // Initialize the LED
    led_initialize(&led);

    // Turn on the LED
    led_turn_on(&led);

    // Wait for a moment
    __delay_ms(1000);

    // Turn off the LED
    led_turn_off(&led);

    return 0;
}
```

### 📚 Resources
- [PIC18F46K20 Datasheet](https://www.microchip.com/wwwproducts/en/PIC18F46K20)

### 📧 Contact
For any questions or suggestions, feel free to reach out:
- Email: your.email@example.com
- GitHub: [YourGitHubUsername](https://github.com/yourusername)

### 🌟 Contribution
Contributions and improvements are welcome! If you find any issues or want to add new features, please fork the repository and submit a pull request.

### 📜 License
This project is licensed under the [MIT License](LICENSE).
