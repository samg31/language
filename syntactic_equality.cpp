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
        if(n1->val == n2->val){
          return true;
        }
        break;
      case "arg":
        if(n1->ix == n2->ix){
          return true;
        }
        break;
      case "arith":
        if(n1->op == n2->op){
          //recursively check if the num_exprs are equal
        }
        break;
      case "if":
        //call beq for the bool expressions of n1 and n2
        //recursively neq for e1 and e2 of n1 and n2
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