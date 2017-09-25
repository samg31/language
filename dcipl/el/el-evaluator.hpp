#pragma once

#include <el/el-context.hpp>

#include <vector>

namespace dcipl
{
namespace el
{
  /// Implements the evaluation function for EL.
  struct evaluator
  {
    evaluator(context& cxt, const std::vector<int>& args)
      : cxt(cxt), args(args)
    { }

    int operator()(const prog* p) { return eval_prog(p); }
    
  protected:
    int eval_prog(const prog* p);
    
    int eval_num_expr(const num_expr* e);
    int eval_int_lit(const int_lit* e);
    int eval_arg_expr(const arg_expr* e);
    int eval_arith_expr(const arith_expr* e);
    int eval_if_expr(const if_expr* e);

    int eval_bool_expr(const bool_expr* e);
    int eval_bool_lit(const bool_lit* e);
    int eval_rel_expr(const rel_expr* e);
    int eval_logic_expr(const logic_expr* e);

    context& cxt;
    std::vector<int> args;
  };

  /// Represents an evaluation error.
  class evaluation_error : public cc::diagnosable_error
  {
  public:
    evaluation_error(cc::location loc, const std::string& msg)
      : cc::diagnosable_error(cc::dk_error, "evaluation", loc, msg)
    { }
  };
  
} // namespace el
} // namespace dcipl
