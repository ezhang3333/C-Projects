;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

;Akhil Morisetty(akhilm6), Aashay Soni(asoni29), Ethan Zhang(Ethanjz2) worked on this mp
;Our program prints out the values stored in the histogram with each letter printed out in
;front before the value in the histogram get printed out. Our program begins by setting the corresponding 
;registers to the addresses and values of the histogram and then begins looping through to print out
;each value in the histogram. Specifically, based on the flowchart given in lab1 we implement a block of
;code that take the value from the histogram and prints that out. Finally, the loop take the value in the histogram
;and stores R0 with the corresponding ascii value so that it can be printed out properly.

;Register Table
;R0 - Carries the value that is to be printed out such as characters,numbers, and values
;R1 - Carries that value that is in the histogram/ the count of letters that appear in the string
;R2 - Carries the address of the histogram and is incremented throughout the program
;R3 - Is the counter for the whole program for printing each letter value and is set to 27 at the start of the program
;R4 - Carries the ascii value for each of the letters that are printed out in the beginning of each line
;R5 - The digit counter in the loop for printing out the hexadecimal
;R6 - The bit counter in the loob for printing out the hexadecimal
;R7 - Temporary register used to check register values throughout program


AND R2,R2,#0 ;init R2
LD R2, HIST_ADDR ;init address of the histogram
LD R3, NUM_BINS ; set R3 to 27 to loop through the histogram


;now set R4 to the beginning ascii value 64 to start the letters of the alphabet
AND R4, R4, #0
ADD R4,R4,#15
ADD R4,R4,#15
ADD R4,R4,#15
ADD R4,R4,#15
ADD R4,R4,#4 ;R4 set to 64

NLETTER
LDR R1,R2,#0 ;Load R1 with the value from the histogram address in R2
ADD R0,R4,#0 ;Store R0 with the ascii value of the letter to be printed
OUT ;prints the first character in the ascii value table
LD R0, SPACE ;Load R0 with the ascii value for space
OUT	     ;print





;M_FUNCTION

AND R5,R5,#0 ;init digit counter
LOOP ADD R7,R5,#-4 ;check if digit counter is less than 4
BRzp DFIN

AND R6,R6,#0 ;init bit counter
AND R0,R0,#0 ;init digit

SLOOP 

ADD R7,R6,#-4 ; check if R6 is less than 4
BRzp SFIN
ADD R0,R0,R0 ;shift digit to left
ADD R1,R1,#0 ;add to check pos or neg
BRzp SK	     ;skip if pos
ADD R0,R0,#1 ;add 1 if it is neg
SK ADD R1,R1,R1 ;left shift the count in the histogram
ADD R6,R6,#1 ;increment the bit counter
BRnzp SLOOP   ;loop back for the bit shifting
SFIN

ADD R7,R0,-9 ;check if the is less than 9
BRnz TSKIP	   ;skip if the digit less than 9
ADD R0,R0,#15	   ;add A - 10 to the digit
ADD R0,R0,#15	   ;
ADD R0,R0,#15	   ;
ADD R0,R0,#10	   ;
BRnzp DON	   ;branch after addition finished
TSKIP 
ADD R0,R0,#15	   ;
ADD R0,R0,#15	   ;
ADD R0,R0,#15	   ;
ADD R0,R0,#3	   ;add '0' to R0
DON
OUT
ADD R5,R5,#1	   ;increment digit counter
BRnzp LOOP	   ;loop back after digit counter incremented
DFIN
LD R0,NEWL	   ;load R0 with the ascii value for NEWL
OUT
ADD R2,R2,#1	   ;increment the histogram address to move onto the next value		
ADD R4,R4,#1	   ;increment the ascii value to move on to the next letter in the alphabet
ADD R3,R3,#-1	   ;decrement the letter counter until all 27 letter have been printed
BRp NLETTER        ;branch back until all 27 values have been printed






	
	
	
	

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
SPACE		.FILL #32
NEWL		.FILL #10

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END






