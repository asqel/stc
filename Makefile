
MAKEFLAGS += --no-print-directory

all:
	make -C src/server/
	make -C src/client/


fclean:
	make -C src/server/ fclean
	make -C src/client/ fclean

clean:
	make -C src/server/ clean
	make -C src/client/ clean
	
server:
	make -C src/server/ run

client:
	make -C src/client/ run

.PHONY: all fclean clean server client
