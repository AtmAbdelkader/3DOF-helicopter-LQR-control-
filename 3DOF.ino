#include<Servo.h>

//for encoder 0
#define encoder0PinA 2
#define encoder0PinB 3
volatile int encoder0Count = 0;
volatile float angle0 = 0;
float desired_angle0 = 0.0;
float desired_velocity0 = 0;
volatile float velocity0 = 0;
volatile float angle0_previous = 0;
volatile float angle0_post = 0;
float rpm0 = (2 * 3.14) / (400 * 4);

//for encoder 1
#define encoder1PinA 21
#define encoder1PinB 20
volatile int encoder1Count = 0;
volatile float angle1 = 0;
float desired_angle1 = 20.0;
float desired_velocity1 = 0;
volatile float velocity1 = 0;
volatile float angle1_previous = 0;
volatile float angle1_post = 0;
float rpm1 = (2 * 3.14) / (400 * 4);

//for encoder 2
#define encoder2PinA 18
#define encoder2PinB 19
volatile int encoder2Count = 0;
volatile float angle2 = 0;
float desired_angle2 = 0;
float desired_velocity2 = 0;
volatile float velocity2 = 0;
volatile float angle2_previous = 0;
volatile float angle2_post = 0;
float rpm2 = (2 * 3.14) / (400 * 4);

// for Timer2
volatile int tcnt2 = 131;
volatile int t = 0;
float Error_elevation = 0.0;
float Error_roll = 0.0;
float Error_travel = 0.0;
float Error_elevationdot = 0.0;
float Error_rolldot = 0.0;
float Error_traveldot = 0.0;
float Error_integral1 = 0.0;
float Error_integral2 = 0.0;
//----------------------------
float u1 = 0.0;
float k11 = 37.67;
float k12 = 13.21;
float k13 = -11.49;
float k14 = 20.95;
float k15 = 4.77;
float k16 = -16.09;
float k17 = 10.0;
float k18 = -1.0;
//----------------------------
float u2 = 0.0;
float k21 = 37.67;
float k22 = -13.21;
float k23 = 11.49;
float k24 = 20.95;
float k25 = -4.76;
float k26 = 16.09;
float k27 = 10.0;
float k28 = 1.0;
//----------------------------
float motor_input1 = 0;
float motor_input2 = 0;
float pwmLeft, pwmRight;
bool x = false;
int INPUT_MAX = 500;

//FOR MOTOR
//int pwm_width_1=0;
Servo PWML;
Servo PWMR;

double vitesse1 = 1200;
double vitesse2 = 1200;

int buttonPin1 = 14; //Start button
int buttonPin2 = 15; //Stop button

void setup() {

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  // for encoder 0
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  attachInterrupt(0, doEncoder0A, CHANGE);
  attachInterrupt(1, doEncoder0B, CHANGE);

  // for encoder 1
  pinMode(encoder1PinA, INPUT_PULLUP);
  pinMode(encoder1PinB, INPUT_PULLUP);
  attachInterrupt(2, doEncoder1A, CHANGE);
  attachInterrupt(3, doEncoder1B, CHANGE);

  // for encoder 2
  pinMode(encoder2PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);
  attachInterrupt(4, doEncoder2A, CHANGE);
  attachInterrupt(5, doEncoder2B, CHANGE);

  // setup for Timer: interrupts every 1 ms
  TIMSK2 &= ~(1 << TOIE2);
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B &= ~(1 << WGM22);
  ASSR &= ~(1 << AS2);
  TIMSK2 &= ~(1 << OCIE2A);
  TCCR2B |= (1 << CS22) | (1 << CS20);
  TCCR2B &= ~(1 << CS21);
  TCNT2 = tcnt2;
  TIMSK2 |= (1 << TOIE2);

  Serial.begin (9600); // for debugging

  //for motor
  PWML.attach(12);//choose PWM PINS ARDUINO
  PWMR.attach(13);//choose PWM PINS ARDUINO
  exitSafeStart();
}

