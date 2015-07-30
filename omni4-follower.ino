//

#define SIZE 14
#define CUTOFF 250
#include <Servo.h>
Servo myservoA; 
Servo myservoB;  
Servo myservoC;
Servo myservoD;
int TRUE = HIGH;
int FALSE = LOW;
int black;
int blacks = 0;
int CENTER = 13;
int CLOCKWISE = 14;
int COUTERCLOCKWISE = 13;
int find = 0;
int i = 0;
int inside = 0;
int loops = 0;
int outside = 0;
int STOP = 15;
int quit = FALSE;
long time;
int debug[2] = {0,1};
int ledPins[SIZE] = {0,31,32,33,34,35,36,37,38,39,40,41,42,43};
int lightLevel[SIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
int list[37] = {0,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12};

void setup() {
  Serial.begin(115200);
  myservoA.attach(22);  
  myservoB.attach(23);
  myservoC.attach(24);
  myservoD.attach(25);
  for (int i = 1; i < SIZE; i++) {
    pinMode(lightLevel[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = 1; i < 4; i++) {
    digitalWrite(ledPins[1], HIGH);
    delay (200);
    digitalWrite(ledPins[1], LOW);
    delay (200);
  }
  digitalWrite(ledPins[1], HIGH);
  delay (3000);
  scan();
  time = millis();
  Serial.println(" ");
  Serial.println ("Point 0 - start");
  Serial.print("time = ");
  Serial.println(time);
  sensors ();
  //
  // find start point
  //
  find = 0;
  do {
    Direction(4);
    if (analogRead(CENTER) > CUTOFF && find == 0){
      find = 1;
    }
    else if (analogRead(CENTER) < CUTOFF && find == 1) {
      find = 2;
    }
  }
  while (find != 2);
  Direction(STOP);
  delay(5);
  Serial.println (" ");
  Serial.println("Point 1 - moved into position, find initial inside outside");
  scan();
  sensors();
  
//
// find inside
//
  i = 1;
  quit = FALSE;
  do {
    if (lightLevel[list[19-i]] < CUTOFF) {
      inside = list[19-i];
      i = i + 1;
    }
    else {
      quit = TRUE;
    }    
  }
  while (quit == FALSE);
  outside = list[inside+9];
  Serial.print("inside = ");
  Serial.println(inside);
  Serial.print("outside = ");
  Serial.println(outside);
}
//---------------------------------end of Void Setup----------------------------------

void loop () {
  //
  // Move inside direction
  //
  loops =  0;
  if (analogRead(outside) < CUTOFF && analogRead(CENTER) < CUTOFF) {
    Direction(inside);
    lightLevel[outside] = analogRead(outside);
    lightLevel[CENTER] = analogRead(CENTER);
    while (lightLevel[outside] < CUTOFF && lightLevel[CENTER] < CUTOFF) {
      lightLevel[outside] = analogRead(outside);
      lightLevel[CENTER] = analogRead(CENTER);
      loops = loops + 1;
    }
  }
  Direction(STOP);
  Serial.println(" ");
  Serial.print("lightLevel[outside] = ");
  Serial.println(lightLevel[outside]);
  Serial.print("lightLevel[CENTER] = ");
  Serial.println(lightLevel[CENTER]);
  Serial.println("Point 2 - moved inside direction - normal move");
  Serial.print("loops = ");
  Serial.println(loops);
  //
  // Move outside direction
  //
  loops = 0;
  if (analogRead(CENTER) < CUTOFF) {
    Direction(outside);
    while (analogRead(CENTER) < CUTOFF) {
      loops = loops + 1;
    }
  }
  Direction(STOP);
  Serial.println(" ");
  Serial.println ("Point 11 - moved outside direction - normal move");
  Serial.print("loops = ");
  Serial.println(loops);
  scan();
  sensors();
  //
  // find new inside
  //
  findInsideOutside();
  loops = 0;
  if (analogRead(CENTER) >= CUTOFF) {
    Direction(list[inside+1]);
    while (analogRead(CENTER) >= CUTOFF) {
      loops = loops + 1;
    }
    Serial.println(" ");
    Serial.println ("Point 13 - moved CENTER off line");
    Serial.print("loops = ");
    Serial.println(loops);
    scan();
    sensors();
  }
}
//---------------------------------end of void loop----------------------------------

    
void Direction (int x) {
  switch (x) {
  case 1:
    digitalWrite(ledPins[1], HIGH);
    myservoA.write(90);     
    myservoB.write(180);
    myservoC.write(90);
    myservoD.write(0);
    break;
    
  case 2:
    digitalWrite(ledPins[2], HIGH);
    myservoA.write(75);     
    myservoB.write(180);
    myservoC.write(107);
    myservoD.write(0);
    break;
  
  case 3:
    digitalWrite(ledPins[3], HIGH);
    myservoA.write(0);     
    myservoB.write(110);
    myservoC.write(180);
    myservoD.write(70);
    break;
  
  case 4:
    digitalWrite(ledPins[4], HIGH);
    myservoA.write(0);     
    myservoB.write(90);
    myservoC.write(180);
    myservoD.write(90);
    break;
  
  case 5:
    digitalWrite(ledPins[5], HIGH);
    myservoA.write(0);     
    myservoB.write(60);
    myservoC.write(180);
    myservoD.write(115);
    break;
  
  case 6:
    digitalWrite(ledPins[6], HIGH);
    myservoA.write(70);     
    myservoB.write(0);
    myservoC.write(110);
    myservoD.write(180);
    break;
  
  case 7:
    digitalWrite(ledPins[7], HIGH);
    myservoA.write(90);     
    myservoB.write(0);
    myservoC.write(90);
    myservoD.write(180);
    break;
  
  case 8:
    digitalWrite(ledPins[8], HIGH);
    myservoA.write(105);     
    myservoB.write(0);
    myservoC.write(75);
    myservoD.write(180);
    break;
  
  case 9:
    digitalWrite(ledPins[9], HIGH);
    myservoA.write(180);     
    myservoB.write(70);
    myservoC.write(0);
    myservoD.write(110);
    break; 
  
  case 10:
    digitalWrite(ledPins[10], HIGH);
    myservoA.write(180);     
    myservoB.write(90);
    myservoC.write(0);
    myservoD.write(90);
    break; 
  
  case 11:
    digitalWrite(ledPins[11], HIGH);
    myservoA.write(180);     
    myservoB.write(111);
    myservoC.write(0);
    myservoD.write(70);
    break;
  
  case 12:
    digitalWrite(ledPins[12], HIGH);
    myservoA.write(110);     
    myservoB.write(180);
    myservoC.write(70);
    myservoD.write(0);
    break;
  
  case 13: //turn counterclockwise
    digitalWrite(ledPins[13], HIGH);
    myservoA.write(0);     
    myservoB.write(0);
    myservoC.write(0);
    myservoD.write(0);
    break;
 
  case 14: //turn clockwise
    digitalWrite(ledPins[13], HIGH);
    myservoA.write(180);     
    myservoB.write(180);
    myservoC.write(180);
    myservoD.write(180);
    break;
    
  case 15: //stop
    digitalWrite(ledPins[13], HIGH);
    myservoA.write(90);     
    myservoB.write(90);
    myservoC.write(90);
    myservoD.write(90);
    break;
  default:
    Serial.println ("No Case Found In Direction");
  }
} 
//---------------------------------end of Direction----------------------------------

void findInsideOutside() {
  //
  // FIND NEAREST blacks
  //
  if (lightLevel[inside] >= CUTOFF) {
    black = inside;
  }
  else if (lightLevel[list[inside+1]] >= CUTOFF){
    black = list[inside+1];
  }
  else if (lightLevel[list[inside+11]] >= CUTOFF){
    black = list[inside+11];
  }
  else if (lightLevel[list[inside+2]] >= CUTOFF){
    black = list[inside+2];
  }
  else if (lightLevel[list[inside+10]] >= CUTOFF){
    black = list[inside+10]; 
  }
  else if (lightLevel[list[inside+3]] >= CUTOFF){
    black = list[inside+3];
  }
  else if (lightLevel[list[inside+9]] >= CUTOFF){
    black = list[inside+9];
  }
  else if (lightLevel[list[inside+4]] >= CUTOFF){
    black = list[inside+4];
  }
  else if (lightLevel[list[inside+8]] >= CUTOFF){
    black = list[inside+8];
  }
  else if (lightLevel[list[inside+5]] >= CUTOFF){
    black = list[inside+5];
  }
  else if (lightLevel[list[inside+7]] >= CUTOFF){
    black = list[inside+7];
  }
  else if (lightLevel[list[inside+6]] >= CUTOFF){
    black = list[inside+6];
  }
  else {
    Direction(STOP);
  }
  for (i = 1; i < 12; i++){
    if (lightLevel[list[black + i]] < CUTOFF){
      inside = list[black + i];
      break;
    }  
  }
  outside = list[inside+9];
  Serial.println(" ");
  Serial.print("inside = ");
  Serial.println(inside);
  Serial.print("outside = ");
  Serial.println(outside);
}
//---------------------------------end of findInsideOutside-------------------------

void scan () {
  for (int i = 1; i < SIZE; i++) {
    digitalWrite(ledPins[i], LOW);
    lightLevel[i] = analogRead(i);
  }
}

//---------------------------------end of Scan---------------------------------------

void sensors () {
  blacks = 0;
  for (int i = 1; i < SIZE; i++) {
    if (lightLevel[i] > CUTOFF) {
      blacks = blacks + 1;
    }
  Serial.print(lightLevel[i]);
  Serial.print(", ");
  }
  Serial.println(" ");
  Serial.print("Number of blacks = ");
  Serial.println(blacks);
  for (int i = 1; i < SIZE; i++) {
    if (lightLevel[i] > CUTOFF) {
      Serial.print(i);
      Serial.print(", ");
    }
  }
  Serial.println(" ");
}
//---------------------------------end of sensors------------------------------------
