#include "postfix-syntax.hpp"
#include "postfix-translator.hpp"
#include "postfix-evaluator.hpp"
#include "postfix-printer.hpp"
#include "postfix-dumper.hpp"

#include <pl/sexpr/sexpr-parser.hpp>
#include <pl/sexpr/sexpr-dumper.hpp>

#include <pl/util/diagnostics.hpp>
#include <pl/util/input.hpp>

#include <iostream>
#include <fstream>
#include <iterator>

using namespace pl;

class usage_error : public diagnosable_error
{
public:
  usage_error(const std::string& msg)
    : diagnosable_error(diagnostic::error, "usage", {}, msg)
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

int 
main(int argc, char* argv[]) 
{
  // Manages errors generating during execution;
  diagnostic_manager diags(std::cerr);
  
  // Manages input sources.
  input_manager inputs(diags);
    
  // Process command line arguments.
  arguments args;
  try {
    process_arguments(argc, argv, args);
  }
  catch (diagnosable_error& err) {
    diags.emit(err);    
    return 1;
  }

  // The first argument is an input source.
  const file& input = inputs.add_file(argv[1]);

  // A table of unique strings.
  symbol_table syms;  
  
  // AST information for s-expressions.
  sexpr::ast_context sexpr(syms);

  // Parse the input.
  //
  // TODO: Build the parser over multiple files?
  sexpr::parser parse(syms, sexpr, input);
  sexpr::expr *ex;
  try {
    ex = parse();
  }
  catch (diagnosable_error& err) {
    diags.emit(err, inputs);
    return 1;
  }

  dump(ex);

  // AST information.
  dcipl::postfix::ast_context postfix(syms);

  // Translate the sexpr tree into postfix.
  dcipl::postfix::translator trans(postfix);
  dcipl::postfix::prog *prog;
  try {
    prog = trans(ex);
  }
  catch (diagnosable_error& err) {
    diags.emit(err, inputs);
    return 1;
  }

  dump(prog);

#if 0
  while (1) {
    // Phase 1: parse uninterpreted s-exprs.
    // On error, advance to the next term.
    base::node* n;
    try {
      n = parse();
    }
    catch (translation_error& err) {
      diags.emit(inputs, err);
      // FIXME: Advance to the next term and continue.
    }
    if (!n)
      return 1;

    // Phase 2: elaborate s-exprs into terms.
    // On error, continue elaborating.
    el::prog_term* p;
    try {
      p = elab.elaborate(n);
    }
    catch (translation_error& err) {
      diags.emit(inputs, err);
      continue;
    }

    // Phase 3: evaluation.
    std::cout << p << '\n';
    try {
      int n = eval.evaluate(p);
      std::cout << "result: " << n << '\n';
    }
    catch (translation_error& err) {
      diags.emit(inputs, err);
      continue;      
    }
  }
  #endif
}
