# Offside-Detection-System

This automatic offside detection system can be used during soccer matches to know instantaneously whether an offside foul has occurred. The design of this project included attaching a wireless circuit that players can wear on their arms. This circuit on the players wirelessly sends their respective distance from the end line that will help in the judgment of an offside foul. The soccer ball also has a circuit implanted in it that sends its distance from the end line as well as its acceleration data. The external system uses this data to determine if an offside foul has occurred.

# Design

Wireless Transmitter - XBee Pro S1
Microcontroller - Arduino Pro Mini 328 
Accelerometer - ADXL335
GPS Module - FGPMMOPA6H

# Code

There are 3 parts to the Arduino code - player, ball, and external software. 
Install the Arduino IDE to run the code (https://www.arduino.cc/en/Main/Donate)
