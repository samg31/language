#include "el-evaluator.hpp"
#include "el-dumper.hpp"

#include <iostream>
#include <sstream>

namespace dcipl
{
namespace el
{
  [[noreturn]]
  static void
  err_too_few_inputs(context& cxt, cc::location loc)
  {
    throw evaluation_error(loc, "too few input arguments");
  }

  static void
  warn_too_many_inputs(context& cxt, cc::location loc, int n, const std::vector<int> &args)
  {
    cc::warning diag("evaluation", loc, "too many input arguments");

    // List unused arguments.
    std::stringstream ss;
    ss << "the following arguments are unused: ";
    for (std::size_t i = n; i < args.size(); ++i) {
      ss << args[i];
      if (i + 1 != args.size())
        ss << ',' << ' ';
    }
    diag.note({}, ss.str());

    cxt.get_diagnostics().emit(diag);
  }

  int
  evaluator::eval_prog(const prog* p)
  {
    if (args.size() < p->nargs)
      err_too_few_inputs(cxt, get_location(p));
    if (args.size() > p->nargs)
      warn_too_many_inputs(cxt, get_location(p), p->nargs, args);
    return eval_num_expr(p->body);
  }

  int
  evaluator::eval_num_expr(const num_expr* e)
  {
    switch (get_expr_kind(e)) {
      case ek_int:
        return eval_int_lit(static_cast<const int_lit*>(e));
      case ek_arg:
        return eval_arg_expr(static_cast<const arg_expr*>(e));
      case ek_arith:
        return eval_arith_expr(static_cast<const arith_expr*>(e));
      case ek_if:
        return eval_if_expr(static_cast<const if_expr*>(e));
    }
  }

  int
  evaluator::eval_int_lit(const int_lit* e)
  {
    return e->val;
  }

  int
  evaluator::eval_arg_expr(const arg_expr* e)
  {
    int arg = e->ix - 1; // Make this 0-based.
    if  (arg < 0 || arg >= args.size())
      throw evaluation_error(get_location(e), "argument index out of bounds");
    return args[arg];
  }

  // FIXME: Detect overflow and division by 0.
  int
  evaluator::eval_arith_expr(const arith_expr* e)
  {
    int v1 = eval_num_expr(e->e1);
    int v2 = eval_num_expr(e->e2);
    switch (e->op) {
      case op_add:
        return v1 + v2;
      case op_sub:
        return v1 - v2;
      case op_mul:
        return v1 * v2;
      case op_div:
        return v1 / v2;
      case op_rem:
        return v1 % v2;
    }
  }

  int
  evaluator::eval_if_expr(const if_expr* e)
  {
    int v1 = eval_bool_expr(e->test);
    if (v1)
      return eval_num_expr(e->e1);
    else
      return eval_num_expr(e->e2);
  }

  int
  evaluator::eval_bool_expr(const bool_expr* e)
  {
    switch (get_expr_kind(e)) {
      case ek_bool:
        return eval_bool_lit(static_cast<const bool_lit*>(e));
      case ek_rel:
        return eval_rel_expr(static_cast<const rel_expr*>(e));
      case ek_logic:
        return eval_logic_expr(static_cast<const logic_expr*>(e));
    }
  }

  int
  evaluator::eval_bool_lit(const bool_lit* e)
  {
    return e->val;
  }

  int
  evaluator::eval_rel_expr(const rel_expr* e)
  {
    int v1 = eval_num_expr(e->e1);
    int v2 = eval_num_expr(e->e2);
    switch (e->op) {
      case op_lt:
        return v1 < v2;
      case op_eq:
        return v1 == v2;
      case op_gt:
        return v1 > v2;
    }
  }

  int
  evaluator::eval_logic_expr(const logic_expr* e)
  {
    int v2 = eval_bool_expr(e->e2);
    if (e->op == op_and) {
      int v = eval_bool_expr(e->e1);
      if (v)
        v = eval_bool_expr(e->e2);
      return v;
    }
    else { // e->op == op_or
      int v = eval_bool_expr(e->e1);
      if (!v)
        v = eval_bool_expr(e->e2);
      return v;
    }
  }

} // namespace el
} // namespace dcipl
