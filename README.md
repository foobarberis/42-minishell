# 42-minishell

- TODO: Write error messages on STDERR
- TODO: Run parsing related tests from minishell-test-cases.pdf
- TODO: Add "real" error messages for parsing errors.
- TODO: Implement proper signal handling.

Unlike Bash, `echo [$HOME]` should not expand since `[` is actually a
built-in that we don't have to handle. Therefore `[` and `[[` are
treated as litteral characters. This goes for `echo \$HOME` which
produces `$HOME` in Bash but produces `\$HOME` here since `\` is not a
metacharacter in MSH.
https://unix.stackexchange.com/questions/99185/what-do-square-brackets-mean-without-the-if-on-the-left
Also, variable names must be of the form [a-zA-Z_]+[a-zA-Z0-9_]*, so
`echo $USER- -> matthieu-`. Since we don't treat \ as a metacharacter
`echo $USER\ -> matthieu\`.
https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names

