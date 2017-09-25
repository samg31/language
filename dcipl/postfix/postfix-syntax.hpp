#pragma once

#include <cc/node.hpp>
#include <cc/symbol.hpp>

#include <vector>

namespace dcipl
{
namespace postfix
{
// -------------------------------------------------------------------------- //
// Imports

  using symbol = cc::symbol;

  using cc::is;
  using cc::as;
  using cc::cast;

// -------------------------------------------------------------------------- //
// Syntax

  /// Program kind.
  enum prog_kind
  {
    pk_prog,
  };

  /// Commands kinds.
  enum cmd_kind 
  {
    ck_int,
    ck_pop,
    ck_swap,
    ck_arith,
    ck_rel,
    ck_get,
    ck_sel,
    ck_exec,
    ck_seq,
  };

  /// Arithmetic operations.
  enum arith_op 
  { 
    op_add,
    op_sub,
    op_mul,
    op_div,
    op_rem 
  };

  /// Relational operations.
  enum rel_op 
  { 
    op_lt, 
    op_eq, 
    op_gt
  };
  
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

  using cmd_seq = std::vector<cmd*>;
  
  /// A postfix program.
  struct prog : cc::node
  {
    prog(cc::span locs, int n, const cmd_seq& cs)
      : cc::node(pk_prog, locs), nargs(n), cmds(cs) { }

    prog(cc::span locs, int n, cmd_seq&& cs)
      : cc::node(pk_prog, locs), nargs(n), cmds(cs) { }

    int nargs;
    cmd_seq cmds;
  };

  /// The set of all commands.
  struct cmd : cc::node
  {
    cmd(cmd_kind k, cc::span locs)
      : cc::node(k, locs) { }
  };

  /// Pushes an integer value.
  struct int_cmd : cmd
  {
    int_cmd(cc::span locs, int n)
      : cmd(ck_int, locs), val(n) { }

    int val;
  };

  /// Pops the top of the stack.
  struct pop_cmd : cmd
  {
    pop_cmd(cc::span locs)
      : cmd(ck_pop, locs) { }
  };

  /// Swaps the top two elements of the stack.
  struct swap_cmd : cmd
  {
    swap_cmd(cc::span locs)
      : cmd(ck_swap, locs) { }
  };
  
  /// An arithmetic operation; pops two values, applies the
  /// operation, and pushes the result.
  struct arith_cmd : cmd
  {
    arith_cmd(cc::span locs, arith_op op)
      : cmd(ck_arith, locs), op(op) { }
  
    arith_op op;
  };

  /// A relational operation.
  struct rel_cmd : cmd
  {
    rel_cmd(cc::span locs, rel_op op)
      : cmd(ck_rel, locs), op(op) { }
  
    rel_op op;
  };

  /// Pushes a copy of the nth value from the top of the stack.
  struct get_cmd : cmd
  {
    get_cmd(cc::span locs)
      : cmd(ck_get, locs) { }
};

  /// A conditional operation.
  struct sel_cmd : cmd
  {
    sel_cmd(cc::span locs)
      : cmd(ck_sel, locs) { }
  };

  /// Evaluates a command sequence.
  struct exec_cmd : cmd
  {
    exec_cmd(cc::span locs)
      : cmd(ck_exec, locs) { }
  };

  /// A sequence of commands.
  struct seq_cmd : cmd
  {
    seq_cmd(cc::span locs, const cmd_seq& cs)
      : cmd(ck_seq, locs), cmds(cs) { }
  
    seq_cmd(cc::span locs, cmd_seq&& cs)
      : cmd(ck_seq, locs), cmds(std::move(cs)) { }

    cmd_seq cmds;
  };

// -------------------------------------------------------------------------- //
// Operations

  /// Returns the kind of a command.
  inline cmd_kind
  get_command_kind(const cmd* c)
  {
    return static_cast<cmd_kind>(c->kind);
  }

  /// Returns the node name of a program.
  const char* get_node_name(const prog* p);

  /// Returns the node name of a program.
  const char* get_node_name(const cmd* c);

  /// Returns the tag name of a program. 
  const char* get_tag_name(const prog* p);
  
  /// Returns the tag name of a command.
  const char* get_tag_name(const cmd* c);

  /// Returns the name of a command kind.
  const char* get_command_name(cmd_kind k);

  /// Returns the name of arithmetic operator.
  const char* get_op_name(arith_op k);

  /// Returns the name of relational operator.
  const char* get_op_name(rel_op k);

// -------------------------------------------------------------------------- //
// Syntactic context

  class ast_context
  {
  public:
    ast_context(cc::symbol_table& syms)
      : syms(syms)
    { }

    /// Returns the symbol table.
    cc::symbol_table& get_symbols() { return syms; }

    symbol* get_symbol(const char* str);
    symbol* get_symbol(const std::string& str);

    prog* make_prog(cc::span locs, int args, cmd_seq&& body);
    
    cmd* make_int_cmd(cc::span locs, int val);
    cmd* make_pop_cmd(cc::span locs);
    cmd* make_swap_cmd(cc::span locs);
    cmd* make_arith_cmd(cc::span locs, arith_op k);
    cmd* make_rel_cmd(cc::span locs, rel_op k);
    cmd* make_get_cmd(cc::span locs);
    cmd* make_sel_cmd(cc::span locs);
    cmd* make_exec_cmd(cc::span locs);
    cmd* make_seq_cmd(cc::span locs, cmd_seq&& cmds);

  private:
    /// The symbol table.
    cc::symbol_table& syms;
  };

} // namespace postfix
} // namespace dcipl
