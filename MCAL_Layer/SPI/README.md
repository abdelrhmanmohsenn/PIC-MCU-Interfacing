### 💡 SPI Driver for PIC18F46K20 💡

This is a simple SPI (Serial Peripheral Interface) driver for PIC18F46K20 microcontroller, designed to facilitate communication with SPI devices. The driver consists of two files: `hal_spi.c` and `hal_spi.h`. Below are the details on how to use this driver and the APIs implemented.

### 📂 File Structure

- `hal_spi.c`: Contains the implementation of the SPI driver functions.
- `hal_spi.h`: Header file defining the SPI driver interface, macros, and data types.

### 🚀 Features
Initialization and deinitialization of SPI.
Blocking and non-blocking modes for transmit and receive operations.
Configurable SPI clock and sampling modes.
Support for interrupt handling (optional).

### 🚀 Getting Started

To use the SPI driver in your PIC18F46K20 project, follow these steps:

1. **Include Files**: Make sure to include the necessary files in your project:

    ```c
    #include "hal_spi.h"
    #include "hal_gpio.h" // If not included already
    #include "mcal_internal_interrupt.h" // If not included already
    #include "compiler.h" // If not included already
    #include "mcal_std_types.h" // If not included already
    #include "std_libraries.h" // If not included already
    ```

2. **Initialize SPI**: Before using SPI, initialize it with your desired configuration. Use `spi_init` function:

    ```c
    spi_t spi_config = {
        .mode_select = SPI_MASTER_MODE_CLOCK_DIV_4, // Choose from available modes
        .sync_mode = CLOCK_LOW_TRAMITTING_ACTIVE_TO_IDLE, // Choose sync mode
        .sample_mode = MASTER_SAMPLE_MODE_AT_END // Choose sample mode
        // Optionally, set SPI_DefaultInterruptHandler and priority for interrupt handling
    };

    spi_init(&spi_config);
    ```

3. **Transmit Data**: Transmit data to a slave device using `spi_master_TransmitOnly_Blocking`:

    ```c
    slave_t slave_device = {
        .port = PORTX, // Your slave device port
        .pin = PIN_X // Your slave device pin
    };

    uint8_t data_to_send = 0x55; // Example data
    spi_master_TransmitOnly_Blocking(&spi_config, &slave_device, data_to_send);
    ```

4. **Receive Data**: Receive data from a slave device using `spi_master_ReceiveOnly_Blocking`:

    ```c
    uint8_t received_data;
    spi_master_ReceiveOnly_Blocking(&spi_config, &slave_device, &received_data);
    ```

5. **Deinitialize**: When SPI communication is done, deinitialize SPI:

    ```c
    spi_Deinit(&spi_config);
    ```

### 📝 APIs

- `spi_init`: Initialize the SPI module with the provided configuration.
- `spi_Deinit`: Deinitialize the SPI module.
- `spi_slave_select_init`: Initialize a slave device for SPI communication.
- `spi_master_TransmitOnly_Blocking`: Transmit data to a slave device in a blocking manner.
- `spi_master_ReceiveOnly_Blocking`: Receive data from a slave device in a blocking manner.
- `spi_master_Transmit_Receive_Blocking`: Transmit and receive data from a slave device in a blocking manner.
- `spi_master_TransmitOnly_NonBlocking`: Transmit data to a slave device in a non-blocking manner.
- `spi_master_ReceiveOnly_NonBlocking`: Receive data from a slave device in a non-blocking manner.
- `spi_master_Transmit_Receive_NonBlocking`: Transmit and receive data from a slave device in a non-blocking manner.
- `spi_slave_TransmitOnly`: Transmit data from a slave device.
- `spi_slave_ReceiveOnly_blocking`: Receive data from a slave device in a blocking manner.
- `spi_slave_Transmit_Receive_blocking`: Transmit and receive data from a slave device in a blocking manner.
- `spi_slave_ReceiveOnly_Nonblocking`: Receive data from a slave device in a non-blocking manner.
- `spi_slave_Transmit_Receive_Nonblocking`: Transmit and receive data from a slave device in a non-blocking manner.

### 📚 Notes

- This driver assumes you have already configured the GPIO pins correctly for SPI.
- Adjust the SPI configuration in `spi_t` struct according to your project's requirements.
- Check the status of `Std_ReturnType` for error handling in your application.

### 🛠️ Contributors

- Author: Mohsen
- Email: [mohsen@example.com](mailto:mohsen@example.com)
- GitHub: [mohsen_spi_driver](https://github.com/mohsen_spi_driver)

Feel free to contribute or report issues on the [GitHub repository](https://github.com/mohsen_spi_driver)!

### 📃 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
