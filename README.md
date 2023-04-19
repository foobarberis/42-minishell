# 42-minishell

Bash syntax: >, <, >>, <<, |, $, "", '',

Parsing:
+ Parse and tokenize env
+ Make tokens for line
+ Expand variables

Pre-execution :
+ Check if is Builtin 
+ Get Path of cmd if needed (not a builtin)
+ Check if there is here_doc
	+ if so, fill them by creating files to stock the data with random name (use a flag to open to do so)
+ Write in the cmd struct that there is files for redirection

Execution :
+ check if there is multiple cmd
	+ if not, directly run the fonction that execute the cmd given (builtin or not)
+ set a pipe
+ check if there is redirection
	+ if so, open all of them in a different fonction
		+ then dup2 only the last redirection with STDIN and STDOUT when needed
	+ else, dup2 STDIN and STDOUT inside the pipe
+ fork and save the pid inside a variable that goes into the struc of your cmd.
+ execute the command with execve
	+ if something went wrong, exit with the pid as a status to know wich fork failed and be able to end the waitpid loop in the main.
+ Make a fonction that write the error directly in the error output.(fd 2)