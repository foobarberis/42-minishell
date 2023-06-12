# 42-minishell

+ [X] Ctrl-C in here-doc should exit here-doc and discard the buffer (WARNING: LEAKS)
+ [X] echo ""'test'""
+ [X] echo """"'test'""""
+ [X] export A && export A=test && export A -> A=test
+ [X] echo ""'$PATH'
+ [X] `<<EOF cat > $USER > '$USER' > "$USER"`
+ [X] < Makefile cd src > oufile -> should go to src
+ [X] `minishell` should not work, only `./minishell` should work
+ [X] exit | exit -> should not write exit
+ [X] "e"cho "hello		world"
+ [X] exit "  3  " -> should exit with code 3
+ [X] Return exit code of the last command when exiting (if exit has no arg return g_rval else r)
+ [X] Return code of <<EOF should be 0 but we get 2.
+ [X] <<EOF in cat > out  + Ctrl-C -> should not create out
+ [X] exit test 52 -> should return 2 check for numeric arg first then num
+ [X]
```sh
<<EOF cd src
  > cat main.c
  -> cat main.c should not be executed, just cd src/
```
```sh
echo "hi" | cat | cat | cat | cat | cat | cat | cat
ps -a
```

export HOLA='"'
echo " $HOLA " | cat -e
