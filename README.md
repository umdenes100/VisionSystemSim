# VisionSystemSim

## Setup
To run the Vision System Simulator, you will need four things:
    1. The Arduino IDE, available [here](https://www.arduino.cc/en/Main/Software#download). Follow the instructions on the website to download the IDE.
    2. The Arduino Library that interfaces with the simulator. You will use this library to control the simulated OSV. It comes with an example sketch to get you started. To download the library, go to [this Github repository](https://github.com/umdenes100/SimulatorArduinoLibrary) and click on the green button that says 'Clone or Download', then click 'Download ZIP'.  Open the Arduino IDE and install the library by going to Sketch > Include Library > Add .ZIP Library and selecting the downloaded file.
    3. The VisionSystemSimulator, available for Windows and MacOS **todo: add link here**
    4. An Arduino board and USB cable. Your instructor will provide these materials to you.

## Usage

### Arduino Code
First, you will need to upload navigation code to the Arduino board. You can upload the example sketch by opening the Arduino IDE and going to File > Examples > DFRTankSimulation > navigation_example
Now, upload this code to the Arduino board. Your instructor or TA will show you how to do this in class.
**Note**: The VisionSystemSimulator should be closed while uploading code to the Arduino.
Once the code has been succesfully uploaded, close the Arduino IDE

### Testing the Code
Now, you are ready to test the navigation code with the VisionSystemSimulator.
Open the VisionSystemSimulator by double-clicking on VisionSystemSim.exe
Then, enable all of the distance sensors that your code will be using by opening the 'Edit OSV' window and clicking on each sensor to toggle it on.
Now, click on 'Select Port' and then click on the port your Arduino is connected to.
The simulated OSV will now execute the navigation code that was uploaded to it. If you want to re-run the navigation, unplug the Arduino, click 'Reset', plug the Arduino back in, and reselect the port. If you want to run the navigation again but with a different obstacle randomization, unplug the Arduino, click 'Randomize', plug the Arduino back in, adn reselect the port.


