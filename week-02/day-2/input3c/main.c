#include <stdio.h>
int main()
{
    //as you know, a character is represented as a numeric value(ASCII value) in the memory
    //write a function which asks for one charcter and prints out the character in character format then in ASCII too
    printf("Type in one character then press enter: \n");
    char char_to_ascii = getch();
    printf("ASCII value of character %c = %d\n", char_to_ascii , char_to_ascii );

    return 0;
}
