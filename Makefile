all:
	make -C ./test/minishell
	gcc -o minishell.out ./tmp/prod/dbllst/*.o ./tmp/prod/exec/*.o ./tmp/prod/libft/*.o ./tmp/prod/minishell/*.o ./test/minishell/main.c ./include/*.h -I./include -I./tmp/prod/dbllst -I./tmp/prod/exec -I./tmp/prod/libft -I./tmp/prod/minishell -I./test/minishell -lreadline 

clean:
	rm -rf ./tmp/prod

fclean: clean
	rm -f minishell.out