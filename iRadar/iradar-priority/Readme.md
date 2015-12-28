On your assignment wiki page explain the differences between this version and the FCFS system (including the scheduler).
• What was affected: efficiency, stability, maintainability, etc

The Priority scheduler implementation is similar to the FCFS but each event has a priority associated with it. 

**SCHEDULER IMPLEMENTATION**
We have defined only two priority levels: High (Motor and Ultrasonic) and Low (Magnetometer and OLED). The events are randomly (to emulate a hardware request) pushed onto the event queue using a ticker/timer every 0.1sec. The interrupt request is serviced in order of priority and is handled using a priority queue implementation in c.

**FCFS Vs. PRIORITY SCHEDULING**
The priority scheduling caused delays in the Radar system as the controller is busy servicing high priority events and pushes back the low priority events. The video demonstrates that the motor and ulta events lead and the radar display is not serviced until all high priority events are processed irrespective of the order in which they are queued. This is seen as a lag in the radar display wrt the motor/ultra. Therefore in our case the system performance drops and the display is unable to keepup with radar and ultra data, missing the object detection information.

However,in some systems it is essential that the scheduling be based on priority. In cases where there are critical events that need to interrupt any ongoing task (like a reactor or process control unit), a priority system would give better stability and help achieve scheduling targets. In a system such as ours, the large amount of high priority events do not allow the low priority events to execute and hence leads to timing misses.

(Consequences of Priority: Low system performance)
## Video: https://www.youtube.com/watch?v=TVXw8hi9qRY
