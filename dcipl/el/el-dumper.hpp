#pragma once

#include <cc/dump.hpp>

namespace dcipl
{
namespace el
{
  struct prog;
  struct num_expr;
  struct int_lit;
  struct arg_expr;
  struct arith_expr;
  struct if_expr;
  struct bool_expr;
  struct bool_lit;
  struct rel_expr;
  struct logic_expr;

  /// The AST dumper is responsible for dumping the internal representation
  /// of a source tree to an output stream.
  class dumper : public cc::dumper
  {
  public:
    using cc::dumper::dumper;

    void operator()(const prog* e) { return dump_prog(e); }
    void operator()(const num_expr* e) { return dump_num_expr(e); }
    void operator()(const bool_expr* e) { return dump_bool_expr(e); }

  private:
    void dump_prog(const prog* p);
    void dump_num_expr(const num_expr* e);
    void dump_int_lit(const int_lit* e);
    void dump_arg_expr(const arg_expr* e);
    void dump_arith_expr(const arith_expr* e);
    void dump_if_expr(const if_expr* e);
    void dump_bool_expr(const bool_expr* e);
    void dump_bool_lit(const bool_lit* e);
    void dump_rel_expr(const rel_expr* e);
    void dump_logic_expr(const logic_expr* e);

    struct dump_guard : cc::dumper::dump_guard
    {
      dump_guard(dumper& d, const prog* e, bool nl = true);
      dump_guard(dumper& d, const num_expr* e, bool nl = true);
      dump_guard(dumper& d, const bool_expr* e, bool nl = true);
    };
  };

  void dump(const prog* p);
  void dump(const num_expr* e);
  void dump(const bool_expr* b);

} // namespace el
} // namespace dcipl
