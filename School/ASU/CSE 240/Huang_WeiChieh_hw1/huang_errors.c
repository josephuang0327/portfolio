#include <stdio.h>


// CSE 240 Code with Errors
// Before starting this assignment, please compile and run this program.
// You will first notice that the program will not compile. Fix the errors and define the error types.
// Next, you will notice that the program is printing incorrect information. Fix the errors and define those error types.

int main(int argc, char** argv)
{
  int problem = 1;

  // problem 1
  // The statement below should prevent compilation, correct the error(s).(2 points)
  printf("Problem #%d\n", problem);
  int value = 50;
  printf("Integer value is %d\n", value);

  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (1 points)
  // Your answer should be either Syntactic, Semantic, or Contextual.

  printf("#1 - Error type: <Syntatic> \n\n"); // syntax error is variable, type, name and initialization.
  problem++;




  // Problem 2:
  // Numbers are numbers aren't they?  correct the error(s)(2 points)
  printf("Problem #%d\n", problem);
  double iWantADecimalValue = 5.5;
  printf("Value: %f should be 5.5\n", iWantADecimalValue);

  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (1 points).
  // Your answer should be either Syntactic, Semantic, or Contextual.

  printf("#2 - Error Type: <Semantic> \n\n"); // initialize the wrong type which change the meaning
  problem++;




  // Problem 3:
  // Half of 50 is 25, why is the program printing that half of 10 is 0? Correct the error(s)(2 points)
  printf("Problem #%d\n", problem);
  int fullValue = 50;

  printf("Half of %d is %d\n", fullValue, (fullValue /2));

  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (1 points).
  // Your answer should be either Syntactic, Semantic, or Contextual.

  printf("#3 - Error Type: <Semantic> \n\n"); // the calculation was wrong which change the meaning.
  problem++;






  // Problem 4:
  // Integer variable amIWrong has been initialized to 50, why does the program seem to think otherwise? Correct the error(s) (2 points).
  printf("Problem #%d\n", problem);
  int amIWrong = 50;

  if (amIWrong == 100)
  printf("x is equal to 100.\n");
  if (amIWrong > 100)
  printf("x is greater than 100.\n");
  if (amIWrong < 100)
  printf("x is less than 100.\n");

  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
  // Your answer should be either Syntactic, Semantic, or Contextual.

  printf("#4 - Error Type: <Semantic> \n\n"); // it is missing a '=' which change the meaning
  problem++;




  // Problem 5:
  // Surely, 10 is an even number. Why is the program printing that 10 is an odd number? Correct the error(s) (1 points).
  printf("Problem #%d\n", problem);
  int amIEven = 10;

  if (amIEven % 2 == 0)
    printf("%d is an even number.\n", amIEven);
  if (amIEven % 2 != 0)
    printf("%d is an odd number.\n", amIEven );

  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
  // Your answer should be either Syntactic, Semantic, or Contextual.

  printf("#5 - Error Type: <Semantic> \n\n"); // the sign was wrong, and it change the behavior.
  problem++;





  // Problem 6:
  // This bit of code is meant to print "Hello World!". Correct the error(s) (2 points).
  printf("Problem #%d\n", problem);
  printf("Hello %s\n", "World!");

  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (1 points).
  // Your answer should be either Syntactic, Semantic, or Contextual.

  printf("#6 - Error Type: <Contextual> \n\n"); // this is a context error
  problem++;

  printf("Problem #%d\n", problem);
  
  
  
  
  // Problem 7: Did you notice it?
  // There is another error in here ... look at your output... find it and fix it
  // Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
  // Your answer should be either Syntactic, Semantic, or Contextual.
  
  printf("#7 - Error Type: <Contextual> \n\n"); // The problem number was incorrect


}
