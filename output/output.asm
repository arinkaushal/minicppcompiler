section .text
global _start
_start:
    push rbp
    mov rbp, rsp
    mov rax, 5
    mov [rbp-8], rax
    mov rax, 10
    mov [rbp-16], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    pop rbx
    add rax, rbx
    mov [rbp-24], rax
    mov rax, [rbp-24]
    mov rdi, rax
    call print_int
    mov rax, 60
    xor rdi, rdi
    syscall
