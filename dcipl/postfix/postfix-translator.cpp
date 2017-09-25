#include "postfix-translator.hpp"
#include "postfix-syntax.hpp"

#include <iostream>
#include <sstream>

using namespace pl::sexpr;

namespace dcipl::postfix 
{
  translator::translator(ast_context& cxt)
    : cxt(cxt)
  { 
    cmds.insert({
      {"pop", ck_pop},
      {"swap", ck_swap}, 
      {"+", ck_arith},
      {"-", ck_arith},
      {"*", ck_arith},
      {"/", ck_arith},
      {"%", ck_arith},
      {"<", ck_rel},
      {"=", ck_rel},
      {">", ck_rel},
      {"get", ck_get},
      {"sel", ck_sel},
      {"exec", ck_exec},
      {"seq", ck_seq}
    });
    arith_ops.insert({
      {"+", op_add},
      {"-", op_sub},
      {"*", op_mul},
      {"/", op_div},
      {"%", op_rem}
    });
    rel_ops.insert({
      {"<", op_lt},
      {"=", op_eq},
      {">", op_gt},
    });
  }

  prog*
  translator::operator()(const expr* e)
  {
    if (const auto* list = as<list_expr>(e))
      return translate_prog(list);
    throw_unexpected_term(e);
  }

  cmd* 
  translator::translate_cmd(const expr* e)
  {
    if (const int_expr* num = as<int_expr>(e))
      return translate_int_cmd(num);
    
    if (const id_expr* id = as<id_expr>(e)) {
      auto iter = cmds.find(*id->id);
      if (iter != cmds.end()) {
        switch (iter->second) {
          default:
            break;
          case ck_pop:
            return translate_pop_cmd(id);
          case ck_swap:
            return translate_swap_cmd(id);
          case ck_arith:
            return translate_arith_cmd(id);
          case ck_rel:
            return translate_rel_cmd(id);
          case ck_get:
            return translate_get_cmd(id);
          case ck_sel:
            return translate_sel_cmd(id);
          case ck_exec:
            return translate_exec_cmd(id);
        }
      }
      throw_unexpected_id(id);
    }

    if (const list_expr* list = as<list_expr>(e))
      return translate_seq_cmd(list);
    
    throw_unexpected_term(e);
  }

  prog*
  translator::translate_prog(const list_expr* e)
  {
    match_min_list(e, 3);

    // Match the "postfix" tag.
    match_id(e->exprs[0], "postfix");

    // Match the number of arguments.
    const int_expr* args = match_int(e->exprs[1]);

    // Translate each command in turn.
    cmd_seq cmds;
    for (std::size_t i = 2; i < e->exprs.size(); ++i)
      cmds.push_back(translate_cmd(e->exprs[i]));

    return cxt.make_prog(e->locs, args->val, std::move(cmds));
  }

  cmd*
  translator::translate_int_cmd(const int_expr* e)
  {
    return cxt.make_int_cmd(e->locs, e->val);
  }

  cmd*
  translator::translate_pop_cmd(const id_expr* e)
  {
    return cxt.make_pop_cmd(e->locs);
  }

  cmd*
  translator::translate_swap_cmd(const id_expr* e)
  {
    return cxt.make_swap_cmd(e->locs);
  }

  cmd*
  translator::translate_arith_cmd(const id_expr* e)
  {
    arith_op op = arith_ops.find(*e->id)->second;
    return cxt.make_arith_cmd(e->locs, op);
  }

  cmd*
  translator::translate_rel_cmd(const id_expr* e)
  {
    rel_op op = rel_ops.find(*e->id)->second;
    return cxt.make_rel_cmd(e->locs, op);
  }

  cmd*
  translator::translate_get_cmd(const id_expr* e)
  {
    return cxt.make_get_cmd(e->locs);
  }

  cmd*
  translator::translate_sel_cmd(const id_expr* e)
  {
    return cxt.make_sel_cmd(e->locs);
  }

  cmd*
  translator::translate_exec_cmd(const id_expr* e)
  {
    return cxt.make_exec_cmd(e->locs);
  }

  cmd*
  translator::translate_seq_cmd(const list_expr* e)
  {
    // Translate each command in turn.
    cmd_seq cmds;
    for (const expr* c : e->exprs)
      cmds.push_back(translate_cmd(c));

    return cxt.make_seq_cmd(e->locs, std::move(cmds));
  }


} // namespace dcipl::postfix
