# Collatz conjecture says that taking the sequence defined in L07_E02
# No matter what value of n, the sequence will always reach 1
# Write a procedure called "CollatzSequence" that receives in $a0 a natural number
# and returns in $v0, the number of elements needed to reach 1

.data
    msg_instruction: .asciiz "\nInsert a natural number:\n>> "
    msg_solution: .asciiz "\nThe number of iterations needed to reach 1 is: "

.text
.globl main
.ent main
main:
    la $a0, msg_instruction
    li $v0, 4
    syscall

    li $v0, 5
    syscall

    move $a0, $v0

    jal CollatzSequence

    move $t1, $v0

    la $a0, msg_solution
    li $v0, 4
    syscall

    move $a0, $t1
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main

CollatzSequence:
    subu $sp, $sp, 4
    sw $ra, ($sp)

    and $s0, $0, $0
    move $s1, $a0

    loop:
        beq $s1, 1, end_loop

        move $a0, $s1
        jal getNextElement
        move $s1, $v0

        addi $s0, $s0, 1
        j loop    
    end_loop:

    move $v0, $s0

    lw $ra, ($sp)
    addu $sp, $sp, 4
    jr $ra

getNextElement:
    and $t0, $a0, 0x1 # LSB

    beq $t0, $0, even
    j odd

    even:
        li $t1, 2
        div $t0, $a0, $t1
        j end_getNextElement

    odd:
        li $t1, 3
        mul $t0, $a0, $t1
        addi $t0, $t0, 1
        j end_getNextElement

    end_getNextElement:

        move $v0, $t0
    jr $ra