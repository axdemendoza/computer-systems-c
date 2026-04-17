.globl find_range
find_range:
    xorps   %xmm1, %xmm1    #set xmm1 register equal to 0
    ucomiss %xmm1, %xmm0    # compare to 0 and set flags (ZF, CF, SF)
    jp      .L4             # if NaN
    jb      .L1             # if signed (input < 0 : SF = 1)
    jz      .L2             # if zero (input = 0 : ZF = 1)
    ja      .L3             # if not signed (input > 0 : SF = 0)
    jmp     .L4
.L1:
    mov     $0, %rax        # ret register set to 0 (NEG)
    ret
.L2:
    mov     $1, %rax        # ret register set to 1 (ZERO)
    ret
.L3:
    mov     $2, %rax        # ret register set to 2 (POS)
    ret
.L4:
    mov     $3, %rax        # else set ret register to 3 (OTHER)
    ret

    


