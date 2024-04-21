all:
	make -C ./test/minishell
	cc ./tmp/prod/dbllst/*.o ./tmp/prod/exec/*.o ./tmp/prod/libft/*.o ./tmp/prod/minishell/*.o ./test/minishell/main.c ./include/*.h -I./include -I./tmp/prod/dbllst -I./tmp/prod/exec -I./tmp/prod/libft -I./tmp/prod/minishell -I./test/minishell -lreadline -Wall -Werror -Wextra
	rm ./include/*.gch

clean:
	rm -rf ./tmp

fclean: clean
	rm -f a.out