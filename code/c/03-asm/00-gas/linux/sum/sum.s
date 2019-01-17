# -----------------------------------------------------------------------------
# A 64-bit function that returns the sum of the elements in a floating-point
# array. The function has prototype:
#
#   double sum(double[] array, unsigned length)
# -----------------------------------------------------------------------------

        .global sum
        .text
sum:
        xorpd   %xmm0, %xmm0            # initialize the sum to 0
        cmp     $0, %rsi                # special case for length = 0
        je      done
next:
        addsd   (%rdi), %xmm0           # add in the current array element
        add     $8, %rdi                # move to next array element
        dec     %rsi                    # count down
        jnz     next                    # if not done counting, continue
done:
        ret               