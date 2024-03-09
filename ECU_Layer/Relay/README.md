### 💡 Relay Driver for PIC18F46K20

This repository contains the Relay driver for the PIC18F46K20 microcontroller. The Relay driver provides functions to easily control relays connected to the microcontroller pins. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `ecu_relay_cfg.h`
This file is used for configuration of the Relay driver. Currently, it does not have any specific configurations.

#### 2. `ecu_relay.h`
- **Includes**: 
  - `hal_gpio.h`: GPIO functions from the MCAL layer.
  - `ecu_relay_cfg.h`: Configuration file.

- **Macros**:
  - `RELAY_ON`: Macro to define the relay ON state.
  - `RELAY_OFF`: Macro to define the relay OFF state.

- **Data Types**:
  - `relay_t`: Structure to hold Relay configurations including port, pin, and status.

- **Functions**:
  - `relay_initialize(const relay_t *relay)`: Initializes the Relay.
  - `relay_turn_on(const relay_t *relay)`: Turns on the Relay.
  - `relay_turn_off(const relay_t *relay)`: Turns off the Relay.

#### 3. `ecu_relay.c`
This file contains the implementation of the Relay driver functions.

### 🚀 How to Use

1. **Clone the Repository**:
   - Clone this repository to your local machine:

     ```sh
     git clone https://github.com/yourusername/relay-driver-pic18f46k20.git
     ```

2. **Include in Your Project**:
   - Include the following files in your project:
     - `ecu_relay.h`
     - `ecu_relay.c`
     - `ecu_relay_cfg.h`
     - `hal_gpio.h` (from your MCAL layer)

3. **Configuration**:
   - Modify `ecu_relay_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pins for each Relay in your `main.c` or configuration file.

4. **Initialization**:
   - Create a `relay_t` structure and populate it with the Relay's port, pin, and initial status.
   - Call `relay_initialize(&relay_config)` to initialize the Relay.

5. **Controlling Relays**:
   - Use the following functions to control the Relay:
     - `relay_turn_on(&relay_config)`: Turns on the Relay.
     - `relay_turn_off(&relay_config)`: Turns off the Relay.

### 🌟 Example
Here's a simple example to demonstrate how to use the Relay driver:

```c
#include <stdio.h>
#include "ecu_relay.h"

int main() {
    // Define Relay configuration
    relay_t relay = {
        .port = PORTB_INDEX,    // Port B
        .pin = PIN0,            // Pin 0
        .relay_status = RELAY_OFF   // Initially off
    };

    // Initialize the Relay
    relay_initialize(&relay);

    // Turn on the Relay
    relay_turn_on(&relay);

    // Wait for a moment
    __delay_ms(1000);

    // Turn off the Relay
    relay_turn_off(&relay);

    return 0;
}
```
