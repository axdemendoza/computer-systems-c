.globl find_range
find_range:
    xorps   %xmm1, %xmm1      # set xmm1 register equal to 0
    ucomiss %xmm1, %xmm0      # compare to 0 and set flags (ZF, CF, PF)
    mov     $0, %rbx          
    mov     $1, %rcx
    mov     $2, %rdx
    mov     $3, %rsi
    cmove   %rcx, %rax        # move 1 (ZERO) into return register if zero flag = 1
    cmova   %rdx, %rax        # move 2 (POS) into return register if xmm1 > 0 (CF=0)
    cmovb   %rbx, %rax        # move 0 (NEG) into return register if xmm1 < 0 (CF=1)
    cmovp   %rsi, %rax        # move 3 (OTHER) into return register if parity flag = 1
    ret

    


