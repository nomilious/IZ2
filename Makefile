simple: pre_build builder

complicated: pre_build2 builder

pre_build:
	cmake -Dsimple=ON -S . -B build

pre_build2:
	cmake -Dsimple=OFF -S . -B build

builder:
	cmake --build build

run:
	./build/a.out

test_time:
	multitime -q -n 10 ./build/a.out

check:
	bash linters/run.sh

format:
	clang-format -i lib/*.c main.c

clean:
	rm -r build