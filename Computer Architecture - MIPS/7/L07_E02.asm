# Take a sequence of natural numbers in which, given c_0, following elements are:
# c_(i+1) = - c_i / 2       if c_i is even
#           - 3 * c_i + 1   if c_i is odd

# Write a procedure getNextElement
# Give it a natural number in $a0 and put the next element in $v0 after printing it

.data
    msg_instruction: .asciiz "\nInsert a natural number:\n>> "
    msg: .asciiz "\nThe next element is: "

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

    jal getNextElement

li $v0, 10
syscall
.end main

getNextElement:
    and $t0, $a0, 0x1 # LSB

    beq $t0, $0, even
    j odd

    even:
        li $t1, 2
        div $t0, $a0, $t1
        j print

    odd:
        li $t1, 3
        mul $t0, $a0, $t1
        addi $t0, $t0, 1
        j print

    print:
        la $a0, msg
        li $v0, 4
        syscall

        move $a0, $t0
        li $v0, 1
        syscall

        move $v0, $t0
    jr $ra