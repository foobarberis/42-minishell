# 42-minishell

+ [X] Ctrl-C in here-doc should exit here-doc and discard the buffer (WARNING: LEAKS)
+ [X] echo ""'test'""
+ [X] echo """"'test'""""
+ [X] export A && export A=test && export A -> A=test
+ [X] echo ""'$PATH'
+ [X] "e"cho "hello		world"
+ [X] `<<EOF cat > $USER > '$USER' > "$USER"`
+ `minishell` should not work, only `./minishell` should work
+ exit | exit -> should not write exit
+ exit "  3  " -> should exit with code 3
+ <<EOF in cat > out  + Ctrl-C -> should not create out
+ Return exit code of the last command when exiting (if exit has no arg return g_rval else r)
+ exit test 52 -> should return 2 check for numeric arg first then num
+ < Makefile cd src > oufile -> should go to src
+ <<EOF cd src
  > cat main.c
  -> cat main.c should not be executed, just cd src/
+ Return code of <<EOF should be 0 but we get 2.
