# Write a procedure that get the masimum value of an array of words
# At the end, print that value

.data
    .eqv DIM 8
    array: .word 10 4 7 27 8 -57 1 -1

    max_str: .asciiz "\nThe maximum value is: "

.text
.globl main
.ent main
main:
    la $a0, array
    li $a1, DIM
    jal getMaximumValue
    move $t0, $v0
    
    la $a0, max_str
    li $v0, 4
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main

getMaximumValue:
    subu $sp, $sp, 12
    sw $t0, 8($sp)
    sw $t1, 4($sp)
    sw $t2, 0($sp)

    # initialise: max = first value
    lw $t1, ($a0)
    add $a0, $a0, 4
    li $t0, 1

    loop:
        bge $t0, $a1, end_loop

        lw $t2, ($a0)
        add $a0, $a0, 4
        blt $t2, $t1, not_greater
        
        # if greater
        move $t1, $t2

        not_greater:

        add $t0, $t0, 1
        j loop
    end_loop:

    move $v0, $t1

    lw $t0, 8($sp)
    lw $t1, 4($sp)
    lw $t2, 0($sp)
    addu $sp, $sp, 12
    jr $ra
