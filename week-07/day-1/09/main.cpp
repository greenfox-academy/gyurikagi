#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * Create a function that prints a multiplication table with a given base number.
 * It should take the base number as a parameter, and print the output to the console.
 *
 * The output should look like this for 5 as base:
 *   1 * 5 = 5
 *   2 * 5 = 10
 *   3 * 5 = 15
 *   4 * 5 = 20
 *   5 * 5 = 25
 *   6 * 5 = 30
 *   7 * 5 = 35
 *   8 * 5 = 40
 *   9 * 5 = 45
 *   10 * 5 = 50
 *
 *  If the function gets invalid parameter
 *  Negative numbers are invalid parameters.
 *  It should throw an exceptions
 */

 int get_a_number(){
    int num = 0;
    cout << "Enter a number: \n";
    cin  >> num;
    return num;
}



int main() {
    try {
    int base = get_a_number();
    if (base < 0){
        throw runtime_error ("Invalid parameter\n");
    }

    for ( int i = 1; i < 11; ++i){
        cout << i << "\t*\t" << base << " \t=\t " << i * base << endl;
    }
    }
    catch (runtime_error &err) {
        cout << err.what();
    }

  return 0;
}
