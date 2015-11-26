#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>
using namespace std;

Parser::Parser(istream* in) {
  scan = new Scanner(in);
}

Parser::~Parser() {
  try {
    delete scan;
  } catch (...) {}
}

AST* Parser::parse() {
  return Prog();
}

AST* Parser::Prog() {
  AST* result = Expr();
  Token* t = scan->getToken();

  if (t->getType() != eof) {
    cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;
    throw ParseError;
  }

  return result;
}

AST* Parser::Expr() {
  return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
  Token* t = scan->getToken();

  if (t->getType() == add) {
    return RestExpr(new AddNode(e,Term()));
  }

  if (t->getType() == sub)
    return RestExpr(new SubNode(e,Term()));

  scan->putBackToken();

  return e;
}

AST* Parser::Term() {
  return RestTerm(Storable());
  }

AST* Parser::RestTerm(AST* e) {
  Token* t = scan->getToken();

  if (t->getType() == times) {
    return RestTerm(new TimesNode(e,Storable()));
  }

  if (t->getType() == divide){
    return RestTerm(new DivideNode(e,Storable()));
  }
  //Agregado el RestTerm para modulo
  if (t->getType() == mod){
    return RestTerm(new ModNode(e,Storable())); 
  }
   
  scan->putBackToken();
  return e;

}
//Storable modificado para MemOperation
AST* Parser::Storable() {

  AST* result = MemOperation(Factor());
  return result;
}

//Agreando MemOperation para mas operaciones de S, P y M
AST* Parser::MemOperation(AST* result){

  Token* t = scan->getToken();

  if(t->getType() == keyword){
    if(t->getLex() == "S") 
      return new StoreNode(result);
    //Caso para PlusNode
    else if(t->getLex() == "P")
      return new PlusNode(result);
    //Caso para MinusNode
    else if(t->getLex() == "M")
      return new MinusNode(result);
  }
  scan->putBackToken();

  return result;
}

  
AST* Parser::Factor() {
  Token* t = scan->getToken();

  if (t->getType() == number) {
    istringstream in(t->getLex());
    int val;
    in >> val;
    return new NumNode(val);
  }
  //Se agrego el tipo identifier
  if(t->getType()==identifier){
    scan->putBackToken();
    return Assignable();
  }

  if(t->getType() == keyword) {
    if(t->getLex() == "R"){
      return new RecallNode();
    }
    //Para el caso de clear
    else if(t->getLex() == "C"){
      return new ClearNode();
    }
    else{
      cout << "Syntax error keyword: "
	   << t->getLex() << " at line: " << t->getLine()

	   << " col: " << t->getCol() << endl;
      throw ParseError;
    }
  }

     
  if(t->getType() == lparen){
    AST *result = Expr();
    t = scan->getToken();
    if(t->getType() == rparen){
      return result;
    }
    else{
      //Aqui va un error
      cout<<"sintax error expected ')' found"
	  << t ->getType() << " at line: " << t->getLine()
	  <<" col: " << t->getCol() << endl;
      throw ParseError;
    }
  }    
     
  cout << "Expected number, R or '('" << endl;
  throw ParseError;
}

//Agregado para las asignaciones
AST* Parser::Assignable(){
  Token* t = scan->getToken();
  if((t->getType())==identifier){
    AST* result = Assign(t->getLex());
    return result;
  }else{
    //cout identifier expcted
  }
}

AST* Parser::Assign(string s){
  
  Token* t= scan->getToken();
  if(t->getType() == equ){
    return new AssignNode(s,Expr());
  }
  else{
    scan->putBackToken();
    return new IdNode(s);
  }
}

