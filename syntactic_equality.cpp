#include "el-syntax.hpp"

/*
  This function takes two numeric expressions and determines if they are 
  syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool neq(NumExpr e1, NumExpr e2) {

  string n1, n2;
  n1 = get_node_name(e1);
  n2 = get_node_name(e2);
  if(n1 == n2){
    switch(n1){
      case "int":
        break;
      case "arg":
        break;
      case "arith":
        break;
      case "if":
        break;
     }
    }
  }
  return false;

}


/*
  This function takes two boolean expressions and determines if they are 
  syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool beq(BoolExpr e1, BoolExpr e2) {
  
  string n1, n2;
  n1 = get_node_name(e1);
  n2 = get_node_name(e2);
  if(n1 == n2){
    switch(n1){
      case "bool":
        break;
      case "rel":
        break;
      case "logic":
        break;
     }
    }
  }
  return false;

}