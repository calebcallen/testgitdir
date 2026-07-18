#include <SD.h> //load sd library
#include <SPI.h> //load SPI communication library
#include <LiquidCrystal.h> //loading lcd library

//creating liquid crystal object and assigning pins
LiquidCrystal LCD(10,9,5,4,3,2);

//setting ultrasonic pins
int triggerpin = 6;
int echopin = 7;

//setting sd card pins
int chipselect = 8;

//setting sd card variables
File sensordata; //object for working with file object

//setting variables
float speedofsound = 343; //meters per second
float pulsetime; 
float distance; 

void setup() {

//pinmodes and serial start and sd start
pinMode(triggerpin,OUTPUT);
pinMode(echopin,INPUT);
Serial.begin(9600);
SD.begin(chipselect); //start sd card with chipselect pin

//LCD title line printing
LCD.begin(16,2); //starting lcd and define size
LCD.setCursor(0,0); //set cursor
LCD.print("Distance:"); //printing title
}

void loop() {

//assigning file object sensordata the SD card file Distance.txt.
//Creates file if non existent, will append data to existing file if is.
//Then defines that it is writing to that file.
sensordata = SD.open("Distance.txt", FILE_WRITE);

//checks to make sure file opened on SD card and was assigned to sensordata.
//if sensordata = true run the rest of program.
//If not it will repeat opening the file until successful
if (sensordata) {

//pulsing ultrasonic sensor and assigning to pulsetime variable
digitalWrite(triggerpin,LOW);
delayMicroseconds(2);

digitalWrite(triggerpin,HIGH);
delayMicroseconds(10);

digitalWrite(triggerpin,LOW);

//convert pulsetime from micro seconds to seconds
pulsetime = pulseIn(echopin,HIGH); //micro seconds
pulsetime = pulsetime / 1000000.; //seconds

//work out distance
distance = (speedofsound * pulsetime)/2;

//print distance
Serial.print("Distance to target: ");
Serial.print(distance);
Serial.println((" M"));

//Print to LCD
LCD.setCursor(0,1); //set cursor
LCD.print("                "); //clear row
LCD.setCursor(0,1); //set cursor
LCD.print(distance); //print distance
LCD.print(" M"); //print unit

//printing distance to SD card then closing file
sensordata.print(distance);
sensordata.println(" M");
sensordata.close();

//delay for legibility
delay(500);
}

}
