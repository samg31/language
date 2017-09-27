#include "el-syntax.hpp"

/*
  This function takes two numeric expressions and determines if they are 
  syntactically the same.
  Returns true if they are, and false otherwise.
*/

bool neq(num_expr* e1, num_expr* e2) {
  if(e1->kind == e2=->kind){
    switch(e1){
      case ek_int:
        if(e1->val == e2->val){
          return true;
        }
        break;
      case ek_arg:
        if(e1->ix == e2->ix){
          return true;
        }
        break;
      case ek_arith:
        if(e1->op == e2->op){
          //recursively check if the num_exprs are equal
          if(neq(e1->e1, e2->e2)){
            if(neq(e1->e2, e2->e2)){
              return true;
            }
          }
        }
        break;
      case ek_if:
        //call beq for the bool expressions of e1 and e2
        //recursively neq for e1 and e2 of e1 and e2
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

bool beq(bool_expr* e1,bool_expr* e2) {
  if(e1 == e2){
    switch(e1){
      case ek_bool:
        if(e1->val == e2->val){
          return true;
        }
        break;
      case ek_rel:
        if(e1->op == e2->op){
          //recursively check if the bool_exprs are equal
          if(beq(e1->e1, e2->e2)){
            if(beq(e1->e2, e2->e2)){
              return true;
            }
          }
        }
        break;
      case ek_logic:
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