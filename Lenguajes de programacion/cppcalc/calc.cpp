#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include "calcex.h"
#include "calculator.h"
using namespace std;

Calculator* calc;

int main(int argc, char* argv[], char* env[]) {
  bool prefEnv = false;
  bool interactive = true;
  int countAsignEnv = 0;
  int countFiles = 0;
  int countVar = 0;
  string line;
  string files[argc];
  string arrAssigns[argc/2];
  string arrAssignsEnv[100];

  calc = new Calculator();
  int i =1;
  while(i<argc){
    string commandEnv = argv[1];
    string command = argv[i];
    if(commandEnv=="-e"){
      prefEnv = true;
    }
    if(command=="-v"){
      arrAssigns[countVar] = argv[i+1];
      i = i + 2;
      countVar++;
    }else{
      (files[countFiles] = command);
      countFiles++;
      i++;
    }
  }
  if(countVar>0){
    for (int j=0; j<countVar; j++){
      calc->eval(arrAssigns[j]);
      //cout << arrAssigns[j] << endl;
    }
    calc->clearAssigns();
  }
  if(countFiles>0){
    for(int j=0;j<countFiles;j++){
      string buffer;
      char* file= new char[files[j].length()+1];
      strcpy(file,files[j].c_str());
      ifstream filein(file);
      delete [] file;
      while(getline(filein,buffer)){
	try {
	  string buffer2(buffer);
	  istringstream ins(buffer2);
	  ins>>line;
	  if(buffer!=""){	    
	    int result = calc->eval(buffer);
	    cout << "=> " << result;
	    if(calc->getAssigns()!=""){
	      cout << " [" << calc->getAssigns() << "]" << endl;
	    }
	    else{
	      cout << endl;
	    }
	    calc->clearAssigns();
	    interactive = false;
	    line="";
	  }else{
	    cout<<"Parser Error, expected expresion"<<endl;
	  }
	}
	catch(Exception ex) {
	  cout << "Program Aborted due to exception!" << endl;
	}
      }
    }
    calc->clearAssigns();
  }
  for (int j = 0; env[j] != NULL; j++) {
    string expr = env[j];
    if(expr.substr(0,7)=="CALCVAR"){
      expr.erase(0,7);
      int k=0;
      string name = "";
      while(expr[k]!='='){
	name += expr[k];
	k++;
      }
      expr.erase(0,k+1);
      istringstream ins(expr);
      int value;
      ins >> value;
      if(prefEnv && calc->exists(name)){
	calc->assign(name,value);
      }
      else if(!calc->exists(name)){
	calc->assign(name,value);
      }
    }
  }
  calc->clearAssigns();
  if(interactive){
    do{
      try {
	cout << "> ";
	getline(cin, line);
	if(cin.eof()){
	  break;
	}
	if(line== ""){
	  cout<<"ParseError, expected expresion"<<endl;
	}else{
	  int result = calc->eval(line);
	  cout << "=> " << result;
	  if(calc->getAssigns()!=""){
	    cout << " [" << calc->getAssigns() << "]" << endl;
	  }
	  else{
	    cout << endl;
	  }
	  calc->clearAssigns();
	}     
      }  
      catch(Exception ex) {
	cout << "Program Aborted due to exception!" << endl;
      }
      
    }while(true);
    delete calc;
  }
}
