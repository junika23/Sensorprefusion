TecTask IoT
=================

SensorPreFusion component (version 1.0.0)
==========================================

A component that receives continous signals from four sensors. 
Two of them are placed in front of the car, two of them are placed in the back. 
The component shall be integrated to the “DriverAssistance” ECU’s application layer. 
The physical connection shall be realized via automotive Ethernet.

Each sensor delivers the following information:
- Coordinates of a detected object with respect to the vehicle’s mass
center [Xv, Yv, Zv] in meter as a scaled 16 bit unsigend integer value, scaling factor 1/1000, the default/init value is 0xFFFF
- timestamp as 32bit unsigned integer, default/init value 0
- objectClass as 8bit unsigned integer, default/init value 0

The “SensorPreFusion” software component shall be triggered every 10ms and
reads the sensor signals from a middleware called “Runtime Environment”.

If an object has been detected twice in the same location via several sensors then 
the component shall output it’s objectClass and the timestamp of the first appearance. 
The result shall be written to the middleware.


Implementation
=================
A console application to receive multiple objects detected by the sensors and publish it to the middleware.

Usage:
SensorPreFusion

Output:
"Publishing object: <object> with timestamp: <timestamp> into the cloud"


Dependencies:
---------------------------------------------------------------------------------------------------------------------------------------
- gcc/g++ version 4.9 or above
- cmake build software
- doxygen to build the code documentation (the output documentation is already included under docs folder)

The solution has been implemented under VMWare on Windows with linux (Ubuntu variant) guest. As IDE, QtCreator has been used.


How to build
---------------------------------------------------------------------------------------------------------------------------------------
Go to the directory where main.cpp and CMakeLists.txt are located
1. mkdir build
2. cd build
3. cmake ../.
4. make

Executable should be generated under build folder and the doxygen html should be located under docs folder.


Major issues and known limitation regarding the implementation of SensorPreFusion:
---------------------------------------------------------------------------------------------------------------------------------------
<b>1) Acquiring sensor information based on periodic timer or listener</b>\n
It's unclear whether the sensor information will be received from a listener class object e.g. RuntimeSensorListener class
OR
the sensor information will be read each 10 ms using periodic timer.

On embedded real time system, the listener way implementation is probably a slightly better approach.

The algorithm to add a new sensor data into internal list or container should be fast. While adding a new sensor data, it will be
checked first whether the same object with same location is already exists in the container. If yes then the existing one will be popped up
and removed from the container. That particular object with the timestamp will be then published into some external data storage 
over the air for analytics purposes.

<b>2) Size or amount of data stored in the container</b>\n
Since we are working on embedded system, the amount of memory and local storage are limited. Therefore we need
to consider the space complexity. We could e.g. set the maximum amount of sensor data stored in the container.
Before adding a new one, we will check first whether the maximum amount is already reached, if yes then we will
delete the oldest data (from timestamp information)


Test
---------------------------------------------------------------------------------------------------------------------------------------
No unit and functional tests are implemented due to limited amount of time.