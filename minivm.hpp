#pragma once

#include "dcipl/el/el-syntax.hpp"
#include "sexpr/translation.hpp"
#include <iostream>
#include <string>

namespace dcipl
{
    namespace el
    {

        struct vm_prog;
        struct vm_block;
        struct vm_command;

        struct vm_prog
        {
            int nargs;
            vm_block* body;

            vm_prog(int n, vm_block* blocks)
            : nargs(n), body(blocks)
            {}
        };

        struct vm_block
        {
            int identifier;
            vm_command* commands;
        };

        struct vm_command
        {
            string command;
        };

        vm_prog* pcomp(prog* program);
        vm_block* ncomp(num_expr* e);
        vm_block* bcomp(bool_expr* e);
    }
}