#include <stdio.h>
void main()
{
  char ch;
  ch = '+'; 
  double f = 0.0, a = 10, b = 20; // it needs to be a double to make the result with decimal
  printf("ch = %c\n", ch);
  switch (ch) //case +
 {
 case '+': f = a + b; printf("f= %f\n", f);
   break;
 case '-': f = a - b; printf("f= %f\n",f);
   break;
case '*': f = a * b; printf("f= %f\n",f);
  break;
 case '/': f = a / b; printf("f= %f\n",f);
   break;
 default: printf("invalid operator\n");
   break;
 }
  ch = '-';
  a = 10, b = 20;
 printf("ch = %c\n", ch);
 switch (ch)  //case -
 {
 case '+': f = a + b; printf("f = %f\n", f);
   break;
case '-': f = a -b; printf("f = %f\n", f);
  break;
 case '*': f = a *b; printf("f = %f\n", f);
   break;
 case '/': f = a /b; printf("f = %f\n", f);
   break;
 default: printf("invalid operator\n");
   break; 
}
  ch = '*';
  a = 10, b = 20;
 printf("ch = %c\n", ch);
 switch (ch)      // case *
 {
 case '+': f = a + b; printf("f = %f\n", f);
   break;
 case '-': f = a -b; printf("f = %f\n", f);
   break;
 case '*': f = a *b; printf("f = %f\n", f);
   break;
 case '/': f = a /b; printf("f = %f\n", f);
   break;
 default: printf("invalid operator\n");
   break;
 }
  ch = '/';
  a = 10, b = 20;
 printf("ch = %c\n", ch);
 switch (ch)       //case /
 {
 case '+': f = a + b; printf("f = %f\n", f);
   break;
 case '-': f = a -b; printf("f = %f\n", f);
   break;
 case '*': f = a *b; printf("f = %f\n", f);
   break;
 case '/': f = a /b; printf("f = %f\n", f);
   break;
 default: printf("invalid operator\n");
   break; 
}
  ch = '%';
  a = 10, b = 20;
 printf("ch = %c\n", ch);
 switch (ch)       //case%
 {
 case '+': f = a + b; printf("f = %f\n", f);
   break;
 case '-': f = a -b; printf("f = %f\n", f);
   break;
 case '*': f = a *b; printf("f = %f\n", f);
   break;
 case '/': f = a /b; printf("f = %f\n", f);
   break;
 default: printf("invalid operator\n");
   break;
 }

 int c = 0;
 while(c < 5)      //while loop to accept 5 input from the user
   {
     scanf("\n%c", &ch);
     switch(ch)
       {
 case '+': f = a + b; printf("f = %0.1f\n", f);
   break;
 case '-': f = a - b; printf("f = %0.1f\n", f);
   break;
 case '*': f = a * b; printf("f = %0.1f\n", f);
   break;
 case '/': f = a / b; printf("f = %0.1f\n", f);
   break;
 default: printf("invalid operator\n");
   break; 
       }
       c++;
   }
}

