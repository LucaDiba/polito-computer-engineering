# Given x = (x1, x2, x3, x4)
# and   y = (y1, y2, y3, y4)
#            ( x1*y1, x1*y2, x1*y3, x1*y4 )
# Find res = ( x2*y1, x2*y2, x2*y3, x2*y4 )
#            ( x3*y1, x3*y2, x3*y3, x3*y4 )
#            ( x4*y1, x4*y2, x4*y3, x4*y4 )

.data
    #DIM = 4
    .eqv DIM 4
    .eqv DIM_VECTOR 16 # 4 * 4byte
    .eqv DIM_MATRIX 256 # 16 * 16

    x: .word 10 -20 30 40
    y: .word 1 2 3 4
    res: .space DIM_MATRIX

    overflow_msg: .asciiz "\nOverflow error\n"
    tab_msg: .asciiz "\t"
    newline_msg: .asciiz "\n"

.text
    # $t5 = tmp_x
    # $t6 = tmp_y

    # $t1 = i * 4
    and $t1, $0, $0

    # $t3 = n * 4
    li $t3, DIM
    mul $t3, $t3, 4

    # $t4 = k (for storing elements in matrix)
    and $t4, $0, $0

    for_i:
        beq $t1, $t3, end_i

        # $t2 = j * 4
        and $t2, $0, $0
        for_j:
            beq $t2, $t3, end_j

            lw $t5, x($t1)
            lw $t6, y($t2)
            mult $t5, $t6

            # check overflow
            #   if HI == 0x00000000 ==> no overflow
            # elif HI == 0xFFFFFFFF ==> no overflow (negative number)
            # else ==> overflow
            mfhi $t0
            beq $t0, $0, no_overflow
            beq $t0, 0xFFFFFFFF, no_overflow
            j overflow

        no_overflow:
            mflo $t0

            # store value
            sw $t0, res($t4)
            addi $t4, $t4, 4

            # print value
            move $a0, $t0
            li $v0, 1
            syscall

            # print space
            la $a0, tab_msg
            li $v0, 4
            syscall

            addi $t2, $t2, 4
            j for_j
        end_j:

        # print new line
        la $a0, newline_msg
        li $v0, 4
        syscall

        addi $t1, $t1, 4
        j for_i
    end_i:
        j end
    
    overflow:
        la $a0, overflow_msg
        li $v0, 4
        syscall

end:
    li $v0, 10
    syscall
.end main