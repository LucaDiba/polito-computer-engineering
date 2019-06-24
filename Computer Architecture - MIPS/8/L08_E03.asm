# Given: tems prices array, discounted items array (empty), number of elements, percentage of discount, rounding method (if 1 ==> round, if 0 ==> floor)
# Write a procedure that returns the total amount of reductions

.data
    .eqv NUM 5
    .eqv DIM 20 # NUM * 4
    .eqv DISCOUNT 30
    .eqv ROUND 1

    prices: .word 39, 1880, 2394, 1000, 1590
    discounted: .space DIM

.text
.globl main
.ent main
main:
    la $a0, prices
    la $a1, discounted
    li $a2, NUM
    li $a3, DISCOUNT
    li $t0, ROUND
    subu $sp, $sp, 4
    sw $t0, ($sp)
    jal getDiscount

li $v0, 10
syscall
.end main

getDiscount:
    # $t0 = prices
    # $t1 = discounted
    # $t2 = NUM - 1
    # $t3 = DISCOUNT
    # $t4 = ROUND
    move $t0, $a0
    move $t1, $a1
    sub $t2, $a2, 1
    move $t3, $a3
    lw $t4, ($sp)
    addu $sp, $sp, 4

    # $s0 = total amount of discounted prices
    and $s0, $0, $0

    loop:
        blt $t2, $0, end_loop

        # $t5 = current item price address
        li $t5, 4
        mul $t5, $t2, $t5 # [i] * 4
        add $t5, $t0, $t5 # address

        # $t5 = current item price value (original_price)
        lw $t5, ($t5)

        # discounted_price = original_price - original_price * discount / 100
        # $t6 = original_price * discount / 100
        mul $t6, $t5, $t3
        li $t7, 100
        div $t6, $t6, $t7

        # TO-DO: add round

        # $t6 = discounted_price
        sub $t6, $t5, $t6

        add $s0, $s0, $t6

        # $t5 = discounted item address
        li $t5, 4
        mul $t5, $t2, $t5
        add $t5, $t1, $t5
        sw $t6, ($t5)

        sub $t2, $t2, 1
        j loop
    end_loop:
    
    move $v0, $s0
    jr $ra
