# NASA TechRise High-Altitude Stratospheric Payload
**Mission Profile:** Stratospheric Radiation levels and Earth's magnetic interference modeling

## Make sure to log all hours on journal.md
https://github.com/BombasticBomb/pesh-techrise/blob/main/journal.md

## Mission Overview
This repository contains the complete technical documentation, bill of materials, circuit architecture, and firmware structure for our NASA TechRise student challenge payload. Designed to meet strict near-space constraints (**<\$300 budget** and **<0.5kg mass limit**), the payload measures ionizing radiation and high-altitude atmospheric profiles while maintaining a strictly controlled internal thermal microclimate. Power is supplied directly via the vehicle's integrated power system.

---

## Physical Architecture & Mechanical Design
The chassis is designed in Autodesk Fusion 360 and 3D printed using **carbon-fiber reinforced nylon (PA-CF)** to provide exceptional structural rigidity and temperature resistance.

- **Dimensions:** 4 x 4 x 8 inches
- **Total Mass:** ~271 grams
- **Thermal Insulation:** Internal walls lined with **extruded polystyrene (XPS) foam** panels.
- **Active Thermal Control:** Dual aluminum thermal spreader plates bonded with 10–15W heating resistors, modulated via a closed-loop **PID controller** running on an **ESP32-S3** through logic-level N-channel MOSFETs.
- **Pressure Venting:** Integrated static pressure port utilizing silicone tubing and a waterproof ePTFE vent patch to prevent dynamic pressure distortion during rapid ascent.

---

## 4. Bill Of Materials (BOM) & Budget

| Name | Estimated Cost (\$) | Mass (g) |
| :--- | :--- | :--- |
| ESP32-S3 Development Board | \$6.00 | 15g |
| SBM-20 Geiger-Müller Tube | \$25.00 | 20g |
| High-Voltage Step-up Module (~400V) | \$10.00 | 10g |
| MS5611 Barometer Breakout | \$12.00 | 5g |
| LIS3MDL Magnetometer Breakout | \$8.00 | 3g |
| u-blox MAX-M10S GPS Module | \$16.00 | 16g |
| MicroSD Card Reader Module (SPI) | \$3.00 | 5g |
| Dual DS18B20 Digital Temp Sensors (Internal/External) | \$15.00 | 15g |
| Aluminum Spreader Plates & 10W Resistors | \$12.00 | 45g |
| N-Channel MOSFETs (Logic-Level Switching for Heaters) | \$2.00 | 2g |
| Custom 4x4x8 in. PA-CF 3D Print Filament | \$15.00 | 110g |
| XPS Foam Panels & Silicone Static Port Tubing | \$8.00 | 25g |
| **Total Payload Profile** | **~\$172.00** | **~271g** |

> *Note: The estimated costs above do not account for shipping fees or iterative prototyping hardware; however, given NASA's $1,500 budget limit, we are confident that total expenses will remain well below the threshold.*

## Avionics & Circuit Integration (KiCad PCB)
To eliminate loose wiring failures under high-vibration flight conditions, all avionics interface through a custom single-layer **KiCad PCB**.

- **Schematic Architecture:**
  * **I2C Bus:** Connects the ESP32-S3 to the MS5611 barometer and LIS3MDL magnetometer.
  * **UART Bus:** Connects the ESP32-S3 hardware serial pins to the u-blox MAX-M10S GPS module for positioning tracking.
  * **SPI Bus:** Connects the ESP32-S3 to the MicroSD card reader module (MOSI, MISO, SCK, CS) for continuous high-frequency data logging.
  * **1-Wire Bus:** Interfaces both DS18B20 digital temperature sensors (external waterproof probe measuring down to -55°C, and internal core sensor).
  * **Interrupt Pin:** Handles pulse-counting input from the SBM-20 Geiger-Müller high-voltage module.
  * **PWM Control & Switching:** Connects ESP32-S3 PWM output pins through gate resistors to logic-level **N-channel MOSFETs**, which safely switch high-current power to the active heating resistors.
- **Layout Notes:** High-voltage traces driving the Geiger tube and high-current paths for the heating elements are physically isolated from sensitive low-voltage digital I/O lines to minimize electromagnetic interference (EMI).

---

## Repository Directory Structure
```text
├── cad/                 # Fusion 360 models and chassis STL files
├── kicad/               # Schematic files (.sch) and PCB layout (.kicad_pcb)
├── firmware/            # ESP32-S3 C++ code, sensor libraries, and PID control loops
└── docs/                # Technical schematics, wiring diagrams, and testing logs
