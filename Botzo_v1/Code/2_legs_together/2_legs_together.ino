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
// {{-4, -16, 300},{-10, -16, 300},{-4, -13, 100},{-4, -16, 300}};  // walk back wards for front
int steps_front[][3] = {{-4, -16, 300},{-1, -14, 300},{-1, -16, 100},{-4, -16, 300}};
int steps_back[][3] = {{-2, -16, 300}, {-5, -14, 300}, {-5, -16, 100}, {-2, -16, 300}};
// each element is (X_cord, Y_cord, Delay/speed) + first one is rest pos
size_t numSteps = sizeof(steps_front) / sizeof(steps_front[0]);



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
  rest2(Femur_BR, Knee_BR, steps_back, numSteps);
  rest2(Femur_FL, Knee_FL, steps_front, numSteps);
  rest1(Femur_BL, Knee_BL, steps_back, numSteps);
  rest1(Femur_FR, Knee_FR, steps_front, numSteps);
  delay(3000);

  ////////////////////////testing
  //
  //UpdatePosition(Femur_BL, Knee_BL, 180, 180);
  //UpdatePosition(Femur_BR, Knee_BR, 0, 0);
  //CartesianMove1(Femur_FR, Knee_FR, 4, -16);
  //CartesianMove1(Femur_BL, Knee_BL, -2, -10);
  //CartesianMove2(Femur_BR, Knee_BR, -9, -13);
  //CartesianMove2(Femur_BR, Knee_BR, -7, -16);
  //Step2(Femur_BR, Knee_BR, steps_front, numSteps);
  //
  //UpdatePosition(Femur_FR, Knee_FR, 180, 180);
  //UpdatePosition(Femur_FL, Knee_FL, 0, 0);
  //Step1(Femur_FR, Knee_FR, steps_front, numSteps);
}

void loop() {
  Step_FL_BR(Femur_FL, Knee_FL, Femur_BR, Knee_BR, steps_front, steps_back, numSteps);
  delay(500);
  Step_FR_BL(Femur_FR, Knee_FR, Femur_BL, Knee_BL, steps_front, steps_back, numSteps);
  delay(500);
}


//////////////////////////////////////////////////////////////////////////////////////////rest
void rest2(Servo& Femur, Servo& Knee, int steps[][3], size_t numSteps){
  int i = 0;
  CartesianMove2(Femur, Knee, steps[i][0], steps[i][1]);
  delay(steps[i][2]);
}
void rest1(Servo& Femur, Servo& Knee, int steps[][3], size_t numSteps){
  int i = 0;
  CartesianMove1(Femur, Knee, steps[i][0], steps[i][1]);
  delay(steps[i][2]);
}
//////////////////////////////////////////////////////////////////////////////////////////update servos angles
void UpdatePosition(Servo& Femur, Servo& Knee, double angle_femur, double angle_knee){ // MOVE TO POSITION
  Femur.write(angle_femur);
  Knee.write(angle_knee);
}



////////////////////////////////////////////////////////////////////////////////////////// FrontLeft - BottomRight
void Step_FL_BR(Servo& Femur_FL, Servo& Knee_FL, Servo& Femur_BR, Servo& Knee_BR, int steps_front[][3], int steps_back[][3], size_t numSteps){
  for (int i = 0; i < numSteps; i++){
    CartesianMove2(Femur_FL, Knee_FL, steps_front[i][0], steps_front[i][1]);
    CartesianMove2(Femur_BR, Knee_BR, steps_back[i][0], steps_back[i][1]);
    delay(steps_front[i][2]);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////FrontRight - BottomLeft
void Step_FR_BL(Servo& Femur_FR, Servo& Knee_FR, Servo& Femur_BL, Servo& Knee_BL, int steps_front[][3], int steps_back[][3], size_t numSteps){
  for (int i = 0; i < numSteps; i++){
    CartesianMove1(Femur_FR, Knee_FR, steps_front[i][0], steps_front[i][1]);
    CartesianMove1(Femur_BL, Knee_BL, steps_back[i][0], steps_back[i][1]);
    delay(steps_front[i][2]);
  }
}


////////////////////////////////////////////////////////////////////////////////////////// FrontLeft - BottomRight
void CartesianMove2(Servo& Femur, Servo& Knee, double X, double Y){
  // check X, Y are reachable:
  float distance = sqrt(pow(X, 2) + pow(Y, 2));

  if (distance <= (L1 + L2)) { // point is reacable
    double Knee_rad = acos(((X*X) + (Y*Y) - (L1*L1) - (L2*L2)) / (2 * L1 * L2));
    double Femur_rad = abs(atan2(Y, X) - atan2((L2 * sin(Knee_rad)), (L1 + (L2 * cos(Knee_rad)))));
    //Transform to deg
    double F_ang = degrees(Femur_rad);
    double Femur_ang = F_ang; //180 -
    double Knee_ang = degrees(Knee_rad);
    // Move servos
    UpdatePosition(Femur, Knee, Femur_ang, Knee_ang);
  }
  else {
    Serial.println("Point not reachable");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////FrontRight - BottomLeft
void CartesianMove1(Servo& Femur, Servo& Knee, double X, double Y){
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
    // Move servos
    UpdatePosition(Femur, Knee, Femur_ang, Knee_ang);
  }
  else {
    Serial.println("Point not reachable");
  }
}



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
