; receiving the string in 'bx'
print:
    pusha

print_loop:
    mov al, [bx]
    cmp al, 0
    je print_end
    mov ah, 0x0e
    int 0x10
    add bx, 1
    jmp print_loop

print_end:
    popa
    ret

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; New line
    int 0x10
    mov al, 0x0d ; Carriage return
    int 0x10

    popa
    ret

clear_screen:
    pusha
    
    mov ah, 0x0
    mov al, 0x3
    int 0x10

    popa
    ret