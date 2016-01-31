all:
	$(CC) -O2 prime.c primegen.c -o primegen

clean:
	$(RM) -rf primegen
