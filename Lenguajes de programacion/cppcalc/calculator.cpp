#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

Calculator::Calculator():
  memory(0)
{
  memory2.clear();
}

int Calculator::eval(string expr) {

   Parser* parser = new Parser(new istringstream(expr));
   
   AST* tree = parser->parse();
   
   int result = tree->evaluate();
   
   delete tree;
   
   delete parser;
   
   return result;
}

void Calculator::store(int val) {
   memory = val;
}

//Agregar funcion P
void Calculator::plus(int val){
  memory += val;
}

//Agregar funcion M
void Calculator::minus(int val){
  memory -= val;
}

int Calculator::recall() {
   return memory;
}

//Implementacion de C (Clear)
int Calculator::clear() {
  memory = 0;
  memory2.clear();
  assigns.clear();
  return memory;
}

//Implementacion de asignar una variable
void Calculator::assign(string s, int val){
  for(map<string,int>::iterator it=memory2.begin();it!=memory2.end();it++){
    if(it->first==s){
      memory2.at(s)=val;
      return;
    }
  }
  memory2.insert(pair<string,int>(s,val));
}

//Implementaciion para buscar una variable
int Calculator::search(string s){
  if(exists(s)){
    return memory2.find(s)->second;
  }
  else{
    return 0;
  }
}

//Implementacion para saber si una variable existe
bool Calculator::exists(string s){
  bool result=false;

  if(memory2.count(s)>0){
    result=true;
  }

  return result;
}

//Insertar una asignacion en el vector
void Calculator::insertAssign(string s){
  assigns.push_back (s);
  return;
}

//Obtener todas las asignaciones del vector
string Calculator::getAssigns(){
  string str="";

  for(int i=0;i<assigns.size();i++){
    str=str + assigns[i];
    if(i!=assigns.size()-1){
      str=str+", ";
    }
  }
  return str;
}

//Limpiar el vector de asignaciones
void Calculator::clearAssigns(){
  assigns.clear();
}
