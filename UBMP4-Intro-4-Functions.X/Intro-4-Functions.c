/*==============================================================================
Project: Intro-4-Functions
Date:    May 16, 2021
This program demonstrates the use of functions, and variable passing between
the main and function code.
Additional program analysis and programming activities examine function code
location, function prototypes, and reinforce the concepts of global and local
variables.
==============================================================================*/
 
#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions
 
#include    "UBMP4.h"           // Include UBMP4 constants and functions
 
// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.
 
// Button constant definitions
const char noButton = 0;
const char UP = 1;
const char DOWN = 2;
 
// Program variable definitions
unsigned char LED5Brightness = 125;
unsigned char button;


int main(void)
{
   OSC_config();               // Configure internal oscillator for 48 MHz
   UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
   while(1)
    {

       // Activate bootloader if SW1 is pressed.
       if(SW1 == 0)
       {
           RESET();
       }
   }
}



// Move the function code to here in Program Analysis, step 5.
 
 
/* Program Analysis
*
* 1.   Which function in this program will run first? How do you know?
*
The main function will be called first because that is its purpose, it allows a place for the program to start.
However, the global variables and functions above the main function initialize/provide the information that invokes the main function.
 
* 2.   What is the purpose of the 'unsigned char' variable type declaration in
*      the button_pressed() function? Is it used by this function to receive
*      a variable from, or return a variable to the main code?
*
The purpose of the 'unsigned char' variable type declaration is to store 8 bit values, which are 8 bit variables that are passed onto the main function.
Yes, it is used by this function because in the main function, the line "button = button_pressed()" allows the contents inside the function to be received and returned by the main function.

* 3.   How does the function call statement 'button = button_pressed();' in the
*      main code support your answer in 2, above?
 
The function call statement 'button = button_pressed(); supports my answer because it allows the main function to receive the information inside the function.
Without this line, the brightness controlling lines would not function.
*
* 4.   What is the purpose of the 'unsigned char' variable type declaration in
*      the pwm_LED5() function? Where does the value of the variable come from?
*      Where does this value get stored in the function?
 
The purpose of the 'unsigned char' variable type declaration is the program to work with positive 8 bit values, since that is what the MCU is most efficient at handling.
The value of this variable comes when you pass an arguement in when calling the function, since it is a parameter. Plus, it is a local variable inside the pwm_LED5 function.

*
* 5.   C language compilers typically read through the entire program in a
*      single pass, converting C code into machine code. The two functions,
*      button_pressed() and pwm_LED5(), are located above the main() function
*      so that their memory locations and variable requirements will be
*      determined before the rest of the program compiles. When the compiler
*      interprets the function call statements in the main code, it already
*      knows where those functions are be in memory and which memory locations
*      are used by their variables.
*
*      Try moving the button_pressed() and pwm_LED5() functions to below the
*      closing brace of the main() function, and build the code. What happens?
 
An error/build failed occurs because the compiler can not interpret the code since functions are not declarable.
*
*      The compiler should have reported an error since it did not understand
*      what the function call was referring to because it had not seen the
*      function before the function call. We can eliminate this error by adding
*      a function prototype above the main code. The function prototype is like
*      the function declaration (the first line of the function), and lets the
*      compiler know both the function's name and the type of variables that
*      the function will use. A C language 'linker' program will take care of
*      sorting out the names and memory locations of all of the functions and
*      variables in a program following the compilation step.
*
*      Let's try this out. Leave the functions in their new location, below
*      the main() function, and add the two function prototypes (shown below)
*      above main(), in the location where the functions were originally
*      located:
 
unsigned char button_pressed(void);
 
void pwm_LED5(unsigned char);
 
*      What is the difference between the function prototype for pwm_LED5()
*      and the actual pwm_LED5() function declaration statement later in the
*      code?
 
The difference between the prototype and actual statement is that the pwm_LED5 protoype has a different parameter.
Instead of unsigned char pwmvalue, it is simply unsigned char.
*
* 6.   Building the program with the added function prototypes should now work
*      without generating errors, just as it did in the original program.
*
*      In C, functions may be located above the code that calls them, below
*      their function calls if a function prototype is supplied, or even in
*      completely separate files known as function libraries.
*
*      Function libraries are typically joined to your project's main '.c' file
*      using an 'include' statement to a '.h' header file containing both
*      variable definitions and the function prototypes for an associated C
*      file which contains the actual function code.
*
*      The '#include "UBMP4.h"' statement near the top of this program is an
*      example of a statement that adds external functions to our program. The
*      'UBMP4.h' file contains function prototypes for functions located in
*      the 'UBMP4.c' file, along with various symbolic constants used by both
*      our program and the code in the UBMP4.c functions.
*
*      Open the UBMP4.c file to find the OSC_config() and UBMP4_config()
*      functions called from the main() function in this program. Are any
*      values passed between this code and the two setup functions? How do
*      you know?

There are several values that are being passed because in this file, the comments beside the called functions tell the reason for being called/what it does. Both functions are called within the main function.
The OSC_config function configures the oscillator for the piezo beeper, and the UBMP4_config function configures the input and output values and devices.
Both are called to be able to program the board. 
*
* 7.   The 'button' variable is a global variable because it was assigned
*      at the beginning of the program, outside of any functions. Global
*      variables are available to all functions. How does the 'button' variable
*      get assigned a value? In which function does this occur?
 
The 'button' variable gets assigned a value by getting assigned to equal button_pressed function.
It equals to what is being returned in the function to be able to use the button_pressed function in the main function to increase and decrease LED5.
*
* 8.   Which variable does the value of LED5Brightness get transferred to in
*      the pwm_LED5() function? Is this variable global, or local to the LED
*      function? Could the pwm_LED5 function use the LED5Brightness variable
*      directly, instead of transferring its value to another variable?
*
The variable that value of LED5Brightness gets transferred to is the local variable pwmValue, because the pwm_LED5 function could use LED5Brightness directly.
This is because both variables are used to create the possibility of adjusting the brightness of the LED.
* Programming Activities
*
* 1.   It might be useful to have a button that instantly turns LED D5 fully
*      on or off instead of waiting for it to brighten and dim while the UP
*      and DOWN buttons are held to change the PWM duty cycle. But, PWM dimming
*      dimming capability is still a useful feature that should be retained.
*
*      Modify the button_pressed() and main() functions to use SW3 as an
*      instant on button, and SW2 as an instant off button. Pressing either of
*      these buttons will over-write the current LED5Brightness value with
*      either 255 or 0, while still allowing SW4 and SW5 to adjust the
*      brightness in smaller increments when pressed.

unsigned char button_pressed(void)
{
   if(SW4 == 0 || SW3 == 0)      // added SW3 == 0
   {
       return(UP);               //added both to correspond with the functions of the other buttons
   }
   else if(SW5 == 0 || SW2 == 0) //added SW2 == 0
   {
       return(DOWN);
   }
   else
   {
       return(noButton);
   }
}

void pwm_LED5(unsigned char pwmValue)
{
   for(unsigned char t = 255; t != 0; t --)
   {
       if(pwmValue == t)
       {
           LED5 = 1;
       }
       __delay_us(20);
   }
   // End the pulse if pwmValue < 255
   if(pwmValue < 255)
   {
       LED5 = 0;
   }
}

int main(void)
{
   OSC_config();               // Configure internal oscillator for 48 MHz
   UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
   while(1)
    {
       // Read up/down buttons and adjust LED5 brightness
       button = button_pressed();
      
       if(button == UP && LED5Brightness < 255)
       {
           LED5Brightness += 1;
       }
 
       if(button == DOWN && LED5Brightness > 0)
       {
           LED5Brightness -= 1;
       }
       if(button == DOWN & SW2 == 0){   //added this if statement
           LED5Brightness = 0;
       }
       if(button == UP & SW3 == 0){     //added this if statement
           LED5Brightness = 254;
       }

       // PWM LED5 with current brightness
       pwm_LED5(LED5Brightness);
 

*
* 2.   Create a function that will return a number from 1-4 corresponding to
*      which of the SW2 to SW5 switches is pressed, or return 0 if no switches
*      are pressed. Then, create a function that will accept a number from 1 to
*      4 that lights the corresponding LED beside each button.
//Activity 2 constant definitions 
const char ONE = 1;
const char TWO = 2;
const char THREE = 3;
const char FOUR = 4;
unsigned char return_Numbers(void){
    if(SW2 == 0){
        return(ONE);
    }
    else if(SW3 == 0){
        return(TWO);
    }
    else if(SW4 == 0){
        return(THREE);
    }
    else if(SW5 == 0){
        return(FOUR);
    }
    else{
        return(noButton);
    }
}


int main(void)
{
   OSC_config();               // Configure internal oscillator for 48 MHz
   UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
   while(1)
    {
    button = return_Numbers();
    if(button == ONE){
        LED3 = 1;
    }
    if(button == TWO){
        LED4 = 1;
    }
    if(button == THREE){
        LED5 = 1;
    }
    if(button == FOUR){
        LED6 = 1;
    }
    if(button == noButton){
        LED3 = 0;
        LED4 = 0;
        LED5 = 0;
        LED6 = 0;
    }
*
* 3.   Create a sound function that receives a parameter representing a tone's
*      period. Modify your button function, above, to return a variable that
*      will be passed to the sound function to make four different tones.
unsigned int period1 = 187;
unsigned int period2 = 371;
unsigned int period3 = 619;
unsigned int period4 = 924;

int main(void)
{
   OSC_config();               // Configure internal oscillator for 48 MHz
   UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
   while(1)
    {
                                 
        if(SW2 == 0){
            BEEPER = !BEEPER;
            __delay_us(period1);
        }
        if(SW3 == 0){
            BEEPER = !BEEPER;
            __delay_us(period2);
        }
        if(SW4 ==0){
            BEEPER = !BEEPER;
            __delay_us(period3);
        }
        if(SW5 == 0){
            BEEPER = !BEEPER;
            __delay_us(period4);
        }
*
* 4.   A function that converts an 8-bit binary value into its decimal
*      equivalent would be useful for helping us to debug our programs. Create
*      a function that converts an 8-bit binary number into three decimal
*      character variables representing the hundreds, tens and ones digits
*      of the binary number passed to it. For example, passing the function
*      a value of 142 will result in the hundreds variable containing the
*      value 1, the tens variable containing 4, and the ones variable 2. How
*      could you test this function to verify that it works? Try it!

//binary code inputs
char eighth2 = 1;
char seventh2 = 0;
char sixth2 = 1;
char fifth2 = 0;
char fourth2 = 0;
char third2 = 0;
char second2 = 1;
char first2 = 0;

unsigned char binaryValues(void){   //values of binary
    if(eighth2 == 1){
        eighth2 = 128;
        return(eighth2);
    }
    if(seventh2 == 1){
        seventh2 = 64;
        return(seventh2);
    }
    if(sixth2 == 1){
        sixth2 = 32;
        return(sixth2);
    }
    if(fifth2 == 1){
        fifth2 = 16;
        return(fifth2);
    }
    if(fourth2 == 1){
        fourth2 = 8;
        return(fourth2);
    }
    if(third2 == 1){
        third2 = 4;
        return(third2);
    }
    if(second2 == 1){
        second2 = 2;
        return(second2);
    }
    if(first2 == 1){
        first2 = 1;
        return(first2);
    }
}

int main(void)
{
   OSC_config();               // Configure internal oscillator for 48 MHz
   UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
   while(1)
    {
    
    button = binaryValues();
    unsigned char decimalNUM = eighth2 + seventh2 + sixth2 + fifth2 + fourth2 + third2 + second2 + first2;
    
    //variables for place value
    unsigned char varHundred = 0;
    unsigned char varTen = 0;
    unsigned char varOne = 0;

//calculating hundreds
    if(decimalNUM >= 0 && decimalNUM <= 99){
        varHundred = 0;
    }
    if(decimalNUM >= 100 && decimalNUM <= 199){
        varHundred = 1;
    }
    if(decimalNUM >= 200 && decimalNUM <= 255){
        varHundred = 2;
    }

//calculating tens
    if((decimalNUM >= 0 && decimalNUM <= 9) || (decimalNUM >= 100 && decimalNUM <= 109) || (decimalNUM >= 200 && decimalNUM <= 209)){
        varTen = 0;
    }
    if((decimalNUM >= 10 && decimalNUM <= 19) || (decimalNUM >= 110 && decimalNUM <= 119) || (decimalNUM >= 210 && decimalNUM <= 219)){
        varTen = 1;
    }
    if((decimalNUM >= 20 && decimalNUM <= 29) || (decimalNUM >= 120 && decimalNUM <= 129) || (decimalNUM >= 220 && decimalNUM <= 229)){
        varTen = 2;
    }
    if((decimalNUM >= 30 && decimalNUM <= 39) || (decimalNUM >= 130 && decimalNUM <= 139) || (decimalNUM >= 230 && decimalNUM <= 239)){
        varTen = 3;
    }
    if((decimalNUM >= 40 && decimalNUM <= 49) || (decimalNUM >= 140 && decimalNUM <= 149) || (decimalNUM >= 240 && decimalNUM <= 249)){
        varTen = 4;
    }
    if((decimalNUM >= 50 && decimalNUM <= 59) || (decimalNUM >= 150 && decimalNUM <= 159) || (decimalNUM >= 250 && decimalNUM <= 259)){
        varTen = 5;
    }
    if((decimalNUM >= 60 && decimalNUM <= 69) || (decimalNUM >= 160 && decimalNUM <= 169)){
        varTen = 6;
    }
    if((decimalNUM >= 70 && decimalNUM <= 79) || (decimalNUM >= 170 && decimalNUM <= 179)){
        varTen = 7;
    }
    if((decimalNUM >= 80 && decimalNUM <= 89) || (decimalNUM >= 180 && decimalNUM <= 189)){
        varTen = 8;
    }
    if((decimalNUM >= 90 && decimalNUM <= 99) || (decimalNUM >= 190 && decimalNUM <= 199)){
        varTen = 9;
    }

    
//calculating ones
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 0){
        varOne = 0;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 1){
        varOne = 1;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 2){
        varOne = 2;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 3){
        varOne = 3;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 4){
        varOne = 4;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 5){
        varOne = 5;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 6){
        varOne = 6;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 7){
        varOne = 7;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 8){
        varOne = 0;
    }
    if((decimalNUM - (varHundred * 100) - (varTen * 10)) == 9){
        varOne = 9;
    }

//test code
    if(varHundred == 1 && varTen == 6 && varOne == 2 && SW2 == 0){
        LED5 = 1;
    }

*/