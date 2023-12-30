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
const double L1 = 8.2; // Length_femur
const double L2 = 9.5; // Length_knee
double X;
double Y;
double pi = M_PI;
int steps[][3] = {{-4, -14, 400}, {-8, -14, 400}, {-3, -12, 200}, {0, -14, 400}, {-4, -14, 400}};
// each element is (X_cord, Y_cord, Delay/speed) + first one is rest pos
size_t numSteps = sizeof(steps) / sizeof(steps[0]);







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
  restposleft(Femur_BL, Knee_BL, steps, numSteps);
  restposleft(Femur_FL, Knee_FL, steps, numSteps);
  restposright(Femur_BR, Knee_BR, steps, numSteps);
  restposright(Femur_FR, Knee_FR, steps, numSteps);
  delay(3000);

  ////////////////////////testing
  //
  //UpdatePosition(Femur_BL, Knee_BL, 180, 0);
  //UpdatePosition(Femur_BR, Knee_BR, 0, 180);
  //UpdatePosition(Femur_BR, Knee_BR, 0, 180);
  //RightStep(Femur_BR, Knee_BR, steps, numSteps);
  //CartesianMoveRight(Femur_BR, Knee_BR, 0, -17);
  //
  //UpdatePosition(Femur_FR, Knee_FR, 180, 180);
  //UpdatePosition(Femur_FL, Knee_FL, 0, 0);
  //RightStep(Femur_FR, Knee_FR, steps, numSteps);
  //CartesianMoveRight(Femur_FR, Knee_FR, 0, -17);
  //restposright(Femur_FR, Knee_FR, steps, numSteps);
}

void loop() {
  LeftStep(Femur_FL, Knee_FL, steps, numSteps);
  //
  restposleft(Femur_BL, Knee_BL, steps, numSteps);
  restposleft(Femur_FL, Knee_FL, steps, numSteps);
  restposright(Femur_BR, Knee_BR, steps, numSteps);
  restposright(Femur_FR, Knee_FR, steps, numSteps);
  delay(1000);
  //
  RightStep(Femur_BR, Knee_BR, steps, numSteps);
  //
  restposleft(Femur_BL, Knee_BL, steps, numSteps);
  restposleft(Femur_FL, Knee_FL, steps, numSteps);
  restposright(Femur_BR, Knee_BR, steps, numSteps);
  restposright(Femur_FR, Knee_FR, steps, numSteps);
  delay(1000);
  //
  RightStep(Femur_FR, Knee_FR, steps, numSteps);
  //
  restposleft(Femur_BL, Knee_BL, steps, numSteps);
  restposleft(Femur_FL, Knee_FL, steps, numSteps);
  restposright(Femur_BR, Knee_BR, steps, numSteps);
  restposright(Femur_FR, Knee_FR, steps, numSteps);
  delay(1000);
  //
  LeftStep(Femur_BL, Knee_BL, steps, numSteps);
  //
  restposleft(Femur_BL, Knee_BL, steps, numSteps);
  restposleft(Femur_FL, Knee_FL, steps, numSteps);
  restposright(Femur_BR, Knee_BR, steps, numSteps);
  restposright(Femur_FR, Knee_FR, steps, numSteps);
  delay(1000);
}


//////////////////////////////////////////////////////////////////////////////////////////rest
void restposleft(Servo& Femur, Servo& Knee, int steps[][3], size_t numSteps){
  int i = 0;
  CartesianMoveLeft(Femur, Knee, steps[i][0], steps[i][1]);
  delay(steps[i][2]);
}
void restposright(Servo& Femur, Servo& Knee, int steps[][3], size_t numSteps){
  int i = 0;
  CartesianMoveRight(Femur, Knee, steps[i][0], steps[i][1]);
  delay(steps[i][2]);
}
//////////////////////////////////////////////////////////////////////////////////////////LEFT
void LeftStep(Servo& Femur, Servo& Knee, int steps[][3], size_t numSteps){
  for (int i = 0; i < numSteps; i++){
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
void RightStep(Servo& Femur, Servo& Knee, int steps[][3], size_t numSteps){
  for (int i = 0; i < numSteps; i++){
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
