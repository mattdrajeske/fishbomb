///////////////////////////////////////////////////////////////
//Matt Drajeske
//CS 1575 Data Structures
//Assignment 1
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <iomanip>
//#include "pch.h"
using namespace std;

void getDimensions(int&, int&);
void allocateFish(int&, int, int);
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

void allocateFish(int& trialNum, int rows, int columns) {

   //columns in 2D array of fish
   int** fishArray = new int*[rows];

   //dynamic allocation of array
   for (int i = 0; i < columns; i++) {
      fishArray[i] = new int[columns];
   }

   //fill array
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         cin >> fishArray[i][j];
      }
   }

   /*//test 1, default array with no changes
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         cout << fishArray[i][j]; //works without a space but a space breaks it for some reason (?)
                                  //seems to be an issue with the test idk it's weird
      }
      cout << endl;
   }*/

   //3 sticks of dynamite are thrown. These will be the coordinates they are thrown to.
   int x1, y1;
   int x2, y2;
   int x3, y3;

   cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

   //counter for having correct output format


   //function call
   cout << "#" << trialNum << ": Bender catches " <<
      bombFish(fishArray, x1, y1, rows, columns) + bombFish(fishArray, x2, y2, rows, columns) + bombFish(fishArray, x3, y3, rows, columns)
      << " fish" << endl;

};

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

   /*//test 2, array after it is bombed
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         cout << fishArray[i][j]; //works without a space but a space breaks it for some reason (?)
                                  //seems to be an issue with the test idk it's weird
      }
      cout << endl;
   }
   cout << endl;*/
   return fishCaught;
};