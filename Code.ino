#include <Stepper.h>
  
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
  
Stepper stepperBase(STEPS, 8, 10, 9, 11);
Stepper stepperArm(STEPS, 4, 6, 5, 7);

const int trigPin = 2;
const int echoPin = 3;
long duration;
int distance;

double baseAngle = 0;
double armAngle = 0;
  
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

double dist()
{
  // Clears the trigPin

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  
  return distance;  
}

void calculate(double d, double alpha, double beta)
{
    double alphaRad = alpha * 0.0174533;
    double betaRad = beta * 0.0174533;
    
    double z = 5 - (d * sin(-betaRad));

    double p = d * cos(betaRad);

    double x = p * cos(alphaRad);
    double y = p * sin(alphaRad);

    Serial.print("v ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(z);
    Serial.print("\n");
}
 
void loop() {

  if(armAngle + 1.0588 * 2 > 90)  //two times faster
  {
    for(double i = armAngle; i >= 0; i=i-1.0588*2)
    {
      stepperArm.setSpeed(10);
      stepperArm.step(6);  
      delay(500);
    }
    delay(1000000);
  }
  
   stepperBase.setSpeed(10); // 1 rpm
   stepperArm.setSpeed(10);

   
   for(int i = 0; i < 509; i=i+6) //90stupnjeva, 360 => 2038
   {
    calculate(dist(), baseAngle, armAngle);
    stepperBase.step(6); // do 2038 steps -- corresponds to one revolution in one minute
    delay(500);
    baseAngle += 1.0588;
   }

   stepperArm.step(-6);
   armAngle += 1.0588;
   delay(500);

   for(int i = 0; i < 509; i=i+6) //90stupnjeva, 360 => 2038
   {
    calculate(dist(), baseAngle, armAngle);
    stepperBase.step(-6); // do 2038 steps -- corresponds to one revolution in one minute
    delay(500);
    baseAngle -= 1.0588;
   }

   stepperArm.step(-6);
   armAngle += 1.0588;
   delay(500);
 }
