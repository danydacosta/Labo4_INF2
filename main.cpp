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
      Fraction<int> f2(-70, 7);
      cout << "f1 = " << f2 << endl;
      cout << "f2.simplifier() = " << f2.simplifier() << endl;
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
      cout << "******** Test de l'operateur += ********" << endl;
      Fraction<short> f1(-16382, 2);
      Fraction<short> f2(-3, 4);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      try {
         cout << "f1 += f2 : ";
         cout << (f1 += f2) << endl;
      } catch(out_of_range& e) {
         cout << e.what() << endl;
      }
      cout << "f1 = " << f1 << endl;
      cout << "************************************" << endl;
   }

   return EXIT_SUCCESS;
}