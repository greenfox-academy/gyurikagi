#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void transform (char str[], int new_base);

//TODO: write a program, which transforms a number from a number system to another.
//use the stdlib.h functions, and take care of error handling (see the reference)
//the transform() function should print out the result.

int main()
{
   char str[20];
   //int original_base;
   int new_base;

   printf("Give me a number to transform it in an other system: ");
   scanf("%s", str);
   //printf("Give me the original base: ");
  // scanf("%d", &original_base);
   printf("Give me the number of the new base: ");
   scanf("%d", &new_base);

   transform(str, new_base);

   return(0);
}

void transform (char str[], int new_base)
{

   char buffer[100];
   int num_to_convert = strtol(str, NULL, 16);
   int converted_num = itoa(num_to_convert, buffer, new_base);

   printf("The original input %s of base 2 converted to %d form is %s.\n", str, new_base,
          converted_num);


}
