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

#ifndef FRACTIOIMPLN_H
#define FRACTIONIMPL_H

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const Fraction<T>& rhs){}

template<typename T>
Fraction<T> operator+ (Fraction<T> lhs, const Fraction<T>& rhs) {
    lhs += rhs;
    return lhs;
}

template<typename T>
Fraction<T> operator* (Fraction<T> lhs, const Fraction<T>& rhs){
    lhs *= rhs;
    return lhs;
}

template<typename T>
Fraction<T>::Fraction(T n, T d){
    if(d <= 0)
        throw (std::invalid_argument("Le denominateur doit etre positif"));
    this->numerateur = n;
    this->denominateur = d;
}

template<typename T>
Fraction<T>::operator float() const {

}

template<typename T>
Fraction<T>::operator double() const {

}

template<typename T>
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

template<typename T>
Fraction<T> Fraction<T>::simplifier() const {
   T thisPgcd = pgcd<T>(numerateur, denominateur);
   Fraction<T> simpleFrac(numerateur/thisPgcd, denominateur/thisPgcd);
   return simpleFrac;
}

template<typename T>
bool Fraction<T>::identite(const Fraction<T>& f) const {
    return this->numerateur == f.numerateur
    and this->denominateur == f.denominateur;
}

template<typename T>
bool Fraction<T>::operator== (const Fraction<T>& rhs) const {
    Fraction<T> thisSimple  = this->simplifier();
    Fraction<T> rhsSimple = this->simplifier();
    return thisSimple.numerateur == rhsSimple.numerateur and
    thisSimple.denominateur == rhsSimple.denominateur;
}

template<typename T>
T ppmc(T a, T b){
   return abs(a*b)/pgcd(a,b);
}

template<typename T>
Fraction<T>& Fraction<T>::operator += (const Fraction<T>& rhs){

}


template<typename T>
Fraction<T>& Fraction<T>::operator *= (const Fraction<T>& rhs){

    Fraction<T> thisSimple = this->simplifier();
    Fraction<T> rhsSimple = rhs.simplifier();
    this->numerateur = thisSimple.numerateur * rhsSimple.numerateur;
    this->simplifier() = thisSimple.denominateur * thisSimple.denominateur;

    return this;

};

#endif
