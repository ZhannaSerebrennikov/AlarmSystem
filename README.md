## Alarm System Project
This is Standard Alarm project that includes Control Panel, sensors and devices wich communicate via RF.
## Multithreading:
  The ControlPanel::monitor method Start in a separate thread to continuously check if any sensor is triggered.
  Each Sensor Devices has it own thread to simulate the triggering of sensors.
## Synchronization:
  The std::mutex mtx is used in the MessageQueue class to ensure thread safety when accessing the data.
