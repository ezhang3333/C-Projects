;Partners: akhilm6, ethanjz2, asoni29
;
;
;Intro Paragraph
;The paragraph takes in a postfix expression entered through the keyboard
;and then outputs the postfix expression and the answer in hexadecimal. 
;Specifically, the program pushes integers to the stack and pops integers
;if it detects an operator. Furthermore, when the program detects an
;operator, it checks for stack underflow, then pops out two integers, and 
;finally performs the operation and pushes the result to the stack. This is
;repeated until the program detects a "=" at which point it prints the fina
;value in stack and stores the final result in R5. If the program detects
;any invalid inputs, the system prints out "INVALID_EXPRESSION."

.ORIG x3000


;start off by getting the input

CHAR 
GETC			;get the input from the keyboard
ST R0,S			;save R0 before begin of any operations
JSR EVALUATE	;Jump to the EVALUATE subroutine
BRnzp CHAR		;branch back to char because the new pc is one after the prev line
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;R0- carries the value that is printed out
;R5- stores the result from the operation
;R1- digit counter
;R2- temp register to check values of counters
;R6- bit counter
;

PRINT_HEX
LD R0,SPACE		;load R0 with space ascii value
OUT				;
AND R0,R0,#0	;init 
AND R3,R3,#0	;init 
AND R5,R5,#0	;init
JSR POP			;go to pop subrountine
ADD R3,R0,R3	;move the newly popped value into R3
ADD R5,R3,R5	;move the value to R5

AND R1,R1,#0 ;init digit counter
LOOP ADD R2,R1,#-4 ;check if digit counter is less than 4
BRzp DFIN

AND R6,R6,#0 ;init bit counter
AND R0,R0,#0 ;init digit

SLOOP 

ADD R2,R6,#-4 ; check if R6 is less than 4
BRzp SFIN
ADD R0,R0,R0 ;shift digit to left
ADD R3,R3,#0 ;add to check pos or neg
BRzp SK	     ;skip if pos
ADD R0,R0,#1 ;add 1 if it is neg
SK ADD R3,R3,R3 ;left shift the count in the histogram
ADD R6,R6,#1 ;increment the bit counter
BRnzp SLOOP   ;loop back for the bit shifting
SFIN

ADD R2,R0,-9 ;check if the is less than 9
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
ADD R1,R1,#1	   ;increment digit counter
BRnzp LOOP	   ;loop back after digit counter incremented
DFIN
HALT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
;your code goes here

ST R7,S7		;Save R7 before using another subroutine
OUT				;echo the value typed in



CHECK_EQUAL		;

LD R1,EQUAL		;load ascii value for equal into R1
NOT R1,R1		;
ADD R1,R1,#1	;negate R1
ADD R1,R0,R1	;add to value to see if they are the same

BRnp CHECK_SPACE ;branch to check for space if the entered value is not the equal sign


LD R1,STACK_TOP ;load the location of the top of the stack into R1
ADD R1,R1,#1	;
NOT R1,R1		;
ADD R1,R1,#1	;negate the STACk_TOP
LD R2,STACK_START	;load R2 with the location of the start of the stack
ADD R2,R1,R2	;add them together to check ifr they are equal
BRz PRINT_HEX	;branch to print hex code block	
JSR INVALID		;go to invalid subrounter



CHECK_SPACE

LD R1,SPACE		;load ascii value for sqace into R1
NOT R1,R1		;
ADD R1,R1,#1	;
ADD R1,R0,R1	;
BRnp CHECK_NUMB		;branch to check for a number
LD R7,S7		;reload R7 with the stored R7 value
RET				;

CHECK_NUMB		;check first if value is a digit then push into stack

LD R1, ZERO		;load the ascii value for ZERO
LD R2, NINE		;load the ascii value for NINE

NOT R1,R1		;
ADD R1,R1,#1	;Negate ascii value for zero and compare to value in R0
ADD R1,R0,R1	;
BRn CHECK_OPERATOR	;check to see if value is a digit if not SKIP
NOT R2,R2		;
ADD R2,R2,#1	;negate R2
ADD R2,R0,R2	;
BRp	CHECK_OPERATOR	;branch to check operator if value is not a number

