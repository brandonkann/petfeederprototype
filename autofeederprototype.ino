#include <LiquidCrystal.h>// include the library code
#include <IRremote.h> 
/**********************************************************/
char array1[] = " Good Morning               "; //the string to print on the LCD
char array2[] = "Yumi the Havanese             "; //the string to print on the LCD
String input = "";     // Temp string array 
int tim = 500;  //the value of delay time
int receiver_pin = 8; 
// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
/*********************************************************/
void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(receiver_pin);

  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
}
/*********************************************************/
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("Yumi's Feeder");
  if (IrReceiver.decode())
  {
    if (IrReceiver.decodedIRData.decodedRawData == 4077715200) {
      input += "1";
      lcd.setCursor(0,1);
      lcd.print(input);
    }
  Serial.println(IrReceiver.decodedIRData.decodedRawData);
  IrReceiver.resume();
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
}
/************************************************************/
