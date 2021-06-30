/*
This program prompts the user for a file name, then does a limited number of syntax checks on the file as an assembly language program.
The three valid opcode are: ret, inc, je
ret cannot have any following operand, both inc and je should have exactly one operand
Any other opcode or operand number miss-match, the program will return corresponding error messages.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string filename;
    // the 3 valid opcode
    const string RET = "ret",
        JUMP_IF_EQ = "je",
        INC = "inc";
    string opcode, operand, rest_of_line;
    //valid opcode checker
    bool valid_opcode = false;

    cout << "This program displays information about a set of Intel-like assembly instructions" << endl;
    cout << endl << "Enter name of file with instructions (no spaces): ";
    cin >> filename;
    //read in file name
    ifstream input(filename);
    int line = 1;
    int expected_operand = 0;
    while (input >> opcode)
    {
        cout << line << ". ";
        // 3 valid opcode return
        if (opcode == RET)
        {
            cout << "The return opcode" << endl;
            valid_opcode = true;
            expected_operand = 0;
        }
        else if (opcode == INC)
        {
            cout << "The increment opcode" << endl;
            valid_opcode = true;
            expected_operand = 1;
        }
        else if (opcode == JUMP_IF_EQ)
        {
            cout << "The jump if equal opcode" << endl;
            valid_opcode = true;
            expected_operand = 1;
        }
        else  // invalid opcode return
        {
            cerr << "Opcode not recognized: " << opcode << endl;
            valid_opcode = false;
        }

        //Handle operands
        getline(input, rest_of_line);
        istringstream operands(rest_of_line);
        //operand number tracker 
        int count = 0;
        string temp;
        if (expected_operand == 0 && valid_opcode == true) {
            if (operands >> operand) { // at least one operand i.e not valid
                cerr << opcode << " should not have any operands, but has: " << operand << endl;
            }
        }
        else if (expected_operand == 1 && valid_opcode == true) {
            while (operands >> operand) {
                count++;
                if (count == 2) { //exit loop while number of operand equal to 2
                    break;
                }
                temp = operand;
            }
            if (count == 1) { //correct output
                cout << "operand " << count << " : " << operand << endl;
            }
            else if (count == 0) {  //operand number miss-match
                cerr << opcode << " should have one operand, but does not" << endl;
            }
            else { //operand number miss-match
                cerr << opcode << " should only have one operand, but has operands " << temp << " and " << operand << endl;
            }
        }
        //line tracker +1
        if (valid_opcode == true)line++;
    }
    input.close();
    return 0;

}