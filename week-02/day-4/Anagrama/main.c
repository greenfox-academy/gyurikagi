#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_expression (char str[]);

int main()
{
    char expression1[255];
    char expression2[255];

    //cleaning expression1 array
     for(int i = 0; i < 255; ++i){
        expression1[i] = '\0';
        }

    //cleaning expression2 array
     for(int i = 0; i < 255; ++i){
        expression2[i] = '\0';
        }
    // Give me your first expression and press enter
    printf("\n Give me your first expression and press enter!\n");
    //Put this expression in an array name is expression1
    int index1 = 0;
	char character1 = getchar();
	while (character1 != '\n') {
		expression1[index1] = character1;
		index1++;
		character1 = getchar();
	}
	expression1[index1] = 0;

    // Give me your second expression and press enter
    printf("\n Give me your second expression and press enter!\n");
    //Put this expression in an array name is expression1
    int index2 = 0;
	char character2 = getchar();
	while (character2 != '\n') {
		expression2[index2] = character2;
		index2++;
		character2 = getchar();
	}
	expression2[index2] = 0;
    //sort expression1
    sort_expression (expression1);
    //sort expression2
    sort_expression (expression2);
    //compare sorted expressions ( if statement - write the answer
    if (strcmp(expression1, expression2) == 0 ) {
        printf("This is Anagrama");
        } else {
        printf("This is not Anagrama");
        }

    return 0;
}
//make a function sorting expression
void sort_expression (char str[])
{
    int temporary = 0;
    int length = strlen(str);

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (str[i] < str[j]) {
                temporary = str [i];
                str [i] = str [j];
                str [j] = temporary;
            }
        }
    }

}

