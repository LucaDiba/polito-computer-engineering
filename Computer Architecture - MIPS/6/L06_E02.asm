# Take the code of L06_E01 and let the user choose the size

.data
    instruction_msg: .asciiz "\nPlease, insert the size:\n>> "

.text
.globl main
.ent main
main:
    la $a0, instruction_msg
    li $v0, 4
    syscall

    li $v0, 5
    syscall

    move $t8, $v0
    move $a0, $t8

    jal printTriangle

    la $a0, '\n'
    li $v0, 11
    syscall

    move $a0, $t8

    jal printSquare

    li $v0, 10
    syscall
.end main


printTriangle:
    move $t9, $a0
    and $t0, $0, $0

    tri_for_i:
    bge $t0, $t9, tri_end_i

        and $t1, $0, $0

        tri_for_j:
        bgt $t1, $t0, tri_end_j

            la $a0, '*'
            li $v0, 11
            syscall

        addi $t1, $t1, 1
        j tri_for_j
        tri_end_j:

        la $a0, '\n'
        li $v0, 11
        syscall

    addi $t0, $t0, 1
    j tri_for_i
    tri_end_i:

    jr $ra

printSquare:
    move $t9, $a0
    and $t0, $0, $0

    sq_for_i:
    bge $t0, $t9, sq_end_i

        and $t1, $0, $0
        sq_for_j:
        bge $t1, $t9, sq_end_j

            la $a0, '*'
            li $v0, 11
            syscall

        addi $t1, $t1, 1
        j sq_for_j
        sq_end_j:

        la $a0, '\n'
        li $v0, 11
        syscall

    addi $t0, $t0, 1
    j sq_for_i
    sq_end_i:

    jr $ra