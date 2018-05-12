#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <math.h>
const String Fixed_Point1 = "N40 06.6979, W088 13.6494";
const String Fixed_Point2 = "N40 06.7023, W088 13.6455";
const float deg2rad = 0.01745329251994;
#define xbeerxPin 2
#define xbeetxPin 3
const float rEarth = 6371000.0;
SoftwareSerial mySerial = SoftwareSerial(5, 4);
SoftwareSerial xbee = SoftwareSerial(xbeerxPin, xbeetxPin);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO true
boolean usingInterrupt = true;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy
void setup()
{
pinMode(xbeerxPin, INPUT);
pinMode (xbeetxPin, OUTPUT);
xbee.begin(9600);
Serial.begin(9600);
mySerial.begin(9600);
Serial.println("Adafruit GPS library basic test!");
GPS.begin(9600);
GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
GPS.sendCommand(PGCMD_ANTENNA);
useInterrupt(usingInterrupt);
delay(1000);
mySerial.println(PMTK_Q_RELEASE);
}
// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
//while(mySerial.available())
//{
char c = GPS.read();
#ifdef UDR0
if (GPSECHO)
if (c) UDR0 = c;
#endif
}
void useInterrupt(boolean v) {
if (v) {
// Timer0 is already used for millis() - we'll just interrupt somewhere
// in the middle and call the "Compare A" function above
OCR0A = 0xAF;
TIMSK0 |= _BV(OCIE0A);
usingInterrupt = true;
} else {
// do not call the interrupt function COMPA anymore
TIMSK0 &= ~_BV(OCIE0A);
usingInterrupt = false;
}
}
uint32_t timer = millis();
void loop() // run over and over again
{
if (! usingInterrupt) {
while(mySerial.available())
{
// read data from the GPS in the 'main loop'
char c = GPS.read();
if (GPSECHO)
if (c) Serial.print(c);
}

}
if (GPS.newNMEAreceived()) {
if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
return; // we can fail to parse a sentence in which case we should just wait for another
}
// if millis() or timer wraps around, we'll just reset it
if (timer > millis()) timer = millis();
// approximately every 2 seconds or so, print out the current stats
if (millis() - timer > 1000) {
timer = millis(); // reset the timer
Serial.print("\nTime: ");
Serial.print(GPS.hour, DEC); Serial.print(':');
Serial.print(GPS.minute, DEC); Serial.print(':');
Serial.print(GPS.seconds, DEC); Serial.print('.');
Serial.println(GPS.milliseconds);
Serial.print("Date: ");
Serial.print(GPS.day, DEC); Serial.print('/');
Serial.print(GPS.month, DEC); Serial.print("/20");
Serial.println(GPS.year, DEC);
Serial.print("Fix: "); Serial.print((int)GPS.fix);
Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
//xbee.println("Code right before checking for fix");
if (GPS.fix) {
//xbee.println("Yay! GPS just got a fix");
Serial.println("Yay! GPS just got a fix");
String Point1 = Fixed_Point1;
String Point2 = Fixed_Point2;
float range1 = haversine(string2lat(Point1), string2lon(Point1), string2lat(Point2), string2lon(Point2));
Serial.print("range1 is : ");
Serial.println(range1);
 
if((((String)GPS.lat == "N") || ((String)GPS.lat == "S")) && (((String)GPS.lon == "E") ||((String)GPS.lon
== "W")) && ((GPS.latitude > 4000.0)&&(GPS.latitude < 4010.0)) && ((GPS.longitude >
8800.0)&&(GPS.longitude < 8820.0)))
{

Point2 = gps2string ((String) GPS.lat, GPS.latitude, (String) GPS.lon, GPS.longitude);
Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
Serial.print(", ");
Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
Serial.print("Current position calculated using gps2string function is : ");
Serial.println(Point2);
float range2 = haversine(string2lat(Point1), string2lon(Point1), string2lat(Point2), string2lon(Point2));
Serial.print("range2 is : ");
Serial.println(range2);
Point1 = Fixed_Point2;
float range3 = haversine(string2lat(Point1), string2lon(Point1), string2lat(Point2), string2lon(Point2));
Serial.print("range3 is : ");
Serial.println(range3);
//calculates s
float s = (range1 + range2 + range3)/(2.0);
float Area = sqrt(s*(s-range1)*(s-range2)*(s-range3));
float Height = (Area * (2.0))/(range1);

if((Height > 0.0) && ( Height < 50.0))
{
xbee.print('\n');
xbee.print("4-"); // CHANGE for different players
xbee.println(Height);
xbee.println("m");
//xbee.print("Speed (knots): "); xbee.println(GPS.speed);
}
Serial.print("Height is : ");
Serial.println(Height);
double final_height = (double) Height;
Serial.print("Height: "); Serial.println(Height);
Serial.print("Location: ");
Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
Serial.print(", ");
Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
Serial.print("Speed (knots): "); Serial.println(GPS.speed);
 Serial.print("Angle: "); Serial.println(GPS.angle);
Serial.print("Altitude: "); Serial.println(GPS.altitude);
Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
}
}
}
}
String int2fw (int x, int n) {
// returns a string of length n (fixed-width)
String s = (String) x;
while (s.length() < n) {
s = '0' + s;
}
return s;
};
String gps2string (String lat, float latitude, String lon, float longitude) {
// returns "Ndd mm.mmmm, Wddd mm.mmmm";
int dd = (int) latitude/100;
int mm = (int) latitude % 100;
int mmmm = (int) round((10000 * (latitude - floor(latitude))));
String gps2lat = lat + int2fw(dd, 2) + " " + int2fw(mm, 2) + "." + int2fw(mmmm, 4);
dd = (int) longitude/100;
mm = (int) longitude % 100;
mmmm = (int) round((10000 * (longitude - floor(longitude))));
String gps2lon = lon + int2fw(dd, 3) + " " + int2fw(mm, 2) + "." + int2fw(mmmm, 4);
String myString = gps2lat + ", " + gps2lon;
return myString;
};
float string2lat (String myString) {
// returns radians: e.g. String myString = "N38 58.8921, W076 29.1771";
float lat = ((myString.charAt(1) - '0') * 10.0) + (myString.charAt(2) - '0') * 1.0 + ((myString.charAt(4) - '0')
/ 6.0) + ((myString.charAt(5) - '0') / 60.0) + ((myString.charAt(7) - '0') / 600.0) + ((myString.charAt(8) - '0') /
6000.0) + ((myString.charAt(9) - '0') / 60000.0) + ((myString.charAt(10) - '0') / 600000.0);
//Serial.print("float lat: ");
//Serial.println(lat);
lat *= deg2rad;
if (myString.charAt(0) == 'S')
lat *= -1; // Correct for hemisphere
return lat;
};
float string2lon (String myString) {
// returns radians: e.g. String myString = "N38 58.8921, W076 29.1771";
float lon = ((myString.charAt(14) - '0') * 100.0) + ((myString.charAt(15) - '0') * 10.0) +
(myString.charAt(16) - '0') * 1.0 + ((myString.charAt(18) - '0') / 6.0) + ((myString.charAt(19) - '0') / 60.0) +
((myString.charAt(21) - '0') / 600.0) + ((myString.charAt(22) - '0') / 6000.0) + ((myString.charAt(23) - '0') /
60000.0) + ((myString.charAt(24) - '0') / 600000.0);
//Serial.print("float lon: ");
//Serial.println(lon);
lon *= deg2rad;
if (myString.charAt(13) == 'W')
lon *= -1; // Correct for hemisphere
return lon;
};
float haversine (float lat1, float lon1, float lat2, float lon2) {
// returns the great-circle distance between two points (radians) on a sphere
float h = sq((sin((lat1 - lat2) / 2.0))) + (cos(lat1) * cos(lat2) * sq((sin((lon1 - lon2) / 2.0))));
float d = 2.0 * rEarth * asin (sqrt(h));
//Serial.println(d);
return d;
};
