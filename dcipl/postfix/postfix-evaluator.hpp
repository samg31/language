#pragma once

#include <cc/diagnostics.hpp>

#include <vector>

namespace dcipl::postfix
{
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
  struct prog;

  // Integer values are just plain ints.
  using int_value = int;

  // A sequence value is a pointer to the sequence to be evaluated. 
  using seq_value = const seq_cmd*;

  enum value_kind 
  {
    vk_int, 
    vk_seq
  };
  
  union value_rep 
  {
    int_value num;
    seq_value seq;
  };

  /// A value on the stack.
  struct value
  {
    value() = default;
    explicit value(int_value n) : kind(vk_int) { rep.num = n; }
    explicit value(seq_value s) : kind(vk_seq) { rep.seq = s; }

    value_kind kind;
    value_rep rep;
  };

  /// Implements the dynamic semantics of the language.
  struct evaluator
  {
    evaluator(const std::vector<int>& args);

    int evaluate(const prog* p);
    
  protected:
    void eval_prog(const prog* c);
  
    void eval_cmd(const cmd* c);
    void eval_int_cmd(const int_cmd* c);
    void eval_pop_cmd(const pop_cmd* c);
    void eval_swap_cmd(const swap_cmd* c);
    void eval_arith_cmd(const arith_cmd* c);
    void eval_rel_cmd(const rel_cmd* c);
    void eval_get_cmd(const get_cmd* c);
    void eval_sel_cmd(const sel_cmd* c);
    void eval_exec_cmd(const exec_cmd* c);
    void eval_seq_cmd(const seq_cmd* c);

    // Stack commands
    void push_num(int_value n);
    void push_seq(seq_value s);
    void push(value v);
    
    value pop_val();
    int_value pop_num();
    seq_value pop_seq();

    std::vector<value> stack;
  };

  /// Represents a postfix evaluation error.
  class evaluation_error : public pl::diagnosable_error
  {
  public:
    evaluation_error(pl::location loc, const std::string& msg)
      : pl::diagnosable_error(pl::diagnostic::error, "evaluation", loc, msg)
    { }
  };


} // namespace dcipl::postfix