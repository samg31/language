#include "postfix-dumper.hpp"
#include "postfix-syntax.hpp"

#include <iostream>

namespace dcipl::postfix
{
  void
  dumper::dump_prog(const prog* p)
  {
    dump_guard g(*this, p);
  }

  void
  dumper::dump_cmd(const cmd* c)
  {
    switch (get_command_kind(c)) {
      case ck_int:
        return dump_int_cmd(static_cast<const int_cmd*>(c));
      case ck_pop:
        return dump_pop_cmd(static_cast<const pop_cmd*>(c));
      case ck_swap :
        return dump_swap_cmd(static_cast<const swap_cmd*>(c));
      case ck_arith:
        return dump_arith_cmd(static_cast<const arith_cmd*>(c));
      case ck_rel:
        return dump_rel_cmd(static_cast<const rel_cmd*>(c));
      case ck_get:
        return dump_get_cmd(static_cast<const get_cmd*>(c));
      case ck_sel:
        return dump_sel_cmd(static_cast<const sel_cmd*>(c));
      case ck_exec :
        return dump_exec_cmd(static_cast<const exec_cmd*>(c));
      case ck_seq:
        return dump_seq_cmd(static_cast<const seq_cmd*>(c));
    }
    throw std::logic_error("invalid command");
  }

  void
  dumper::dump_int_cmd(const int_cmd* c)
  {
    dump_guard g(*this, c);
  }

  void
  dumper::dump_pop_cmd(const pop_cmd* c)
  {
    dump_guard g(*this, c);    
  }

  void
  dumper::dump_swap_cmd(const swap_cmd* c)
  {
    dump_guard g(*this, c);    
  }

  void
  dumper::dump_arith_cmd(const arith_cmd* c)
  {
    dump_guard g(*this, c);
    os << " " << get_op_name(c->op);
  }

  void
  dumper::dump_rel_cmd(const rel_cmd* c)
  {
    dump_guard g(*this, c);
    os << " " << get_op_name(c->op);    
  }

  void
  dumper::dump_get_cmd(const get_cmd* c)
  {
    dump_guard g(*this, c);    
  }

  void
  dumper::dump_sel_cmd(const sel_cmd* c)
  {
    dump_guard g(*this, c);    
  }

  void
  dumper::dump_exec_cmd(const exec_cmd* c)
  {
    dump_guard g(*this, c);    
  }

  void
  dumper::dump_seq_cmd(const seq_cmd* c)
  {
    dump_guard g(*this, c);
    indent();
    for (const cmd* c : c->cmds)
      dump_cmd(c);
    undent();
  }

  dumper::dump_guard::dump_guard(dumper& d, const prog* p)
    : pl::dumper::dump_guard(d, p, get_node_name(p))
  { }

  dumper::dump_guard::dump_guard(dumper& d, const cmd* c)
    : pl::dumper::dump_guard(d, c, get_node_name(c))
  { }

  void
  dump(const prog* p)
  {
    dumper d(std::cerr);
    d(p);
  }

  void
  dump(const cmd* c)
  {
    dumper d(std::cerr);
    d(c);
  }


} // dcipl::postfix
