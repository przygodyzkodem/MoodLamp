# MoodLamp

MoodLamp is an ESP8266 based WS2812B addressable LED controller. It's key features are:
- 55 different togglable light effects
- adjust light color
- adjust brightness
- quick on/off toggle
- easy configuration via captive portal
- minimalistic hardware design - cheap and easy to assemble and to install in your home

## Demo / Use Case Examples

Demo video (click to watch, don't forget to slap like :P ):
[![MoodLamp Demo Video](https://github.com/przygodyzkodem/MoodLamp/blob/master/Image%20Resources/MoodLamp_demo_video.png?raw=true)](https://www.youtube.com/watch?v=sJ2Bf1LhpAg)

Litophane lamp (gift for my lovely girlfriend):

![MoodLamp Litophane Lamp](https://github.com/przygodyzkodem/MoodLamp/blob/master/Image%20Resources/MoodLamp_litophaneLamp.JPG?raw=true)

3D Printer project kudos to GrkMangas from Thingiverse: [https://www.thingiverse.com/thing:2730082](https://www.thingiverse.com/thing:2730082)

## How to assemble your own Mood Lamp

In this repository you can find several types of resources. I plan to create few form factors of hardware and several software versions. The common thing for all of them will be the usage of ESP8266 module and Arduino code to drive addressable LEDs (e.g. WS2812B). To create your own Mood Lamp, you need to follow steps listed below. Please note that each hyperlink will take you to another part of this repository which will contain another piece of documenation that will provide you with further details.

1. Pick your hardware version:
- you can build circuit out of Arduino modules based on Fritzing layout which you can find here
- you can assemble a NodeMCU shield with resources in folder: 
2. Select your software:
- currently only implementation using Blynk platform: 
3. Select proper power supply:
- all of the hardware designs will require power supply with 5V DC voltage
- to calculate the current required by your circuit, you can use the following equation: (60mA x N) + 120mA, where N is number of WS2812B diodes in your project
- please note, that if your project current requirement goes above few Amperes it is crossing a border where it becomes dangerous, consider splitting the project into few, separately powered modules
4. Install required software to control the Mood Lamp:
- currently it means installing Blynk app and properly configuring your project, check instructions in Software section for detailed instructions
5. Design your enclosure or use some ideas from repository.

## Plans / ToDo:

- add documentation for Fritzing layout / basic connections on breadboard
- add documentation for Blynk software implementation
- add documentation for Hardware version (NodeMCU shield)
- design a 3D printed enclosure for NodeMCU + hardware shield

## Contributing

If you find any errors/bugs/problems with either hardware or software, please create a new issue in this repository to let me know. If you have an idea for a new feature or hardware or software variant, please also use Issues section so we can discuss it.

## License
MoodLamp project is available under the MIT License. See the [LICENSE](https://github.com/przygodyzkodem/MoodLamp/blob/master/LICENSE) file for more info.
