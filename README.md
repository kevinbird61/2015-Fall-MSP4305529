# 2015-Fall-MSP430f5529
Some useful note and code.

Every file have "main.c" which is main program.

And some fraction image or user script in it.

##About "finalterm" : 

###1. There comes the table created method :
* 0000 - 0000 =>dash,dot,dash,dot - dash,dot,dash,dot
* read bit => if bit is 1 , set filter on , 
* delay is unit and led light up ; 
* if bit is 0, set filter off, delay is unit*3 and light off .
* Count until 8 and than skip to next character.