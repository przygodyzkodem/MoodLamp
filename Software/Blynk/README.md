# Blynk platform Software Version

This software variant utilizes Blynk platform to allow easy installation, configuration and usage of your MoodLamp device. Best choice for beginners or if you don't plan to create bigger smart home system.

## Features
- easy installation and configuration
- 55 different togglable light effects
- adjust light color
- adjust brightness
- quick on/off toggle

## How to install & configure

### Arduino Software

1. Install Arduino (I'm currently using version 1.8.10)
2. Launch Sketch file (.ino file format) and open Arduino Preferences window.
3. Enter `https://arduino.esp8266.com/stable/package_esp8266com_index.json` into the Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
4. Open Boards Manager from Tools > Board menu and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).
4. Install required 3rd party libraries or copy them from this repository's libraries folder (recommended - you will avoid problems with library version compatibility).
5. Enter correct value that represents number of NeoPixel leds you want to drive in line:
`#define PIXEL_COUNT 36`
6. (Optional) enter your WiFi network SSID and password and Blynk auth token to speed up integration process.
7. Flash your Arduino software to NodeMCU (note: you should avoid connecting long LED strips to your computer USB port to prevent high current drain).

### Mobile app

1. Install Blynk mobile app (available for Android and iOS devices)
2. Create account / sign in into Blynk app
3. Run QR code scanner in Blynk app (QR Code icon on navigation bar) and scan code below to clone project configuration:
[![Clone Blynk Project Configuration](https://github.com/przygodyzkodem/MoodLamp/blob/master/Image%20Resources/blynk_app_configuration.jpeg?raw=true)]

That's it, your mobile app for controlling MoodLamp device is ready! :) Now for the final step!

### Integration

If you have already successfully flashed Arduino software and configured Blynk app you're ready to integrate them together, so you can control your device with Blynk app. If you've completed step 6. from Arduino Software installation tutorial, you can skip all of this and go directly to Blynk app to control your MoodLamp! In other case read along to complete the integration.

We'll start with getting Blynk Auth Token. Open your Blynk app and go to project settings (nut icon on navigation bar). Here you will see a blue text consisting of 32 letters and digits. It is labeled as Auth Token. If you tap it, it will be copied to the clipboard of your device. We will need it in the next step.

Power up your MoodLamp device if you haven't already and go to network settings on your mobile device. On the list of available WiFi networks, you should be able to see the network broadcasted by your MoodLamp device. By default it should be named "MoodLamp" if you didn't change it in Arduino code. Click it as if you wanted to connect to it. The Captive Portal should open with fields for SSID (network name) and Password of WiFi network you want your MoodLamp to connect to (note: it must be 2.4GHz WiFi network). Third text field is for Auth Token that we copied in previous step. Paste it here and save the data. Your MoodLamp will restart and connect to the WiFi network and Blynk service and should be ready to be controlled by the mobile app. Launch Blynk and try it out! :) 

## Plans / ToDo
- Add error handling (use first NeoPixel in strip to signal common types of errors to the user)
- Improve documentation styling
- Add some screenshots to the README file
