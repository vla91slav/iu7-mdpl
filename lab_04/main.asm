STK SEGMENT PARA STACK 'STACK'
    db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
    newLine db 10, 13, '$'
DSEG ENDS

MATRIX SEGMENT PARA PUBLIC 'DATA'
    M dw (0)
    N dw (0)
    mtrx db 9 * 9 dup (0)
MATRIX ENDS

CSEG SEGMENT PARA PUBLIC 'DATA'
    assume CS:CSEG, DS:DSEG, ES:MATRIX, SS:STK

input:
    mov ah, 1
    int 21h
    xor ah, ah
    sub al, 30h
    mov M, ax
    cmp M, 0
    je turnOff

    mov dx, offset newLine
    mov ah, 9
    int 21h

    mov ah, 1
    int 21h
    xor ah, ah
    sub al, 30h
    mov N, ax
    cmp N, 0
    je turnOff

    mov dx, offset newLine
    mov ah, 9
    int 21h

    mov cx, M
    xor bx, bx

    inputMtx:
        call inputRow
        add bx, 9
        mov dx, offset newLine
        mov ah, 9
        int 21h
        loop inputMtx
    ret

turnOff:
    mov ax, 4c00h
    int 21h

inputRow:
    mov di, cx
    mov cx, N
    xor si, si

    mov ah, 1

    readElemLoop:
        int 21h
        mov mtrx[bx][si], al
        inc si
        loop readElemLoop

        mov cx, di
        ret

deleteXColumns:
    xor si, si ; индекс столбца

    lbl_nextColumn:
        push si
        mov cx, M
        xor bx, bx
        xor ah, ah
        lbl_checkRow:
            mov al, mtrx[bx][si]
            cmp al, 'X'
            jne lbl_notAllX
            add bx, 9
            loop lbl_checkRow

            ; если все элементы в столбце - Х
            call deleteColumn
            pop si
            jmp lbl_nextColumn ; здесь мы снова проверяем текущий столбец после удаления

        lbl_notAllX:
            pop si
            inc si
            cmp si, N
            jl lbl_nextColumn
    ret


deleteColumn:
    mov di, si ; индекс столбца для удаления
    lbl_shiftColumns:
        mov cx, M
        xor bx, bx
        lbl_shiftRows:
            mov al, mtrx[bx+1][di]
            mov mtrx[bx][di], al
            add bx, 9
            loop lbl_shiftRows
        inc di
        cmp di, N
        jl lbl_shiftColumns
        dec N
    ret

output:
    mov dx, offset newLine
    mov ah, 9
    int 21h

    mov cx, M
    xor bx, bx

outputMtx:
    ; проверка на пустой вывод
    cmp M, 0
    je skip
    cmp N, 0
    je skip

    call outputRow
    add bx, 9
    mov dx, offset newLine
    mov ah, 9
    int 21h
    loop outputMtx

    skip:
        ret

outputRow:
    xor si, si
    mov di, cx
    mov cx, N

    mov ah, 2
outputChar:
    mov dl, mtrx[bx][si]
    int 21h
    inc si
    loop outputChar

    mov cx, di
    ret

main:
    mov ax, DSEG
    mov ds, ax

    mov ax, MATRIX
    mov es, ax

    call input

    call deleteXColumns

    call output

    mov ax, 4c00h
    int 21h

CSEG ENDS
END main

