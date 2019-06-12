# Read a single char and verify if it is a number or not
# If number, verify that it is rappresentable on 4 bytes
# Terminate when '\n' is detected

.data
    insert_number: .asciiz "Insert a number\n>> "
    is_number_on_4_bytes: .asciiz "\nThe number is rappresentable on 4 bytes\n"
    is_number_not_on_4_bytes: .asciiz "\nThe number is NOT rappresentable on 4 bytes\n"
    is_not_number: .asciiz "\nThe char is NOT a number\n"

.text
.globl main
.ent main

main:
    # print instruction
    la $a0, insert_number
    li $v0, 4
    syscall

    # $t0 = digits counter
    and $t0, $0, $0

    # $t1 = total number
    and $t1, $0, $0

loop:
    # read a character
    li $v0, 12
    syscall

    # if (char == '\n') ==> end
    beq $v0, '\n', end
    # elif (char < '0' OR char > '0') ==> not_number
    blt $v0, '0', not_number
    bgt $v0, '9', not_number
    # else continue
    
    # subtract '0' to get the integer (and not the ASCII representation)
    # $t5 = int number
    sub $t5, $v0, '0'

    # $t6 = 10 ^ $t0 (loop)
    li $t6, 1

    # multiply current number * 10, then add the last digit
    mul $t6, $t6, 10

    # mult: write result in 64-bit
    mult $t1, $t6
    # move from high part result to $t1
    mfhi $t1
    # if high part is not 0 ==> overflow on 4 bytes ==> print not rapresentable error message
    bne $t1, 0, number_is_not_rappresentable

    # else continue
    mflo $t1
    add $t1, $t1, $t5
    add $t0, $t0, 1

    j loop

not_number:
    # print not number message
    la $a0, is_not_number
    li $v0, 4
    syscall
    j loop

number_is_not_rappresentable:
    la $a0, is_number_not_on_4_bytes
    li $v0, 4
    syscall

end:
    # print entire number
    move $a0, $t1
    li $v0, 1
    syscall

end_main:
    li $v0, 10
    syscall
.end main
