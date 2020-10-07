#include <Stepper.h>
  
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
  
Stepper stepper(STEPS, 8, 10, 9, 11);

double baseAngle = 0;
  
void setup() {
  // nothing to do
  Serial.begin(9600);
}
 
 void loop() {
   stepper.setSpeed(10); // 1 rpm
   for(int i = 0; i < 2038; i=i+6)
   {
    stepper.step(-6); // do 2038 steps -- corresponds to one revolution in one minute
    delay(500);
    Serial.println(baseAngle);
    baseAngle += 1.0588;
   }

   for(int i = 0; i < 2038; i=i+6)
   {
    stepper.step(-6); // do 2038 steps -- corresponds to one revolution in one minute
    delay(500);
    Serial.println(baseAngle);
    baseAngle -= 1.0588;
   }
 }
