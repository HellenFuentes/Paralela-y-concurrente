compile: goldbach_serial.c main.c goldbach_serial.h
	cc -g -Wall -Wextra main.c goldbach_serial.c -o exe

tsan: goldbach_serial.h main.c goldbach_serial.c
	clang -g -Wall -Wextra -fsanitize=thread main.c goldbach_serial.c -o exe_tsan -std=gnu99

asan: goldbach_serial.h main.c goldbach_serial.c
	clang -g -Wall -Wextra -fsanitize=address main.c goldbach_serial.c -o exe_asan -std=gnu99

msan: goldbach_serial.h main.c goldbach_serial.c
	clang -g -Wall -Wextra -fsanitize=memory main.c goldbach_serial.c -o exe_msan -std=gnu99

.PHONY: lint
lint:
	cpplint --filter=-readability/casting goldbach_serial.c main.c goldbach_serial.h

.PHONY: clean
clean:
	rm -rf exe exe_tsan exe_asan exe_msan
