build:
	cmake -S . -B build && cmake --build build

test2:
	./build/a.out > a.log

test:
	./build/a.out

rm:
	rm -r build