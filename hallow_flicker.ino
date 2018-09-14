#include <NewPing.h>

int relay_1 = 2;
int vcc = 5;  //attach pin 2 to vcc
int trig = 7; // attach pin 3 to Trig
int echo = 8; //attach pin 4 to Echo
int gnd = 6;  //attach pin 5 to GND
int delays[] = {50, 100, 150, 200, 250, 300};
long dist_to_flicker = 42;
NewPing sonar(trig, echo, 100);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(vcc,OUTPUT);
  pinMode(gnd,OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(echo,INPUT);
  digitalWrite(vcc, HIGH);
  digitalWrite(gnd, LOW); 
}

void loop() {

  Serial.println("");

  unsigned int duration = sonar.ping();
  Serial.print("Duration ");
  Serial.println(duration);
  // convert the time into a distance
  unsigned int inches = sonar.convert_in(duration);
  Serial.print("Delay Variables: ");
  Serial.println(sizeof(delays) / sizeof(*delays));
  Serial.print("Distance from Sensor ");
  Serial.println(inches);
  if(inches < dist_to_flicker && inches > 2){
    random_flicker(relay_1, delays, sizeof(delays) / sizeof(*delays));
  }
  
}

long take_measurement(int trig, int echo){


  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trig, LOW);
  delayMicroseconds(3);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 
  return pulseIn(echo, HIGH);

  
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

void random_flicker(int flicker_pin, int *delay_times, int n_delays){
  
   int randomOff = random(0, n_delays-1);
   int randomOn = random(0, n_delays-1);
  
   digitalWrite(flicker_pin, HIGH);
   Serial.print("Off delay: ");
   Serial.println(delay_times[randomOff]);
   delay(delays[randomOff]);
   digitalWrite(flicker_pin, LOW);
   Serial.print("Off delay: ");
   Serial.println(delay_times[randomOn]);
   delay(delay_times[randomOn]);
}
