CC=emcc
SHELL_HTML=index.html


INC= vendor/raylib_wasm/include
LIB= vendor/raylib_wasm/libraylib.a

EXPORTED_FUNC = test

all: docs docs/script.js
	$(info Building wasm..)
	@$(CC) main.c -o docs/index.html -I$(INC) -sUSE_GLFW=3 -sASYNCIFY\
	  --shell-file $(SHELL_HTML) $(LIB_PARAMS) $(LIB) -L$(LIB)\
	   -s EXPORTED_FUNCTIONS=_makeScreenshot,_setColor,_main,_toggleEraser -s 'EXPORTED_RUNTIME_METHODS=ccall,cwrap'

docs:
	$(info mkdir docs..)
	@mkdir docs

docs/script.js: ./script.js
	$(info Copying script.js..)
	@cp script.js docs/script.js


.PHONY: clean

clean:
	@rm -rfv docs

