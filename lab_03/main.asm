STACK SEGMENT PARA STACK 'STACK'
    db 100h dup (?)
STACK ENDS

OUTPUT SEGMENT PARA 'CODE'
    ASSUME CS:OUTPUT
output_char:
    mov dx, 10
    mov ah, 02h
    int 21h

    mov dx, bx
    add dx, 33
    int 21h

    mov ah, 4ch
    int 21h
OUTPUT ENDS

INPUT SEGMENT PARA 'CODE'
    ASSUME CS:INPUT, SS:STACK
input_char:
    mov ah, 01h
    int 21h
    mov bx, ax

    call OUTPUT:output_char
INPUT ENDS
END input_char
