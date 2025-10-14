#include "scanner.hpp"
#include <set>

int  scanner::udef = -1;

scanner::scanner(string fname): file(fname) {

    q = 0;

}


const std::set<std::string> reservadas = {
    "tellme",
    "allsat",
    "true",
    "false",
    "and",
    "or",
    "not",
    "if",
    "then"
};



int scanner::id() {
    int actual = 0;
    elemento.clear();

    while (true) {
        if (file.eof()) break;
        char c = read();

        switch (actual) {
            case 0:
                if (isalpha(c)) {
                    actual = 1;
                    elemento.push_back(c);
                } else {
                    fback();
                    return _err;
                }
                break;

            case 1:
                if (isalnum(c)) {
                    actual = 1;
                    elemento.push_back(c);
                } else if (c == '_') {
                    actual = 2;
                    elemento.push_back(c);
                } else if (c == '\'') {
                    actual = 4;
                    elemento.push_back(c);
                } else {
                    fback();
                    success();


                    if (reservadas.count(elemento))
                        return _reservadas;

                    return _id;
                }
                break;

            case 2:
                if (isalnum(c)) {
                    actual = 3;
                    elemento.push_back(c);
                } else {
                    fback();
                    return _err;
                }
                break;

            case 3:
                if (isalnum(c)) {
                    actual = 3;
                    elemento.push_back(c);
                } else if (c == '\'') {
                    actual = 4;
                    elemento.push_back(c);
                } else {
                    fback();
                    success();

                    if (reservadas.count(elemento))
                        return _reservadas;

                    return _id;
                }
                break;

            case 4:
                if (c == '\'') {
                    actual = 4;
                    elemento.push_back(c);
                } else {

                     fback();
                     success();
                 if (reservadas.count(elemento))

                     return _reservadas;
                     return _id;
                   }
                  break;
            case 5:

    			 if (c == '\'') {
       			 elemento.push_back(c);
    			} else {
        		fback();
       			 return _err;
   			 }

             break;

		}
}



    return _err;
}


int scanner::num() {
    int actual = 0;
    elemento.clear();


    while (true) {
        if (file.eof()) break;

        char c = read();

        switch (actual) {
            case 0:
                if (c == '0') {
                    actual = 1;
                    elemento.push_back(c);
                } else if (c >= '1' && c <= '9') {
                    actual = 2;
                    elemento.push_back(c);
                } else {
                    fback();
                    return _err;
                }
                break;

            case 1:
                if (c >= '1' && c <= '7') {
                    actual = 3;
                    elemento.push_back(c);
                } else if (c == 'x' || c == 'X') {
                    actual = 4;
                    elemento.push_back(c);
                } else if (c == '.') {
                    actual = 5;
                    elemento.push_back(c);
                } else {
                    fback();
                    success();
                    return _octales;
                }
                break;

            case 2:
                if (c >= '0' && c <= '9'){
                    actual = 2;
                    elemento.push_back(c);
                } else if (c == '.'){
                    actual = 5;
                    elemento.push_back(c);
                } else {
                    fback();
                    success();
                    return _enteros;
                }
                break;

            case 3:
                if (c >= '1' && c <= '7') {
                    actual = 6;
                    elemento.push_back(c);
                } else {
                    fback();
                    success();
                    return _octales;
                }
                break;

            case 4:
            if ((c >= '0' && c <= '9') ||
               (c >= 'A' && c <= 'F') ||
               (c >= 'a' && c <= 'f')) {
                actual = 7;
               elemento.push_back(c);
                }else {
                    fback();
                    success();
                    return _err;
                }
                break;

            case 5:
                if (c >= '0' && c <= '9') {
                    actual = 8;
                    elemento.push_back(c);
                } else {
                    return _err ;
                }
                break;

            case 6:
                if (c >= '1' && c <= '7') {
                    actual = 6;
                    elemento.push_back(c);
                } else {
                    fback();
                    success();
                    return _octales;
                }
                break;

            case 7:
               if ((c >= '0' && c <= '9') ||
                  (c >= 'A' && c <= 'F') ||
                  (c >= 'a' && c <= 'f')){
                  actual = 9;
                  elemento.push_back(c);
                  } else {
                    fback();
                    success();
                     return _err;
                  }
                  break;
            case 8:

                 if (c >= '0' && c <= '9') {
                     actual = 8;
                 } else {
                     fback();
                     success();
                     return _real ;
                 }
                 break;

            case 9:

                if ((c >= '0' && c <= '9') ||
                (c >= 'A' && c <= 'F') ||
                (c >= 'a' && c <= 'f')) {
                actual = 7;
               elemento.push_back(c);
            } else {
                fback();
                success();
                return _hexadecimales;
            }

			break;

        }
    }

    return _err;
}

int scanner::delimitadores() {

    switch (read()) {
        case '(':
            success();
            return _lpar;
            break;
        case ')':
            success();
            return _rpar;
            break;
        case ';':
            success();
            return _scolon;
            break;
        case ':':
            success();
            return _def;
            break;
        case '|':
            success();
            return _or;
        case '&':
            success();
            return _and;
        case '!':
            success();
            return _not;
        case '?':
            success();
            return _selector;
            break;
        default:
            fback();
            return _err;
    }
}


void scanner::trim() {
    char c;
    do {
        c = read();
        if (c == -1) break;
        if (c == '\n') lineas++;
    } while (isspace(c));
    if (c != -1) fback();
}




bool scanner::eof() {

    char c = read();
    if ( c == -1 || file.eof()) {
        return true;
    }
     fback();
    return false;
}


int scanner::next() {
    trim();

    tipo = id();

    if (tipo != _err)
        return tipo;

    tipo = num();

    if (tipo != _err) return tipo;

    tipo = delimitadores();

    if (tipo != _err)  return  tipo;


    if (eof()) return _eof;

    return _err;
}
