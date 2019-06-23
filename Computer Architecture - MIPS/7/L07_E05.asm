# Get 3x3 matrix determinant
# [ 2   3   12 ]
# [ 5   6   8  ]
# [ 14  23  1  ]

.data
    msg_res: .asciiz "\nMatrix determinant: "

.text
.globl main
.ent main
main:
    # [ To avoid syscall 10 - QtSpim ASSEMBLER]
    # subu $sp, $sp, 4
    # sw $ra, ($sp)

    li $a0, 2
    li $a1, 3
    li $a2, 12
    li $a3, 5

    subu $sp, $sp, 20
    li $t0, 6
    sw $t0, 16($sp)
    li $t0, 8
    sw $t0, 12($sp)
    li $t0, 14
    sw $t0, 8($sp)
    li $t0, 23
    sw $t0, 4($sp)
    li $t0, 1
    sw $t0, 0($sp)

    jal getDeterminant_3x3

    move $t1, $v0

    la $a0, msg_res
    li $v0, 4
    syscall

    move $a0, $t1
    li $v0, 1
    syscall


    # [ To avoid syscall 10 - QtSpim ASSEMBLER]
    # lw $ra, ($sp)
    # addu $sp, $sp, 4
    # jr $ra

    # On Mars:
    li $v0, 10
    syscall

getDeterminant_3x3:
    move $s3, $ra

    # $s0 = result

    subu $sp, $sp, 16
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)
    sw $a3, 12($sp)

    # Situation:
    # [ SP+0     SP+4     SP+8  ]
    # [ SP+12    SP+32    SP+28 ]
    # [ SP+24    SP+20    SP+16 ]

    # Defining:
    # [ a1  b1  c1 ]
    # [ a2  b2  c2 ]
    # [ a3  b3  c3 ]

    # a1 * det2x2(b2, c2 ; b3, c3)
    lw $a0, 32($sp)
    lw $a1, 28($sp)
    lw $a2, 20($sp)
    lw $a3, 16($sp)
    jal getDeterminant_2x2

    lw $t0, ($sp)
    mul $s0, $v0, $t0 

    # b1 * det2x2(a2, c2 ; a3, c3)
    lw $a0, 12($sp)
    lw $a1, 28($sp)
    lw $a2, 24($sp)
    lw $a3, 16($sp)
    jal getDeterminant_2x2

    lw $t0, 4($sp)
    mul $t1, $v0, $t0
    sub $s0, $s0, $t1

    # c1 * det2x2(a2, b2 ; a3, b3)
    lw $a0, 12($sp)
    lw $a1, 32($sp)
    lw $a2, 24($sp)
    lw $a3, 20($sp)
    jal getDeterminant_2x2

    lw $t0, 8($sp)
    mul $t1, $v0, $t0
    add $s0, $s0, $t1

    addu $sp, $sp, 36
    move $v0, $s0

    move $ra, $s3
    jr $ra

getDeterminant_2x2:

    mul $t0, $a0, $a3
    mul $t1, $a1, $a2
    sub $v0, $t0, $t1

    jr $ra