ADD R0,R0,#-15	;
ADD R0,R0,#-15	;
ADD R0,R0,#-15	;
ADD R0,R0,#-3	;subtract '0' from the value
JSR PUSH		;push the number to the stack
LD R7,S7		;
RET

CHECK_OPERATOR	;check if the value is a operator 

;check if there are at least 2 items in the stack
AND R3,R3,#0	;init R3
AND R4,R4,#0	;init R4

JSR POP			;pop first number
ADD R5,R5,#0	;
BRp	INVALID		;
ADD R3,R3,R0	;store first pop into R3
JSR POP			;pop second number
ADD R5,R5,#0	;
BRp INVALID		;
ADD R4,R4,R0	;store second pop into R4

;check if it is a add


LD R0,S			;
LD R1,PLU		;
NOT R1, R1		;
ADD R1, R1, #1 ;
ADD R1, R1, R0 	;
BRnp CHECK_MINUS		;
JSR PLUS		;
JSR PUSH		;
LD R7,S7		;
RET				;

CHECK_MINUS		;
LD R1, MINUS	;
NOT R1, R1		;
ADD R1, R1, #1	;
ADD R1, R1, R0	;
BRnp CHECK_MULT
JSR MIN
JSR PUSH		;
LD R7,S7		;
RET				;

CHECK_MULT		;
LD R1, MULT	;
NOT R1, R1		;
ADD R1, R1, #1	;
ADD R1, R1, R0	;

BRnp CHECK_DIV
JSR MUL
JSR PUSH		;
LD R7,S7		;
RET				;

CHECK_DIV		;
LD R1, DIVIDE	;
NOT R1, R1		;
ADD R1, R1, #1	;
ADD R1, R1, R0	;
BRnp CHECK_EXP
JSR DIV
JSR PUSH		;
LD R7,S7		;
RET				;

CHECK_EXP		;
LD R1, EXW	;
NOT R1, R1		;
ADD R1, R1, #1	;
ADD R1, R1, R0	;
BRnp INVALID
JSR EXP
JSR PUSH		;
LD R7,S7		;
RET				;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
AND R0,R0,#0	; init R0
ADD R0,R3,R4	; add R3 and R4 and put it into R0
RET ;return back to the 
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
AND R0, R0, #0	;
NOT R3, R3		;
ADD R3, R3, #1	;
ADD R0, R4, R3	;
RET				;

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
AND R0,R0,#0	;init R0
MUL_AGAIN
ADD R0, R0, R4	;
ADD R3, R3, #-1	;
BRp MUL_AGAIN
RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
NOT R3, R3		;
ADD R3, R3, #1	;
AND R0,R0,#0	;init 
ADD R0, R0, #-1
DIV_AGAIN
ADD R0, R0, #1	;
ADD R4, R4, R3	;
BRzp DIV_AGAIN
RET				;

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

ST R4,XP		;

AND R0, R0, #0	;init 

ADD R3,R3,#-1
BRn ONE 		;
BRz FOUR		;

XAG
LD R1,XP		;
AND R0,R0,#0	;

EAG				;
ADD R0, R0, R4	;
ADD R1, R1,#-1	;
BRp EAG
AND R4, R4, #0
ADD R4,R0,R4	;
ADD R3,R3,#-1	;
BRp XAG			;
RET

ONE
ADD R0,R0,#1	;
RET
FOUR
ADD R0,R4,R0	;
RET

INVALID

LEA R0,INV	;
PUTS		;
HALT		;



;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
S7			.FILL x6000	;
S			.FILL x6001	;
NINE		.FILL x0039	;
ZERO		.FILL x0030 ;
EQUAL 		.FILL x003D ;
SPACE 		.FILL #32	;
PLU			.FILL x002B	;
MINUS		.FILL x002D	;
MULT		.FILL x002A	;
DIVIDE		.FILL x002F	;
EXW			.FILL x005E	;
INV .STRINGZ	"INVALID EXPRESSION" ;
XP 			.FILL x6002	;



.END
