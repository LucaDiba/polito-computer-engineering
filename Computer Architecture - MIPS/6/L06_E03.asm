# Write a procedure that converts a lowercase string to UPPERCASE

.data
    string: .asciiz "uppercase me"

.text
.globl main
.ent main
main:
    and $t0, $0, $0

loop:
    lbu $t1, string($t0)
    beq $t1, '\0', end_loop
    
    move $a0, $t1
    jal lowercaseToUppercase
    sb $v0, string($t0)

    add $t0, $t0, 1
    j loop
end_loop:

    la $a0, string
    li $v0, 4
    syscall

li $v0, 10
syscall
.end main

lowercaseToUppercase:
    sub $sp, $sp, 4
    sw $t0, ($sp)

    li $t0, 'A'
    subi $t0, $t0, 'a'
    add $v0, $a0, $t0

    lw $t0, ($sp)
    add $sp, $sp, 4
    jr $ra