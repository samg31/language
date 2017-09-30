#include "dcipl/el/el-syntax.cpp"


using namespace dcipl::el;

/*
  This function takes two numeric expressions and determines if they are syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool neq(num_expr* e1, num_expr* e2) 
{
  return (get_node_name(e1) == get_node_name(e2) ? true : false);
}

/*
  This function takes two boolean expressions and determines if they are syntactically the same.
  Returns true if they are, and false otherwise.
*/
bool beq(bool_expr* e1, bool_expr* e2) 
{
  return (get_node_name(e1) == get_node_name(e2) ? true : false);  
}