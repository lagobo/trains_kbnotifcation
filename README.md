# README #

Create a visual alert for failing AI experiments on the [Allegro Trains](https://github.com/allegroai/trains) 
platform. Keyboard LEDs will flash red if an experiment failed in a specific project.

This repository was inspired by this awesome [work](https://blog.cynthia.re/post/keyboard-alerts) ([code](https://github.com/bitcynth/kb-alerter)) 
[as seen on hackaday](https://hackaday.com/2020/04/14/reverse-engineering-an-rgb-keyboard-under-linux/)

Implementation is based on [this](https://github.com/pbludov/hv-kb390l-config) great Havit configuration utility, thank you so much!
We added support for multiple keyboard vendors / products, and the missing RGB LED color control.  

### What is this repository for? ###

* Experiment monitoring service (python)
* Havit Keyboard lighting control utility (CLI c++)
  - Tested on model HV-390L but should work on other compatible keyboards like Sharkoon  
* Alert user when an experiment failed (crashed)
* On alert, change the keyboard lighting to flashing RED

### How do I get set up? ###

* check your keyboard compatibility
*   `lsusb | grep 04d9`
*   If you have one of the following, your keyboard is supported :)
  
    ```
    04d9:a131 Holtek Semiconductor, Inc.  
    04d9:a232 Holtek Semiconductor, Inc.
    ```
  
* Compile `hv-390l-control` utility (No need to compile if you are using ubuntu 16.04/18.04)
* Run python the service

### Running the alert monitor service ###

To monitor failing experiments on a specific project:

`python monitor_project.py --project <my_project_name> --refresh-rate <refresh_every_x_sec>`

Example:

`python monitor_project.py --project examples --refresh-rate 1.5`


### Compiling `hv-390l-control` utility  ###

Pre-requisites are QT5, libHIDapi, libUSBdev

`sudo apt-get install -y libusb-dev libhidapi-dev libqt5core5a`

Build `hv-390l-control` utility:

```
qmake
make
make clean
```

### Contribution guidelines ###

* Feel free to PR with any cool improvement

