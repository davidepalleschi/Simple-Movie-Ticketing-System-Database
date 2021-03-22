all:
	gcc -g *.c -o client `mysql_config --cflags --include --libs`
clean:
	-rm client
