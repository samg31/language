#pragma once

#include <cc/node.hpp>
#include <cc/symbol.hpp>

namespace dcipl
{
namespace el
{
  /// Imports
  using cc::symbol;

  /// The kind of a program.
  enum prog_kind
  {
    pk_prog
  };

  /// The kinds of numeric expressions.
  enum num_expr_kind 
  {
    ek_int,
    ek_arg,
    ek_arith,
    ek_if
  };

  // The kinds of boolean expressions.
  enum bool_expr_kind
  {
    ek_bool,
    ek_rel,
    ek_logic
  };

  /// The kinds of arithmetic operations.
  enum arith_op 
  { 
    op_add, 
    op_sub, 
    op_mul, 
    op_div, 
    op_rem 
  };

  /// The kinds of relational operations.
  enum rel_op 
  { 
    op_lt, 
    op_eq, 
    op_gt 
  };

  /// The kinds of logical operations.
  enum logic_op 
  { 
    op_and, 
    op_or 
  };

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

  /// An EL program.
  struct prog : cc::node
  {
    prog(cc::span locs, int nargs, num_expr* body)
      : cc::node(pk_prog, locs), nargs(nargs), body(body) { }

    int nargs;
    num_expr* body;
  };

  /// Numeric expressions.
  struct num_expr : cc::node
  {
    num_expr(num_expr_kind k, cc::span locs)
      : cc::node(k, locs) { }
  };

  /// Integer values.
  struct int_lit : num_expr
  {
    int_lit(cc::span locs, int n)
      : num_expr(ek_int, locs), val(n) { }
    
    int val;
  };

  /// Program argument access.
  struct arg_expr : num_expr
  {
    arg_expr(cc::span locs, int n)
      : num_expr(ek_arg, locs), ix(n) { }

    int ix;
  };

  /// Arithmetic operations.
  struct arith_expr : num_expr
  {
    arith_expr(cc::span locs, arith_op op, num_expr* e1, num_expr* e2)
      : num_expr(ek_arith, locs), op(op), e1(e1), e2(e2) { }

    arith_op op;
    num_expr* e1;
    num_expr* e2;
  };

  /// An if expression.
  struct if_expr : num_expr
  {
    if_expr(cc::span locs, bool_expr* t, num_expr* e1, num_expr* e2)
      : num_expr(ek_if, locs), test(t), e1(e1), e2(e2) { }

    bool_expr* test;
    num_expr* e1;
    num_expr* e2;
  };

  /// The set of boolean expressions.
  struct bool_expr : cc::node
  {
    bool_expr(bool_expr_kind k, cc::span locs)
      : cc::node(k, locs) { }
  };

  /// Boolean values.
  struct bool_lit : bool_expr
  {
    bool_lit(cc::span locs, bool b)
      : bool_expr(ek_bool, locs), val(b) { }

    bool val;
  };

  /// Relational operations.
  struct rel_expr : bool_expr
  {
    rel_expr(cc::span locs, rel_op op, num_expr* e1, num_expr* e2)
      : bool_expr(ek_rel, locs), op(op), e1(e1), e2(e2) { }

    rel_op op;
    num_expr* e1;
    num_expr* e2;
  };

  /// Logic operations.
  struct logic_expr : bool_expr
  {
    logic_expr(cc::span locs, logic_op, bool_expr* e1, bool_expr* e2)
      : bool_expr(ek_logic, locs), e1(e1), e2(e2) { }

    logic_op op;
    bool_expr* e1;
    bool_expr* e2;
  };

// -------------------------------------------------------------------------- //
// Operations

  /// Returns the name of the program node.
  inline const char* 
  get_node_name(prog_kind k)
  {
    return "prog";
  }

  /// Returns the name of a numeric expression.
  const char* get_node_name(num_expr_kind k);

  /// Returns the name of boolean expression.
  const char* get_node_name(bool_expr_kind k);

  /// Returns the name of arithmetic operator.
  const char* get_op_name(arith_op op);
    
  /// Returns the name of relational operator.
  const char* get_op_name(rel_op op);

  /// Returns the name of logical operator.
  const char* get_op_name(logic_op op);

  /// Returns the kind of a program.
  inline prog_kind
  get_program_kind(const prog* p)
  {
    return static_cast<prog_kind>(p->kind);
  }

  /// Returns the kind of of a numeric expression.
  inline num_expr_kind
  get_expr_kind(const num_expr* e)
  {
    return static_cast<num_expr_kind>(e->kind);
  }

  /// Returns the kind of of a boolean expression.
  inline bool_expr_kind
  get_expr_kind(const bool_expr* e)
  {
    return static_cast<bool_expr_kind>(e->kind);
  }
  
  /// Returns the node name of a program.
  inline const char* 
  get_node_name(const prog* p)
  {
    return get_node_name(get_program_kind(p));
  }

  /// Returns the node name of a numeric expression.
  inline const char*
  get_node_name(const num_expr* e)
  {
    return get_node_name(get_expr_kind(e));
  }

  /// Returns the node name of a boolean expression.
  inline const char*
  get_node_name(const bool_expr* e)
  {
    return get_node_name(get_expr_kind(e));
  }

  /// Returns the tag name of a program.
  inline const char* 
  get_tag_name(const prog* p)
  {
    return "el";
  }

  /// Returns the tag of a numeric expression.
  const char* get_tag_name(const num_expr* e);

  /// Returns the tag name of a boolean expression.
  const char* get_tag_name(const bool_expr* e);

} // namespace el
} // namespace dcipl
