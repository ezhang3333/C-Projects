//Akhilm6(Akhil Morisetty), Asoni29(Aashay Soni), Ethanjz2(Ethan Zhang) worked on this lab.


//Introduction
//The following code is for the game codebreaker. In the game, the user enters a seed and the game (code)
//spits out 4 integers specific to that seed. The user has 4 guesses in order to guess the 4 integers.
//After every guess, the user gets to see how many perfect and imperfect matches they had in order to improve on their guess.

//This program contains 3 methods: set_seed, start_game, and make_guess.
//Set_seed: This method checks whether the input from the user is valid, if it is a a random seed is generated with the help of
//the library function srand()
//Start_game:This method generates thea random sequence
//Make_guess:This method allows the user to input 4 integers. The user is then told whether their guess is valid,
//and if they have any perfect or any imperfect matches

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "prog5.h"

/*
* You will need to keep track of the solution code using file scope
* variables as well as the guess number.
*/

 
static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
* set_seed -- This function sets the seed value for pseudorandom
* number generation based on the number the user types.
* The input entered by the user is already stored in the string seed_str by the code in main.c.
* This function should use the function sscanf to find the integer seed value from the
* string seed_str, then initialize the random number generator by calling srand with the integer
* seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
* INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
* OUTPUTS: none
* RETURN VALUE: 0 if the given string is invalid (string contains anything
* other than a single integer), or 1 if string is valid (contains one integer)
* SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
* if string is invalid. Prints nothing if it is valid.
*/

int set_seed (const char seed_str[]) //init int method set_seed
{
    char post[2];//create of array of chars of length 2
    int seed = 0; //init and set int seed to 0
 
    if(sscanf (seed_str, "%d%1s", &seed, post) == 1) //if statement in order to check user has only inputted an integer
    {
        srand(seed);//randomize seed
        return 1;//end method with return
    }
    else
        printf("set_seed: invalid seed\n");//tells user to input a valid seed


//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read successfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below

    return 0; //end method

}

 
/*
* start_game -- This function is called by main.c after set_seed but before the user makes guesses.
*               This function creates the four solution numbers using the approach
*               described in the wiki specification (using rand())
*               The four solution numbers should be stored in the static variables defined above.
*              The values at the pointers should also be set to the solution numbers.
*               The guess_number should be initialized to 1 (to indicate the first guess)
* INPUTS: none
* OUTPUTS: *one -- the first solution value (between 1 and 8)
*          *two -- the second solution value (between 1 and 8)
*          *three -- the third solution value (between 1 and 8)
*          *four -- the fourth solution value (between 1 and 8)
* RETURN VALUE: none
* SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
*/

void start_game (int* one, int* two, int* three, int* four) //init and declare method start_game
{
    //your code here

    guess_number = 1;//increase number of guesses to one
    solution1 = *one = rand()%8+1;//sets random number to solution1
    solution2 = *two = rand()%8+1;//sets random number to solution2
    solution3 = *three = rand()%8+1;//sets random number to solution3
    solution4 = *four = rand()%8+1;//sets random number to solution4

}
 
/*
* make_guess -- This function is called by main.c after the user types in a guess.
*               The guess is stored in the string guess_str.
*               The function must calculate the number of perfect and misplaced matches
*               for a guess, given the solution recorded earlier by start_game
*               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
*               the number of correct and incorrect matches should be printed, using the following format
*               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
*               If valid, the guess_number should be incremented.
*               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
*               For an invalid guess, the guess_number is not incremented.
* INPUTS: guess_str -- a string consisting of the guess typed by the user
* OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
*          *one -- the first guess value (between 1 and 8)
*          *two -- the second guess value (between 1 and 8)
*          *three -- the third guess value (between 1 and 8)
*          *four -- the fourth color value (between 1 and 8)
* RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
*               numbers between 1 and 8), or 0 if it is invalid
* SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
*               or an error message (invalid guess)
*               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
*/

