#MIT License...

.PHONY: all cuda-gdb libtirpc gpu cpu tests clean install install-cpu bin/tests

all: gpu cpu install

clean:
	@echo -e "\033[31m----> Cleaning up gpu\033[0m"
	$(MAKE) -C gpu clean
	@echo -e "\033[31m----> Cleaning up cpu\033[0m"
	$(MAKE) -C cpu clean
	@echo -e "\033[31m----> Cleaning up test kernels\033[0m"
	$(MAKE) -C tests clean
	rm -rf bin/

cuda-gdb:
	@echo -e "\033[36m----> Building submodules\033[0m"
	$(MAKE) -C submodules cuda-gdb
	$(MAKE) -C submodules cuda-gdb-libs

libtirpc:
	@echo -e "\033[36m----> Building libtirpc\033[0m"
	$(MAKE) -C submodules libtirpc/install

gpu: cuda-gdb
	@echo -e "\033[36m----> Building gpu\033[0m"
	$(MAKE) -C gpu

cpu: libtirpc
	@echo -e "\033[36m----> Building cpu\033[0m"
	$(MAKE) -C cpu

tests:
	@echo -e "\033[36m----> Building test kernels\033[0m"
	$(MAKE) -C tests

install-cpu: bin/RRTO-client.so bin/RRTO-rpc-server bin/libtirpc.so bin/libtirpc.so.3 bin/tests
	@echo -e "\033[36m----> Copying cpu binaries to build/bin\033[0m"

install: install-cpu bin/RRTO
	@echo -e "\033[36m----> Copying to build/bin\033[0m"

bin:
	mkdir bin

bin/tests: bin tests
	ln -s ../tests/bin bin/tests

bin/RRTO-client.so: bin
	$(MAKE) -C cpu RRTO-client.so
	cp cpu/RRTO-client.so bin

bin/RRTO-server.so: bin
	$(MAKE) -C cpu RRTO-server.so
	mv cpu/RRTO-server.so bin/RRTO-server.so


bin/RRTO-rpc-server: bin
	$(MAKE) -C cpu RRTO-rpc-server
	mv cpu/RRTO-rpc-server bin/RRTO-rpc-server

bin/RRTO: bin gpu
	cp gpu/RRTO bin

bin/libtirpc.so: bin submodules/libtirpc/install/lib/libtirpc.so
	cp submodules/libtirpc/install/lib/libtirpc.so bin

bin/libtirpc.so.3: bin submodules/libtirpc/install/lib/libtirpc.so.3 libtirpc
	cp submodules/libtirpc/install/lib/libtirpc.so.3 bin
