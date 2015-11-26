#pragma once

#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();

 private:
   AST* Prog();
   AST* Expr();
   AST* RestExpr(AST* e);
   AST* Term();
   AST* RestTerm(AST* t);
   AST* Storable();
   //Funcion para S,P,M 
   AST* MemOperation(AST* e);
   AST* Factor();
   //Funciones para las asignasiones
   AST* Assignable();
   AST* Assign(string s);
   
   Scanner* scan;
};
