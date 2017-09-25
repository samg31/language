#include "el-context.hpp"

namespace dcipl
{
namespace el
{
  context::context(cc::input_manager& in, 
                   cc::diagnostic_manager& diags,
                   cc::symbol_table& syms)
   : inputs(in), diags(diags), syms(syms)
  { }
  
  prog*
  context::make_prog(cc::span locs, int args, num_expr* body)
  {
  return new prog{locs, args, body};
  }
  
  num_expr*
  context::make_int_lit(cc::span locs, int val)
  {
  return new int_lit{locs, val};
  }
  
  num_expr*
  context::make_arg_expr(cc::span locs, int ix)
  {
  return new arg_expr{locs, ix};
  }
  
  num_expr*
  context::make_arith_expr(cc::span locs, arith_op op, num_expr* e1, num_expr* e2)
  {
  return new arith_expr{locs, op, e1, e2};
  }
  
  num_expr*
  context::make_if_expr(cc::span locs, bool_expr* e1, num_expr* e2, num_expr* e3)
  {
  return new if_expr{locs, e1, e2, e3};
  }
  
  bool_expr*
  context::make_bool_lit(cc::span locs, bool val)
  {
  return new bool_lit{locs, val};
  }
  
  bool_expr*
  context::make_rel_expr(cc::span locs, rel_op op, num_expr* e1, num_expr* e2) 
  {
  return new rel_expr{locs, op, e1, e2};
  }
  
  bool_expr*
  context::make_logic_expr(cc::span locs, logic_op op, bool_expr* e1, bool_expr* e2) 
  {
  return new logic_expr{locs, op, e1, e2};
  }
  
} // namespace el
} // namespace dcipl

