# L3-Task1: Advanced LED Control with Zephyr OS

## Description : LED Subsystem Kconfig configuration

## Personal Information
**Done by:**
* **Name:** Juan Carlos Suárez B.
* **GitHub:** [jsuarezbaron16](https://github.com/jsuarezbaron16)
* **Profile:** [https://github.com/jsuarezbaron16](https://github.com/jsuarezbaron16)

## Development Setup
| Component | Version / Model |
| :--- | :--- |
| **Board** | NUCLEO-F401RE |
| **Zephyr OS** | v4.4.0-rc2 |
| **West Tool** | v1.5.0 |
| **Toolchain** | Zephyr SDK 1.0.1 |


## Project Overview
In this project, I developed a modular LED control application for the NUCLEO-F401RE board using **Zephyr OS**. The main focus was to integrate the hardware configuration (Devicetree) with a user-friendly configuration interface (Kconfig).

### Demo Videos
* [View: Default Blinky Task 1](./l3-task1_LEDSubSystem_Kconfig.mp4)
* [View: Brightness 100% - Fade 500ms](./l3-task1_Brghtness_100_Fade_500ms.mp4)
* [View: Brightness 50% - Fade 25ms](./l3-task1_Brightness_50_Fade_25ms.mp4)

### 1. Hardware Configuration (PWM)
Instead of a simple GPIO toggle, I configured the user LED (PA5) to work with **Pulse Width Modulation (PWM)**. 
* Created a `nucleo_f401re.overlay` file to define a `pwm-led` child node.
* Mapped the `pwm2` peripheral to the `tim2_ch1_pa5` pin.
* This allows for granular control over the LED brightness.

### 2. Custom Kconfig Menu Structure
I implemented a hierarchical menu system using **Kconfig**, enabling the configuration of the firmware without modifying the source code. The structure includes:
* **LED Subsystem Toggle:** A top-level switch to enable/disable the entire module.
* **Blink Sleep Time:** A `choice` menu to select predefined intervals (250ms, 500ms, 1s, 2s) or a custom integer value.
* **Advanced Settings:** * **Brightness Control:** An integer range (0-100) to set the duty cycle.
    * **Fade Duration:** A configurable time (ms) to transition between ON and OFF states.
* **Expert Settings:** Conditional menu for debugging logs and custom patterns.

### 3. Firmware Logic (Main Application)
The application was written in **C++** (`main.cpp`) and utilizes the following features:
* **Fade Effect:** I implemented a `led_fade_to` function that uses linear interpolation to smoothly transition the LED brightness over the duration specified in Kconfig.
* **Thread Safety:** Used `k_msleep` for precise timing and power-efficient waiting.
* **Logging:** Integrated the Zephyr Logging API (`LOG_INF`) to provide real-time feedback on the LED state and PWM duty cycle values via the serial console.

### 4. Compilation and Usage
Using the `west` build system:
1.  Run `west build -t menuconfig` to set parameters.
2.  Compiled the firmware, ensuring that the `autoconf.h` correctly generated macros from the Kconfig file.
3.  Flashed the NUCLEO board using `west flash` via the STM32CubeProgrammer runner.