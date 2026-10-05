Do a couple of logs here to log our work, and if we get accepted hopefully we'll continue work on this journal log. This is essentially our engineering notebook ig. Follow the format I used.

# Ahmad Farzad Taquee - 10/05/2026 18:19 PM - Setting up a basic voltage regulator system for the circuit and added the ESP32 ic.

_Time spent: 27m_

Firstly, I added an ESP32 chip which'll be out main microcontroller for the project. Then, I added a 5v voltage regulator for the external electronics and added a 3.3v one for the ESP32. Also added a 0.1uF and 1uF decoupled capacitors on VDD_SPI pins on ESP32. The rest of the VDD pins I leaked current from the main VDD chip, as they all need power. The capacitors are there to reduce noise.
<img width="1574" height="901" alt="image" src="https://github.com/user-attachments/assets/1d034ae1-3fb6-48fe-b4f3-bd0a31124333" />
<img width="1480" height="788" alt="image" src="https://github.com/user-attachments/assets/cb968f23-1d56-4e7f-bf02-595500fd8053" />

