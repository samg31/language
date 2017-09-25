#include "el-printer.hpp"
#include "el-syntax.hpp"

#include <iostream>

namespace dcipl
{
namespace el
{
  void 
  printer::print_prog(const prog* p)
  {
    sexpr s(os, get_tag_name(p));
    os << p->nargs << ' ';
    print_num_expr(p->body);
  }

  void
  printer::print_num_expr(const num_expr* e)
  {
    switch (get_expr_kind(e)) {
      case ek_int:
        return print_int_lit(static_cast<const int_lit*>(e));
      case ek_arg:
        return print_arg_expr(static_cast<const arg_expr*>(e));
      case ek_arith:
        return print_arith_expr(static_cast<const arith_expr*>(e));
      case ek_if:
        return print_if_expr(static_cast<const if_expr*>(e));
    }
  }

  void 
  printer::print_int_lit(const int_lit* val)
  {
    os << val->val;
  }

  void 
  printer::print_arg_expr(const arg_expr* e)
  {
    sexpr s(os, get_tag_name(e));
    os << e->ix;
  }

  void 
  printer::print_arith_expr(const arith_expr* op)
  {
    sexpr s(os, get_tag_name(op));
    print_num_expr(op->e1);
    os << ' ';
    print_num_expr(op->e2);
  }

  void 
  printer::print_if_expr(const if_expr* e)
  {
    sexpr s(os, get_tag_name(e));
    print_bool_expr(e->test);
    os << ' ';
    print_num_expr(e->e1);
    os << ' ';
    print_num_expr(e->e2);
  }

  void
  printer::print_bool_expr(const bool_expr* e)
  {
    switch (get_expr_kind(e)) {
      case ek_bool:
        return print_bool_expr(static_cast<const bool_expr*>(e));
      case ek_rel:
        return print_rel_expr(static_cast<const rel_expr*>(e));
      case ek_logic:
        return print_logic_expr(static_cast<const logic_expr*>(e));
    }
  }

  void 
  printer::print_bool_lit(const bool_lit* e)
  {
    os << (e->val ? "true" : "false");
  }

  void 
  printer::print_rel_expr(const rel_expr* e)
  {
    sexpr s(os, get_tag_name(e));
    print_num_expr(e->e1);
    os << ' ';
    print_num_expr(e->e2);
  }

  void 
  printer::print_logic_expr(const logic_expr* e)
  {
    sexpr s(os, get_tag_name(e));
    print_bool_expr(e->e1);
    os << ' ';
    print_bool_expr(e->e2);
  }

  std::ostream&
  operator<<(std::ostream& os, const prog* p)
  {
    printer print(os);
    print(p);
    return os;
  }

  std::ostream&
  operator<<(std::ostream& os, const num_expr* e)
  {
    printer print(os);
    print(e);
    return os;
  }

  std::ostream&
  operator<<(std::ostream& os, const bool_expr* e)
  {
    printer print(os);
    print(e);
    return os;
  }

} // namespace el
} // namespace dcipl
