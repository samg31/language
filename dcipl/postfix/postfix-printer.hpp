#pragma once

#include <pl/util/print.hpp>

#include <vector>

namespace dcipl::postfix
{
  class prog;
  class cmd;

  // The printer is responsible for pretty printing a program.
  class printer : public pl::printer
  {
  public:
    using pl::printer::printer;

    using pl::printer::print;

    void print(const prog* p);
    void print(const cmd* c);

  private:
    void print_prog(const prog* p);
    void print_cmd(const cmd* c);
    void print_cmds(const std::vector<cmd*>& cs);
  };

  std::ostream& operator<<(std::ostream& os, const prog* p);
  std::ostream& operator<<(std::ostream& os, const cmd* c);

} // namespace dcipl::postfix
