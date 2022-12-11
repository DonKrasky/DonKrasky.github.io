/* This program will eventually integrate bluetooth control for one or two stepper motors

Every time you want the motor to move, call the step(#steps, direction, steptype) 
  procedure.#steps is how many steps you'd like it to take.
  direction is either FORWARD or BACKWARD and the step type is SINGLE, DOUBLE. INTERLEAVE or MICROSTEP.
    "Single" means single-coil activation, 
     "double" means 2 coils are activated at once (for higher torque)
     "interleave" means that it alternates between single and double to get twice the resolution (but of course its half the speed).
     "Microstepping" is a method where the coils are PWM'd to create smooth motion between steps.
*/

#include <AFMotor.h>

AF_Stepper motor(200, 1);

int value_bluetooth = 0;

String readString = "";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9800);           // set up Serial library at 9600 bps (Baud rate = Bits Per Second)
  Serial.println("Stepper test with bluetooth!");

  motor.setSpeed(120);  // Enter rpm   

  motor.step(200, FORWARD, DOUBLE); 
  motor.step(200, BACKWARD, DOUBLE);
  motor.release();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //readString.charAt(readString.length()) != '⸮'
  if (Serial.available())
  {
      String readString = "";
      char c= Serial.read();
      
      readString += c;
      Serial.println(readString);
      
  }

  // Motor movement logic
  if(readString.length() >0)
  {
   value_bluetooth =readString.toInt();
  }
  
  if (value_bluetooth >  0   )
  {
    motor.setSpeed(value_bluetooth);
    motor.step(200, FORWARD, SINGLE);
    Serial.println(value_bluetooth);
    
  }
  else if (value_bluetooth <0)
  {
    motor.setSpeed(-value_bluetooth);
    motor.step(200, BACKWARD, SINGLE);
    Serial.println(value_bluetooth);
  }

  

//Serial.println(value_bluetooth);

 readString="";

}





/* Sample code for motor movement.
  motor.step(200, FORWARD, SINGLE); 
  motor.step(200, BACKWARD, SINGLE); 
  
  motor.step(200, FORWARD, DOUBLE); 
  motor.step(200, BACKWARD, DOUBLE);

  motor.step(200, FORWARD, INTERLEAVE); 
  motor.step(200, BACKWARD, INTERLEAVE); 

  motor.step(200, FORWARD, MICROSTEP); 
  motor.step(200, BACKWARD, MICROSTEP);
  */







  /* Sample bluetooth controlled app.
 
   while (Serial.available()){
    char c= Serial.read();
    readString+=c;
  }

  if(readString.length() >0) {
   
    value_bluetooth =readString.toInt();

   if (value_bluetooth >  0   ){
      delay_time = 15;  
    }
    else
    {
      delay_time=0;
      }

Serial.println(value_bluetooth);

 
digitalWrite(8, HIGH); digitalWrite(step_pin_2, HIGH); digitalWrite(step_pin_3, LOW); digitalWrite(step_pin_4, LOW);   
delay(delay_time);


digitalWrite(step_pin_1, LOW); digitalWrite(step_pin_2, HIGH); digitalWrite(step_pin_3, HIGH); digitalWrite(step_pin_4, LOW);  
delay(delay_time);

digitalWrite(step_pin_1, LOW); digitalWrite(step_pin_2, LOW); digitalWrite(step_pin_3, HIGH); digitalWrite(step_pin_4, HIGH);  
delay(delay_time);
 
digitalWrite(step_pin_1, HIGH); digitalWrite(step_pin_2, LOW); digitalWrite(step_pin_3, LOW); digitalWrite(step_pin_4, HIGH);  
delay(delay_time); 


readString="";
*/
