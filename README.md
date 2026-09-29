# NASA TechRise High-Altitude Stratospheric Payload
**Mission Profile:** Stratospheric Radiation levels and Earth's magnetic interference modeling

---

## Mission Overview
This repository contains the complete technical documentation, bill of materials, circuit architecture, and firmware structure for our NASA TechRise student challenge payload. Designed to meet strict near-space constraints (**<$300 budget** and **<0.5kg mass limit**), the payload measures ionizing radiation and high-altitude atmospheric profiles while maintaining a strictly controlled internal thermal microclimate.

---

## Physical Architecture & Mechanical Design
The chassis is designed in Autodesk Fusion 360 and 3D printed using **carbon-fiber reinforced nylon (PA-CF)** to provide exceptional structural rigidity and temperature resistance.

* **Dimensions:** 4 x 4 x 8 inches
* **Total Mass:** ~343 grams
* **Thermal Insulation:** Internal walls lined with **extruded polystyrene (XPS) foam** panels.
* **Active Thermal Control:** Dual aluminum thermal spreader plates bonded with 10–15W heating resistors, modulated via a closed-loop **PID controller** running on an **ESP32-S3**.
* **Pressure Venting:** Integrated static pressure port utilizing silicone tubing and a waterproof ePTFE vent patch to prevent dynamic pressure distortion during rapid ascent.

---

## Bill of Materials (BOM)

| Component Category | Part / Item Description | Estimated Cost ($) | Mass (g) |
| :--- | :--- | :--- | :--- |
| **Processing & Core** | ESP32-S3 Development Board | $6.00 | 15g |
| **Radiation Suite** | SBM-20 Geiger-Müller Tube | $25.00 | 20g |
| **Radiation Suite** | High-Voltage Step-up Module (~400V) | $10.00 | 10g |
| **Environment** | MS5611 Barometer Breakout | $12.00 | 5g |
| **Environment** | LIS3MDL Magnetometer Breakout | $8.00 | 3g |
| **Thermal Suite** | Dual DS18B20 Digital Temp Sensors (Internal/External) | $15.00 | 15g |
| **Thermal Suite** | Aluminum Spreader Plates & 10-15W Resistors | $12.00 | 45g |
| **Power Architecture** | 5000mAh 3.7V LiPo Battery Pack | $18.00 | 95g |
| **Mechanical Chassis** | Custom 4x4x8 in. PA-CF 3D Print Filament | $15.00 | 110g |
| **Insulation & Plumbing** | XPS Foam Panels & Silicone Static Port Tubing | $8.00 | 25g |
| **Total Payload Profile** | *Complete Integrated Stratospheric Assembly* | **~$169.00** | **~343g** |

---

## Avionics & Circuit Integration (KiCad PCB)
To eliminate loose wiring failures under high-vibration flight conditions, all avionics interface through a custom single-layer **KiCad PCB**.

* **Schematic Architecture:**
  * **I2C Bus:** Connects the ESP32-S3 to the MS5611 barometer and LIS3MDL magnetometer.
  * **1-Wire Bus:** Interfaces both DS18B20 digital temperature sensors (external waterproof probe measuring down to -55°C, and internal core sensor).
  * **Interrupt Pin:** Handles pulse-counting input from the SBM-20 Geiger-Müller high-voltage module.
  * **PWM Control:** Drives a logic-level N-channel MOSFET regulating current to the active heating plates.
* **Layout Notes:** High-voltage traces driving the Geiger tube are physically isolated from sensitive low-voltage digital I/O lines to minimize electromagnetic interference (EMI).

---

## Repository Directory Structure
```text
├── cad/                 # Fusion 360 models and chassis STL files
├── kicad/               # Schematic files (.sch) and PCB layout (.kicad_pcb)
├── firmware/            # ESP32-S3 C++ code, sensor libraries, and PID control loops
└── docs/                # Technical schematics, wiring diagrams, and testing logs
