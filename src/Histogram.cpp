/**
 * @file Histogram.cpp
 * @author Emilio Guillén Álvarez
 */
#include<iostream>
#include<string>
#include "Histogram.h"

using namespace std;

const double Histogram::HISTOGRAM_TOLERANCE = 0.01; ///< Value of the default tolerance

string Histogram::inspect() const {
    std::string result = "";
    for (int i = 0; i < HISTOGRAM_LEVELS; i++) {
        result += to_string(_data[i]);
    }
    result = std::to_string(mphash((unsigned char*) result.c_str(), result.length()));
    result = std::to_string(HISTOGRAM_LEVELS) + " " + result;
    return result;
}

Histogram::Histogram() {

    for (int n = 0; n < HISTOGRAM_LEVELS; n++) {
        _data[n] = 0;
    }
}

int Histogram::size() const {
    return HISTOGRAM_LEVELS;
}

void Histogram::clear() {

    for (int n = 0; n < HISTOGRAM_LEVELS; n++) {
        _data[n] = 0;
    }
}

int Histogram::getLevel(Byte level) const {
    return _data[level.getValue()]; //preguntar
}

void Histogram::setLevel(Byte level, int npixeles) {

    _data[level.getValue()] = npixeles;
}

int Histogram::getMaxLevel() const {
    int max = 0;
    for (int i = 0; i < HISTOGRAM_LEVELS; i++) {
        if (_data[i] > max) {
            max = _data[i];
        }
    }
    return max;
}

int Histogram::getAverageLevel()const {
    int contador;
    for (int i = 0; i < HISTOGRAM_LEVELS; i++) {
        contador += _data[i];
    }

    return contador / HISTOGRAM_LEVELS;
}

int Histogram::getBalancedLevel() const {
    int cont, total=0, i, n;
    for ( i = 0; i < HISTOGRAM_LEVELS; i++) {
       total += _data[i];
    }
    for ( i = 0, n = 0; i < total/2; n++) {
        i += _data[n];
    } 
    n--;
    return n;
}
