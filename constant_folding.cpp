#include "constant_folding.hpp"

namespace dcipl
{
    namespace el
    {
        prog* 
        pfold(prog* program)
        {
            return prog(program->locs, program->nargs, nfold(program -> body));
        }

        num_expr* 
        nfold(num_expr* num)
        {
            switch(num->kind)
            {
                case ek_int:
                    return static_cast<int_lit*>(num);
                case k_argc:
                    return static_cast<arg_expr*>(num);
                case k_arith:
                    return eval_arith(static_cast<arith_expr*>(num));
                case k_if:
                    return eval_if(static_cast<if_expr*>(num));
            }
        }

    }

    num_expr* 
    eval_arith(arith_expr* arith)
    {
        arith->e1 = nfold(arith->e1);
        arith->e2 = nfold(arith->e2);
        if(arith->e1->kind == k_argc || arith->e2->kind == k_argc )
            return arith;
        return int_lit(arith->locs, eval_arith_expr(arith));
    }

    num_expr* 
    eval_if(if_expr* cond)
    {
        if(cond->e1->kind == k_argc || cond->e2->kind == k_argc )
            return cond;
        return int_lit(cond->locs, eval_if_expr(cond));
    }
}