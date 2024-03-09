### 🔢 7-Segment Driver for PIC18F46K20

This repository contains the 7-segment driver for the PIC18F46K20 microcontroller. The 7-segment driver allows you to easily interface with 7-segment displays for numeric output. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `ecu_7_segment_cfg.h`
This file is used for configuration of the 7-segment display driver. Currently, it does not have any specific configurations.

#### 2. `ecu_7_segment.h`
- **Includes**: 
  - `ecu_7_segment_cfg.h`: Configuration file.
  - `hal_gpio.h`: GPIO functions from the MCAL layer.

- **Macros**:
  - `SEGMENT_PIN0`, `SEGMENT_PIN1`, `SEGMENT_PIN2`, `SEGMENT_PIN3`: Pins for each segment of the 7-segment display.

- **Data Types**:
  - `segment_type_t`: Enum to specify common anode or common cathode.
  - `segment_t`: Structure to hold segment pin configurations.

- **Functions**:
  - `segment_initialize(const segment_t *segment)`: Initializes the 7-segment display.
  - `segment_write_number(const segment_t *segment, uint8 number)`: Writes a number to the 7-segment display.

#### 3. `ecu_7_segment.c`
This file contains the implementation of the 7-segment display driver functions.

### 🚀 How to Use

1. **Clone the Repository**
   
2. **Include in Your Project**:
   - Include the following files in your project:
     - `ecu_7_segment.h`
     - `ecu_7_segment.c`
     - `ecu_7_segment_cfg.h`
     - `hal_gpio.h` (from MCAL_layer)

3. **Configuration**:
   - Modify `ecu_7_segment_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pins for each segment in your `main.c` or configuration file.

4. **Initialization**:
   - Create a `segment_t` structure and populate it with the pin configurations and segment type (common anode or common cathode).
   - Call `segment_initialize(&segment)` to initialize the 7-segment display.

5. **Writing Numbers**:
   - Use `segment_write_number(&segment, number)` to display a number on the 7-segment display. The `number` should be between 0 and 9.

### 📄 Documentation
- Detailed descriptions and usage guidelines can be found in the comments within the header and source files.
- Feel free to modify the code as needed for your specific project requirements.

### 🌟 Example
Here's a simple example to demonstrate how to use the 7-segment driver to display numbers:

```c
#include <stdio.h>
#include "ecu_7_segment.h"

int main() {
    // Define the 7-segment configuration
    segment_t segment = {
        .segment_pin = {
            {PORTA_INDEX, SEGMENT_PIN0, PIN_DIRECTION_OUTPUT, PIN_LOW}, // A
            {PORTA_INDEX, SEGMENT_PIN1, PIN_DIRECTION_OUTPUT, PIN_LOW}, // B
            {PORTA_INDEX, SEGMENT_PIN2, PIN_DIRECTION_OUTPUT, PIN_LOW}, // C
            {PORTA_INDEX, SEGMENT_PIN3, PIN_DIRECTION_OUTPUT, PIN_LOW}  // D
        },
        .segment_type = SEGMENT_COMMON_CATHODE // Common cathode 7-segment display
    };

    // Initialize the 7-segment display
    segment_initialize(&segment);

    // Display numbers 0 to 9
    for (uint8_t i = 0; i <= 9; ++i) {
        segment_write_number(&segment, i);
        delay_ms(1000); // Delay for 1 second
    }

    return 0;
}
```
