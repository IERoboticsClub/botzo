#include <Servo.h>

//define joystick pins (analog)
int joyX = 0;

//variable to read the values from the analog pins
int joyValX;

Servo Femur_TopLeft;
Servo Knee_TopLeft;
Servo Femur_TopRight;
Servo Knee_TopRight;
Servo Femur_BottomLeft;
Servo Knee_BottomLeft;
Servo Femur_BottomRight;
Servo Knee_BottomRight;

int posFemur_TopLeft = 135;         //2
int posKnee_TopLeft = 90;          //3
int posFemur_TopRight= 45;         //4
int posKnee_TopRight = 90;         //5
int posFemur_BottomLeft = 135;      //6
int posKnee_BottomLeft = 90;       //7
int posFemur_BottomRight = 45;     //8
int posKnee_BottomRight = 90;      //9

void setup() {
  Serial.begin(9600);
  
  Femur_TopLeft.attach(2);  
  Knee_TopLeft.attach(3);  
  Femur_TopRight.attach(4);
  Knee_TopRight.attach(5);
  Femur_BottomLeft.attach(6);  
  Knee_BottomLeft.attach(7);  
  Femur_BottomRight.attach(8);
  Knee_BottomRight.attach(9);

  Femur_TopLeft.write(posFemur_TopLeft);
  Knee_TopLeft.write(posKnee_TopLeft);
  Femur_TopRight.write(posFemur_TopRight);
  Knee_TopRight.write(posKnee_TopRight);
  Femur_BottomLeft.write(posFemur_BottomLeft);
  Knee_BottomLeft.write(posKnee_BottomLeft);
  Femur_BottomRight.write(posFemur_BottomRight);
  Knee_BottomRight.write(posKnee_BottomRight);

  delay(5000);
}

void loop() 
{
  // read the value of joystick (btw 0-1023)
  joyValX = analogRead(joyX);
  joyValX = map(joyValX, 0, 1023, 0, 180); //transform analogue in angle for servos
  if (joyValX > 100)
  {
    ONE_STEP(Femur_TopRight, Knee_TopRight, Femur_BottomLeft, Knee_BottomLeft);
    ONE_STEP(Femur_BottomRight, Knee_BottomRight, Femur_TopLeft, Knee_TopLeft);
  }
}



// FUNCTIONS
void ONE_STEP(Servo &FemurRight, Servo &KneeRight, Servo &FemurLeft, Servo &KneeLeft)
{
  //Step 1
  int pos_FemurRight = 55;
  int pos_KneeRight = 70;
  int pos_FemurLeft = 125;
  int pos_KneeLeft = 110;
  FemurLeft.write(pos_FemurLeft);
  KneeLeft.write(pos_KneeLeft);
  FemurRight.write(pos_FemurRight);
  KneeRight.write(pos_KneeRight);
  delay(100);

  //Step 2
  pos_FemurRight = 25;
  pos_FemurLeft = 155;
  FemurLeft.write(pos_FemurLeft);
  FemurRight.write(pos_FemurRight);
  delay(100);


  //Step 3
  pos_KneeRight = 170;
  pos_KneeLeft = 10;
  KneeLeft.write(pos_KneeLeft);
  KneeRight.write(pos_KneeRight);
  delay(100);


  //Step 4
  pos_FemurRight = 60;
  pos_FemurLeft = 120;
  FemurLeft.write(pos_FemurLeft);
  FemurRight.write(pos_FemurRight);
  delay(100);


  //Step 5
  pos_KneeRight = 45;
  pos_KneeLeft = 135;
  KneeLeft.write(pos_KneeLeft);
  KneeRight.write(pos_KneeRight);
  delay(100);


  //Step 6
  pos_FemurRight = 55;
  pos_KneeRight = 70;
  pos_FemurLeft = 125;
  pos_KneeLeft = 110;
  FemurLeft.write(pos_FemurLeft);
  KneeLeft.write(pos_KneeLeft);
  FemurRight.write(pos_FemurRight);
  KneeRight.write(pos_KneeRight);
  delay(500);
}
