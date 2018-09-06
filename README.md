# VisionSystemSim #

## Summary ##
The Vision System Simulator is a tool that will provide students with an avenue to test navigation code without having access to a physical tank. The program is written in C++ and communicates with a physical arduino board over serial port to execute a navigation program which is uploaded on the arduino board. It is designed to mimic the API used for RF and tank communication which will be used later on in the course. It is also designed to current mission specifications, ensuring that the navigation code will be executed on relevant randomizations. The OSV in the simulation is designed to move and look like the tanks provided by the course for testing. 

NOTE: This simulator is provided as a convinence. Even though your code may work on the simulator, that does not nessesarily imply that the code will work in a physical system, it only ensures that your navigation algorithm is logically sound.

## Setup ##
To run the Vision System Simulator, you will need four things:
1. The Arduino IDE, available [here](https://www.arduino.cc/en/Main/Software#download). Follow the instructions on the website to download the IDE.
2. The Arduino Library that interfaces with the simulator. You will use this library to control the simulated OSV. It comes with an example sketch to get you started. To download the library, go to [this Github repository](https://github.com/umdenes100/SimulatorArduinoLibrary) and click on the green button that says 'Clone or Download', then click 'Download ZIP'.  Open the Arduino IDE and install the library by going to Sketch > Include Library > Add .ZIP Library and selecting the downloaded file.
3. An Arduino board and USB cable. Your instructor will provide these materials to you.

### Windows Installation ###
1. Follow this link (Todo) to download the vision system installer.
2. Run the installer and follow the prompts to install it on your machine.
3. Open the simulator (should be in your start menu).

### Mac Installation ###

## Usage ##

### Arduino Code ###
First, you will need to upload navigation code to the Arduino board. You can upload the example sketch by opening the Arduino IDE and going to File > Examples > DFRTankSimulation > navigation_example
Now, upload this code to the Arduino board. Your instructor or TA will show you how to do this in class.
**Note**: The VisionSystemSimulator should be closed while uploading code to the Arduino.
Once the code has been succesfully uploaded, close the Arduino IDE

### Testing the Code ###
Now, you are ready to test the navigation code with the VisionSystemSimulator.
Run the simulator by locating it in your computer and double clicking it. If you have not created a shortcut on windows, you may have to look through your C: drive.
Then, enable all of the distance sensors that your code will be using by opening the 'Edit OSV' window and clicking on each sensor referenced in the example code to toggle it on.
Now, click on 'Select Port' and then click on the port your Arduino is connected to.
The simulated OSV will now execute the navigation code that was uploaded to it. If you want to re-run the navigation, unplug the Arduino, click 'Reset', plug the Arduino back in, and reselect the port. If you want to run the navigation again but with a different obstacle randomization, unplug the Arduino, click 'Randomize', plug the Arduino back in, and reselect the port.

## Moving off of the simulator ##
If you wish to take your simulator code and move it onto the physical tanks, there are a few basic steps to follow:
1. Switch libraries from Enes100Simulation.h to Enes100.h and from DFRTankSimulation.h to DFRTank.h (Note: If you do not already have the Enes100 library downloaded, you can download it [here](https://github.com/umdenes100/Enes100ArduinoLibrary).)
2. locate the line 'DFRTankSimulation tank;' in your code and replace it with 'DFRTank tank;'
3. Locate the line 'Enes100Simulation enes' in your code and replace it with the correct instantiation for the Enes100 object. (You can find examples in the Enes100 library examples folder)
4. The Enes100Simulation function readDistanceSensor() will not work with the new libraries. You are responsible for implementing this function yourself. 

Once you have completed these steps, you should be able to upload your navigation code to a physical tank. WARNING: Even though your code may work on the simulator, that does not nessesarily guarantee that it will work in real life. The simulator is meant to serve as a tool to assist in the programming process and is not 100% indicative of real life conditions. To ensure that your code will work on your osv, you will need to test in the real world.

## Simulator Library ##

### Purpose ###
The Simulator library serves as a bridge between the arduino and the simulator program. It is designed to mimic the API of the enes and dfr tank libraries to create as simple a transition as possible from the simulator to a physical system. The API is described below. more information about the code can be found on the github repo linked above.

### Function Definitions ###

#### DFRTankSimulation Object ####

The functions associated with the DFRTankSimulation object control the movement of the OSV. 


`void turnOffMotors()`

This function simply stops the OSV by setting both motor PWM's to zero.


`void setRightMotorPWM()`

This function sets the PWM of the tank's right motor. It accepts one argument (an integer), which should be in the range [-255, 255]

`void setLeftMotorPWM()`

This function sets the PWM of the tank's left motor. It accepts one argument (an integer), which should be in the range [-255, 255]


#### Enes100Simulation Object ####

The functions associated with the Enes100Simulation object provide information about the OSV's location, destination, and distance sensor readings. They also allow print messages to be sent to the console for debugging purposes. 


`bool retrieveDestination()`

This function retrieves the destination for the current run from the simulator, stores the destination in the destination variable, and returns true or false depending on the success of the call. This function should be encapsulated in a while loop to ensure that the OSV has retrieved the destination before begining the run.


`bool updateLocation()`

This function communicates with the simulator to retrieve the current OSV location and updates the location variable in the object. It returns true or false depending on the success of the call.


`float readDistanceSensor(int sensorIndex)`

This function reads the distance sensor on the simulator OSV and returns the distance as a float. The sensor index is a number from 0-11 as defined in the simulator 'Edit OSV' form.


`void print(msg), void println(msg)`

These functions are print messages to the console. These functions may be helping in debugging your code. 