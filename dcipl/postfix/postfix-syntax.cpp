#include "postfix-syntax.hpp"

#include <sstream>

namespace dcipl
{
namespace postfix
{
  const char*
  get_node_name(const prog* p)
  {
    return "prog";
  }

  const char*
  get_node_name(const cmd* c)
  {
    return get_command_name(get_command_kind(c));
  }

  const char*
  get_tag_name(const prog* p)
  {
    return "postfix";
  }

  // \todo This is not valid for integer commands. Perhaps it should fail.
  const char*
  get_tag_name(const cmd* c)
  {
    switch (get_command_kind(c)) {
      default:
        return get_node_name(c);
      case ck_arith:
        return get_op_name(static_cast<const arith_cmd*>(c)->op);
      case ck_rel:
        return get_op_name(static_cast<const rel_cmd*>(c)->op);
    }
  }

  const char* 
  get_command_name(cmd_kind k)
  {
    switch (k) {
      case ck_int:
        return "int";
      case ck_pop:
        return "pop";
      case ck_swap:
        return "swap";
      case ck_arith:
        return "arith";
      case ck_rel:
        return "rel";
      case ck_get:
        return "get";
      case ck_sel:
        return "sel";
      case ck_exec:
        return "exec";
      case ck_seq:
        return "seq";
      default:
        break;
    }
    throw std::logic_error("invalid node kind");
  }

  const char*
  get_op_name(arith_op k)
  {
    switch (k) {
      case op_add:
        return "+";
      case op_sub:
        return "-;";
      case op_mul:
        return "*";
      case op_div:
        return "/";
      case op_rem:
        return "%";
    }
  }

  const char*
  get_op_name(rel_op k)
  {
    switch (k) {
      case op_lt:
        return "<";
      case op_eq:
        return "=;";
      case op_gt:
        return ">";
    }
  }

  prog*
  ast_context::make_prog(cc::span locs, int args, cmd_seq&& body)
  {
    return new prog(locs, args, std::move(body));
  }
  
  cmd*
  ast_context::make_int_cmd(cc::span locs, int val)
  {
    return new int_cmd(locs, val);
  }

  cmd*
  ast_context::make_pop_cmd(cc::span locs)
  {
    return new pop_cmd(locs);
  }

  cmd*
  ast_context::make_swap_cmd(cc::span locs)
  {
    return new swap_cmd(locs);
  }

  cmd*
  ast_context::make_arith_cmd(cc::span locs, arith_op k)
  {
    return new arith_cmd(locs, k);
  }

  cmd*
  ast_context::make_rel_cmd(cc::span locs, rel_op k)
  {
    return new rel_cmd(locs, k);
  }

  cmd*
  ast_context::make_get_cmd(cc::span locs)
  {
    return new get_cmd(locs);
  }

  cmd*
  ast_context::make_sel_cmd(cc::span locs)
  {
    return new sel_cmd(locs);
  }

  cmd*
  ast_context::make_exec_cmd(cc::span locs)
  {
    return new exec_cmd(locs);
  }

  cmd*
  ast_context::make_seq_cmd(cc::span locs, cmd_seq&& cmds)
  {
    return new seq_cmd(locs, std::move(cmds));
  }

  symbol* 
  ast_context::get_symbol(const char* str)
  {
    return syms.get(str);
  }
  
  symbol* 
  ast_context::get_symbol(const std::string& str)
  {
    return syms.get(str);
  }

} // namespace postfix
} // namespace dcipl
