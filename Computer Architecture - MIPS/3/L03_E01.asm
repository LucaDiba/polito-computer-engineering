# Read a single char and verify if it is a number or not
# Terminate when '\n' is detected

.data
    insert_number: .asciiz "Insert a character\n>> "
    is_number: .asciiz "\nThe char is a number\n"
    is_not_number: .asciiz "\nThe char is NOT a number\n"

.text
.globl main
.ent main

main:
    # print instruction
    la $a0, insert_number
    li $v0, 4
    syscall

    # read a character
    li $v0, 12
    syscall

    beq $v0, '\n', end
    blt $v0, '0', not_number
    bgt $v0, '9', not_number
    
    # print is number message
    la $a0, is_number
    li $v0, 4
    syscall
    j main

not_number:
    # print not number message
    la $a0, is_not_number
    li $v0, 4
    syscall
    j main

end:
    li $v0, 10
    syscall
.end main