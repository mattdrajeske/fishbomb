

///////////////////////////////////////////////////////////////
//Matt Drajeske
//CS 1575 Data Structures
//Assignment 1: Fish Bomb
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <iomanip>
//#include "pch.h"

using namespace std;

void getDimensions(int&, int&);
void allocateFish(int&, int&, int&);
int bombFish(int*[], int, int, int, int);

int main() {

   //rows and columns represent the dimensions of the fish matrix
   //x and y represent the coordinates of the dynamite
   //numTrials is the number of trials 
   int rows, columns;
   int numTrials;

   cin >> numTrials;

   //execute functions for however many trials the user inputs
   for (int i = 0; i < numTrials; i++) {
      getDimensions(rows, columns);
      allocateFish(i, rows, columns);
   }
   return 0;
}

void getDimensions(int& r, int& c) {
   cin >> r >> c;
};


//////////////////////////////////////////////////////////////////////////////////////
/// @fn allocateFish
/// @brief allocate a 2D array dynamically and deallocate it after it is bombed
/// @param trialNum used to format output correctly, value should be trial number - 1
/// @param rows height of 2D array
/// @param columns width of 2D array
//////////////////////////////////////////////////////////////////////////////////////
void allocateFish(int& trialNum, int& rows, int& columns) {

   //columns in 2D array of fish
   //using malloc instead of new because otherwise i got a bunch of heap corruption errors
   //this worked though`
   int** fishArray = (int**)malloc(rows * sizeof(int*));
   for (int i = 0; i < rows; i++) {
      fishArray[i] = (int*)malloc(columns * sizeof(int));
   }

   /*//dynamic allocation of array
   for (int i = 0; i < columns; i++) {
      fishArray[i] = new int[columns];
   }*/

   //fill array
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         cin >> fishArray[i][j];
      }
   }

   //3 sticks of dynamite are thrown. These will be the coordinates they are thrown to.
   int x1, y1;
   int x2, y2;
   int x3, y3;

   cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

   //function call
   cout << "#" << trialNum << ": Bender catches " <<
      bombFish(fishArray, x1, y1, rows, columns) + bombFish(fishArray, x2, y2, rows, columns) + bombFish(fishArray, x3, y3, rows, columns)
      << " fish" << endl;

   for (int i = 0; i < rows; i++) {
      free(fishArray[i]);
   }
   free(fishArray);
   fishArray = NULL;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn bombFish
/// @brief set a 5x5 area in the array to 0 and increment a value to determine the number of fish caught
/// @param fishArray dynamic 2D array that represents sonar grid for fish
/// @param x x coordinate
/// @param y y coordinate
/// @param rows height of 2D array
/// @param columns width of 2D array
/// @return returns the number of fish that were caught using bombs
////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int bombFish(int* fishArray[], int x, int y, int rows, int columns) {

   //Bombing a fish means setting its (x, y) coordinate in the grid to 0 and add its value to total fish caught
   //integers to mark where in the array the fish were bombed. (startX, startY) is top left corner of blast,
   //(endX, endY) is bottom right corner.
   int startX, startY;
   int endX, endY;

   //declare a variable for counting fish caught and initialize to 0
   int fishCaught = 0;

   //determine where the x value is to start bombing fish
   //Must account for when the explosion goes off the grid
   if (x - 2 >= 0) {
      startX = x - 2;
   }
   else {
      startX = 0;
   }

   if (x + 2 <= rows - 1) {
      endX = x + 2;
   }
   else {
      endX = rows - 1;
   }

   //determine where start position y is
   if (y - 2 >= 0) {
      startY = y - 2;
   }
   else {
      startY = 0; //should work
   }

   //end position y
   if (y + 2 <= columns - 1) {
      endY = y + 2;
   }
   else {
      endY = columns - 1; //should work
   }

   //iterate through dynamic array
   for (int i = 0; i < rows; i++) {


      for (int j = 0; j < columns; j++) {

         //determine which tiles have been bombed
         if (i >= startX && i <= endX && j >= startY && j <= endY) {
            fishCaught += fishArray[i][j];
            fishArray[i][j] = 0;
         }
      }
   }

   return fishCaught;
};