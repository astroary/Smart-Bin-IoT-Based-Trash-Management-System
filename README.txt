📋 Project Overview
The system utilizes a dual-Arduino architecture to monitor and display trash levels in real-time. The primary goal is to streamline household chores by providing immediate feedback on how full a bin is without requiring the user to open it.


🛠️ Key Features
Multi-Sensor Detection: Uses three ultrasonic sensors to calculate an average trash height, ensuring accuracy across the entire bin surface.

Automated Calibration: Features a dedicated push button to store the maximum height of the bin when empty.

Real-Time UI: Displays trash percentage on a 16x2 LCD screen.

Multilevel Alerts:

Safe (<65%): Green LED indicates the trash level is fine.

Warning (65%-89%): Red LED signals the bin is filling up.

Critical (≥90%): A 5KHz buzzer activates to notify the user to empty the trash immediately.


⚙️ Technical Implementation
The project consists of two Arduinos communicating via a hardwired serial connection (TX to RX).

1. Trash Detection Unit (Arduino 1)
Attached to the bin lid, this unit handles data collection:

Input: 3x HC-SR04 Ultrasonic Sensors, 2x Push Buttons.

Logic: Calculates the current distance and sends the "Trash Filled Percentage" to the display unit via serial communication.

2. User Display Unit (Arduino 2)
Located in a convenient viewing area, this unit provides feedback:

Output: 16x2 LCD, Red/Green LEDs, and a Buzzer.

Logic: Interprets incoming serial data to trigger the appropriate visual and auditory status indicators.


🔧 Components Used

- 2x Arduino Uno

- 3x HC-SR04 Ultrasonic Sensors

- 1x 16x2 LCD Display

- 2x LEDs (Red and Green)

- 1x Buzzer

- 2x Push Buttons

- 1x 10kΩ Potentiometer (for LCD contrast)

- 2x 10kΩ Resistor

- 3x 200Ω Resistor



👥 Author
Aryansingh Chauhan (astroary)

---
Course: CS 362 (Computer Design), Fall 2023  
Instructor: Prof. Pat Troy
University of Illinois Chicago