 #include "scanner.hpp"
#include <iostream>

using namespace std;


int main(int argc, const char * argv[]) {
    scanner s("D:/Ing_SistemasComputacinales/LenguajesAutonomas/AnalizadorLexico/sara.txt");

    int token;

    do {
        token = s.next();
        switch (token) {
            case scanner::_id:
                cout << "Id: " << s.getelemento() << endl;
                break;

            case scanner::_octales:
                cout << "Octal: " << s.getelemento() << endl;
                break;

            case scanner::_hexadecimales:
                cout << "Hexadecimal: "  << s.getelemento() << endl;
                break;

            case scanner::_real:
                cout << "Real: "  << s.getelemento() << endl;
                break;

            case scanner::_enteros:
                cout << "Entero: "  << s.getelemento() << endl;
                break;

            case scanner::_lpar:
                cout << "lpar " << endl;
                break;
            case scanner::_rpar:
                cout << "rpar " << endl;
                break;
            case scanner::_scolon:
                cout << "scolon " << endl;
                break;
            case scanner::_def:
                cout << "def " << endl;
                break;
            case scanner::_or:
                cout << "or " << endl;
                break;
            case scanner::_and:
            cout << "and " << endl;
            break;
            case scanner::_not:
            cout << "not " << endl;
            break;
            case scanner::_selector:
            cout << "selector" << endl;
            break;
                case scanner::_reservadas:
                cout  << s.getelemento() << endl;
                break;

            case scanner::_eof:
                cout << "\nFin de analisis, se leyeron " << s.getlinea() << " lineas" << endl;
                break;

            case scanner::_err:
                cout << "\nError en la linea: " << s.getlinea() << endl;
                break;

        }
    } while (token != scanner::_err && token != scanner::_eof);
}


