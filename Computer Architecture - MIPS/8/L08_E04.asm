.data
    .eqv DIM 5
    arr1: .word 56, 12, 98, 129, 58
    arr2: .word 1, 0, 245, 129, 12
    res:  .space DIM

.text
.globl main
.ent main
main:
    la $a0, arr1
    la $a1, arr2
    la $a2, res
    li $a3, DIM
    jal getHammingDistance

li $v0, 10
syscall
.end main

getHammingDistance:
    move $t0, $a0 # $t0 = vet1
    move $t1, $a1 # $t1 = vet2
    move $t2, $a2 # $t2 = res
    subi $t3, $a3, 1 # $t3 = DIM - 1

    loop: # $t3 = i, starting from n-1
        blt $t3, $0, end_loop

        # $t4 = vet1[i]
        li $t5, 4
        mul $t5, $t3, $t5
        add $t4, $t0, $t5
        lw $t4, ($t4)

        # $t5 = vet2[i]
        add $t5, $t5, $t1
        lw $t5, ($t5)

        # $t4 = xor (bits not equal to each other to 1)
        xor $t4, $t4, $t5

        # shift 8 times the bits and check if the LSB is 1 or 0
        # count the number of 1s
        # $t5 = i
        # $t6 = number of 1s
        # $t7 = (0000 0001)bin
        and $t5, $0, $0
        and $t6, $0, $0
        li $t7, 1

        shift_loop:
            bge $t5, 8, shift_loop_end

            and $t8, $t4, $t7
            beq $t8, $0, same_bit

            addi $t6, $t6, 1

            same_bit:
            srl $t4, $t4, 1

            addi $t5, $t5, 1
            j shift_loop
        shift_loop_end:

        # $t5 = res address
        add $t5, $t2, $t3
        sb $t6, ($t5)

        subi $t3, $t3, 1
        j loop
    end_loop:

    jr $ra
