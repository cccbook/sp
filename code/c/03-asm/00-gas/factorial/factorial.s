# ----------------------------------------------------------------------------
# A 64-bit recursive implementation of the function
#
#     uint64_t factorial(unsigned n)
#
# implemented recursively
# ----------------------------------------------------------------------------

        .globl  factorial

        .text
factorial:
        cmp     $1, %rdi                # n <= 1?
        jnbe    L1                      # if not, go do a recursive call
        mov     $1, %rax                # otherwise return 1
        ret
L1:
        push    %rdi                    # save n on stack (also aligns %rsp!)
        dec     %rdi                    # n-1
        call    factorial               # factorial(n-1), result goes in %rax
        pop     %rdi                    # restore n
        imul    %rdi, %rax              # n * factorial(n-1), stored in %rax
        ret