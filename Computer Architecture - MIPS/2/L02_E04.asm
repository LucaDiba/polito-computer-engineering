# Prints number of bits == 1 in val

.data
    val: .half 1979

.text
.globl  main
.ent    main
main:
    and $t0, $0, $0 # $t0 = counter
    and $t1, $0, $0 # $t1 = number of bit I'm analysing
    lh $t2, val

    # $t3 = (val AND 0001)
    # if 0 ==> the last bit is 0
    # else ==> the last bit is 1
    and $t3, $t2, 1 # 0001bin = 1dec
    beq $t3, 0, bit_4_0 # last bit == 0
    j bit_4_1           # last bit == 1

bit_4_1:
    add $t0, $t0, 1
    j bit_4_end
bit_4_0:
    j bit_4_end
bit_4_end:

    # $t3 = (val AND 0010)
    # if 0 ==> the third bit is 0
    # else ==> the third bit is 1
    and $t3, $t2, 2 # 0010bin = 2dec
    beq $t3, 0, bit_3_0 # third bit == 0

bit_3_1:
    add $t0, $t0, 1
    j bit_3_end
bit_3_0:
    j bit_3_end
bit_3_end:

    # $t3 = (val AND 0100)
    and $t3, $t2, 4 # 0100bin = 4dec
    beq $t3, 0 bit_2_end
    add $t0, $t0, 1

bit_2_end:

    # $t3 = (val AND 1000)
    and $t3, $t2, 8 # 1000bin = 8dec
    beq $t3, 0, bit_1_end
    add $t0, $t0, 1

bit_1_end:

    # print number of bit == 1
    li $v0, 1
    move $a0, $t0
    syscall

li $v0, 10
syscall
.ent main