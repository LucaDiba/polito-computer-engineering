.data
    .eqv DIM 4
    matr: .word 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1

    diagonal_msg: .asciiz "\nMatrix is diagonal\n"
    symmetric_msg: .asciiz "\nMatrix is symmetric\n"
    not_symmetric_msg: .asciiz "\nMatrix is NOT symmetric\n"

.text
.globl main
.ent main
main:
    # $t0 = i (rows)
    # $t1 = j (columns)
    # $t2 = k (offset from first element)
    and $t0, $0, $0
    and $t1, $0, $0
    and $t2, $0, $0
    
    # diagonal
    for_i:
    bge $t0, DIM, end_i
        and $t1, $0, $0

        for_j:
        bge $t1, DIM, end_j

            beq $t0, $t1, check_not_needed
                lw $t5, matr($t2)
                bne $t5, 0, matr_is_not_diagonal

            check_not_needed:
            addi $t2, $t2, 4

        addi $t1, $t1, 1
        j for_j
        end_j:

    addi $t0, $t0, 1
    j for_i
    end_i:
        j matr_is_diagonal

matr_is_not_diagonal:

    # TO-DO: check if symmetric

    la $a0, not_symmetric_msg
    li $v0, 4
    syscall
    
    j end
matr_is_diagonal:
    la $a0, diagonal_msg
    li $v0, 4
    syscall
    j end

end:
    li $v0, 10
    syscall
.end main