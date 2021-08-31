APPNAME=goldbach_optimization
EXECUTABLES=$(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan $(APPNAME)_ubsan

CC=cc
CC2=clang
CFLAGS=-g -Wall -Wextra
LIBS=-pthread

all: $(EXECUTABLES)

$(APPNAME): $(APPNAME).c
	$(CC) $(CFLAGS) $(APPNAME).c main.c queue.c prodcons.c -o $(APPNAME) $(LIBS) -std=gnu99

$(APPNAME)_asan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=address $(APPNAME).c main.c queue.c prodcons.c -o $(APPNAME)_asan $(LIBS) -std=gnu99

$(APPNAME)_msan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=memory $(APPNAME).c main.c queue.c prodcons.c -o $(APPNAME)_msan $(LIBS) -std=gnu99

$(APPNAME)_tsan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=thread $(APPNAME).c main.c queue.c prodcons.c -o $(APPNAME)_tsan $(LIBS) -std=gnu99

$(APPNAME)_ubsan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=undefined $(APPNAME).c main.c queue.c prodcons.c -o $(APPNAME)_ubsan $(LIBS) -std=gnu99

.PHONY: memcheck
memcheck:
	valgrind ./$(APPNAME)

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind --quiet ./$(APPNAME)

.PHONY: rebuild
rebuild: clean $(APPNAME)

.PHONY: lint
lint:
	cpplint --filter=-readability/casting $(APPNAME).c

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES)
