# app.exe: main.c
# 	gcc main.c -m80387 -O0 -o app.exe -lm

_MAKE_OUT_DIR_ := $(shell mkdir -p out)
_MAKE_ASM_DIR_ := $(shell mkdir -p assembly)
_MAKE_DISASM_DIR_ := $(shell mkdir -p disassembly)

fpu:
	gcc main.c -m80387 -mno-sse -D FPU -O0 -o fpu_app.exe -lm

sse:
	gcc main.c -mno-80387 -D SSE -O0 -o sse_app.exe -lm

asm:
	gcc main.c -masm=intel -DASM -O0 -o asm_app.exe -lm

assembly:
	gcc -S main.c -mno-80387 -D SSE -O0 -o assembly/sse_app.s
	gcc -S main.c -m80387 -mno-sse -D FPU -O0 -o assembly/fpu_app.s
	gcc -S main.c -masm=intel -DASM -O0 -o assembly/asm_app.s

disassembly:
	gcc -c main.c -mno-80387 -D SSE -O0 -o out/sse_app.o
	gcc -c main.c -m80387 -mno-sse -D FPU -O0 -o out/fpu_app.o
	gcc -c main.c -masm=intel -DASM -O0 -o out/asm_app.o
	objdump -M intel-mnemonic -d out/sse_app.o  > disassembly/sse_app.txt
	objdump -M intel-mnemonic -d out/fpu_app.o  > disassembly/fpu_app.txt
	objdump -M intel-mnemonic -d out/asm_app.o  > disassembly/asm_app.txt

clean:
	rm -rf assembly/* disassembly/* out/* *.exe