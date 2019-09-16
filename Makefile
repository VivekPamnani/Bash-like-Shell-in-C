all: prompt.c tokenize.c cd.c echo.c pwd.c pinfo.c ls.c exec.c main.c
	gcc -o shell prompt.c tokenize.c cd.c echo.c pwd.c pinfo.c ls.c exec.c main.c