void loop() {

  bool buttonStatus1 = digitalRead(buttonPin1);
  bool buttonStatus2 = digitalRead(buttonPin2);
 
// Serial.println(buttonStatus1);
// Serial.println(buttonStatus2);

 Serial.println((angle1*90)/2*3.14);
Serial.print(" "); // a space ' ' or tab '\t' character is printed between the two values.
delay(100);


//  // for encoder 0
//  Serial.print("cnt0: ");
//  Serial.print(encoder0Count,DEC);
//  Serial.print("; ");
//  Serial.print("agl0: ");
//  Serial.print(angle0, 4);
//  Serial.print("; ");
//  Serial.print("vel0: ");
//  Serial.print(velocity0, 4);
//  Serial.println("; ");
//
//  // for encoder 1
//  Serial.print("cnt1: ");
//  Serial.print(encoder1Count, DEC);
//  Serial.print("; ");
//  Serial.print("agl1: ");
//  Serial.print(angle1, 4);
//  Serial.print("; ");
//  Serial.print("Vel1: ");
//  Serial.print(velocity1, 4);
//  Serial.println(".");
////
//  // for encoder 2
//  Serial.print("cnt2: ");
//  Serial.print(encoder2Count, DEC);
//  Serial.print("; ");
//  Serial.print("agl1: ");
//  Serial.print(angle2, 4);
//  Serial.print("; ");
//  Serial.print("Vel1: ");
//  Serial.print(velocity2, 4);
//  Serial.println(".");

  if ( (buttonStatus1 == true) & (buttonStatus2 == true) && (x = false))
  {
    buttonStatus1 == true;
    x = true;
    PWML.writeMicroseconds(1000);
    PWMR.writeMicroseconds(1000);
    delay(7000);
  }

  if ( (buttonStatus1 == false) & (buttonStatus2 == false))
  {
    buttonStatus1 == false;
    x = false;
    PWML.writeMicroseconds(0);
    PWMR.writeMicroseconds(0);
    delay(7000);
  }

//  u1 = Error_integral1 + (k11*Error_elevation+k12*Error_roll+k13*Error_travel+k14*Error_elevationdot+k15*Error_rolldot+k16*Error_traveldot);
//  u2 = Error_integral2 + (k21*Error_elevation+k22*Error_roll+k23*Error_travel+k24*Error_elevationdot+k25*Error_rolldot+k26*Error_traveldot);

  u1 = 0; 
  u2 = 0;
  motor_input1 = u1;
  motor_input2 = u2;
  motor_input1 = (int)motor_input1;
  motor_input2 = (int)motor_input2;

  if (-30<angle0>30) {
    if (motor_input1 >= INPUT_MAX)
    {
      motor_input1 = INPUT_MAX;
    }
    else if (motor_input1 <= -INPUT_MAX)
    {
      motor_input1 = -INPUT_MAX;
    }
    if (motor_input2 >= INPUT_MAX)
    {
      motor_input2 = INPUT_MAX;
    }
    else if (motor_input2 <= -INPUT_MAX)
    {
      motor_input2 = -INPUT_MAX;
    }
  }
  else
  {
    motor_input1 = 0;
    motor_input2 = 0;
  }

  if ( (buttonStatus1 == true) & (buttonStatus2 == true)) {
    setMotorSpeed(motor_input1, motor_input2);
  }
}

//--------------------
// for encoder 0
//--------------------
void doEncoder0A() { // interrupt 0 function
  if (digitalRead(encoder0PinA) == HIGH) { // look for a low-to-high on channel A
    if (digitalRead(encoder0PinB) == LOW) { // check channel B to see which way encoder is turning
      encoder0Count = encoder0Count + 1;
    }
    else
    {
      encoder0Count = encoder0Count - 1;
    }
  }
  else { // must be a high-to-low edge on channel A
    if (digitalRead(encoder0PinB) == HIGH) { // check channel B to see which way encoder is turning
      encoder0Count = encoder0Count + 1;
    }
    else {
      encoder0Count = encoder0Count - 1;
    }
  }
  angle0 = rpm0 * encoder0Count; // unit: radian counts ||6000/(2*pi) = counts / angle|||angle = 2*pi/6000 counts
}

void doEncoder0B() { // interrupt 1 function
  if (digitalRead(encoder0PinB) == HIGH) { // look for a low-to-high on channel B
    if (digitalRead(encoder0PinA) == HIGH) { // check channel A to see which way encoder is turning
      encoder0Count = encoder0Count + 1;
    }
    else
    {
      encoder0Count = encoder0Count - 1;
    }
  }
  else { // must be a high-to-low edge on on channel B
    if (digitalRead(encoder0PinA) == LOW) { // check channel B to see which way encoder is turning
      encoder0Count = encoder0Count + 1;
    }
    else
    {
      encoder0Count = encoder0Count - 1;
    }
  }
  angle0 = rpm0 * encoder0Count; // unit: radian
}

