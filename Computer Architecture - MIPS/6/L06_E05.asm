# Given n and k, calculate the mathematical combinations
.data
    n: .word 12
    k: .word 2

.text
.globl main
.ent main
main:
    lw $a0, n
    lw $a1, k
    jal calculateCombination

    move $a0, $v0
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main

calculateCombination:
    subu $sp, $sp, 12
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    sw $t2, 8($sp)

    # $a0 = n
    # $a1 = k

    # $t0 = numerator: n(n-1)(n-2)...(n-k+1)
    # $t1 = n-k+1
    # $t2 = denominator: k!
    li $t0, 1
    li $t2, 1
    sub $t1, $a0, $a1
    add $t1, $t1, 1
    
    numerator_loop:
        blt $a0, $t1, end_numerator_loop

        mul $t0, $t0, $a0
        sub $a0, $a0, 1

        j numerator_loop
    end_numerator_loop:
    denominator_loop:
        ble $a1, 1, end_denominator_loop

        mul $t2, $t2, $a1
        sub $a1, $a1, 1

        j denominator_loop
    end_denominator_loop:

    div $v0, $t0, $t2

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    lw $t2, 8($sp)
    addu $sp, $sp, 12

    jr $ra