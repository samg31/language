#include "el-translator.hpp"
#include "el-context.hpp"

#include <sexpr/dumper.hpp>

#include <cassert>
#include <iostream>
#include <sstream>

namespace dcipl
{
namespace el
{
  using cc::is;
  using cc::as;
  using cc::cast;

  /// Elaborate an EL program.
  prog*
  translator::operator()(const sexpr::expr* e)
  {
    if (const sexpr::list_expr* list = as<sexpr::list_expr>(e))
      return translate_prog(list);
    sexpr::throw_unexpected_term(e);
  }

  prog*
  translator::translate_prog(const sexpr::list_expr* list)
  {
    int nargs;
    num_expr* body;
    match_list(list, "el", &nargs, &body);
    return cxt.make_prog(list->locs, nargs, body);
  }

  num_expr*
  translator::translate_num_expr(const sexpr::expr* e) 
  {
    // Match bare integer literals.
    if (const sexpr::int_expr* num = as<sexpr::int_expr>(e))
      return translate_int_lit(num);
    
    // Match phrases.
    //
    // FIXME: Use a lookup table + switch.
    if (const sexpr::list_expr* list = as<sexpr::list_expr>(e)) {
      symbol* sym;
      match_list(list, &sym);
      if (*sym == "arg")
        return translate_arg_expr(list);
      if (*sym == "+")
        return translate_add_op(list);
      if (*sym == "-")
        return translate_sub_op(list);
      if (*sym == "*")
        return translate_mul_op(list);
      if (*sym == "/")
        return translate_div_op(list);
      if (*sym == "%")
        return translate_rem_op(list);
      if (*sym == "if")
        return translate_if_expr(list);
      throw_unexpected_id(cast<sexpr::id_expr>(list->exprs[0]));
    }
    throw_expected_term(e, "numeric expression");
  }

  num_expr*
  translator::translate_int_lit(const sexpr::int_expr* num)
  {
    return cxt.make_int_lit(num->locs, num->val);
  }
  
  num_expr*
  translator::translate_arg_expr(const sexpr::list_expr* list)
  {
    int arg;
    match_list(list, "arg", &arg);
    return cxt.make_arg_expr(list->locs, arg);
  }
  
  num_expr*
  translator::translate_arith_expr(arith_op op, const sexpr::list_expr* list)
  {
    symbol* sym;
    num_expr* e1;
    num_expr* e2;
    match_list(list, &sym, &e1, &e2);
    return cxt.make_arith_expr(list->locs, op, e1, e2);
  }

  num_expr*
  translator::translate_add_op(const sexpr::list_expr* list)
  {
    return translate_arith_expr(op_add, list);
  }

  num_expr*
  translator::translate_sub_op(const sexpr::list_expr* list)
  {
    return translate_arith_expr(op_sub, list);
  }
  
  num_expr*
  translator::translate_mul_op(const sexpr::list_expr* list)
  {
    return translate_arith_expr(op_mul, list);
  }

  num_expr*
  translator::translate_div_op(const sexpr::list_expr* list)
  {
    return translate_arith_expr(op_div, list);
  }

  num_expr*
  translator::translate_rem_op(const sexpr::list_expr* list)
  {
    return translate_arith_expr(op_rem, list);
  }

  num_expr*
  translator::translate_if_expr(const sexpr::list_expr* list)
  {
    bool_expr* test;
    num_expr* pass;
    num_expr* fail;
    match_list(list, "if", &test, &pass, &fail);
    return cxt.make_if_expr(list->locs, test, pass, fail);
  }

  bool_expr*
  translator::translate_bool_expr(const sexpr::expr* e) 
  {
    // Match bare keyword literals.
    if (const sexpr::id_expr* id = as<sexpr::id_expr>(e)) {
      if (*id->id == "true")
        return translate_true_lit(id);
      if (*id->id == "false")
        return translate_false_lit(id);
      throw_unexpected_id(id);
    }

    // Match phrases.
    //
    // FIXME: Use a lookup table and a switch statement.
    if (const sexpr::list_expr* list = as<sexpr::list_expr>(e)) {
      symbol* sym;
      match_list(list, &sym);
      if (*sym == "<")
        return translate_lt_op(list);
      if (*sym == "=")
        return translate_eq_op(list);
      if (*sym == ">")
        return translate_gt_op(list);
      if (*sym == "and")
        return translate_and_op(list);
      if (*sym == "or")
        return translate_or_op(list);
      throw_unexpected_id(cast<sexpr::id_expr>(list->exprs[0]));
    }
    throw_expected_term(e, "boolean expression");
  }

  bool_expr*
  translator::translate_true_lit(const sexpr::id_expr* id)
  {
    return cxt.make_bool_lit(id->locs, true);
  }

  bool_expr*
  translator::translate_false_lit(const sexpr::id_expr* id)
  {
    return cxt.make_bool_lit(id->locs, false);
  }

  bool_expr*
  translator::translate_rel_expr(rel_op op, const sexpr::list_expr* list)
  {
    symbol* sym;
    num_expr* e1;
    num_expr* e2;
    match_list(list, &sym, &e1, &e2);
    return cxt.make_rel_expr(list->locs, op, e1, e2);
  }

  bool_expr*
  translator::translate_lt_op(const sexpr::list_expr* list)
  {
    return translate_rel_expr(op_lt, list);
  }
  
  bool_expr*
  translator::translate_eq_op(const sexpr::list_expr* list)
  {
    return translate_rel_expr(op_eq, list);
  }

  bool_expr*
  translator::translate_gt_op(const sexpr::list_expr* list)
  {
    return translate_rel_expr(op_gt, list);
  }

  bool_expr*
  translator::translate_logic_expr(logic_op op, const sexpr::list_expr* list)
  {
    symbol* sym;
    bool_expr* e1;
    bool_expr* e2;
    match_list(list, &sym, &e1, &e2);
    return cxt.make_logic_expr(list->locs, op, e1, e2);
  }
  
  bool_expr*
  translator::translate_and_op(const sexpr::list_expr* list)
  {
    return translate_logic_expr(op_and, list);
  }

  bool_expr*
  translator::translate_or_op(const sexpr::list_expr* list)
  {
    return translate_logic_expr(op_or, list);
  }

} // namespace el
} // namespace dcipl
