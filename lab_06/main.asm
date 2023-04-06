.MODEL TINY

CodeSeg SEGMENT
    ASSUME CS:CodeSeg, DS:CodeSeg
    ORG 100h ; размер PSP - 256 байт

main:
    jmp init ; сначала данные и подпрограммы обработчиков прерываний, затем секция инициализации
             ; устанавливаем резидент в памяти, потом удалим

    old_interrupt dd 0 ; адрес старого прерывания
    time_check db 0
    speed db 1Fh
    is_init db 1 ; проверка, запущена ли программа
    start_message db '[PROGRAM STARTED]', '$'
    end_message db '[PROGRAM ENDED]', '$'

init:
    mov ax, 3508h ; прерывание на ввод символа
    int 21h ; адрес обработчика прерывания таймера теперь в es:bx

    cmp es:is_init, 1 ; проверяем, запущена ли программа
    je uninstall ; если да - выходим

    jmp install ; если нет - устанавливаем

my_interupt:
    pushf ; сохряняем флаги в стеке
    call cs:old_interrupt ; косвенный дальний переход
    ; call dword ptr old_interrupt

    mov ah, 02h ; функция чтения системного времени
    int 1Ah ; текущее время, секунды в dh

    cmp dh, time_check ; время изменилось?
    je end_interrupt ; время не изменилось -> скорость не изменилась
    mov time_check, dh ; иначе запись в time_check

    ; out - отправка данные из регистра на порт ввода/вывода
    mov al, 0F3h ; команда установки скорости и задержки для клавиатуры
    out 60h, al ; первый байт - команда
    mov al, speed
    out 60h, al ; второй байт - данные, установка новой скорости автоповтора ввода

    dec speed
    test speed, 01Fh
    jz skip
    jmp end_interrupt

    skip:
        mov speed, 01Fh
    end_interrupt:
        IRET ; завершение работы, восстановление из стека IP, CS, FLAGS
        ; аналогично RETF + POPF

install:
    ; запись  изначального вектора прерывания
    mov word ptr old_interrupt, bx ; смещение
    mov word ptr old_interrupt + 2, es ; сегмент, делаем +2 байта, тк каждый сегмент и смещение занимают 2 байта

    ; замена вектора прерываний в таблице на свой
    mov ax, 2508h ; команда установки адреса обработчика прерывания
    mov dx, offset my_interupt
    int 21h ; ds – сегмент обработчика прерывания dx – смещение обработчика прерывания  

    ; вывод сообщения о запуске
    mov dx, offset start_message
    mov ah, 9h
    int 21h

    mov dx, offset init
    int 27h ; освобождение памяти из-под всего после init

uninstall:
    pushf

    ; вывод сообщение о завершении
    mov dx, offset end_message
    mov ah, 9h
    int 21h

    ; восстановление скорости по умолчанию
    mov al, 0F3h ; команда установки скорости и задержки для клавиатуры
    out 60h, al
    mov al, 0 ; т. е. в 0000
    out 60h, al

    ; установка изначального вектора прерывания
    mov dx, word ptr es:old_interrupt
    mov ds, word ptr es:old_interrupt + 2

    mov ax, 2508h ; команда установки адреса обработчика прерывания
    int 21h

    popf

    mov ah, 49h ; освобождение памяти
    int 21h

    mov ax, 4c00h
    int 21h
CodeSeg ENDS
END main