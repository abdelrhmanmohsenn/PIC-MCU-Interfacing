# 🌟 PIC18F46K20 I2C Driver 

This repository contains an I2C (Inter-Integrated Circuit) driver for the PIC18F46K20 microcontroller. The I2C driver provides APIs to initialize and use the I2C module for communication with I2C devices.

## 📁 Files

- `hal_i2c.h`: Header file containing I2C function declarations and data types.
- `hal_i2c.c`: Source file containing I2C function implementations.

## 🚀 Features

- Initialize the I2C module for both master and slave modes.
- Write data to I2C devices in blocking and non-blocking modes.
- Read data from I2C devices in blocking and non-blocking modes.
- Send start, repeated start, and stop signals on the I2C bus.
- Enable/disable slew rate control, SMBus compatibility, general call, and more.

## 🛠️ Getting Started

### Installation

1. Clone or download this repository to your development environment.

2. Include the necessary files (`hal_i2c.h`, `hal_i2c.c`) in your PIC18F46K20 project.

### Usage

1. Include `hal_i2c.h` in your source file where I2C functions will be used.

   ```c
   #include "hal_i2c.h"
   ```

2. Initialize the I2C module for master mode:

   ```c
   // Example I2C configuration for master mode
   i2c_t i2cConfig = {
       .mode_select = I2C_MASTER_MODE_DEFINED_CLOCK,
       .clock_speed = 100000,  // 100kHz clock speed
       .i2c_slave_address = 0x50,  // Example slave address
       .i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
       .i2c_general_call = I2C_GENERAL_CALL_DISABLE
   };

   // Initialize the I2C module in master mode
   I2C_master_Init(&i2cConfig);
   ```

3. Write data to an I2C device in blocking mode:

   ```c
   uint8_t dataToSend = 0xAA;
   uint8_t ack;

   // Write data to I2C device in blocking mode
   MSSP_I2C_Master_Write_Blocking(&i2cConfig, dataToSend, &ack);
   ```

4. Read data from an I2C device in blocking mode:

   ```c
   uint8_t receivedData;
   uint8_t ack;

   // Read data from I2C device in blocking mode
   MSSP_I2C_Master_Read_Blocking(&i2cConfig, I2C_MASTER_SEND_ACK, &receivedData);
   ```

5. Send start and stop signals:

   ```c
   // Send start signal
   MSSP_I2C_Master_Send_Start(&i2cConfig);

   // Send stop signal
   MSSP_I2C_Master_Send_Stop(&i2cConfig);
   ```

6. Deinitialize the I2C module (if needed):

   ```c
   // Deinitialize the I2C module
   I2C_DeInit(&i2cConfig);
   ```

## ⚙️ Configuration

- `i2c_mode_cfg_t`: Enum defining different I2C modes such as master, slave, with or without interrupts.
- `i2c_t`: Struct containing I2C configuration settings:
  - `mode_select`: Selects the I2C mode (master, slave, etc.).
  - `clock_speed`: I2C clock speed in Hz.
  - `i2c_slave_address`: Address of the I2C slave device.
  - `i2c_slew_rate`: Enable/disable slew rate control.
  - `i2c_general_call`: Enable/disable general call.

## 📝 Notes

- This I2C driver is designed for the PIC18F46K20 MCU. Ensure that your project is configured for this microcontroller.
- Modify the `i2c_t` structure to suit your specific I2C configurations.

## 🌟 Example

Here's an example of how to use the I2C driver to communicate with an I2C device:

```c
#include "hal_i2c.h"

int main() {
    // Example I2C configuration for master mode
    i2c_t i2cConfig = {
       .mode_select = I2C_MASTER_MODE_DEFINED_CLOCK,
       .clock_speed = 100000,  // 100kHz clock speed
       .i2c_slave_address = 0x50,  // Example slave address
       .i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
       .i2c_general_call = I2C_GENERAL_CALL_DISABLE
    };

    // Initialize the I2C module in master mode
    I2C_master_Init(&i2cConfig);

    // Write data to an I2C device
    uint8_t dataToSend = 0xAA;
    uint8_t ack;
    MSSP_I2C_Master_Write_Blocking(&i2cConfig, dataToSend, &ack);

    // Read data from the I2C device
    uint8_t receivedData;
    MSSP_I2C_Master_Read_Blocking(&i2cConfig, I2C_MASTER_SEND_ACK, &receivedData);

    // Send stop signal
    MSSP_I2C_Master_Send_Stop(&i2cConfig);

    // Deinitialize the I2C module
    I2C_DeInit(&i2cConfig);

    return 0;
}
```
