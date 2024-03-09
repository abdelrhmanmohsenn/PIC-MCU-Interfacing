Certainly! Here's a README file for the UART driver for the PIC18F46K20:

### 🔧 PIC18F46K20 UART Driver

This repository contains a UART (Universal Asynchronous Receiver-Transmitter) driver for the PIC18F46K20 microcontroller. The driver provides APIs to easily configure and use the UART module for asynchronous serial communication.

### 📁 Files:
- `hal_usart.c`
- `hal_usart.h`
- `hal_usart_cfg.h`

### 🚀 Features:
- **Asynchronous Operation:** Supports asynchronous mode for UART communication.
- **Baud Rate Selection:** Configurable baud rate generation for various communication speeds.
- **Transmit and Receive:** APIs for sending and receiving data over UART.
- **Interrupt Support:** Optional interrupt-based handling for both transmit and receive operations.
- **Error Handling:** Detects and reports framing and overrun errors.

### 📝 hal_usart.c:
- USART_TX_ISR: Interrupt service routine for UART transmission.
- USART_RX_ISR: Interrupt service routine for UART reception.
- USART_ASYNC_Init: Initializes UART with specified configurations.
- USART_ASYNC_DeInit: De-initializes UART.
- USART_ASYNC_ReadByteBlocking: Reads a byte from UART (blocking).
- USART_ASYNC_ReadByteNonBlocking: Reads a byte from UART (non-blocking).
- USART_ASYNC_RX_Restart: Restarts UART reception.
- USART_ASYNC_WriteByteBlocking: Writes a byte to UART (blocking).
- USART_ASYNC_WriteStringBlocking: Writes a string to UART (blocking).
- USART_ASYNC_WriteByteNonBlocking: Writes a byte to UART (non-blocking).
- USART_ASYNC_WriteStringNonBlocking: Writes a string to UART (non-blocking).

### 📄 hal_usart.h:
- Data Types:
- baudrate_gen_t: Enumeration for different baud rate configurations.
- usart_tx_cfg_t: Structure for UART transmit configurations.
- usart_rx_cfg_t: Structure for UART receive configurations.
- usart_error_status_t: Union for UART error status.
- usart_t: Structure combining all UART configurations.
- Functions:
- USART_ASYNC_Init: Initializes UART with specified configurations.
- USART_ASYNC_DeInit: De-initializes UART.
- USART_ASYNC_ReadByteBlocking: Reads a byte from UART (blocking).
- USART_ASYNC_ReadByteNonBlocking: Reads a byte from UART (non-blocking).
- USART_ASYNC_RX_Restart: Restarts UART reception.
- USART_ASYNC_WriteByteBlocking: Writes a byte to UART (blocking).
- USART_ASYNC_WriteStringBlocking: Writes a string to UART (blocking).
- USART_ASYNC_WriteByteNonBlocking: Writes a byte to UART (non-blocking).
- USART_ASYNC_WriteStringNonBlocking: Writes a string to UART (non-blocking).

### 💻 How to Use:
1. **Include Files:**
   - Make sure to include `hal_usart.h` in your project.
   ```c
   #include "hal_usart.h"
   ```

2. **Initialization:**
   - Create a `usart_t` structure with your desired configurations.
   ```c
   usart_t my_usart = {
       .baudrate = 9600,  // Set your baud rate
       .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,
       .usart_tx_cfg = { .usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE },
       .usart_rx_cfg = { .usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE },
   };
   ```

3. **Initialize UART:**
   - Call the initialization function with your `usart_t` structure.
   ```c
   USART_ASYNC_Init(&my_usart);
   ```

4. **Sending Data:**
   - Use the provided functions to send data.
   ```c
   uint8_t data_to_send = 'A';
   USART_ASYNC_WriteByteBlocking(data_to_send);
   ```

5. **Receiving Data:**
   - Use the provided functions to receive data.
   ```c
   uint8_t received_data;
   USART_ASYNC_ReadByteBlocking(&received_data);
   ```

6. **Interrupts (Optional):**
   - If using interrupts, set up your interrupt handlers and enable interrupts.
   ```c
   void MyTxInterruptHandler(void) {
       // Your code here
   }

   void MyRxInterruptHandler(void) {
       // Your code here
   }

   // Set interrupt handlers
   my_usart.USART_TxDefaultInterruptHandler = MyTxInterruptHandler;
   my_usart.USART_RxDefaultInterruptHandler = MyRxInterruptHandler;

   // Enable interrupts
   my_usart.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
   my_usart.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
   ```

7. **Deinitialization (Optional):**
   - When done, you can deinitialize the UART module.
   ```c
   USART_ASYNC_DeInit(&my_usart);
   ```

### 📝 Notes:
- Ensure proper configuration of the `hal_usart_cfg.h` file for your specific project requirements.
- Refer to the comments within the code for more detailed explanations of each function and configuration option.
- Feel free to customize the driver according to your application's needs.
