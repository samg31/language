#include "dcipl/el/el-syntax.cpp"


using namespace dcipl::el;

bool beq(bool_expr* e1, bool_expr* e2);
/*
  This function takes two numeric expressions and determines if they are syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool neq(num_expr* e1, num_expr* e2) 
{
  if(num_expr_kind k = get_expr_kind(e1); k == get_expr_kind(e2)) {
    switch(k) {
      default: break;
      case ek_int:
        return (static_cast<const int_lit*>(e1)->val == static_cast<const int_lit*>(e2)->val);
      case ek_arg:
        return (static_cast<const arg_expr*>(e1)->ix == static_cast<const arg_expr*>(e2)->ix);
      case ek_arith: { 
        const arith_expr *a1 = static_cast<const arith_expr*>(e1);
        const arith_expr *a2 = static_cast<const arith_expr*>(e2);
        return get_op_name(a1->op) == get_op_name(a2->op) ? neq(a1->e1, a1->e2) == neq(a2->e1, a2->e2) : false;
      }
      case ek_if: { 
        const if_expr* i1 = static_cast<const if_expr*>(e1);
        const if_expr* i2 = static_cast<const if_expr*>(e2);
        return beq(i1->test, i2->test) ? neq(i1->e1, i1->e2) == neq(i2->e1, i2->e2) : false;
      }
    }
  }
  throw std::logic_error("invalid expression");
}


/*
  This function takes two boolean expressions and determines if they are syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool beq(bool_expr* e1, bool_expr* e2) 
{
  if(bool_expr_kind k = get_expr_kind(e1); k == get_expr_kind(e2)) { 
    switch(k) {
      default: break;
      case ek_bool:
        return (static_cast<const bool_lit*>(e1)->val == static_cast<const bool_lit*>(e2)->val);
      case ek_rel: { 
        const rel_expr *r1 = static_cast<const rel_expr*>(e1);
        const rel_expr *r2 = static_cast<const rel_expr*>(e2);
        return get_op_name(r1->op) == get_op_name(r2->op) ? neq(r1->e1, r1->e2) == neq(r2->e1, r2->e2) : false;
      }
      case ek_logic: { 
        const logic_expr *l1 = static_cast<const logic_expr*>(e1);
        const logic_expr *l2 = static_cast<const logic_expr*>(e2);
        return get_op_name(l1->op) == get_op_name(l2->op) ? beq(l1->e1, l1->e2) == beq(l2->e1, l2->e2) : false;
      }
    }
  }
  throw std::logic_error("invalid expression");
}