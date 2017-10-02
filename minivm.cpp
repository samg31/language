#include "minivm.hpp"

vm_prog* 
pcomp(prog* program)
{
    return vm_prog(program-nargs, ncomp(program->body));
}

vm_block* 
ncomp(num_expr* e)
{
    switch(e->kind)
    {
        case ek_int:
            return static_cast<int_lit*>(num);
        case ek_argc:
            return static_cast<arg_expr*>(num);
        case ek_arith:
            return eval_arith(static_cast<arith_expr*>(num));
        case ek_if:
            return eval_if(static_cast<if_expr*>(num));
    }
}

vm_block* 
bcomp(bool_expr* e)
{}

vm_command* 
num_command(num_expr* e)
{
    switch(e->kind)
    {
        case ek_int:
            return vm_command("push " + (static_cast<int_lit*>(num))->val);
        case ek_argc:
            return vm_command("arg " + (static_cast<arg_expr*>(num))->ix);
        case ek_arith:
            return tran_arith(static_cast<arith_expr*>(num));
        case ek_if:
            return tran_if(static_cast<if_expr*>(num));
    }
}

vm_command* 
bool_command(bool_expr* e)
{
    switch(b->kind)
    {
        case ek_bool:
            return static_cast<bool_expr*>(b);
        case ek_logic:
            return tran_logic(static_cast<logic_expr*>(b));
        case ek_rel:
            return tran_rel(static_cast<rel_expr*>(b));
    }
}

vm_commmand* 
tran_arith(arith_expr* e)
{
    return vm_command(tran_op(e->op), &vm_command(num_command(e->e1), &vm_command(num_command(e->e2))))
}

vm_commmand* 
tran_if(if_expr* e)
{

}

vm_commmand* 
tran_logic(logic_expr* e)
{

}

vm_commmand* 
tran_rel(rel_expr* e)
{

}

string tran_op(arith_op op)
{
    switch (op) 
    {
        case op_add:
          return "add";
        case op_sub:
          return "sub";
        case op_mul:
          return "mul";
        case op_div:
          return "div";
        case op_rem:
          return "rem";
    }
}
