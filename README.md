# Break-in home alarm system with TTS

This project uses Arduino, ESP32 and ESP8266 to monitor doors or windows for break-ins. It has a text-to-speech engine, wireless alarm sensors and a main hub with a keypad and an LCD screen.

https://github.com/user-attachments/assets/8359e088-80c3-4375-a72e-56698194db19

## Hardware ([link](/hardware/))

Contains Kicad files of the circuits (.kicad_sch), symbols (.dcm, .lib) and footprints (.mod). 

## Software ([link](/software/))

### Main hub ([link](/software/nano_main_hub/))

Has a D1 mini for wifi connection to alarm units and an Arduino to process incoming alarms via hardware interrupts.

### Text-to-speech ([link](/software/esp32_tts/))

ESP32 gets string data via serial connection to Arduino Nano, stores it into a buffer and controls a speaker to produce speech from the chars in the buffer.

### Alarm sensor ([link](/software/esp8266_window_sensor/))

Made using a D1 Mini. Uses an IMU and a magnet sensor to detect door or window opening or shaking.

### Wifi server ([link](/software/esp8266_server/))

D1 Mini runs a wifi server and relays any alarms received via wifi to Arduino Nano by wire.

