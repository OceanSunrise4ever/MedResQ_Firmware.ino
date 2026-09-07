# MedResQ Firmware

# MedResQ: AI-Assisted Disaster Triage Control Loop

This repository contains the official open-source firmware for **MedResQ**, a semi-autonomous robotic platform designed to enhance early search, safety assessment, and situational awareness in mass-casualty disaster settings. 

This research and development is part of a study submitted to the *Journal of Emerging Investigators (JEI)*.

## 🚀 System Overview
MedResQ utilizes dual-channel sensory inputs processed continuously on an ATmega328P (Arduino Uno) architecture to navigate debris-filled environments safely while concurrently searching for human life signs.

* **Obstacle Avoidance:** Uses an HC-SR04 Ultrasonic sensor to measure boundaries and dynamically adjust motor speed profiles.
* **Life Detection:** Uses a Passive Infrared (PIR) sensor to register human heat signatures instantly without blocking navigation processing strings.

## 📈 Navigation Logic Thresholds
* **Path Clear (> 40 cm):** Maximum forward searching mobility (PWM Speed 255).
* **Deceleration Zone (20 cm - 40 cm):** Safe braking threshold, reduces speed by 41.1% (PWM Speed 150) to protect hardware from collisions.
* **Collision Evasion (≤ 20 cm):** Full braking mechanism engaged, followed by defensive reverse and right-turn escape tracking maneuvers.

## 🛠️ Hardware Requirements
To replicate this circuit physically or via an emulator (such as Tinkercad Circuits), you will need:
* 1x Arduino Uno R3
* 1x HC-SR04 Ultrasonic Distance Sensor
* 1x PIR Motion Sensor
* 1x L298N Dual H-Bridge Motor Driver
* 2x DC Core Motors
* 1x 12V External Battery Source

## 📝 License
This project is licensed under the MIT License - see the LICENSE file for details.
