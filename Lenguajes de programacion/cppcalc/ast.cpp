#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivideNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

//Implementacion de la clase ModNode
ModNode::ModNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModNode::evaluate() {
   return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

StoreNode::StoreNode(AST *sub) :
  UnaryNode(sub)
{}

int StoreNode::evaluate(){
  int valchild = getSubTree()->evaluate();
  calc->store(valchild);
  return calc->recall();
}

//Implementacion clase MinusNode
MinusNode::MinusNode(AST *sub):
  UnaryNode(sub)
{}

int MinusNode::evaluate(){
  int valchild = getSubTree()->evaluate();
  calc->minus(valchild);
  return calc->recall();
}

//Implementacion clase PlusNode
PlusNode::PlusNode(AST *sub):
  UnaryNode(sub)
{}

int PlusNode::evaluate(){
  int valchild = getSubTree()->evaluate();
  calc->plus(valchild);
  return calc->recall();
}

NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
}
RecallNode::RecallNode():
  AST()  
{}
int RecallNode::evaluate(){
  return calc->recall();
}

//Implementacion de ClearNode
ClearNode::ClearNode():
  AST()
{}

int ClearNode::evaluate(){
  calc->clear();
  return calc->recall();
}

//Implementacion de AsingNode (Asignaciones)
AssignNode::AssignNode(string s, AST* t):
  UnaryNode(t),
  id(s)
{}

int AssignNode::evaluate(){
  
  int valchild = getSubTree()->evaluate();
  calc->assign(id, valchild);
  string value;
  stringstream stream;
  
  stream << valchild;
  value = stream.str();   
  calc->insertAssign(id+" <- "+value);
   
  return valchild;
}

//Implementacion de Nodo de identifier
IdNode::IdNode(string s):
  AST(),
  id(s)
{}

int IdNode::evaluate(){
  int val = calc->search(id);
  return val;
}