//--------------------
// for encoder 1
//--------------------
void doEncoder1A() {
  if (digitalRead(encoder1PinA) == HIGH) {
    if (digitalRead(encoder1PinB) == LOW) {
      encoder1Count = encoder1Count + 1;
    }
    else
    {
      encoder1Count = encoder1Count - 1;
    }
  }
  else {
    if (digitalRead(encoder1PinB) == HIGH)
    {
      encoder1Count = encoder1Count + 1;
    }
    else
    {
      encoder1Count = encoder1Count - 1;
    }
  }
  angle1 = rpm1 * encoder1Count;
}
void doEncoder1B() {
  if (digitalRead(encoder1PinB) == HIGH) {
    if (digitalRead(encoder1PinA) == HIGH) {
      encoder1Count = encoder1Count + 1;
    }
    else {
      encoder1Count = encoder1Count - 1;
    }
  }
  else {
    if (digitalRead(encoder1PinA) == LOW) {
      encoder1Count = encoder1Count + 1;
    }
    else {
      encoder1Count = encoder1Count - 1;
    }
  }
  angle1 = rpm1 * encoder1Count;
}

//--------------------
// for encoder 2
//--------------------

void doEncoder2A() {
  if (digitalRead(encoder2PinA) == HIGH) {
    if (digitalRead(encoder2PinB) == LOW) {
      encoder2Count = encoder2Count + 1;
    }
    else {
      encoder2Count = encoder2Count - 1;
    }
  }
  else {
    if (digitalRead(encoder2PinB) == HIGH) {
      encoder2Count = encoder2Count + 1;
    }
    else {
      encoder2Count = encoder2Count - 1;
    }
  }
  angle2 = rpm2 * encoder2Count;
}
void doEncoder2B() {
  if (digitalRead(encoder2PinB) == HIGH) {
    if (digitalRead(encoder2PinA) == HIGH) {
      encoder2Count = encoder2Count + 1;
    }
    else {
      encoder2Count = encoder2Count - 1;
    }
  }
  else {
    if (digitalRead(encoder2PinA) == LOW) {
      encoder2Count = encoder2Count + 1;
    }
    else {
      encoder2Count = encoder2Count - 1;
    }
  }
  angle2 = (rpm2 * encoder2Count);
}
//--------------------
// estimate velocity
//--------------------
ISR(TIMER2_OVF_vect) {
  TCNT2 = tcnt2; // reload the timer
  t++;
  if (t == 1) {
    angle0_previous = angle0;
    angle1_previous = angle1;
    angle2_previous = angle2;
  }
  else if (t == 20) {
    angle0_post = angle0;
    angle1_post = angle1;
    angle2_post = angle2;
  }
  else if (t == 21) {
    velocity0 = (angle0_post-angle0_previous) * 50; // unit: rad/s
    velocity1 = (angle1_post-angle1_previous) * 50;
    velocity2 = (angle2_post-angle2_previous) * 50;
    
//    Error_elevation = angle0-desired_angle0;
//    Error_roll = angle1-desired_angle1;
//    Error_travel = angle2-desired_angle2;
//    Error_elevationdot = velocity0;
//    Error_rolldot = velocity1;
//    Error_traveldot = velocity2;
//    Error_integral1 = Error_integral1+((k17* Error_elevation)+(k18*Error_travel));
//    Error_integral2 = Error_integral2+((k27* Error_elevation)+(k28*E

    t = 0;
  }
}

// required to allow motors to move
// must be called when controller restarts and after any error
void exitSafeStart()
{
  PWML.writeMicroseconds(1000);
  PWMR.writeMicroseconds(1000);
  delay(7000);
}
// speed should be a number from -3200 to 3200
void setMotorSpeed(int motor_input1, int motor_input2)
{
  pwmLeft = vitesse1 ;
  pwmRight = vitesse2 ; 
  //Left
  if (pwmLeft < 1000)
  {
    pwmLeft = 1000;
  }
  if (pwmLeft > 2000)
  {
    pwmLeft = 2000;
  }
  //Right
  if (pwmRight < 1000)
  {
    pwmRight = 1000;
  }
  if (pwmRight > 2000)
  {
    pwmRight = 2000;
  }
  //FOR MOTOR
  PWML.writeMicroseconds(pwmLeft);
  PWMR.writeMicroseconds(pwmRigh);
}
