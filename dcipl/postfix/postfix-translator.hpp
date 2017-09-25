#pragma once

#include <postfix/postfix-syntax.hpp>

#include <sexpr/translation.hpp>

#include <unordered_map>

namespace dcipl::postfix
{
  /// Transforms s-expressions into postfix programs and commands.
  class translator
  {
  public:
    translator(ast_context& cxt);

    prog* operator()(const pl::sexpr::expr* e);

  private:
    prog* translate_prog(const pl::sexpr::list_expr* e);

    cmd* translate_cmd(const pl::sexpr::expr* e);
    cmd* translate_int_cmd(const pl::sexpr::int_expr* e);
    cmd* translate_pop_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_swap_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_arith_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_rel_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_get_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_sel_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_exec_cmd(const pl::sexpr::id_expr* e);
    cmd* translate_seq_cmd(const pl::sexpr::list_expr* e);

  protected:
    /// The ast context; used to allocate terms.
    ast_context& cxt;

    /// A mapping of command names to kinds.
    std::unordered_map<std::string, cmd_kind> cmds;

    /// A mapping of strings to arithmetic operations.
    std::unordered_map<std::string, arith_op> arith_ops;
    
    /// A mapping of strings to relational opreations.
    std::unordered_map<std::string, rel_op> rel_ops;
  };

} // namespace dcipl::postfix
