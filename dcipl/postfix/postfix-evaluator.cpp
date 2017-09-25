#include "postfix-evaluator.hpp"
#include "postfix-syntax.hpp"

#include <iostream>

namespace dcipl::postfix
{
  evaluator::evaluator(const std::vector<int>& args)
  {
    stack.resize(args.size());
    std::transform(args.begin(), args.end(), stack.begin(), [](int n) {
      return value(n);
    });
  }

  int 
  evaluator::evaluate(const prog* p)
  {
    eval_prog(p);
    return pop_num();
  }

  void
  evaluator::eval_prog(const prog* p)
  {
    for (const cmd* c : p->cmds)
      eval_cmd(c);
  }

  void
  evaluator::eval_cmd(const cmd* c)
  {
    switch (get_node_kind(c)) {
      case ck_int:
        return eval_int_cmd(static_cast<const int_cmd*>(c));
      case ck_pop:
        return eval_pop_cmd(static_cast<const pop_cmd*>(c));
      case ck_swap:
        return eval_swap_cmd(static_cast<const swap_cmd*>(c));
      case ck_arith:
        return eval_arith_cmd(static_cast<const arith_cmd*>(c));
      case ck_rel:
        return eval_rel_cmd(static_cast<const rel_cmd*>(c));
      case ck_get:
        return eval_get_cmd(static_cast<const get_cmd*>(c));
      case ck_sel:
        return eval_sel_cmd(static_cast<const sel_cmd*>(c));
      case ck_exec:
        return eval_exec_cmd(static_cast<const exec_cmd*>(c));
      case ck_seq:
        return eval_seq_cmd(static_cast<const seq_cmd*>(c));
      default:
        break;
    }
    throw std::logic_error("invalid command");
  }

  void
  evaluator::eval_int_cmd(const int_cmd* c)
  {
    push_num(c->val);
  }
  
  void
  evaluator::eval_pop_cmd(const pop_cmd* c)
  {
    pop_val();
  }

  void
  evaluator::eval_swap_cmd(const swap_cmd* c)
  {
    int n1 = pop_num();
    int n2 = pop_num();
    push_num(n1);
    push_num(n2);
  }

  void
  evaluator::eval_arith_cmd(const arith_cmd* c)
  {
    int n1 = pop_num();
    int n2 = pop_num();
    switch (c->op) {
      case op_add:
        return push_num(n1 + n2);
      case op_sub:
        return push_num(n1 - n2);
      case op_mul:
        return push_num(n1 * n2);
      case op_div:
        return push_num(n1 / n2);
      case op_rem:
        return push_num(n1 % n2);
    }
  }

  void
  evaluator::eval_rel_cmd(const rel_cmd* c)
  {
    int n1 = pop_num();
    int n2 = pop_num();
    switch (c->op) {
      case op_lt:
        return push_num(n1 < n2);
      case op_eq:
        return push_num(n1 == n2);
      case op_gt:
        return push_num(n1 > n2);
    }
  }

  void
  evaluator::eval_get_cmd(const get_cmd* c)
  {
    int ix = pop_num();
    auto iter = stack.end() - ix;
    push_num(iter->rep.num);
  }

  void
  evaluator::eval_sel_cmd(const sel_cmd* c)
  {
    int v1 = pop_num();
    int v2 = pop_num();
    int v3 = pop_num();
    if (v3 == 0)
      push_num(v1);
    else
      push_num(v2);
  }

  // FIXME: This recursively evaluates commands. That should be equivalent
  // to explicitly inserting those commands into the front of the command
  // queue.
  void
  evaluator::eval_exec_cmd(const exec_cmd* c)
  {
    seq_value cs = pop_seq();
    for (const cmd* sc : cs->cmds)
      eval_cmd(sc);
  }

  void
  evaluator::eval_seq_cmd(const seq_cmd* c)
  {
    push_seq(c);
  }

  void
  evaluator::push_num(int_value n)
  {
    stack.emplace_back(n);
  }

  void
  evaluator::push_seq(seq_value s)
  {
    stack.emplace_back(s);
  }

  void
  evaluator::push(value v)
  {
    stack.push_back(v);
  }

  value
  evaluator::pop_val()
  {
    value v = stack.back();
    stack.pop_back();
    return v;
  }

  int_value
  evaluator::pop_num()
  {    
    value v = pop_val();
    if (v.kind != vk_int)
      throw evaluation_error({}, "stack operand error");
    return v.rep.num;
  }

  seq_value
  evaluator::pop_seq()
  {    
    value v = pop_val();
    if (v.kind != vk_seq)
      throw evaluation_error({}, "stack operand error");
    return v.rep.seq;
  }


} // namespace dcipl::postfix
