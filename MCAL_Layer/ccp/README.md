### 📝 CCP Driver for PIC18F46K20

This is a CCP (Capture/Compare/PWM) driver for the PIC18F46K20 microcontroller. The driver consists of three files:

- `hal_ccp.c`
- `hal_ccp.h`
- `ccp_cfg.h`

### 📁 Files

#### `hal_ccp.c`

This file contains the implementation of the CCP driver functions. Below are the available functions:

- `ccp_init`: Initializes the CCP module based on the configuration provided in the `ccp_t` structure.
- `ccp_DeInit`: De-initializes the CCP module.
- `set_dutyCycle`: Sets the duty cycle for PWM mode.
- `pwm_start`: Starts the PWM operation.
- `pwm_stop`: Stops the PWM operation.
- `CCP_IsCompareComplete`: Checks if a compare operation is complete.
- `CCP_Compare_Mode_Set_Value`: Sets the compare value for the CCP module.
- `CCP_IsCapturedDataReady`: Checks if captured data is ready.
- `CCP_Capture_Mode_Read_Value`: Reads the captured value from the CCP module.

#### `hal_ccp.h`

This header file contains macros, enums, and function declarations for the CCP driver. Here are some of the important declarations:

##### Enums:
- `ccp1_mode_t`: Enum for CCP modes (Capture, Compare, PWM).
- `ccp_timer_select_t`: Enum for timer selection.
- `ccp_inst_t`: Enum for CCP instances (CCP1, CCP2).

##### Macros:
- Various macros for CCP modes and configurations.
- Timer2 input clock post-scaler and pre-scaler macros.
- CCP Capture and Compare mode state macros.

##### Structs:
- `ccp_reg_t`: Union for CCP register values.
- `ccp_t`: Structure containing CCP configuration parameters.

##### Functions:
- Function declarations for all the functions defined in `hal_ccp.c`.

#### `ccp_cfg.h`

This header file contains configuration macros for the CCP driver:
- `CCP_CFG_PWM_MODE_SELECTED`
- `CCP_CFG_CAPTURE_MODE_SELECTED`
- `CCP_CFG_COMPARE_MODE_SELECTED`

### 🛠️ How to Use

1. **Include the Files:**
   - Include `hal_ccp.c`, `hal_ccp.h`, and `ccp_cfg.h` in your project.

2. **Configure CCP:**
   - Define your CCP configuration using the `ccp_t` structure.
   - Set the CCP mode (`ccp_mode`) to `CCP_CAPTURE_MODE_SELECTED`, `CCP_COMPARE_MODE_SELECTED`, or `CCP_PWM_MODE_SELECTED`.
   - Specify other parameters such as timer selection, frequency, post-scaler, and pre-scaler values if needed.

3. **Initialization:**
   - Call `ccp_init(&ccp_obj)` to initialize the CCP module with your configuration.

4. **Operate CCP:**
   - For PWM mode:
     - Set duty cycle using `set_dutyCycle(&ccp_obj, dutyValue)`.
     - Start PWM with `pwm_start(&ccp_obj)`.
     - Stop PWM with `pwm_stop(&ccp_obj)` when needed.
   - For Capture mode:
     - Check if data is ready using `CCP_IsCapturedDataReady(&ccp_obj, &_capture_status)`.
     - Read captured value using `CCP_Capture_Mode_Read_Value(&ccp_obj, &capture_value)`.
   - For Compare mode:
     - Check if compare is complete using `CCP_IsCompareComplete(&ccp_obj, &_compare_status)`.
     - Set compare value using `CCP_Compare_Mode_Set_Value(&ccp_obj, compare_value)`.

5. **Interrupts (Optional):**
   - If interrupts are enabled:
     - Define interrupt handlers.
     - Enable interrupts using `interrupt_config(&ccp_obj)`.

### 🚀 Example

```c
#include "hal_ccp.h"

int main() {
    ccp_t ccp_obj;
    
    // Configure CCP for PWM mode
    ccp_obj.ccp_inst = CCP1_INST;
    ccp_obj.ccp_timer = ccp1_ccp2_timer1;
    ccp_obj.ccp_mode = CCP_PWM_MODE_SELECTED;
    ccp_obj.pwm_frequency = 1000;  // 1 kHz
    ccp_obj.timer2_postscaler_value = CCP_TIMER2_POSTSCALER_DIV_BY_1;
    ccp_obj.timer2_prescaler_value = CCP_TIMER2_PRESCALER_DIV_BY_1;
    
    // Initialize CCP
    ccp_init(&ccp_obj);
    
    // Set duty cycle to 50%
    set_dutyCycle(&ccp_obj, 50);
    
    // Start PWM
    pwm_start(&ccp_obj);
    
    while(1) {
        // Your main code here
    }
    
    return 0;
}
```

### 📄 Note
- Make sure to configure the GPIO pins accordingly for the CCP module.
- Check the datasheet of PIC18F46K20 for specific register details and configurations.
