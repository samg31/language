#pragma once

#include <pl/util/dump.hpp>

namespace dcipl::postfix
{
  struct prog;
  struct cmd;
  struct int_cmd;
  struct pop_cmd;
  struct swap_cmd;
  struct arith_cmd;
  struct rel_cmd;
  struct get_cmd;
  struct sel_cmd;
  struct exec_cmd;
  struct seq_cmd;
  

  /// Emits a formatted AST representation. This is primarily included to
  /// support debugging.
  class dumper : public pl::dumper
  {
  public:
    using pl::dumper::dumper;
    
    void operator()(const prog* p) { dump_prog(p); }
    void operator()(const cmd* c) { dump_cmd(c); }

  private:
    void dump_prog(const prog* p);
    void dump_cmd(const cmd* c);
    void dump_int_cmd(const int_cmd* c);
    void dump_pop_cmd(const pop_cmd* c);
    void dump_swap_cmd(const swap_cmd* c);
    void dump_arith_cmd(const arith_cmd* c);
    void dump_rel_cmd(const rel_cmd* c);
    void dump_get_cmd(const get_cmd* c);
    void dump_sel_cmd(const sel_cmd* c);
    void dump_exec_cmd(const exec_cmd* c);
    void dump_seq_cmd(const seq_cmd* c);

    struct dump_guard : pl::dumper::dump_guard
    {
      dump_guard(dumper& d, const prog* p);
      dump_guard(dumper& d, const cmd* p);
    };
  };

  void dump(const prog* p);
  void dump(const cmd* c);

} // namespace dcipl::postfix
