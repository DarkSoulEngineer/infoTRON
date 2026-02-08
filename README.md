# infoTRON 2026 - Applications

Hands-on Arduino/ESP32 labs used in the **infoTRON 2026** mechatronics program. The exercises are designed for classroom delivery: short demos you can show live, followed by student practice tasks and extension ideas.

## Learning objectives
- Read/write digital pins and use PWM on the ESP32.
- Build simple state machines (patterns, semaphores, button-driven modes).
- Serve a minimal web UI from the microcontroller using SPIFFS and AsyncWebServer.
- Practice disciplined uploads: flashing sketches, pushing SPIFFS assets, and checking serial output.

## Repository layout
- `LED/`
  - `blink_led_example/` - minimal GPIO toggle on pin 25 at 1 s interval.
  - `led_pattern/` - three-LED pattern that cycles through modes via a push-button on pin 34.
  - `led_semaphore/` - traffic-light sequence with configurable timings.
  - `rgb_led/` - RGB color cycling with PWM on pins 25 (R), 26 (G), 27 (B).
- `Web/aplicatia1/`
  - `led_web_control.ino` - ESP32 AsyncWebServer that exposes HTTP endpoints to toggle an on-board LED (GPIO 2) and serves UI assets from SPIFFS.
  - `data/` - HTML/CSS/JS uploaded to SPIFFS; shows current LED state and a toggle button.
  - `images/` - screenshots of the UI and code snippets for slides/handouts.

## Hardware
- ESP32 development board (Wi-Fi capable).
- Breadboard, jumper wires, USB cable.
- For LED labs: 3x single-color LEDs, 1x RGB LED, series resistors (220-330 ohm), 1x momentary push-button.
- Typical wiring
  - Single-color LEDs: pins 25 (red), 26 (yellow), 27 (green).
  - Button input (pull-up): pin 34.
  - RGB LED: pins 25/26/27 for R/G/B.
  - Web demo LED: GPIO 2 (on-board LED on many boards).

## Software prerequisites
- Arduino IDE 2.x with **ESP32 by Espressif** board package.
- Libraries (Library Manager or ZIP): `ESPAsyncWebServer`, `ESPAsyncTCP`.
- SPIFFS upload tool: **ESP32FS** plugin.

## Quick start (teacher flow)
1. Clone/download this repo into your Arduino projects folder.
2. Open a lab:
   - GPIO labs: open the `.ino` inside `LED/<exercise>/` and upload.
   - Web demo: open `Web/aplicatia1/led_web_control.ino`.
3. For the web demo:
   - Set `ssid` and `password`.
   - Upload `Web/aplicatia1/data/` to SPIFFS via *Tools -> ESP32 Sketch Data Upload*.
   - Flash the sketch, open Serial Monitor @ 115200, browse to the printed IP, and toggle the LED.
4. Show the PNGs in `Web/aplicatia1/images/` during lecture or lab kickoff.

## Teaching tips
- Start with `blink_led_example` to verify wiring and board drivers.
- Use `led_pattern` to discuss debouncing and mode switching.
- Switch to `led_semaphore` to introduce timing/state diagrams.
- Finish with `rgb_led` and `Web/aplicatia1` to connect PWM and networking concepts.
- Encourage students to tweak timings, add more states, or extend the web API (e.g., brightness slider).

## Contributing
Pull requests for clearer comments, wiring diagrams, or new lab variants are welcome. Align additions with the 2026 curriculum scope (introductory mechatronics and IoT).

## License
MIT License. See `LICENSE`.
