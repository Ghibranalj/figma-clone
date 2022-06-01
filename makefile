CC=emcc
SHELL_HTML=index.html


INC= vendor/raylib_wasm/include
LIB= vendor/raylib_wasm/libraylib.a

all: docs
	$(CC) main.c -o docs/index.html -I$(INC) -s USE_GLFW=3\
	  --shell-file $(SHELL_HTML) $(LIB_PARAMS) $(LIB) -L$(LIB)
docs:
	mkdir docs

.PHONY: clean

clean:
	rm -rf docs

