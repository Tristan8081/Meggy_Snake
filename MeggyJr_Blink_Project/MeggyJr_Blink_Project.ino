/*
  MeggyJr_Project.pde by Tristan Scharfenstein-Montgomery
 
 Example file using the The Meggy Jr Simplified Library (MJSL)
  from the Meggy Jr RGB library for Arduino
   
 Blink a damned LED.
   
   
 
 Version 1.25 - 12/2/2008
 Copyright (c) 2008 Windell H. Oskay.  All right reserved.
 http://www.evilmadscientist.com/
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
 	  
 */

 
 
 
 

/*
 * Adapted from "Blink,"  The basic Arduino example.  
 * http://www.arduino.cc/en/Tutorial/Blink
 */

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.
int xapple = random(8);
int yapple = random(8);
int binary = 0;
int speed = 200;

struct Point
{
  int x;
  int y;
};


Point p1 = {2,4};
Point p2 = {3,4};
Point p3 = {4,4};
Point p4 = {5,4};
Point snakeArray[64] = {p1,p2,p3,p4};
int marker = 4;// Index of the first empty sgement of array
int direction = 0;

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
}

void loop()                     // run over and over again
{
 CheckButtonsDown();
 if (Button_Up)
 {
  direction = 0;
 }
 if (Button_Right)
 {
  direction = 90;
 }
 if (Button_Down)
 {
  direction = 180;
 }
 if (Button_Left)
 {
  direction = 270;
 }
 updateSnake();
 DrawPx(xapple, yapple, Red);
 //Have we eaten apple?
 if (ReadPx(snakeArray[0].x,snakeArray[0].y) == Red)
 {
   xapple = random(8);              // Roll new values for apple
   yapple = random(8);
   Tone_Start(18182,50);
   binary = binary * 2 + 1;
   if (binary > 255)
   {
    binary = 0;                       // Restart to zero LED lights
    Tone_Start(10000,100);           // Beep after eight apples eaten
    speed = speed - 10;               // Change Speed
    marker ++;                      // Add one body part to the snake.
   }
 }
 drawSnake();
 SetAuxLEDs(binary);
 DisplaySlate(); 
 delay(200);
 ClearSlate();
}

//checks the direction and updates the x or y value.
void updateSnake()
{
  //Move Body
  for (int i = marker - 1; i > 0; i--)
  {
    //Copy the value at i-1 into i
    snakeArray[i] = snakeArray[i - 1];
  }
  
  // Move head
  if (direction == 0)
    //updates y
    snakeArray[0].y = snakeArray [0].y + 1;
    
    //corrects for out of bounds
    if (snakeArray[0].y > 7)
    {
      snakeArray[0].y = 0;
    }
  if (direction == 90)
    //updates x
    snakeArray[0].x = snakeArray[0].x + 1;
    //corrects for out of bounds
    if (snakeArray[0].x > 7)
    {
     snakeArray[0].x = 0;
    } 
  if (direction == 180)
    //updates y
    snakeArray[0].y = snakeArray[0].y - 1;
    //corrects for out of bounds
    if (snakeArray[0].y < 0)
    {
      snakeArray[0].y = 7;
    }
  if (direction == 270)
    //updates x
    snakeArray[0].x = snakeArray[0].x - 1;
    //corrects for out of bounds
    if (snakeArray[0].x < 0)
    {
     snakeArray[0].x = 7;
    }
}

void drawSnake()
{
  //Iterate through the enitre array and draw the segment.
  for (int i = 0; i < marker; i++)
  {
    DrawPx(snakeArray[i].x, snakeArray[i].y,Blue);
  }
}


