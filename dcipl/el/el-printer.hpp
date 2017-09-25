#pragma once

#include <cc/print.hpp>

namespace dcipl
{
namespace el
{
  class prog;
  class num_expr;
  class int_lit;
  class arg_expr;
  class arith_expr;
  class if_expr;
  class bool_expr;
  class bool_lit;
  class rel_expr;
  class logic_expr;

  // The printer is responsible for pretty printing a program.
  class printer : public cc::printer
  {
  public:
    printer(std::ostream& os)
      : cc::printer(os)
    { }

    void operator()(const prog* p) { return print_prog(p); }
    void operator()(const num_expr* e) { return print_num_expr(e); }
    void operator()(const bool_expr* e) { return print_bool_expr(e); }

  private:
    void print_prog(const prog* p);

    void print_num_expr(const num_expr* e);
    void print_int_lit(const int_lit* n);
    void print_arg_expr(const arg_expr* n);
    void print_arith_expr(const arith_expr* n);
    void print_if_expr(const if_expr* n);

    void print_bool_expr(const bool_expr* e);
    void print_bool_lit(const bool_lit* n);
    void print_rel_expr(const rel_expr* n);
    void print_logic_expr(const logic_expr* n);
  };

  std::ostream& operator<<(std::ostream& os, const prog* p);
  std::ostream& operator<<(std::ostream& os, const num_expr* e);
  std::ostream& operator<<(std::ostream& os, const bool_expr* e);

} // namespace el
} // namespace dcipl

