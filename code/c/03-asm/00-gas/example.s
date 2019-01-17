        .text
        .globl  example
example:
        sub     $24, %rsp
        movl    $7, 8(%rsp)
        mov     %rdi, %rax
        imul    8(%rsp), %rax
        add     %rsi, %rax
        add     $24, %rsp
        ret