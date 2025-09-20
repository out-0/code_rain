all:
	@cc code.c -lncurses -o code	
	@./code
fclean:
	@rm -f code
