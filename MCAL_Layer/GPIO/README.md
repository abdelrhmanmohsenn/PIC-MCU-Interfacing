# 💡**PIC18F46K20 GPIO Driver**

This repository contains a GPIO (General Purpose Input/Output) driver for the PIC18F46K20 microcontroller. The GPIO driver provides APIs to initialize and control GPIO pins and ports on the PIC18F46K20 MCU.

## 📁**Files**

- **`hal_gpio.h`**: Header file containing GPIO function declarations and data types.
- **`hal_gpio.c`**: Source file containing GPIO function implementations.
- **`gpio_config.h`**: Header file for GPIO configuration settings.
- **`gpio_config.c`**: Source file for GPIO configuration settings.

## 🪄**Features**

- Initialize GPIO pins and ports.
- Set pin direction (input or output).
- Write logic levels (high or low) to pins.
- Read logic levels from pins.
- Toggle pin states.

**Getting Started**

### 📥**Installation**

1. Clone or download this repository to your development environment.
    
    ```bash
    git clone https://github.com/your-username/your-repository.git
    ```
    
2. Include the necessary files (**`hal_gpio.h`**, **`hal_gpio.c`**, **`gpio_config.h`**) in your PIC18F46K20 project.

### 💻**Usage**

1. Include **`hal_gpio.h`** in your source file where GPIO functions will be used.
    
    ```c
    #include "hal_gpio.h"
    ```
    
2. Initialize a GPIO pin:
    
    ```c
    // Example pin configuration
    pin_config_t pinConfig = {
        .port = PORTA_INDEX,     // Port A
        .pin = PIN0,             // Pin 0
        .direction = PIN_DIRECTION_OUTPUT,  // Output direction
        .logic = PIN_HIGH        // Initial logic level
    };
    
    // Initialize the GPIO pin
    gpio_pin_initialize(&pinConfig);
    ```
    
3. Write to a GPIO pin:
    
    ```c
    // Write logic low to the pin
    gpio_pin_write(&pinConfig, PIN_LOW);
    ```
    
4. Read from a GPIO pin:
    
    ```c
    logic_t pinLogic;
    gpio_pin_read(&pinConfig, &pinLogic);
    
    if (pinLogic == PIN_HIGH) {
        // Pin is logic high
    } else {
        // Pin is logic low
    }
    ```
    
5. Toggle a GPIO pin:
    
    ```c
    gpio_pin_toggle(&pinConfig);
    ```
    

## ☑️**Configuration**

In **`gpio_config.h`**, you can enable or disable GPIO port/pin configurations:

```c
#define GPIO_PORT_PIN_CONFIGRATIONS   CONFIG_ENABLE
```

Setting **`CONFIG_ENABLE`** will enable port/pin configurations, while **`CONFIG_DISABLE`** will disable them.

## 🗒️**Notes**

- This GPIO driver is designed for the PIC18F46K20 MCU. Ensure that your project is configured for this microcontroller.
- Modify the **`pin_config_t`** structure to suit your specific pin configurations.

## **Example**

Here's an example of how to use the GPIO driver to control an LED connected to Pin 0 of Port A:

```c
#include "hal_gpio.h"
int main() {
    // Define LED pin configuration
    pin_config_t ledPin = {
        .port = PORTA_INDEX,
        .pin = PIN0,
        .direction = PIN_DIRECTION_OUTPUT,
        .logic = PIN_LOW  // Start with LED off
    };

    // Initialize LED pin
    gpio_pin_initialize(&ledPin);

    while (1) {
        // Toggle LED every second
        gpio_pin_toggle(&ledPin);
        __delay_ms(1000);
    }

    return 0;
}
```
