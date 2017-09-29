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
                case ek_argc:
                    return static_cast<arg_expr*>(num);
                case ek_arith:
                    return eval_arith(static_cast<arith_expr*>(num));
                case ek_if:
                    return eval_if(static_cast<if_expr*>(num));
            }
        }


			bool_expr*
			bfold(bool_expr* b)
			{
				switch(b->kind)
				{
				case ek_bool:
					return static_cast<bool_expr*>(b);
				case ek_logic:
					return eval_logic(static_cast<logic_expr*>(b));
				case ek_rel:
					return eval_rel(static_cast<rel_expr*>(b));
				}
			}

    }

namespace {	
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
            cond->test = bfold(cond->test);
            cond->e1 = nfold(cond->e1);
            cond->e2 = nfold(cond->e2);

            if(cond->e1->kind == k_argc || cond->e2->kind == k_argc || cond->test->e1->kind == k_argc || cond->test->e2->kind == k_argc)
                return cond;
            return int_lit(cond->locs, eval_if_expr(cond));
        }

	bool_expr*
	eval_logic(logic_expr* l)
	{
		l->e1 = bfold(l->e1);
		l->e2 = bfold(l->e2);

		if(l->e1->kind == ek_argc || l->e2->kind == ek_argc )
			return l;

		return new bool_lit(l->locs, eval_logic_expr(l));
	}

	bool_expr*
	eval_rel(rel_expr* r)
	{
		r->e1 = bfold(r->e1);
		r->e2 = bfold(r->e2);

		if(r->e1->kind == ek_argc || r->e2->kind == ek_argc )
			return r;

		return new bool_lit(r->locs, eval_logic_expr(r));		
	}
}	
}

