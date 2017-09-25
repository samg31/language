add_library(dcipl-el
  el-syntax.cpp
  el-context.cpp
  el-printer.cpp
  el-dumper.cpp
  el-translator.cpp
  el-evaluator.cpp
)
target_link_libraries(dcipl-el PUBLIC sexpr cc)

# Build the evaluator.
add_executable(el el.cpp)
target_link_libraries(el dcipl-el)
