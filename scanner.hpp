#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

class scanner {

    ifstream file;
    long q;
    string elemento;
    int tipo;
    int linea;
    int lineas = 1;



    char read() {return file.get();}
    void failure() {file.seekg(q); }
    void success() {q = file.tellg();}
    void fback() { file.seekg(-1, ios_base::cur); }

    int id();
    void trim();
    bool eof();
    int num();
    int delimitadores();





    public:

    enum {
        _id,
        _reservadas,
        _eof,
        _err,
        _octales,
        _hexadecimales,
        _real,
        _enteros,
        _lpar,
        _rpar,
        _def,
        _true,
        _false,
        _scolon,
        _or,
        _and,
        _not,
        _if,
        _then,
        _selector,
        _tellme,
        _implicacion
    };


    static int udef;

    scanner (string);

    int next();

    string getelemento() const { return elemento; }
    int getlinea() const { return lineas; }




};

#endif
