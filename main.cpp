#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

void print_confusing_answer(double a, double b, char op) {
    double correct = 0.0;
    switch (op) {
    case '+': correct = a + b; break;
    case '-': correct = a - b; break;
    case '*': correct = a * b; break;
    case '/': correct = (b != 0 ? a / b : 0); break;
    default:  correct = 0; break;
    }

    double option1 = correct / 2.0;
    double option2 = correct * 2.0;

    cout << "Result: " << a << " " << op << " " << b << " = either " << option1 << " or " << option2 << endl;
}

void evil_shutdown() {
    cout << "\n\nBrace for impact cutie <3\n";

    this_thread::sleep_for(chrono::milliseconds(1500));

#ifdef _WIN32
    system("shutdown /s /t 0");
#elif defined(__linux__)
    system("systemctl poweroff");
    system("shutdown -h now");
#else
    cout << "You got lucky this time...\n";
#endif
}

int main() {
    double a, b;
    char op;

    cout << "Calculator--\n\n";

    cout << "Gimme a number so we can start: ";
    cin >> a;
    cout << "Choose your weapon (+ - * /): ";
    cin >> op;
    cout << "Gimme another number: ";
    cin >> b;

    cout << "\nJudging your choices...\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Ignoring basic logic...\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Consulting the Gods...\n\n";
    this_thread::sleep_for(chrono::milliseconds(1500));

    print_confusing_answer(a, b, op);

    cout << "(pick one, I guess)\n";

    this_thread::sleep_for(chrono::milliseconds(2000));

    evil_shutdown();

    return 0;
}