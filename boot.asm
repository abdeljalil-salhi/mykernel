global _start

section .text
    _start:
        ; Set up stack
        mov esp, stack
        mov ebp, esp

        ; Call kernel_main
        call kernel_main

        ; Hang the system
    hang:
        jmp hang

section .bss
    stack:
        resb 8192   ; 8KB stack space

section .data
    ; Define any data here

extern kernel_main

