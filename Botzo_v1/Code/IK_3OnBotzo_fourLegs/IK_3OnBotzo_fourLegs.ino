#include <Servo.h>
#include <math.h>
#include <Arduino.h>

////////////////////////define pins for servos
#define pinFemur_FR 2
#define pinKnee_FR 3
//
#define pinFemur_FL 4
#define pinKnee_FL 5
//
#define pinFemur_BL 6
#define pinKnee_BL 7
//
#define pinFemur_BR 8
#define pinKnee_BR 9

////////////////////////define femurs varibles
Servo Femur_FR; 
Servo Knee_FR; 
// 
Servo Femur_FL; 
Servo Knee_FL; 
// 
Servo Femur_BR; 
Servo Knee_BR; 
// 
Servo Femur_BL;
Servo Knee_BL;

////////////////////////define angles varibles
double Femur_FR_ang;
double Knee_FR_ang ;
//
double Femur_FL_ang;
double Knee_FL_ang;
//
double Femur_BR_ang;
double Knee_BR_ang;
//
double Femur_BL_ang;
double Knee_BL_ang;

////////////////////////define constants
const double L1 = 8.5; // Length_femur
const double L2 = 9.5; // Length_knee
double X;
double Y;
double pi = M_PI;






void setup() {
  Serial.begin(9600);

  ////////////////////////attach servos
  Femur_FR.attach(pinFemur_FR);
  Knee_FR.attach(pinKnee_FR);
  //
  Femur_FL.attach(pinFemur_FL);
  Knee_FL.attach(pinKnee_FL);
  //
  Femur_BR.attach(pinFemur_BR);
  Knee_BR.attach(pinKnee_BR);
  //
  Femur_BL.attach(pinFemur_BL);
  Knee_BL.attach(pinKnee_BL);

  ////////////////////////rest position
  //UpdatePosition(Femur_BR, Knee_BR, 90, 90);
  //RightStep(Femur_BR, Knee_BR);
  CartesianMoveRight(Femur_BR, Knee_BR, 0, -17);
  //
  //UpdatePosition(Femur_BL, Knee_BL, 100, 30);
  //LeftStep(Femur_BL, Knee_BL);
  CartesianMoveLeft(Femur_BL, Knee_BL, 0, -17);
  //
  //UpdatePosition(Femur_FR, Knee_FR, 90, 90);
  //RightStep(Femur_FR, Knee_FR);
  CartesianMoveRight(Femur_FR, Knee_FR, 0, -17);
  //
  //UpdatePosition(Femur_FL, Knee_FL, 90, 90);
  //LeftStep(Femur_FL, Knee_FL);
  CartesianMoveLeft(Femur_FL, Knee_FL, 0, -17);

  delay(3000);
}

void loop() {
  RightStep(Femur_FR, Knee_FR);
  delay(300);
  LeftStep(Femur_BL, Knee_BL);
  delay(300);
  LeftStep(Femur_FL, Knee_FL);
  delay(300);
  RightStep(Femur_BR, Knee_BR);
  delay(300);
}