int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)//init and declare method make_guess
{
    int pm = 0;//init and set perfect matches to 0
    int im = 0;//initialize and set imperfect matches to 0
    bool one_pair,two_pair,three_pair,four_pair,one_guess,two_guess,three_guess,four_guess;//initialize boolean variables
    one_guess = false;//set all boolean variables to false
    two_guess = false;
    three_guess = false;
    four_guess = false;
    one_pair = false;
    two_pair = false;
    three_pair = false;
    four_pair = false;
   
   
    char post[2]; //Initialize array of characters to length of 2
    int w,x,y,z; //Initialize int variables
    if(sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) != 4 ) //Check if guess has four integers
    {
        printf("make_guess: invalid guess\n"); //Print out invalid guess
        return 0;
    }
    if(!(1 <= w && w <= 8 && 1 <= x && x <= 8 && 1 <= y && y <= 8 && 1 <= z && z<= 8)) //Check if each guess is between 1 and 8
    {
        printf("make_guess: invalid guess\n"); //If not returns invalid guess
        return 0;
    }

    *one = w; //Set pointer to w
    *two = x; //Set pointer to x
    *three = y; //Set pointer to y
    *four = z; //Set pointer to z
   
    if(*one == solution1) //Check if pointer is equal to solution1
    {
        pm++; //Increment perfect match
        one_pair = true; //Set one_pair to true
        one_guess = true; //Set one_guess to true
    }
    if(*two == solution2) //Check if pointer is equal to solution2
    {
        pm++; //Increment perfect match
        two_pair = true; //Set two_pair to true
        two_guess = true; //Set two_guess to true
    }
    if(*three == solution3) //Check if pointer is equal to solution3
    {
        pm++; //Increment perfect match
        three_pair = true; //Set three_pair to true
        three_guess = true; //Set three_guess to true
    }
    if(*four == solution4) //Check if pointer is equal to solution4
    {
        pm++; //Increment perfect match
        four_pair = true; //Set four_pair to true
        four_guess = true; //Set four_guess to true
    }
    if(!one_guess)//if one_guess is false
    {
        if(*one == solution2 && !two_pair)//checks if guess one is the same as solution 2 and
        //that the user hasn't already correctly guessed two pair
        {
            im++;//increment imperfect match
            one_guess = true;//user has used first guess
            two_pair = true;//user has correctly guessed second int
        }
        else if(*one == solution3 && !three_pair) //checks if guess one is the same as solution 3 and
        //that the user hasn't already correctly guessed three pair
        {
            im++;//increment imperfect match
            one_guess = true; //Set one_guess to true
            three_pair = true; //Set three_pair to true
        }
        else if(*one == solution4 && !four_pair) //checks if guess one is the same as solution 4 and
        //that the user hasn't already correctly guessed four pair
        {
            im++;//increment imperfect match
            one_guess = true; //Set one_guess to true
            four_pair = true; //Set four_pair to true
        }
    }
    if(!two_guess) //Check if two_guess is false
    {
        if(*two == solution1 && !one_pair) //checks if guess two is the same as solution 1 and
        //that the user hasn't already correctly guessed one pair
        {
            im++;//increment imperfect match
            two_guess = true; //Set two_guess to true
            one_pair = true; //Set one_pair to true
        }
        else if(*two == solution3 && !three_pair) //checks if guess two is the same as solution 3 and
        //that the user hasn't already correctly guessed three pair
        {
            im++;//increment imperfect match
            two_guess = true; //Set two_guess to true
            three_pair = true; //Set three_pair to true
        }
        else if(*two == solution4 && !four_pair) //checks if guess two is the same as solution 4 and
        //that the user hasn't already correctly guessed four pair
        {
            im++;//increment imperfect match
            two_guess = true; //Set two_guess to true
            four_pair = true; //Set four_pair to true
        }
    }
    if(!three_guess) //Check if three_guess is false
    {
        if(*three == solution2 && !two_pair) //checks if guess three is the same as solution 2 and
        //that the user hasn't already correctly guessed two pair
        {
            im++;//increment imperfect match
            three_guess = true; //Set three_guess to true
            two_pair = true; //Set two_pair to true
        }
        else if(*three == solution1 && !one_pair)//checks if guess three is the same as solution 1 and
        //that the user hasn't already correctly guessed lone pair
       {
            im++;//increment imperfect match
            one_pair = true; //Set one_pair to true
            three_guess = true; //Set three_guess to true
        }
        else if(*three == solution4 && !four_pair)//checks if guess three is the same as solution 4 and
        //that the user hasn't already correctly guessed four pair
        {
            im++;//increment imperfect match
            three_guess = true; //Set three_guess to true
            four_pair = true; //Set four_pair to true
        }
    }
    if(!four_guess) //Check if four_guess is false
    {
        if(*four == solution2 && !two_pair)//checks if guess four is the same as solution 2 and
        //that the user hasn't already correctly guessed two pair
        {
            im++;//increment imperfect match
            four_guess = true; //Set four_guess to true
            two_pair = true;
        }
        else if(*four == solution3 && !three_pair)//checks if guess four is the same as solution 3 and
        //that the user hasn't already correctly guessed three pair
        {
            im++;//increment imperfect match
            four_guess = true; //Set four_guess to true
            three_pair = true; //Set three_pair to true
        }
        else if(*four == solution1 && !one_pair)//checks if guess four is the same as solution 1 and
        //that the user hasn't already correctly guessed one pair
        {
            im++;//increment imperfect match
            one_pair = true; //Set one_pair to true
            four_guess = true; //Set four_guess to true
        }
    }
 
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,pm,im); //Print our result of number of perfect and imperfect matches
    //as well as misplaced matches
    guess_number++; //Increment guess_number

 

//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_see
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    return 1;

}