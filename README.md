# VisionSystemSim #

## Setup ##
To run the Vision System Simulator, you will need four things:
1. The Arduino IDE, available [here](https://www.arduino.cc/en/Main/Software#download). Follow the instructions on the website to download the IDE.
2. The Arduino Library that interfaces with the simulator. You will use this library to control the simulated OSV. It comes with an example sketch to get you started. To download the library, go to [this Github repository](https://github.com/umdenes100/SimulatorArduinoLibrary) and click on the green button that says 'Clone or Download', then click 'Download ZIP'.  Open the Arduino IDE and install the library by going to Sketch > Include Library > Add .ZIP Library and selecting the downloaded file.
3. The VisionSystemSimulator, available for Windows and MacOS **todo: add link here**
4. An Arduino board and USB cable. Your instructor will provide these materials to you.

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

### Moving off of the simulator ###
If you wish to take your simulator code and move it onto the physical tanks, there are a few basic steps to follow:
1. Switch library from simulation.h to enes100.h and DFRTank.h.
2. locate the line 'DFRTankSimulation tank;' in your code and replace it with 'DFRTank tank;'
3. create the enes object as defined in the Enes100 library.
4. replace the instance of 'tank.retrieveDestination()' with 'enes.retrieveDestination()'.
5. replace all instances of 'tank.updateLocation()' with 'enes.updateLocation()'.
6. replace all instances of 'tank.location' and 'tank.destination' with 'enes.location' and 'enes.destination'.
7. replace all instances of 'tank.print' with 'enes.print'.
8. re-implement the distance sensor function on your own.

Once you have completed these steps, you should be able to upload your navigation code to a physical tank. WARNING: Even though your code may work on the simulator, that does not nessesarily guarantee that it will work in real life. The simulator is meant to serve as a tool to assist in the programming process and is not 100% indicative of real life conditions. To ensure that your code will work on your osv, you will need to test in the real world.

## Simulator Library ##

### Purpose ###
The Simulator library serves as a bridge between the arduino and the simulator program. It is designed to mimic the API of the enes and dfr tank libraries to create as simple a transition as possible from the simulator to a physical system. The API is described below. more information about the code can be found on the github repo linked above.

### Function Definitions ###
`void turnOffMotors()`

This function simply stops the OSV. It can and should be used when the OSV arrives at the destination.

`void setRightMotorPWM(), void setLeftMotorPWM()`

These functions set the PWM of the right and left motors. They can be used to manuver the OSV as needed.

`bool retrieveDestination()`

This function retrieves the destination for the current run from the simulator, stores the destination in the destination variable, and returns true or false depending on the success of the call. This function should be encapsulated in a while loop to ensure that the OSV has retrieved the destination before begining the run.

`bool updateLocation()`

This function communicates with the simulator to retrieve the current OSV location and updates the location variable in the object. It returns true or false depending on the success of the call.

`float readDistanceSensor(int sensorIndex)`

This function reads the distance sensor on the simulator OSV and returns the distance as a float. The sensor index is a number from 0-11 as defined in the simulator 'Edit OSV' form.

`void print(msg), void println(msg)`

These functions are provided to mimic the enes library but are not nessesary for the simulator. When switching to a physical system, if regular print statements are used, you should switch them to enes.print statements.