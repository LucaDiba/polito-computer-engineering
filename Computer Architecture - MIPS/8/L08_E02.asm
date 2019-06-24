# Given an array of years, check whether they are bissextile
# Put the result in a "res" array

.data
    .eqv DIM 6

    # years: word | res: byte
    
    years: .word 1945 2008 1800 2006 1748 1600
    res:   .space DIM

.text
.globl main
.ent main
main:
    la $a0, years
    la $a1, res
    li $a2, DIM
    jal checkIfBissextile

li $v0, 10
syscall
.end main

checkIfBissextile:
    subu $sp, $sp, 4
    sw $ra, ($sp)

    subi $a2, $a2, 1
    checkIfBissextile_loop:
        blt $a2, $0, checkIfBissextile_loop_end

        li $t0, 4
        mul $t0, $a2, $t0
        add $t0, $t0, $a0
        lw $t0, ($t0)

        li $t1, 100
        div $t0, $t1
        mfhi $t1
        bne $t1, $0, not_divisible_by_100
        # divisible by 100
            li $t1, 400
            div $t0, $t1
            mfhi $t1
            bne $t1, $0, is_not_bissextile
            # divisible by 400
                j is_bissextile
        
        not_divisible_by_100:
            li $t1, 4
            div $t0, $t1
            mfhi $t1
            bne $t1, $0, is_not_bissextile
            j is_bissextile

        is_bissextile:
            li $t1, 1
            j continue

        is_not_bissextile:
            li $t1, 0
            j continue

        continue:
            add $t0, $a1, $a2
            sb $t1, ($t0)

            subi $a2, $a2, 1
            j checkIfBissextile_loop
    checkIfBissextile_loop_end:

    lw $a0, ($sp)
    jr $a0