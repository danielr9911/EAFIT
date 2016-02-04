#pragma once
#define calculator_h
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Calculator {
 public:
   Calculator();
   
   int eval(string expr);
   void store(int val);
   void plus(int val);
   void minus(int val);
   int recall();
   int clear();
   void assign(string s, int val);
   int search(string s);
   bool exists(string s);
   void insertAssign(string s);
   string getAssigns();
   void clearAssigns();

 private:
   int memory;
   //Memoria 2 para las asignaciones de variables
   map<string, int> memory2;
   //Vector para imprimir asignaciones
   vector<string> assigns;
};
extern Calculator* calc;
