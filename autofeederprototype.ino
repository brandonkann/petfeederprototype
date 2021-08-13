#include <LiquidCrystal.h>// include the library code
#include <IRremote.h> 
#include <Servo.h> 
/**********************************************************/
/***Declare Global variables***/
char array1[] = " Good Morning               "; //the string to print on the LCD
char array2[] = "Yumi the Havanese             "; //the string to print on the LCD
String input = "";     // Temp string array 
int tim = 500;  //the value of delay time
int servoPin = 3;

bool set_breakfast = false;
bool set_lunch = false;
bool set_dinner = false; 

bool breakfast_done = false;
bool lunch_done = false; 
bool dinner_done = false;

String breakfast_time = ""; 
String lunch_time = ""; 
String dinner_time = ""; 

String val;
String result; 

Servo servo; 

int servoAngle = 0; 
int receiver_pin = 8; 


/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
/*********************************************************/
void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  IrReceiver.begin(receiver_pin);

  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
}
/*********************************************************/
void loop()
{ 
  if (set_breakfast == false || set_lunch == false || set_dinner == false) {
    if (set_breakfast == false) {
      lcd.setCursor(0,0);
      lcd.print("Breakfast Time:");
      delay(1000);
      set_breakfast = true;
      lcd.clear(); 
      while (breakfast_time.length() != 4) {
        if (IrReceiver.decode()) {
          val = decodeSignal(IrReceiver.decodedIRData.decodedRawData);
          IrReceiver.resume();
          breakfast_time += val;
          lcd.print(breakfast_time); 
        }
      }
        
    }
    else if (set_lunch == false) {
      lcd.setCursor(0,0);
      lcd.print("Lunch Time:");
      delay(1000);
      set_lunch = true;
      lcd.clear();
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("Dinner Time:");
      delay(1000);
      set_dinner = true;
      lcd.clear(); 
    }
  }
  else  {
    lcd.setCursor(0,0);
    lcd.print("Starting now!");
  }
}

/***Decoding IRremote helper function***/
String decodeSignal(int ir_data) {
  switch(ir_data)
  {
    case 4077715200:
      result = "1";
      break;    
  }
  return result;
 
}



// Code for LC1602 Display that will display from left to right
//  lcd.setCursor(15, 0); // set the cursor to column 15, line 0
//  for ( int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
//  {
//    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
//    lcd.print(array1[positionCounter1]);  // Print a message to the LCD.
//    delay(tim);  //wait for 250 ms
//  }
//  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
//  lcd.setCursor(15, 1); // set the cursor to column 15, line 1
//  for (int positionCounter2 = 0; positionCounter2 < 26; positionCounter2++)
//  {
//    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
//    lcd.print(array2[positionCounter2]);  // Print a message to the LCD.
//    delay(tim);  //wait for 250 ms
//  }
//  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
/************************************************************/
