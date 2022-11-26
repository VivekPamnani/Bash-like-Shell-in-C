Linux Shell in C

1.  Introduction:
        The is a simple Linux shell implemented using C language.
2.  Run instructions: type the following in the terminal,
    1.   make
    2.   ./shell
3.  Features:
    1.  Built-ins:
        1. cd: change directory
        1. pinfo: print process info for a given pid
        1. exit: exits the shell
        1. pwd: prints the present working directory
        1. ls: lists all files and folders under a given directory; -a for hidden and -l for long listing format
        1. jobs: list all pending / running jobs
        1. kjobs: sends a signal to a process for a given pid
        1. overkill: kill all background processes
        1. setenv: create/edit an environment variable
    2.  Support for '~' (HOME directory)
    3.  Input multiple commands using ';' separator.
    4.  I/O redirections
    5.  Piping
4.  Files:
    1.  main.c:
        The driver file, this is used to execute any built-in / installed commands.
    2.  prompt.c:
        Displays the prompt and takes input.
    3.  set_streams.c:
        Configures stdin and stdout for I/O redirections.
    4.  tokenize.c:
        Converts ';' separated commands in input into individual 'tokens'.
        Also, tokenizes each command by ' ' separated words.
    5.  echo.c:
        Implements the 'echo' command.
    6.  cd.c:
        Implements the 'cd' command. Supports '~' (HOME directory).
    7.  exec.c:
        Handles foreground / background processes.
    8.  pinfo.c:
        Implements 'pinfo' command.
    9.  setenv.c:
            Implements 'setenv' and 'unsetenv' commands.