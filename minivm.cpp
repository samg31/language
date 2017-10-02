#include "minivm.hpp"

vm_prog* 
pcomp(prog* program)
{
    return vm_prog(program-nargs, ncomp(program->body));
}

vm_block* 
ncomp(num_expr* e)
{}

vm_block* 
bcomp(bool_expr* e)
{}