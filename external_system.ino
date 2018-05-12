// Xbee Testing
#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
int pass = 0;
double p1_d = -1.0;
double p2_d = -1.0;
double p3_d = -1.0;
double p4_d = -1.0;
double b_d = -1.0;
int offside = 0;
SoftwareSerial xbee = SoftwareSerial(rxPin, txPin);
void setup ()
{
pinMode(rxPin, INPUT);
pinMode(txPin, OUTPUT);
xbee.begin(9600);
Serial.begin(9600);
Serial.println("Starting...");
}
void loop ()
{
 char random1;
 char random2;
 char random3;
 char random4;
 char random5;
 char random6;
 pass = 0;
 offside = 0;
//if (xbee.available()){
 while(xbee.available() == 0)
 {
 }
 random1 = (char)xbee.read();
 if(random1 == 'B')
 {
 while(xbee.available() == 0)
 {
 }
 random2 = (char)xbee.read();
 if(random2 == '-')
 {
 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();
 if(random3 == 'P')
 {
 Serial.println("Good Pass");
 pass = 1;
 }
 else
 {
 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();
 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();

 b_d = (((double)random3)-48.0);

 while(xbee.available() == 0)
 {
 }
 random4 = (char)xbee.read();
 if(random4 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 b_d = b_d +(((double)random6 - 48.0)/10.0);
 // code for single digit
 }
 else
 {
 b_d = b_d * 10.0;
 b_d = b_d + (((double)random4)-48.0);
 while(xbee.available() == 0)
 {
 }
 random5 = (char)xbee.read();
 if(random5 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 b_d = b_d +(((double)random6 - 48.0)/10.0);
 }
 else
 {//This should never happen}
 // code for double digit
 }

 //Record the distance of Player1

 // Use the distance from the ball if useful
 }
 }
 }
 else if (random1 == '1')
 {
 while(xbee.available() == 0)
 {
 }
 random2 = (char)xbee.read();
 if(random2 == '-')
 {

 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();
 p1_d = (((double)random3)-48.0);

 while(xbee.available() == 0)
 {
 }
 random4 = (char)xbee.read();
 if(random4 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p1_d = p1_d +(((double)random6 - 48.0)/10.0);
 // code for single digit
 }
 else
 {
 p1_d = p1_d * 10.0;
 p1_d = p1_d + (((double)random4)-48.0);
 while(xbee.available() == 0)
 {
 }
 random5 = (char)xbee.read();
 if(random5 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p1_d = p1_d +(((double)random6 - 48.0)/10.0);
 }
 else
 {
 //This should never happen
 }

 // code for double digit
 }

 //Record the distance of Player1
 }
 Serial.print("P1 - "); // Debugging
 Serial.println(p1_d); // Statements

 }
 else if (random1 == '2')
 {
 while(xbee.available() == 0)
 {
 }
 random2 = (char)xbee.read();
 if(random2 == '-')
 {

 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();
 p2_d = (((double)random3)-48.0);

 while(xbee.available() == 0)
 {
 }
 random4 = (char)xbee.read();
 if(random4 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p2_d = p2_d +(((double)random6 - 48.0)/10.0);
 // code for single digit
 }
 else
 {
 p2_d = p2_d * 10.0;
 p2_d = p2_d + (((double)random4)-48.0);
 while(xbee.available() == 0)
 {
 }
 random5 = (char)xbee.read();
 if(random5 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p2_d = p2_d +(((double)random6 - 48.0)/10.0);
 }
 else
 {
 //This should never happen }

 // code for double digit
 }

 //Record the distance of Player2
 }
 Serial.print("P2 - "); // Debugging
 Serial.println(p2_d); // Statements
 }
 else if (random1 == '3')
 {
 while(xbee.available() == 0)
 {
 }
 random2 = (char)xbee.read();
 if(random2 == '-')
 {

 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();
 p3_d = (((double)random3)-48.0);

 while(xbee.available() == 0)
 {
 }
 random4 = (char)xbee.read();
 if(random4 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p3_d = p3_d +(((double)random6 - 48.0)/10.0);
 // code for single digit
 }
 else
 {
 p3_d = p3_d * 10.0;
 p3_d = p3_d + (((double)random4)-48.0);
 while(xbee.available() == 0)
 {
 }
 random5 = (char)xbee.read();
 if(random5 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p3_d = p3_d +(((double)random6 - 48.0)/10.0);
 }
 else
 {
 //This should never happen
 }

 // code for double digit
 }

 //Record the distance of Player3
 }
 Serial.print("P3 - "); // Debugging
 Serial.println(p3_d); // Statements

 }
 else if (random1 == '4')
 {
 while(xbee.available() == 0)
 {
 }
 random2 = (char)xbee.read();
 if(random2 == '-')
 {

 while(xbee.available() == 0)
 {
 }
 random3 = (char)xbee.read();
 p4_d = (((double)random3)-48.0);

 while(xbee.available() == 0)
 {
 }
 random4 = (char)xbee.read();
 if(random4 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p4_d = p4_d +(((double)random6 - 48.0)/10.0);
 // code for single digit
 }
 else
 {
 p4_d = p4_d * 10.0;
 p4_d = p4_d + (((double)random4)-48.0);
 while(xbee.available() == 0)
 {
 }
 random5 = (char)xbee.read();
 if(random5 == '.')
 {
 while(xbee.available() == 0)
 {
 }
 random6 = (char)xbee.read();
 p4_d = p4_d +(((double)random6 - 48.0)/10.0);
 }
 else
 {
 //This should never happen
 }

 // code for double digit
 }

 //Record the distance of Player4
 }

 Serial.print("P4 - "); // Debugging
 Serial.println(p4_d); // Statements
 }

 if(pass == 1)
 {
 if((p1_d > 0.0) && (p2_d > 0.0) && (p3_d > 0.0) && (p4_d > 0.0))
 {

 if((p1_d > p2_d)&&(p1_d > p3_d) && (p4_d < p2_d) && (p4_d < p3_d)) // Pass from P1 to P4
 {
 offside = 1; // OFFSIDE detected
 }
 else if ((p4_d > p2_d)&&(p4_d > p3_d) && (p1_d < p2_d) && (p1_d < p3_d)) // Pass from P4 to P1
 {
 offside = 1;// OFFSIDE detected
 }
 // Check for OFFSIDES
 }
 }
if(offside == 1)
{
 Serial.println("OFFSIDE HAS BEEN DETECTED, YAYYYY !!!!!!!!"); // Make the announcement
}
//Serial.print("OnePacketDone");
//}
}
