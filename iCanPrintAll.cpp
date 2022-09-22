#include <iostream>

using namespace std;

void iCanPrintAll(const char* text) {
    while (*text) {
        if (*text == '%') {
            if (*(text + 1) != '%') {
                cout << "\nERROR! You forgot arguments.";
                break;
            }
            else {
                cout << "%";
                text++;
            }
        }
        else {
            cout << *text++;
        }
    }
    cout << "\n\n";
}

template<typename T, typename ... Args>
void iCanPrintAll(const char* text, T value, Args ...args) {
    while (*text) {
        if (*text == '%') {
            if (*(text + 1) == '%') {
                cout << "%";
                text++;
            }
            else {
                switch (*(++text)) {
                case 'c':
                    cout << static_cast<char>(value);
                    break;
                case 's':
                    cout << value;
                    break;
                case 'd':
                case 'i':
                    cout << static_cast<int>(value);
                    break;
                case 'x':
                case 'X':
                    cout << hex << value;
                    break;
                case 'u':
                    cout << dec << value;
                    break;
                case 'f':
                case 'F':
                    cout << static_cast<float>(value);
                    break;
                case 'e':
                case 'E':
                    cout << scientific << value;
                    break;
                case 'n':
                    break;
                case 'p':
                    cout << &value;
                    break;
                default:
                    break;
                }
                text += 2;
                iCanPrintAll(text, args...);
                return;
            }
        }
        cout << *text++;
    }
    //cout << endl;
}

int main()
{
    iCanPrintAll("ewrtfgf %d   %f    %i", 'f', 'f', 765432.654);
    iCanPrintAll("ewrtfgf %d  %%   %f    %i", 'f', 'f');
    iCanPrintAll("ewrtfgf");
    iCanPrintAll("first", "second");        //don`t print
    iCanPrintAll("sdfgh", 456, 'e', 7.3);   //ignored 456, 'e', 7.3, print only text "sdfgh"
    return 0;
}
