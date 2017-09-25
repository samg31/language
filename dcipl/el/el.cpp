#include "el-context.hpp"
#include "el-translator.hpp"
#include "el-evaluator.hpp"
#include "el-printer.hpp"
#include "el-dumper.hpp"

#include <sexpr/parser.hpp>
#include <sexpr/context.hpp>
#include <sexpr/dumper.hpp>
#include <sexpr/printer.hpp>

#include <cc/diagnostics.hpp>
#include <cc/input.hpp>
#include <cc/output.hpp>

#include <iostream>
#include <fstream>
#include <iterator>

class usage_error : public cc::diagnosable_error
{
public:
  usage_error(const std::string& msg)
    : cc::diagnosable_error(cc::dk_error, "usage", {}, msg)
  { }
};

/// Encodes command line arguments.
struct arguments
{
  /// The input source file.
  std::string input;

  /// The input arguments.
  std::vector<int> vals;
};

static void
process_arguments(int argc, char* argv[], arguments& args)
{
  // Process command line arguments.
  if (argc < 2)
    throw usage_error("no input file given");

  // The input file is expected as the first argument.
  args.input = argv[1];
  
  // The remaining arguments are inputs to the program.
  //
  // TODO: Check for valid integers.
  for (int i = 2; i < argc; ++i)
    args.vals.push_back(std::stoi(argv[i]));
}

/// An RAII guard used to ensure that diagnostics are printed
/// before main exits.
///
/// \todo: Consider using a `finally()` facility.
struct diagnostic_guard
{
  diagnostic_guard(const cc::diagnostic_manager& diags, 
                   const cc::input_manager& in,
                   cc::output_device& out)
    : diags(diags), in(in), out(out)
  { }

  ~diagnostic_guard()
  {
    print(diags.get_diagnostics(), in, out);
  }

  const cc::diagnostic_manager& diags;
  const cc::input_manager& in;
  cc::output_device& out;
};

int 
main(int argc, char* argv[]) 
{
  /// Detects output information.
  cc::output_device error(std::cerr);

  // Manages input sources.
  cc::input_manager inputs;

  // Accumulates errors diagnostics.
  cc::diagnostic_manager diags;

  /// Ensure that diangostics are printed on return from main.
  diagnostic_guard print_errs_on_exit(diags, inputs, error);
    
  // Process command line arguments.
  arguments args;
  try {
    process_arguments(argc, argv, args);
  }
  catch (cc::diagnosable_error& err) {
    diags.emit(err);    
    return 1;
  }

  // The first argument is an input source.
  // FIXME: This can throw.
  const cc::file& input = inputs.add_file(argv[1]);

  // A table of unique strings.
  cc::symbol_table syms;  
  
  // AST information for s-expressions.
  sexpr::context sexpr(diags, inputs, syms);

  // Parse the input.
  sexpr::parser parse(sexpr, input);
  sexpr::expr *ex;
  try {
    ex = parse();
  }
  catch (cc::diagnosable_error& err) {
    diags.emit(err);
    return 1;
  }

  // AST information for EL programs.
  dcipl::el::context el(inputs, diags, syms);
  
  // Translate the sexpr tree into el.
  dcipl::el::translator trans(el);
  dcipl::el::prog *prog;
  try {
    prog = trans(ex);
  }
  catch (char) { }
  // catch (cc::diagnosable_error& err) {
  //   diags.emit(err);
  //   return 1;
  // }

  std::cout << prog << '\n';
  dump(prog);

  // Evalaute the program.
  dcipl::el::evaluator eval(el, args.vals);
  int ret;
  try {
    ret = eval(prog);
  } catch (cc::diagnosable_error& err) {
    diags.emit(err);
    return 1;
  }
  std::cout << ret << '\n';

  return 0;
}
