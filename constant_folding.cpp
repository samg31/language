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


    }
}