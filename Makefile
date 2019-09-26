all: prompt.c tokenize.c cd.c echo.c pwd.c pinfo.c ls.c exec.c main.c
	gcc -g -o shell prompt.c tokenize.c get_arrows.c set_streams.c cd.c echo.c pwd.c pinfo.c ls.c exec.c setenv.c main.c -lreadline