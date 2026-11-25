format elf64
section '.text'
public systemV_convert
extrn systemV_call
systemV_convert:
    mov rdi , rax
    mov rsi , rbx
    call systemV_call
    ret