# Write a procedure that prints a triangle and a square

.data
    .eqv DIM 8

.text
.globl main
.ent main
main:
    jal printTriangle

    la $a0, '\n'
    li $v0, 11
    syscall

    jal printSquare

    li $v0, 10
    syscall
.end main


printTriangle:
    and $t0, $0, $0

    tri_for_i:
    bge $t0, DIM, tri_end_i

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
    and $t0, $0, $0

    sq_for_i:
    bge $t0, DIM, sq_end_i

        and $t1, $0, $0
        sq_for_j:
        bge $t1, DIM, sq_end_j

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