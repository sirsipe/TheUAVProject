# The UAV Project

Motivation of this project is absolutely nothing else than learning & for fun. Some years ago I bought a cheap amateur RC plane just to try the hobby and soon realized that I have drawers full of Arduinos, Raspberry Pies and other nerdy stuff I'd love to fly to the moon. So here we go!

**!!! WORK IN PROGRESS !!!**

**Agenda:** _~1,5m wingspan hobby-grade RC plane with on-board Raspberry Pi flight computer running custom firmware._


## Brief 

**Arduino Pro Mini** reads PWM signals of the on-board **RC receiver** and re-routes the signals to **PWM Driver** (PCA9685) as I2C master device. The PWM Driver controls the engine and all servos.

RPi sends its display using the analog TV out with **FPV transmitter** (TX5258). The display will have **live camera feed** and overlay with available **flight data**. When the RPi boots up and has its **custom firmware** running, it will notify Arduino with a continues ping that Arduino should switch to I2C slave mode, and RPi will become I2C master.
 
When RPi is I2C master, it will first query PWM values from Arduino and then send them to Servo driver. Since RPi can also query **orientation from MPU9250** and **position from GPS**, it is possible to write **autoleveling, autopilot and such routines**.

The radio has 6 channels and 2 of them (knobs) will be utilized to access **flight menu** of the custom OSD software.

## Stuff used

- An RC Plane (6CH): [Hobbyking Bix3 /w Flaps](https://hobbyking.com/en_us/hobbykingtm-bix3-trainer-fpv-epo-1550mm-mode-2-ready-to-fly.html?___store=en_us)
  - Hobbyking radio + 6CH receiver
  - ESC with 5v BEC
- FPV Transmitter: [Eachine TX5258](https://www.banggood.com/Eachine-TX5258-5_8G-72CH-25-or-200-or-500-or-800mW-Switchable-FPV-Transmitter-Support-OSD-Configuring-Smartaudio-p-1248768.html?imageAb=2&cur_warehouse=CN&akmClientCountry=FI): _Power from battery's balanced connector_
- FPV Receiver: [Eachine VR D2 Pro](https://www.getfpv.com/eachine-vr-d2-pro-40ch-5-8g-diversity-fpv-goggles-with-dvr.html): _Power from ESC BEC_
- [Arduino Pro Mini 5v](https://www.adafruit.com/product/2378): _Power from ESC BEC_
- [Raspberry Pi 0w](https://www.raspberrypi.com/products/raspberry-pi-zero-w/) + [Camera](https://thepihut.com/products/zerocam-camera-for-raspberry-pi-zero): _According to [this page](https://raspi.tv/2017/how-much-power-does-pi-zero-w-use), current draw when recording video is around 230mA. In addition Beitian BN-880 GPS draws 50mA@5V, but it will be run at 3v3. Eachine TX5258 can supply 300mA so... not much playroom there :)_
- [Beitian BN-880 GPS](https://uk.banggood.com/Beitian-BN-880-Flight-Control-GPS-Module-Dual-Module-Compass-With-Cable-for-RC-Drone-FPV-Racing-p-971082.html?cur_warehouse=CN): _Power from RPi (3v3)_
- GY-91 (MPU9250+BMP280) 10-DOF sensor: _Power from ESC BEC_

## Initial schematics

![image](/Docs/Schematics.png)


## Progress

- [x] Custom Linux with Buildroot for RPi 0w
  - [x] Raspivid working
  - [x] GPS via UART working
    - [ ] Flight path recording 
  - [x] [Raylib](https://github.com/raysan5/raylib) working (for custom OSD)
  - [ ] OSD software base
  - [ ] Master Ping -line
  - [ ] I2C
    - [ ] GY-91 communication
  - [ ] Power from Trasmitter

- [x] 6CH PWM signals from RC receiver for Arduino Pro Mini
  - [x] Re-route received signals to servo driver
  - [x] Power from ESC
  - [ ] I2C slave mode

![image](/Docs/PWM%20Routing.png)


## Unrelated picture

![image](https://user-images.githubusercontent.com/15073095/161447498-e270d2ec-56ca-40bf-9fa9-c19f0553dd55.png)
