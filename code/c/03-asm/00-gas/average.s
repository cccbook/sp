# -----------------------------------------------------------------------------
# 64-bit program that treats all its command line arguments as integers and
# displays their average as a floating point number.  This program uses a data
# section to store intermediate results, not that it has to, but only to
# illustrate how data sections are used.
# -----------------------------------------------------------------------------

        .globl  main

        .text
main:
        dec     %rdi                    # argc-1, since we don't count program name
        jz      nothingToAverage
        mov     %rdi, count             # save number of real arguments
accumulate:
        push    %rdi                    # save register across call to atoi
        push    %rsi
        mov     (%rsi,%rdi,8), %rdi     # argv[rdi]
        call    atoi                    # now rax has the int value of arg
        pop     %rsi                    # restore registers after atoi call
        pop     %rdi
        add     %rax, sum               # accumulate sum as we go
        dec     %rdi                    # count down
        jnz     accumulate              # more arguments?
average:
        cvtsi2sd sum, %xmm0
        cvtsi2sd count, %xmm1
        divsd   %xmm1, %xmm0            # xmm0 is sum/count
        mov     $format, %rdi           # 1st arg to printf
        mov     $1, %rax                # printf is varargs, there is 1 non-int argument

        sub     $8, %rsp                # align stack pointer
        call    printf                  # printf(format, sum/count)
        add     $8, %rsp                # restore stack pointer

        ret

nothingToAverage:
        mov     $error, %rdi
        xor     %rax, %rax
        call    printf
        ret

        .data
count:  .quad   0
sum:    .quad   0
format: .asciz  "%g\n"
error:  .asciz  "There are no command line arguments to average\n"