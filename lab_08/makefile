# app.exe: main.c
# 	gcc main.c -m80387 -O0 -o app.exe -lm

_MAKE_OUT_DIR_ := $(shell mkdir -p out)
_MAKE_ASM_DIR_ := $(shell mkdir -p assembly)
_MAKE_DISASM_DIR_ := $(shell mkdir -p disassembly)

fpu:
	gcc main.c -m80387 -O0 -o fpu_app.exe -lm

sse:
	gcc main.c -mno-80387 -D SSE -O0 -o sse_app.exe -lm

asm:
	gcc main.c -masm=intel -O0 -o asm_app.exe -lm

f1:
	gcc -S main.c -mno-80387 -D SSE -O0 -o sse_app.s
	gcc -S main.c -m80387 -O0 -o fpu_app.s
	gcc -S main.c -masm=intel -O0 -o asm_app.s

f2:
	gcc -c main.c -mno-80387 -D SSE -O0 -o sse_app.o
	gcc -c main.c -m80387 -O0 -o fpu_app.o
	gcc -c main.c -masm=intel -O0 -o asm_app.o
	objdump -M intel-mnemonic -d sse_app.o  > sse_app.txt
	objdump -M intel-mnemonic -d fpu_app.o  > fpu_app.txt
	objdump -M intel-mnemonic -d asm_app.o  > asm_app.txt
	rm *.o

all: fpu sse asm

clean:
	rm -rf *.txt *.s *.o *.exe