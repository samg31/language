#include "postfix-printer.hpp"
#include "postfix-syntax.hpp"

#include <iostream>

namespace dcipl::postfix 
{
  void
  printer::print(const prog* p)
  {
    return print_prog(p);
  }

  void
  printer::print(const cmd* c)
  {
    return print_cmd(c);
  }

  void
  printer::print_prog(const prog* p)
  {
    sexpr s(os, get_tag_name(p));
    os << p->nargs << ' ';
    print_cmds(p->cmds);
  }

  void
  printer::print_cmd(const cmd* c)
  {
    switch (get_node_kind(c)) {
      case ck_int:
        os << static_cast<const int_cmd*>(c)->val;
        break;
      case ck_pop:
      case ck_swap:
      case ck_arith:
      case ck_rel:
      case ck_get:
      case ck_sel:
      case ck_exec:
        os << get_tag_name(c);
        break;
      case ck_seq:
        os << '(';
        print_cmds(static_cast<const seq_cmd*>(c)->cmds);
        os << ')';
        break;
      default:
        break;
    }
    throw std::logic_error("invalid command");
  }

  void
  printer::print_cmds(const cmd_seq& cmds)
  {
    for (auto iter = cmds.begin(); iter != cmds.end(); ++iter) {
      print(*iter);
      if (std::next(iter) != cmds.end())
        os << ' ';
    }
  }


  std::ostream&
  operator<<(std::ostream& os, const prog* p)
  {
    printer pp(os);
    pp.print(p);
    return os;
  }

  std::ostream&
  operator<<(std::ostream& os, const cmd* c)
  {
    printer p(os);
    p.print(c);
    return os;
  }

} // namespace dcipl::postfix
