#include <stdio.h>
#include <stdlib.h>

//Akhil Morisetty(akhilm6), Aashay Soni(asoni29), Ethan Zhang(Ethanjz2) worked on this mp.
//Our program prints out the values of the fibonacci sequence based on a user inputed 
//value labeled row. Based on the formula given on canvas, we implemented a nested for 
//loop using 'k' as the row number and 'i' as the number in the row. We used an if statement
//before the nested for loop to check if the user inputed 0 since row 0 doesn't follow the 
//formula given. After each iteration of the inner for loop, we printed the first number in the
//fibonacci sequence before printing an extra space and iterating again. 

int main()
{
  int row; //Initialize integer variable to assign the row number

  printf("Enter a row index: "); //Print line for user to read
  scanf("%d",&row); //Scans the user input for the row number
  unsigned long result = 1; //Initialize result variable into unsigned long integer
  


  if(row == 0)
    printf("1"); //Print out 1 if the user inputs row 0
  else{
    for(int k = 0;k <= row;k++) //Initialize for loop for the row number k
    {
      result = 1; //Set result to 1 
      for(int i = 1;i <= k;i++) //Initialize for loop for the number 'i' in the row
      {
        result = (result * (row+1-i))/i; //Formula to calculate number i in row k
      }
      printf("%ld",result); //Print out unisnged long integer
      printf(" "); //Print out a space in between each number in the fibonacci sequence 
    }
  }

  return 0; 
}
