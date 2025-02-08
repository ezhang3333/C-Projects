#include <stdlib.h>
#include <stdio.h>
//Completed by Akhil Morisetty(akhilm6)
/* The semiprime.c program prints out the semiprimes that exist 
along the interval given through the user input. There were multiple errors 
in the program that have been fixed. The first error occured in the is_prime function.
The error was that the function returned 1 if the number was not a prime and 0 if the number was a prime. 
The effect of that error was that all numbers that are not semiprimes would be printed out that exist along the interval
The second error was the lack of a break command in the print_semiprimes function.
The effect of this error was that whenever the print_semiprimes function was called each of the semiprimes would
get printed multiple times created duplicated in the output. The third error was not setting the "ret" to 1 when the number is a semiprime
within the interval. The effect of the error is that the return value would always be equal 0 regardless of whether semiprime exist along the 
interval or not. The final error was in the print_semiprimes function where integer k was set to k = i%j. Instead k should be set as 
k = i/j. The effect of the error is that the remainder of the quotient of the expression is checked as a prime not the actual quotient.
This would cause the wrong numbers to be printed out as semi-primes.
*/


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j < i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
