simple_off: pre_build_simple builder

simple_on: pre_build_simple_sanitizer builder

simple_time: pre_build_simple_time builder


complicated_off: pre_build_complicated builder

complicated_on: pre_build_complicated_sanitizer builder

complicated_time: pre_build_complicated_time builder



pre_build_simple_sanitizer:
	cmake -DV_HOW="Simple_on" -S . -B build

pre_build_simple:
	cmake -DV_HOW="Simple_off" -S . -B build

pre_build_simple_time:
	cmake -DV_HOW="Simple_time" -S . -B build

pre_build_complicated_sanitizer:
	cmake -DV_HOW="Complicated_on" -S . -B build

pre_build_complicated:
	cmake -DV_HOW="Complicated_off" -S . -B build

pre_build_complicated_time:
	cmake -DV_HOW="Complicated_time" -S . -B build

builder:
	cmake --build build

run:
	./build/a.out < in.txt

check:
	bash linters/run.sh

format:
	clang-format -i lib1/*.c lib2/*.c mains/*.c tests/*.cpp

test_time:
	multitime -q -n 10 ./build/a.out < in.txt 2>> build/report/log.txt

test:
	./build/tests/test

test_valgrind:
	sudo valgrind --tool=memcheck --leak-check=yes ./build/a.out < in.txt

test_coverage: test
	cd build && lcov -t "tests/test" -o coverage.info -c -d lib2/ -d lib1/ && genhtml -o report coverage.info

clean:
	rm -r build