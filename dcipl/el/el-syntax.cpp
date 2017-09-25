#include "el-syntax.hpp"

#include <sstream>

namespace dcipl
{
namespace el
{
  const char* 
  get_node_name(num_expr_kind k)
  {
    switch (k) {
      case ek_int:
        return "int";
      case ek_arg:
        return "arg";
      case ek_arith:
        return "arith";
      case ek_if:
        return "if";
    }
  }

  const char*
  get_node_name(bool_expr_kind k)
  {
    switch (k) {
      case ek_bool:
        return "bool";
      case ek_rel:
        return "rel";
      case ek_logic:
        return "logic";
    }
  }

  const char*
  get_op_name(arith_op op)
  {
    switch (op) {
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
  get_op_name(rel_op op)
  {
    switch (op) {
      case op_lt:
        return "<";
      case op_eq:
        return "=;";
      case op_gt:
        return ">";
    }
  }

  const char*
  get_op_name(logic_op op)
  {
    switch (op) {
      case op_and:
        return "and";
      case op_or:
        return "or";
    }
  }

  const char*
  get_tag_name(const num_expr* e)
  {
    switch (get_expr_kind(e)) {
      default:
        break;
      case ek_arg:
        return "arg";
      case ek_arith:
        return get_op_name(static_cast<const arith_expr*>(e)->op);
      case ek_if:
        return "if";
    }
    throw std::logic_error("no such tag name");
  }

  const char*
  get_tag_name(const bool_expr* e)
  {
    switch (get_expr_kind(e)) {
      default:
        break;
      case ek_rel:
        return get_op_name(static_cast<const rel_expr*>(e)->op);
      case ek_logic:
        return get_op_name(static_cast<const logic_expr*>(e)->op);
    }
    throw std::logic_error("no such tag name");
  }

} // namespace el
} // namepace dcipl
