# Peter-Pan - Interactive Tinker Bell Lighting Installation

## Project Overview

Peter-Pan is an interactive Arduino-based lighting installation featuring a 3D model of Tinker Bell enclosed within a glass sphere. The system dynamically controls surrounding lights based on the number of people simultaneously touching the glass sphere, creating an engaging and magical interactive experience.

This project was done by Emile GIRARD, Maryem LAHMER and Raphaëlle BREBION, three students at Télecom SudParis and/or ENSIIE, for their studies in [JIN](https://www.telecom-sudparis.eu/formation/jeux-videos-interactions-collaborations-numeriques/).

## Features

- **Touch-Activated Lighting**: Multiple capacitive touch sensors detect when users touch the glass sphere
- **Dynamic Light Control**: Light intensity and behavior change based on the number of active touches
- **Arduino-Powered**: Custom Arduino code manages sensor input and light output
- **Interactive Experience**: Real-time response to user interaction, creating an immersive environment

## Hardware Components

- Arduino microcontroller
- Capacitive touch sensors
- Glass sphere housing for the 3D Tinker Bell model
- LED lighting system
- 3D model of Tinker Bell (centerpiece)

## Project Structure

```
Peter-Pan/
├── main/
│   ├── main.ino              # Main Arduino sketch
│   ├── OracleTouch.cpp       # Touch sensor control logic
│   └── OracleTouch.h         # Touch sensor header file
├── bocal_tinker_bell/
│   ├── bocal_tinker_bell.ino # Alternative implementation
│   └── tinkerbell_lights.ino # Light control logic
└── README.md                  # Project documentation
```

## Installation & Setup

1. Install the Arduino IDE on your computer
2. Connect your Arduino board via USB
3. Upload the main sketch from `main/main.ino` to your Arduino
4. Configure the touch sensor pins and LED pins according to your hardware setup
5. Power the system and test the touch interactions

## How It Works

- The Arduino continuously reads capacitive touch sensor inputs from the glass sphere
- Each detected touch increments a counter
- The lighting system responds by adjusting LED brightness, color, or patterns based on the number of simultaneous touches
- Release of touches decreases the counter, creating dynamic responsive behavior

## Video Demo

For a visual demonstration of the interactive installation in action, check out our demo video: [YouTube Demo](https://www.youtube.com/watch?v=Bch1zuCKuNY)

## License

This project is under a MIT License