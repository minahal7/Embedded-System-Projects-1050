# Task A – LED Mode Controller with OLED Display

## Student Info
- Name: Minahal Fatima  
- Reg No: 23-NTU-CS-1050  
- Board: ESP32  

## Objective
- Implement 4 LED modes controlled by MODE and RESET buttons.  
- Display the current mode on OLED.  
- Use buzzer for button feedback.  
- Learn interrupts and software debouncing.

## Hardware Components
| Component | Pin |
|-----------|-----|
| LED1 (Red) | 2 |
| LED2 (Green) | 4 |
| LED3 (Blue) | 5 |
| Buzzer | 27 |
| MODE Button | 12 |
| RESET Button | 14 |
| OLED SDA | 21 |
| OLED SCL | 22 |

## LED Modes
1. Mode 0 → All LEDs OFF  
2. Mode 1 → Alternate blinking LEDs  
3. Mode 2 → Both LEDs ON  
4. Mode 3 → PWM fade effect on LED3  

## Wokwi JSON
- `/wokwi/taskA.json`  
- Wokwi Link: https://wokwi.com/projects/445853794784446465
  

## Folder Structure
assignment1-23-NTU-CS-1050/
├── src/taskA.ino
├── include/
├── wokwi/taskA.json
├── screenshots/mode0.png ... mode3.png
└── docs/TaskA_Report.pdf


## Results
- OLED shows mode changes.  
- LEDs behave according to selected mode.  
- Buzzer provides feedback.
## Screenshots
1:Blink Mode
![Blink Mode](screenshots/Blink.png)
2:Both Off
![Both Off](screenshots/bothoff.png)
3:pwm fade
![pwm fade](screenshots/pwmfade.png)
4:reset mode
![reset mode](screenshots/resetmode.png)