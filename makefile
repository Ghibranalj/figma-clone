CC=emcc
SHELL_HTML=index.html


INC= vendor/raylib_wasm/include
LIB= vendor/raylib_wasm/libraylib.a

EXPORTED_FUNC = test

all: docs
	$(CC) main.c -o docs/index.html -I$(INC) -sUSE_GLFW=3 -sASYNCIFY\
	  --shell-file $(SHELL_HTML) $(LIB_PARAMS) $(LIB) -L$(LIB)\
	   -s EXPORTED_FUNCTIONS=_makeScreenshot,_setColor,_main -s 'EXPORTED_RUNTIME_METHODS=ccall,cwrap'
docs:
	mkdir docs
	cp script.js docs

.PHONY: clean

clean:
	rm -rf docs

