CORES := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

all: install test gcov_report

install:
	@mkdir -p "build"
	@cd build && cmake .. && cmake --build . --target 3DViewer -- -j$(CORES)

uninstall:
	@rm -rf build

dist: install
	@cd build && tar -cf 3DViewer_v2.0.tar 3DViewer.app && cp 3DViewer_v2.0.tar ../
	@rm -rf build

dvi:
	@cd Doc && doxygen doxygen.conf
	@open Doc/html/index.html

build_test:
	@mkdir -p "tests_build"
	@cd tests_build && cmake .. && cmake --build . --target tests_run -- -j$(CORES)

test: build_test
	@cd tests_build && ./tests_run

gcov_report: build_test
	@cd tests_build && make coverage_report

open_report:
	@open tests_build/coverage.html

style_test:
	@clang-format -n --style=Google *.cpp *.h

style_format:
	@clang-format -i --style=Google *.cpp *.h

clean:
	@rm -rf tests_build *.tar Doc/html Doc/latex
