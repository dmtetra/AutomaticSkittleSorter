//Skittle Sorting Machine 

//Required libraries
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>

int led = 5;
int x = 2;
int y = 3;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo pusher;
Servo funnal;

void setup(void) {
  Serial.begin(9600);

  pinMode (led, OUTPUT); 
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  //setting both servo motors to proper position
  pusher.attach(9, 500, 2500);
  funnal.attach(3, 500, 2500);
  
  pusher.write(0);
  funnal.write(0);

}

void loop(void) {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  //lines below print the RGB colour reading from the sensor to the serial monitor
  Serial.print("Red: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("Green: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("Blue: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.println(" ");
  delay(100);

 if (y == 3)
 {
   if(r > g && r > b)  // check if colour of skittle is red
   {
    funnal.write(45);
    delay(1000); // Wait for 1000 millisecond(s)
   }
   else if(g > r && g > b)//check if colour of skittle is green
   {
     funnal.write(67.5); /* writes bottom servo to applicable location to allow for skittle to fall in correct location*/
     delay(1000);
   }
   else if(b > r && b > g)//check if colour of skittle is purple
   {
     funnal.write(90); /* writes bottom servo to applicable location to allow for skittle to fall in correct location*/

     delay(1000); // Wait for 1000 millisecond(s)
   }
   else if(r > b && g > r) //check if colour of skittle is yellow
   {
     funnal.write(112.5) ;/* writes bottom servo to applicable location to allow for skittle to fall in correct location*/
     delay(1000); // Wait for 1000 millisecond(s)
   }

   else if(r > g && g > b) //check if colour of skittle is orange
   {
     funnal.write(135); /* writes bottom servo to applicable location to allow for skittle to fall in correct location*/
     delay(1000);
   }
 }

 if (x == 2)
 {
  //the following lines control the upper servo that picks up the skittle
  pusher.write(75); //writes upper servo to sensor position
  delay(1000); // Wait for 1000 millisecond(s)
  
  pusher.write(45); //write upper servo to dropdown position
  delay(1000); // Wait for 1000 millisecond(s)
  pusher.write(0); // moves servo back to starting position to pick up another skittle
  delay(1000); // Wait for 1000 millisecond(s)
 }
}
