# Write Fibonacci's sequence in an array of 20 items

.data
    # ELEM_NUMBER = 20
    .eqv ELEM_NUMBER 20
    .eqv ARRAY_DIM 80
    fib_array: .space ARRAY_DIM

.text
.globl main
.ent main
main:
    # $t0 = fib_array index
    # $t1 = fib_array[i-1]
    # $t2 = fib_array[i-2]

    and $t0, $0, $0
    and $t2, $0, $0
    li $t1, 1
    li $t9, ELEM_NUMBER

loop:
    beq $t0, $t9, loop_end
    
    # $t3 = $t1 + $t2
    add $t3, $t1, $t2

    mul $t5, $t0, 4
    sw $t3, fib_array($t5)

    move $t2, $t1
    move $t1, $t3
    add $t0, $t0, 1

    j loop

loop_end:

li $v0, 10
syscall

.end main