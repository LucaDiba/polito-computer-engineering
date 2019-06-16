# Get DIM word values
# Calculate and print the average

.data
    # DIM = 5
    .eqv DIM 5 # for Mars
    print_msg: .asciiz "\nInsert a number:\n>> "
    result_msg: .asciiz "\nThe average is "

.text
.globl main
.ent main
main:
    # $t0 = sum of insered numbers
    # $t8 = loop counter
    and $t0, $0, $0
    and $t8, $0, $0
    
    li $t9, DIM

loop:
    beq $t8, $t9, loop_end

    # print instructions
    la $a0, print_msg
    li $v0, 4
    syscall

    # read integer
    li $v0, 5
    syscall

    add $t0, $t0, $v0

    add $t8, $t8, 1
    j loop

loop_end:
    div $t0, $t9
    mflo $t0

    # print average
    la $a0, result_msg
    li $v0, 4
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main