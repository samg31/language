#pragma once

#include <el/el-syntax.hpp>

#include <sexpr/translation.hpp>

namespace dcipl
{
namespace el
{
  struct prog;
  struct num_expr;
  struct bool_expr;
  class context;

  // The EL translator transforms uninterpreted s-expressions into EL programs.
  class translator : public sexpr::translator<translator>
  {
  public:
    translator(context& cxt)
      : cxt(cxt)
    { }

    prog* operator()(const sexpr::expr*);

    prog* translate_prog(const sexpr::list_expr* e);
    
    num_expr* translate_num_expr(const sexpr::expr* e);
    num_expr* translate_int_lit(const sexpr::int_expr* e);
    num_expr* translate_arg_expr(const sexpr::list_expr* e);
    num_expr* translate_arith_expr(arith_op op, const sexpr::list_expr* e);
    num_expr* translate_add_op(const sexpr::list_expr* e);
    num_expr* translate_sub_op(const sexpr::list_expr* e);
    num_expr* translate_mul_op(const sexpr::list_expr* e);
    num_expr* translate_div_op(const sexpr::list_expr* e);
    num_expr* translate_rem_op(const sexpr::list_expr* e);
    num_expr* translate_if_expr(const sexpr::list_expr* e);

    bool_expr* translate_bool_expr(const sexpr::expr* e);
    bool_expr* translate_true_lit(const sexpr::id_expr* e);
    bool_expr* translate_false_lit(const sexpr::id_expr* e);
    bool_expr* translate_rel_expr(rel_op op, const sexpr::list_expr* e);
    bool_expr* translate_lt_op(const sexpr::list_expr* e);
    bool_expr* translate_eq_op(const sexpr::list_expr* e);
    bool_expr* translate_gt_op(const sexpr::list_expr* e);
    bool_expr* translate_logic_expr(logic_op op, const sexpr::list_expr* e);
    bool_expr* translate_and_op(const sexpr::list_expr* e);
    bool_expr* translate_or_op(const sexpr::list_expr* e);

    // Values
    int translate_int(const sexpr::expr* e);
  
    using sexpr::translator<translator>::match;

    void
    match(const sexpr::list_expr* list, int n, num_expr** ne)
    {
      *ne = translate_num_expr(get(list, n));
    }

    void
    match(const sexpr::list_expr* list, int n, bool_expr** be)
    {
      *be = translate_bool_expr(get(list, n));
    }

  private:
    // The AST context.
    context& cxt;
  };

} // namespace el
} // namespace dcipl
