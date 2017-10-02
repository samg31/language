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
            vm_block* next;
        };

        struct vm_command
        {
            string command;
            vm_command* next;

            vm_command(string com)
            :command(com), next(nullptr)
            {}
            
            vm_command(string com, vm_command* c)
            :command(com), next(c)
            {}
        };

        vm_prog* pcomp(prog* program);
        vm_block* ncomp(num_expr* e);
        vm_block* bcomp(bool_expr* e);

        vm_command* num_command(num_expr* e);
        vm_command* bool_command(bool_expr* e);

        vm_commmand* tran_arith(arith_expr* e);
        vm_commmand* tran_if(if_expr* e);
        vm_commmand* tran_logic(logic_expr* e);
        vm_commmand* tran_rel(rel_expr* e);
        
        string tran_op(arith_op op);
    }
}