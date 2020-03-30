/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.cpp
 Auteur(s)   : Oliveira da Costa Dany, Pozniakoff Lev, Vallon Axel
 Date        : 10.04.2020
 But         : -

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTIONIMPL_H
#define FRACTIONIMPL_H

//
// Created by Lev on 30.03.2020.
//
#include "fraction.h"
#include <iostream>

#define type T
#define tmplt template<typename type>

#ifndef FRACTIOIMPLN_H
#define FRACTIONIMPL_H

using namespace std;

tmplt
ostream& operator<<(ostream& os, const Fraction<T>& rhs){

}

tmplt
Fraction<T>::operator float() const {}

tmplt
Fraction<T>::operator double() const{}

tmplt
Fraction<T> Fraction<T>::simplifier() const {}

tmplt
bool identite(const Fraction<T>& f) const {}

tmplt
bool Fraction<T>::operator== (const Fraction<T>& rhs) const {}

tmplt
Fraction<T> Fraction<T>::operator+ (const Fraction<T>& rhs) const{}

tmplt
Fraction<T>& Fraction<T>::operator += (const Fraction<T>& rhs){}

tmplt
Fraction<T> Fraction<T>::operator* (const Fraction<T>& rhs) const{}

tmplt
Fraction<T>& Fraction<T>::operator *= (const Fraction<T>& rhs){};

#endif
