# Task B – Single Button Press Detection

## Student Info
- Name: Minahal Fatima  
- Reg No: 23-NTU-CS-1050  
- Board: ESP32  

## Objective
- Detect short and long presses on a single button.  
- Toggle LED on short press, play buzzer on long press.  
- Show event on OLED display.  

## Hardware Components
| Component | Pin |
|-----------|-----|
| LED | 2 |
| Buzzer | 27 |
| Button | 12 |
| OLED SDA | 21 |
| OLED SCL | 22 |

## Press Events
- **Short Press (<1.5s)** → Toggle LED ON/OFF  
- **Long Press (≥1.5s)** → Play buzzer tone  

## Wokwi JSON
- `/wokwi/taskB.json`  
- Wokwi Link: https://wokwi.com/projects/445858202457393153
  

## Folder Structure
assignment1-23-NTU-CS-1050/
├── src/taskB.ino
├── include/
├── wokwi/taskB.json
├── screenshots/short_press.png long_press.png
└── docs/TaskB_Report.pdf


## Results
- OLED shows detected event.  
- LED toggles correctly on short press.  
- Buzzer sounds correctly on long press.
- # Screen shots
1:Short Press
![Short Press](screenshots/shortbuttonpress.png)
2:Long Press
![Long Press](screenshots/longbuttonpress.png)