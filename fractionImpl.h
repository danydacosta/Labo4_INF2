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

//
// Created by Lev on 30.03.2020.
//
#include "fraction.h"
#include <iostream>
#include <cmath>

#define type T
#define tmplt template<typename type>

#ifndef FRACTIOIMPLN_H
#define FRACTIONIMPL_H

using namespace std;

tmplt
ostream& operator<<(ostream& os, const Fraction<T>& rhs){}

tmplt
Fraction<T> operator+ (Fraction<T> lhs, const Fraction<T>& rhs) {
    lhs += rhs;
    return lhs;
}

tmplt
Fraction<T> operator* (Fraction<T> lhs, const Fraction<T>& rhs){
    lhs *= rhs;
    return lhs;
}

tmplt
Fraction<T>::operator float() const {

}

tmplt
Fraction<T>::operator double() const {

}

tmplt
T pgcd(T a, T b){
    a = abs(a);
    b = abs(b);
    while(a != b)
    {
        if(a > b)
            a -= b;
        else
            b -= a;
    }
}

tmplt
Fraction<T> Fraction<T>::simplifier() const {
   T thisPgcd = pgcd<T>(numerateur, denominateur);
   Fraction<T> simpleFrac(numerateur/thisPgcd, denominateur/thisPgcd);
   return simpleFrac;
}

tmplt
bool Fraction<T>::identite(const Fraction<T>& f) const {
    return this->numerateur == f.numerateur
    and this->denominateur == f.denominateur;
}

tmplt
bool Fraction<T>::operator== (const Fraction<T>& rhs) const {
    Fraction<T> thisSimple  = this->simplifier();
    Fraction<T> rhsSimple = this->simplifier();
    return thisSimple.numerateur == rhsSimple.numerateur and
    thisSimple.denominateur == rhsSimple.denominateur;
}

tmplt
T ppmc(T a, T b){
   return abs(a*b)/pgcd(a,b);
}

tmplt
Fraction<T>& Fraction<T>::operator += (const Fraction<T>& rhs){
    
}


tmplt
Fraction<T>& Fraction<T>::operator *= (const Fraction<T>& rhs){

    Fraction<T> thisSimple = this->simplifier();
    Fraction<T> rhsSimple = rhs.simplifier();
    this->numerateur = thisSimple.numerateur * rhsSimple.numerateur;
    this->simplifier() = thisSimple.denominateur * thisSimple.denominateur;

    return this;

};

#endif
