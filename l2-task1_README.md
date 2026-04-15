## l2-task1: LED Blink Application with Zephyr Setup

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

### What I did:
- Built and flashed the LED blink application on NUCLEO-F401RE
- LED toggles every 500ms
- Verified LED state via UART logs
- Video output attached: 
                         [📎 Download/View Video: Blinky_Task1.mp4](./Blinky_Task1.mp4)
						 
### Notes:
- I used the `west` build system to manage the project:
- Flashed the NUCLEO board using `west flash` via the STM32CubeProgrammer runner.