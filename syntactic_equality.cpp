#include "el-syntax.hpp"

/*
  This function takes two numeric expressions and determines if they are 
  syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool neq(NumExpr* e1, NumExpr* e2) {

  string n1, n2;
  n1 = get_node_name(e1);
  n2 = get_node_name(e2);
  if(n1 == n2){
    switch(n1){
      case "int":
        if(e1->val == e2->val){
          return true;
        }
        break;
      case "arg":
        if(e1->ix == e2->ix){
          return true;
        }
        break;
      case "arith":
        if(e1->op == e2->op){
          //recursively check if the num_exprs are equal
          if(neq(e1->e1, e2->e2)){
            if(neq(e1->e2, e2->e2)){
              return true;
            }
          }
        }
        break;
      case "if":
        //call beq for the bool expressions of n1 and n2
        //recursively neq for e1 and e2 of n1 and n2
        if(beq(e1->test,e2->test)){
          if(neq(e1->e1, e2->e2)){
            if(neq(e1->e2, e2->e2)){
              return true;
            }
          }
        }
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
bool beq(BoolExpr* e1, BoolExpr* e2) {
  
  string n1, n2;
  n1 = get_node_name(e1);
  n2 = get_node_name(e2);
  if(n1 == n2){
    switch(n1){
      case "bool":
        if(e1->val == e2->val){
          return true;
        }
        break;
      case "rel":
        if(e1->op == e2->op){
          //recursively check if the bool_exprs are equal
          if(beq(e1->e1, e2->e2)){
            if(beq(e1->e2, e2->e2)){
              return true;
            }
          }
        }
        break;
      case "logic":
        if(e1->op == e2->op){
          //recursively check if the bool_exprs are equal
          if(beq(e1->e1, e2->e2)){
            if(beq(e1->e2, e2->e2)){
              return true;
            }
          }
        }
        break;
     }
    }
  }
  return false;

}