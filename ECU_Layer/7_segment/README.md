🔢 7-Segment Driver for PIC18F46K20
This repository contains the 7-segment driver for the PIC18F46K20 microcontroller. The 7-segment driver allows you to easily interface with 7-segment displays for numeric output. Below are the instructions on how to use the implemented APIs.

📁 Files
1. ecu_7_segment_cfg.h
This file is used for configuration of the 7-segment display driver. Currently, it does not have any specific configurations.

2. ecu_7_segment.h
Includes:

ecu_7_segment_cfg.h: Configuration file.
hal_gpio.h: GPIO functions from the MCAL layer.
Macros:

SEGMENT_PIN0, SEGMENT_PIN1, SEGMENT_PIN2, SEGMENT_PIN3: Pins for each segment of the 7-segment display.
Data Types:

segment_type_t: Enum to specify common anode or common cathode.
segment_t: Structure to hold segment pin configurations.
Functions:

segment_initialize(const segment_t *segment): Initializes the 7-segment display.
segment_write_number(const segment_t *segment, uint8 number): Writes a number to the 7-segment display.
3. ecu_7_segment.c
This file contains the implementation of the 7-segment display driver functions.

🚀 How to Use
Clone the Repository:

Clone this repository to your local machine:

sh
Copy code
git clone https://github.com/yourusername/7-segment-driver-pic18f46k20.git
Include in Your Project:

Include the following files in your project:
ecu_7_segment.h
ecu_7_segment.c
ecu_7_segment_cfg.h
hal_gpio.h (from your MCAL layer)
Configuration:

Modify ecu_7_segment_cfg.h if needed for specific configurations (currently empty).
Ensure to set the correct GPIO pins for each segment in your main.c or configuration file.
Initialization:

Create a segment_t structure and populate it with the pin configurations and segment type (common anode or common cathode).
Call segment_initialize(&segment) to initialize the 7-segment display.
Writing Numbers:

Use segment_write_number(&segment, number) to display a number on the 7-segment display. The number should be between 0 and 9.
