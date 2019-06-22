# Problem: syscall 1 is for signed integers. It can print ints from -2^31 to 2^31-1
# Write a program that is able to print integers from 2^31 to 2^32-1 using syscall 11

.data
    int: .word 3141592653
    msg: .asciiz "\nThe stored number is: "

.text
.globl main
.ent main
main:
    lw $t0, int
    li $t1, 10
    and $t2, $0, $0

loop:
    divu $t0, $t1
    mfhi $t9
    mflo $t0
    
    # store in stack
    subu $sp, $sp, 4
    sw $t9, ($sp)

    addi $t2, $t2, 1
    bne $t0, 0, loop
# end_loop

    la $a0, msg
    li $v0, 4
    syscall

print_loop:
    beq $t2, 0, end_print_loop

    lw $a0, ($sp)
    addu $sp, $sp, 4

    addi $a0, $a0, '0'
    li $v0, 11
    syscall

    subi $t2, $t2, 1
    j print_loop
end_print_loop:

    li $v0, 10
    syscall
.end main
