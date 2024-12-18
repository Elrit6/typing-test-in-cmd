#include <conio.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

string text;

string getFile() {
    system("cls");
    ifstream file("text.txt");
    if (!file) {
        return "No file found. Place the txt file in the program's directory and rename it to 'text.txt'.";
    }
    string line, text;
    while (getline(file, line)) {
        text += line;
    }
    file.close();
    return text;
}

int getAcc(const size_t& progress, const size_t& errors) {
    return progress ? 100 - 100 * errors / progress : 0;
}

void displayText(size_t& progress, size_t& errors, const clock_t& startTime) {   
    string buffer;
    int acc = getAcc(progress, errors);
    buffer += 
        "(" + to_string(progress) + "/" + to_string(text.size()) + ") (" + // progress
        to_string((clock() - startTime) / 1000) + "s) (err: " +           // time
        to_string(errors) + ") (" + to_string(acc) + "%)\n\n";           // errors & accuracy
    for (size_t i = 0; i < text.size(); i++) {
        if (i > progress - 1 || progress == 0) {
            buffer += text[i];
        } else {
            buffer += "\033[42m" + string(1, text[i]) + "\033[0m";
        }
    }
    system("cls");
    cout << buffer << endl;
}

void stopTest(const size_t& progress, const size_t& errors, const clock_t& startTime) {
    float elapsedTime = float(clock() - startTime) / 1000;
    int acc = getAcc(progress, errors);
    system("cls");
    cout 
        << "\ntime: " << to_string(elapsedTime)
        << "s\naccuracy: " << to_string(acc)
        << "%\nerrors: " << to_string(errors)
        << "\npress any key to restart";
    Sleep(2000);
    while (_kbhit()) {
        _getch();
    } // buffer clear
    while (true) {
        if (_kbhit()) {
            _getch();
            return;
        }
    }
}

void runTest() {
    system("cls");
    size_t progress = 0, errors = 0;
    clock_t startTime = clock();
    displayText(progress, errors, startTime);
    while (true) {
        if (progress == text.size()) {
            stopTest(progress, errors, startTime);
            return;
        } else if (_kbhit()) {
            char ch = _getch();
            if (ch == text[progress]) {
                progress++;
            } else {
                errors++;
            }
            displayText(progress, errors, startTime);
        }
    }    
}

int main() {
    text = getFile();
    while (true) {
        runTest();
    }
}   

