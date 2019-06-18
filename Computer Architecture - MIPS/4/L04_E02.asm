# Given 2 operands (type: word) in menory, execute an operation between integers and save the result in the var "res" (word)
# The operation differs depending on the user input:
# - 0: res = a + b
# - 1: res = a - b
# - 2: res = a * b
# - 3: res = a / b (integer division)

.data
    opa: .word 2043
    opb: .word 5
    res: .space 4
    tab: .word addition, subtraction, multiplication, division
    input_msg: .asciiz "\nSelect the operation you want:\n>> "
    result_msg: .asciiz "\nThe result is "
    error_msg: .asciiz "\nPlease, insert a number between 0 and 3"

.text
.globl main
.ent main
main:
    lw $t1, opa
    lw $t2, opb

input:
    la $a0, input_msg
    li $v0, 4
    syscall

    li $v0, 5
    syscall

    bgt $v0, 3, error
    blt $v0, 0, error
    sll $t0, $v0, 2 # $t0 = $v0 * 2^2
    lw $t0, tab($t0)
    jr $t0

addition:
    add $t0, $t1, $t2
    j end

subtraction:
    sub $t0, $t1, $t2
    j end

multiplication:
    mul $t0, $t1, $t2
    j end

division:
    div $t0, $t1, $t2
    j end

error:
    la $a0, error_msg
    li $v0, 4
    syscall
    j input

end:
    sw $t0, res

    la $a0, result_msg
    li $v0, 4
    syscall

    li $v0, 1
    move $a0, $t0
    syscall

li $v0, 10
syscall
.end main