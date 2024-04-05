/* Grace Lane
 * cipher.cpp
 */

#include <iostream>
#include <fstream>   // for file access
#include <vector>
#include <algorithm>


using namespace std;

const std::vector<int> NONLETTERTABLE{0,1,2,3,4,5,6,7,8,9,10,
                     11,12,13,14,15,16,17,18,19,20,
                     21,22,23,24,25,26,27,28,29,30,
                     31,32,33,34,35,36,37,38,39,40,
                     41,42,43,44,45,46,47,48,49,50,
                     51,52,53,54,55,56,57,58,59,60,
                     61,62,63,64,91,92,93,94,95,96,
                     123,124,125,126,127};

int askForFile();

int cipherFile(const string& filename);

string getInputFile();

int getShiftValue();

int main() {
    int success;
    success = askForFile();
    if (success == 1) {
        cout << endl;
        cout << "Error: cannot open file" << endl;
        return 1;
    }
    return 0;
}

int askForFile() {
    int success;
    char cont = 'y';
    int choice;
    while (cont == 'y' || cont == 'Y') {
        string filename = getInputFile();
        success = cipherFile(filename);
        if (success == 1) {
            return 1;
        }
        cout << endl;
        cout << "Would you like to enter another file? (y/n): ";
        cin >> cont;
        while (cont != 'y' && cont != 'n' && cont != 'Y' && cont != 'N') {
            cout << "Please enter a valid letter (y/n)" << endl;
            cout << "Would you like to enter another file? (y/n): ";
        }
    }
    return 0;
}

int cipherFile(const string& filename) {
    ifstream inputFile;
    inputFile.open(filename);

    if (inputFile.is_open()) {    // if file is successfully opened
        string output;
        cout << "Please enter the output file name:";
        cin >> output;
        ofstream outputFile;
        outputFile.open(output);

        int shift = getShiftValue();
        char letter;
        int ascii;
        while (inputFile.get(letter)) {
            if (letter != EOF) {
                ascii = (int)letter;
                auto it = find(NONLETTERTABLE.begin(), NONLETTERTABLE.end(), ascii);
                if (it == NONLETTERTABLE.end()) {     // if the character is letter character
                    if (ascii >= (int)'a' && ascii <= (int)'z') {      // if the letter is lowercase to begin with
                        if ((ascii + shift) < (int)'a') {
                            letter = (char)((int)'z' - ((int)'a' - (ascii + shift) - 1));
                        } else if ((ascii + shift) > (int)'z') {
                            letter = (char)((int)'a' + ((ascii + shift) - (int)'z' - 1));
                        } else {
                            letter = (char) (ascii + shift);
                        }
                    } else if (ascii >= (int)'A' && ascii <= (int)'Z') {      // if the letter is uppercase to begin with
                        if ((ascii + shift) < (int)'A') {
                            letter = (char)((int)'Z' - ((int)'A' - (ascii + shift) - 1));
                        } else if ((ascii + shift) > (int)'Z') {
                            letter = (char)((int)'A' + ((ascii + shift) - (int)'Z' - 1));
                        } else {
                            letter = (char) (ascii + shift);
                        }
                    }
                    outputFile << letter;
                } else {    // if the character in the input file is a non-letter character, then just input it into the file
                    outputFile << letter;
                }
            }
        }
        outputFile.close();
    } else {           // if file was not successfully opened return a 1
        return 1;
    }
    inputFile.close();
    return 0;
}

string getInputFile() {
    string filename;
    cout << endl;
    cout << "Please enter the text file to be converted:";
    cin >> filename;
    return filename;
}

int getShiftValue() {
    int shift;
    cout << endl;
    cout << "Please enter the value to shift by (negative shifts left and positive shifts right):";
    cin >> shift;
    return shift;
}