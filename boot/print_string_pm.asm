[bits 32] ; Using 32-bit protected mode

; This is how constants are defined
VIDEO_MEMORY equ 0xb8000
WHITE_ON_GREEN equ 0x2f ; The color byte for each character
; Prints a null - terminated string pointed to by EDX
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; Set edx to the start of the video memory

print_string_pm_loop:
    mov al, [ebx] ; Store the char at ebx in al
    mov ah, WHITE_ON_GREEN ; Store the attributes in ah

    cmp al, 0
    je print_pm_end

    mov [edx], ax ; Store char and attributes at current character cell
    add ebx, 1 ; Increment ebx to the next char in the string
    add edx, 2 ; Increment edx to the next cell in the video memory
    jmp print_string_pm_loop

print_pm_end:
    popa
    ret