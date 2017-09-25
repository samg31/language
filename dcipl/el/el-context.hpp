#pragma once

#include <el/el-syntax.hpp>

#include <cc/diagnostics.hpp>
#include <cc/input.hpp>
#include <cc/symbol.hpp>

namespace dcipl
{
namespace el
{
  /// The EL programming language context binds together a large number of
  /// services that can be used in various translation algorithms.
  ///
  /// \todo Factor node creation into a factory facility.
  class context
  {
  public:
    context(cc::input_manager& in, 
            cc::diagnostic_manager& diags, 
            cc::symbol_table& syms);

    /// Returns the diagnostic manager.
    cc::diagnostic_manager& get_diagnostics() const { return diags; }
    
    /// Returns the input manager.
    cc::input_manager& get_inputs() const { return inputs; }
    
    /// Returns the symbol table.
    cc::symbol_table& get_symbols() { return syms; }

    prog* make_prog(cc::span locs, int args, num_expr* body);
    
    num_expr* make_int_lit(cc::span locs, int val);
    num_expr* make_arg_expr(cc::span locs, int ix);
    num_expr* make_arith_expr(cc::span locs, arith_op k, num_expr* e1, num_expr* e2);
    num_expr* make_if_expr(cc::span locs, bool_expr* e1, num_expr* e2, num_expr* e3);
    
    bool_expr* make_bool_lit(cc::span locs, bool val);
    bool_expr* make_rel_expr(cc::span locs, rel_op k, num_expr* e1, num_expr* e2);
    bool_expr* make_logic_expr(cc::span locs, logic_op k, bool_expr* e1, bool_expr* e2);

  private:
    cc::input_manager& inputs;
    cc::diagnostic_manager& diags;
    cc::symbol_table& syms;
  };

} // namespace el
} // namespace dcipl
