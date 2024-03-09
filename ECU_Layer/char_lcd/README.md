### 🖥️ Char LCD Driver for PIC18F46K20

This repository contains the Char LCD driver for the PIC18F46K20 microcontroller. The Char LCD driver provides functions to easily control character LCDs connected to the microcontroller pins. Below are the instructions on how to use the implemented APIs.

### 📁 Files

#### 1. `ecu_char_lcd_cfg.h`
This file is used for configuration of the Char LCD driver. Currently, it does not have any specific configurations.

#### 2. `ecu_char_lcd.h`
- **Includes**: 
  - `ecu_char_lcd_cfg.h`: Configuration file.
  - `hal_gpio.h`: GPIO functions from the MCAL layer.

- **Macros**:
  - Macros for various LCD commands such as clearing display, setting cursor, etc.
  - Macros for specifying rows: `ROW1`, `ROW2`, `ROW3`, `ROW4`.

- **Data Types**:
  - `char_lcd_4bit_t`: Structure for 4-bit mode LCD control.
  - `char_lcd_8bit_t`: Structure for 8-bit mode LCD control.

- **Functions**:
  - Functions for 4-bit mode:
    - `lcd_4bit_initialize(char_lcd_4bit_t *lcd)`: Initializes the 4-bit mode LCD.
    - `lcd_4bit_send_command(char_lcd_4bit_t *lcd, uint8 command)`: Sends a command to the 4-bit mode LCD.
    - `lcd_4bit_send_char(char_lcd_4bit_t *lcd, uint8 data)`: Sends a character to the 4-bit mode LCD.
    - `lcd_4bit_send_char_pos(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data)`: Sends a character to a specific position on the 4-bit mode LCD.
    - `lcd_4bit_send_string(char_lcd_4bit_t *lcd, uint8 *str)`: Sends a string to the 4-bit mode LCD.
    - `lcd_4bit_send_string_pos(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str)`: Sends a string to a specific position on the 4-bit mode LCD.
    - `lcd_4bit_send_custom_char(char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos)`: Sends a custom character to a specific position on the 4-bit mode LCD.
    
  - Functions for 8-bit mode:
    - `lcd_8bit_initialize(char_lcd_8bit_t *lcd)`: Initializes the 8-bit mode LCD.
    - `lcd_8bit_send_command(char_lcd_8bit_t *lcd, uint8 command)`: Sends a command to the 8-bit mode LCD.
    - `lcd_8bit_send_char(char_lcd_8bit_t *lcd, uint8 data)`: Sends a character to the 8-bit mode LCD.
    - `lcd_8bit_send_char_pos(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data)`: Sends a character to a specific position on the 8-bit mode LCD.
    - `lcd_8bit_send_string(char_lcd_8bit_t *lcd, uint8 *str)`: Sends a string to the 8-bit mode LCD.
    - `lcd_8bit_send_string_pos(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str)`: Sends a string to a specific position on the 8-bit mode LCD.
    - `lcd_8bit_send_custom_char(char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos)`: Sends a custom character to a specific position on the 8-bit mode LCD.

- **Utility Functions**:
  - `convert_byte_to_string(uint8 value, uint8 *str)`: Converts a byte value to a string.
  - `convert_short_to_string(uint16 value, uint8 *str)`: Converts a short value to a string.
  - `convert_int_to_string(uint32 value, uint8 *str)`: Converts an integer value to a string.

#### 3. `ecu_char_lcd.c`
This file contains the implementation of the Char LCD driver functions.

### 🚀 How to Use

1. **Clone the Repository**:
   - Clone this repository to your local machine

2. **Include in Your Project**:
   - Include the following files in your project:
     - `ecu_char_lcd.h`
     - `ecu_char_lcd.c`
     - `ecu_char_lcd_cfg.h`
     - `hal_gpio.h` (from your MCAL layer)

3. **Configuration**:
   - Modify `ecu_char_lcd_cfg.h` if needed for specific configurations (currently empty).
   - Ensure to set the correct GPIO pins for the LCD control lines and data lines in your `main.c` or configuration file.

4. **Initialization**:
   - Create a `char_lcd_4bit_t` or `char_lcd_8bit_t` structure, populate it with the LCD's control and data pin configurations.
   - Call `lcd_4bit_initialize(&lcd_4bit_config)` or `lcd_8bit_initialize(&lcd_8bit_config)` to initialize the LCD.

5. **Using LCD Functions**:
   - Use the provided functions to control the LCD:
     - For 4-bit mode:
       - `lcd_4bit_send_command(&lcd_4bit_config, command)`: Send a command to the LCD.
       - `lcd_4bit_send_char(&lcd_4bit_config, data)`: Send a character to the LCD.
       - `lcd_4bit_send_string(&lcd_4bit_config, str)`: Send a string to the LCD.
       - `lcd_4bit_send_string_pos(&lcd_4bit_config, row, column, str)`: Send a string to a specific position on the LCD.
       - `lcd_4bit_send_custom_char(&lcd_4bit_config, row, column, chr[], mem_pos)`: Send a custom character to a specific position on the LCD.

     - For 8-bit mode:
       - `lcd_8bit_send_command(&lcd_8bit_config, command)`: Send a command to the LCD.
       - `lcd_8bit_send_char(&lcd_8bit_config, data)`: Send a character to the LCD.
       - `lcd_8bit_send_string(&lcd_8bit_config, str)`: Send a string to the LCD.
       - `lcd_8bit_send_string_pos(&lcd_8bit_config, row, column, str)`: Send a string to a specific position on the LCD.
       - `lcd_8bit_send_custom_char(&lcd_8bit_config, row, column, chr[], mem_pos)`: Send a custom character to a specific position on the LCD.

6. **Example**:
     ```c
     #include "ecu_char_lcd.h"

     // Define LCD configurations
     char_lcd_4bit_t lcd_4bit_config = {
         .lcd_rs = {PORTA, PIN0, OUTPUT},
         .lcd_en = {PORTA, PIN1, OUTPUT},
         .lcd_data = {
             {PORTB, PIN0, OUTPUT},
             {PORTB, PIN1, OUTPUT},
             {PORTB, PIN2, OUTPUT},
             {PORTB, PIN3, OUTPUT}
         }
     };

     int main() {
         // Initialize the LCD
         lcd_4bit_initialize(&lcd_4bit_config);

         // Send some text
         lcd_4bit_send_string(&lcd_4bit_config, "Hello, LCD!");

         while (1) {
             // Your main code here
         }

         return 0;
     }
     ```

### 📝 Notes
- Make sure to adjust the LCD pin configurations in `ecu_char_lcd.h` and your hardware setup.
