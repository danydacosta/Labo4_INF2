/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : main.cpp
 Auteur(s)   : Oliveira da Costa Dany, Pozniakoff Lev, Vallon Axel
 Date        : 10.04.2020
 But         : -

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#include "fraction.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
   cout << "======== Debut du programme de test ========" << endl;
   {
      cout << "******** Test de la simplification ********" << endl;
      Fraction<int> f1(70, 7);
      cout << "f1 = " << f1 << endl;
      cout << "f1.simplifier() = " << f1.simplifier() << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'identite ********" << endl;
      Fraction<int> f1(1, 4);
      Fraction<int> f2(1, 4);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      cout << "f1.identite(f2) = " << boolalpha << f1.identite(f2) << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur d'egalite ********" << endl;
      Fraction<int> f1(12, 4);
      Fraction<int> f2(3, 1);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      cout << "f1 == f2 : " << boolalpha << (f1 == f2) << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'opérateur += ********" << endl;
      Fraction<int> f1(12, 4);
      Fraction<int> f2(12, 4);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      cout << "f1 += f2 : " << (f1 += f2) << endl;
      cout << "************************************" << endl;
   }

   return EXIT_SUCCESS;
}