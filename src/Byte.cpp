/**
 * @file Byte.cpp
 * @brief Operators for bit level
 * @note To be implemented by students 
 * @author MP-DGIM, MP-IADE, MP-II (grupo B)
 * @author Emilio Guillén Álvarez: 
 *
 */
#include <iostream>
#include <string>
#include "MPTools.h"
#include "Byte.h"


using namespace std;

const Byte Byte::MAX_BYTE_VALUE(255);
const Byte Byte::MIN_BYTE_VALUE(0);

    Byte:: Byte() {
        _data = 0;
    }

    Byte:: Byte(int value) {
        _data = (unsigned char) value;
}

int Byte::getValue() const {
    return (int) _data;
}

void Byte::setValue(unsigned char v) {
    _data = v;
}

void Byte::onBit( int pos) {

    if (pos >= 0 && pos <= 7) {
        Byte mascara(1); 
        mascara.shiftLByte(pos);
        setValue(_data | mascara._data ) ;
    }
}

void Byte::offBit( int pos) {

    if (pos >= 0 && pos <= 7) {
        Byte mascara(1);
         mascara.shiftLByte(pos);
         mascara.setValue( ~(mascara._data));
         setValue( mascara._data & _data);
    }
}

bool Byte::getBit( int pos) const {

    bool s;
    Byte mascara (1);
    mascara.shiftLByte(pos);
    Byte c (_data & mascara._data);
    if (c._data != 0) {
        s = true;
    } else {
        s = false;
    };
    return s;
}

 std:: string Byte::to_string() const {
    string escrito(8, '0');
    for (int i = 0; i <= 7; i++) {
        if ( getBit(i) == true) {
            escrito[7 - i] = '1';
        }
    }
    return escrito;

}

void Byte::onByte() {
  Byte mascara (~_data);
  setValue(mascara._data | _data) ;
}

void Byte::offByte() {
    Byte mascara (~_data);
    setValue(mascara._data & _data);

}

void Byte::encodeByte( const bool v[]) {

    for (int i = 0; i <= 7; i++) {
        if (v[i] == true) {
           onBit(i);
        } else  {
           offBit( i);
        }
    }

}

void Byte::decodeByte( bool v[]) const {
    for (int i = 0; i <= 7; i++) {
        if (getBit( i) == true) {
            v[i] == true;
        }
        else {
            v[i] == false;
        }//Indico en las posiciones que no son true, un false para tener completo el code.
    }
}

void Byte::decomposeByte( int posits[], int &n) const {
    for (int i = 0, n = 0; i <= 7; i++) {
        if (getBit( i) == true) {
            posits[n] == i;
            cout << i << ", ";
            n++;
        }
    }
}

void Byte::shiftRByte( int n) {
   _data = _data >> n;

}

void Byte::shiftLByte( int n) {
   _data = _data << n; 

}

void Byte::mergeByte( const Byte  &merge, int percentage) {
    _data = (_data * (100 - percentage) + merge._data * percentage) / 100;
    
}
