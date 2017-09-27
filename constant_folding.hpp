#pragma once

#include <el/el-syntax.hpp>

#include <sexpr/translation.hpp>

namespace dcipl
{
    namespace el
    {
        prog* pfold(prog* program);
        num_expr* nfold(num_expr* num);
        bool_expr* bfold(bool_expr* b);

        num_expr* eval_arith(arith_expr* arith);
        num_expr* eval_if(if_expr* cond);

        bool_expr* eval_logic(bool_expr* expr)
    }
}