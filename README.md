# 42-minishell

Bash syntax: >, <, >>, <<, |, $, "", '',

Parsing:
+ Parse and tokenize env
+ Make tokens for line
+ Expand variables

Pre-execution :
+ Mandatory : run all the here_doc in child to be able to handle the singals without exit the minishell.
+ Check if is Builtin 
+ Get Path of cmd if needed (not a builtin)
+ Check if there is here_doc
	+ if so, fill them by creating files to stock the data with random name (use a flag to open to do so)
+ Opening all of the other redirection (input or output)
	- use to struct, one for input, the other for output, with double array, save only the last index since this is the one that we will read from or write in
	- If one file has a per;ission denied, stop immediatly the openin or execution of everything and jumps to the next cmd!
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