add_library(postfix-core
  postfix-syntax.cpp
  # postfix-dumper.cpp
  # postfix-printer.cpp
  # postfix-translator.cpp
  # postfix-evaluator.cpp
)
target_link_libraries(postfix-core PUBLIC pl-util pl-sexpr)

# add_executable(postfix postfix.cpp)
# target_link_libraries(postfix postfix-core)

