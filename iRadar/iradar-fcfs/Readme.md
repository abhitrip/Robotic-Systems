We wire the MBED, OLED display, motor, ultrasonic and magnetometer sensor to create a radar system. 

The following are the details of the **SETUP**:

1. The platform is rotated 0-180degree with the sensor mounted on top. The center is taken as the reference north (0degree).

2. The OLED screen display the Radar image with the sweep and the object represented as collection of pixels as blip.

3. The heading is derived from the motor steps/angle as the magnetometer readings are displaced by the motor magnetic field. The heading is calibrated to north as 0degree. The radar sweeps +90 in anticlockwise and -90 in clockwise direction giving a complete 180degree sweep. The real time position is displayed on the top right corner of the screen.

4. The blip is constructed by a 2x2 pixel. As the objects are of some thickness, the blip is seen as a series of these 2x2 pixels. Bigger objects produces more reflections and hence are seen as long series of blips on the display. The blip is retained until the next sweep.

The system **PARAMETERS** are as follows:

a. Radius of arc of display circle: **r=63pixel** (The maximum possible semicircle is drawn on screen). Succesive concentric circles are drawn with **r'=nr/4**.

b. Maximum sense distance: The utlra-sonic sensor is able to sense objects as far as 4m, but for practical purposes the system has been limited to **20cm** objects.

c. The depth is calculated as **d/20*63**, where d is the actual distance measured by the sensor.

**IMPLEMENTATION:**

This code implements a First come First Serve (FCFS) protocol for task management. The tasks which request a service are served in order of filling the request. All the system events (motor, ultrasonic sensor, magnetometer and the led display) have equal priority (hard-coded 'low' by default).

**PROS & CONS**:
The FCFS provides a simple and quick way to implement a task manager. FCFS works well if there are no critical tasks that are expected to interrupt the system and all events carry equal weight for exectution i.e. a sequential service type. The drawback of such a system is the case where there are high priority events that may need to be addressed by the system immediately. Such systems are better implemented with a 'priority' based schemes.
Example: Our system executes Motor-->Ultra-->LED-->Magneto-->... repetitivly on a first come first serve basis. The system is at risk of lossing some data/infomation in case one of the devices is ready to sent/receive data while the controller is busy executing other lower priority tasks.

## Video: https://www.youtube.com/watch?v=We3mmS9L6GY