//////////////////////////////////////////////////////////////////////////////////////////LEFT
void LeftStep(Servo& Femur, Servo& Knee){
  int steps[][3] = {{-5, -17, 800}, {-10, -17, 800}, {5, -15, 800}, {5, -17, 800}, {-5, -17, 800}}; // each element is (X_cord, Y_cord, Delay/speed)
  for (int i = 0; i <= sizeof(steps) / sizeof(steps[0]); i++){
    CartesianMoveLeft(Femur, Knee, steps[i][0], steps[i][1]);
    delay(steps[i][2]);
  }
}
void CartesianMoveLeft(Servo& Femur, Servo& Knee, double X, double Y){
  // check X, Y are reachable:
  float distance = sqrt(pow(X, 2) + pow(Y, 2));
  
  if (distance <= (L1 + L2)) { // point is reacable
    double Knee_rad = acos(((X*X) + (Y*Y) - (L1*L1) - (L2*L2)) / (2 * L1 * L2)); 
    double Femur_rad = abs(atan2(Y, X) - atan2((L2 * sin(Knee_rad)), (L1 + (L2 * cos(Knee_rad)))));
    //Transform to deg
    double F_ang = degrees(Femur_rad);
    double Femur_ang = F_ang; //180 - 
    double Knee_ang = degrees(Knee_rad);
    /*
    // Print statments:
    Serial.print(X);
    Serial.print("  :   ");
    Serial.print(Y);
    Serial.print("  =>   ");
    Serial.print("  Femur_ang:  ");
    Serial.print(Femur_ang);
    Serial.print("  Knee_ang:  ");
    Serial.println(Knee_ang);
    */
    // Move servos
    UpdatePosition(Femur, Knee, Femur_ang, Knee_ang);
  }
  else {
    Serial.println("Point not reachable");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////RIGHT
void RightStep(Servo& Femur, Servo& Knee){
  int steps[][3] = {{-5, -17, 800}, {-10, -17, 800}, {5, -15, 800}, {5, -17, 800}, {-5, -17, 800}}; // each element is (X_cord, Y_cord, Delay/speed)
  for (int i = 0; i <= sizeof(steps) / sizeof(steps[0]); i++){
    CartesianMoveRight(Femur, Knee, steps[i][0], steps[i][1]);
    delay(steps[i][2]);
  }
}
void CartesianMoveRight(Servo& Femur, Servo& Knee, double X, double Y){
  // check X, Y are reachable:
  float distance = sqrt(pow(X, 2) + pow(Y, 2));
  
  if (distance <= (L1 + L2)) { // point is reacable
    double Knee_rad = acos(((X*X) + (Y*Y) - (L1*L1) - (L2*L2)) / (2 * L1 * L2)); 
    double Femur_rad = abs(atan2(Y, X) - atan2((L2 * sin(Knee_rad)), (L1 + (L2 * cos(Knee_rad)))));
    //Transform to deg
    double F_ang = degrees(Femur_rad);
    double Femur_ang = 180 - F_ang; 
    double K_ang = degrees(Knee_rad);
    double Knee_ang = 180 - K_ang;
    /*
    // Print statments:
    Serial.print(X);
    Serial.print("  :   ");
    Serial.print(Y);
    Serial.print("  =>   ");
    Serial.print("  Femur_ang:  ");
    Serial.print(Femur_ang);
    Serial.print("  Knee_ang:  ");
    Serial.println(Knee_ang);
    */
    // Move servos
    UpdatePosition(Femur, Knee, Femur_ang, Knee_ang);
  }
  else {
    Serial.println("Point not reachable");
  }
}



void UpdatePosition(Servo& Femur, Servo& Knee, double angle_femur, double angle_knee){
// MOVE TO POSITION
  Femur.write(angle_femur);
  Knee.write(angle_knee);
}




//////////////////////// Read joystick values
int readJoystick(int pin) {
  return map(analogRead(pin), 0, 1023, -100, 100);
}









//////////////////////// walking using sine wave
void WalkSineWave(Servo& Femur, Servo& Knee, double amplitude, double frequency, double offsetX, double offsetY) {
  for (double t = 0.0; t <= 2.0 * M_PI; t += 0.10) {
    double X = offsetX + amplitude * cos(frequency * t);
    double Y = offsetY + amplitude * sin(frequency * t);

    CartesianMove(Femur, Knee, X, Y);
    delay(10); // Delay, try changing for smoother motion
  }
}

//////////////////////// walking elipse motion
void WalkEllipse(Servo& Femur, Servo& Knee, double semiMajorAxis, double semiMinorAxis, double offsetX, double offsetY) {
  for (double t = 0.0; t <= 2.0 * M_PI; t += 0.10) {
    double X = offsetX + semiMajorAxis * cos(t);
    double Y = offsetY + semiMinorAxis * sin(t);

    CartesianMove(Femur, Knee, X, Y);
    delay(10); // Delay, try changing for smoother motion
  }
}

void WalkLoop(double joyX) {
  // Parameters
  double semiMajorAxis = 1.0;
  double semiMinorAxis = 1.0;
  double offsetX = 0.0;
  double offsetY = 0.0;
  int delayBetweenLegs = 1000; // Set the delay between movements for each leg

  if (joyX > 0) {
    WalkEllipse(Femur_FR, Knee_FR, semiMajorAxis, semiMinorAxis, offsetX, offsetY);
    delay(delayBetweenLegs);
  }

  if (joyX > 0) {
    WalkEllipse(Femur_FL, Knee_FL, semiMajorAxis, semiMinorAxis, offsetX, offsetY);
    delay(delayBetweenLegs);
  }

  if (joyX > 0) {
    WalkEllipse(Femur_BR, Knee_BR, semiMajorAxis, semiMinorAxis, offsetX, offsetY);
    delay(delayBetweenLegs);
  }

  if (joyX > 0) {
    WalkEllipse(Femur_BL, Knee_BL, semiMajorAxis, semiMinorAxis, offsetX, offsetY);
    delay(delayBetweenLegs);
  }
}

