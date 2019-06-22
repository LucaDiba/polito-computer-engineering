# Given a, b and c, check whether the equation ax^2+bx+c=0 has real solutions

.data
    msg_instructions: .asciiz "\nInsert a, b, c for ax^2 + bx + c = 0\n"
    msg_insert_a: .asciiz "Insert a: >> "
    msg_insert_b: .asciiz "Insert b: >> "
    msg_insert_c: .asciiz "Insert c: >> "
    msg_has_real_solution: .asciiz "\nThe equation has real solutions\n"
    msg_has_not_real_solution: .asciiz "\nThe equation has NOT real solutions\n"

.text
.globl main
.ent main
main:
    # $t0 = a
    # $t1 = b
    # $t2 = c

    la $a0, msg_instructions
    li $v0, 4
    syscall

    # Insert a msg
    la $a0, msg_insert_a
    li $v0, 4
    syscall
    
    # Insert a
    li $v0, 5
    syscall
    move $t0, $v0

    # Insert b msg
    la $a0, msg_insert_b
    li $v0, 4
    syscall
    
    # Insert b
    li $v0, 5
    syscall
    move $t1, $v0

    # Insert c msg
    la $a0, msg_insert_c
    li $v0, 4
    syscall
    
    # Insert c
    li $v0, 5
    syscall
    move $t2, $v0

    # Solution is real if b^2 - 4ac >= 0
    # $t3 = b^2
    # $t4 = a*c
    sll $t3, $t1, 1
    mul $t4, $t0, $t2

    li $t5, 4
    mul $t4, $t4, $t5 # 4ac

    # $t3 = b^2 - 4ac
    sub $t3, $t3, $t4

    blt $t3, $0, not_real_solutions

# has real solutions:
    la $a0, msg_has_real_solution
    li $v0, 4
    syscall

    j end
not_real_solutions:
    la $a0, msg_has_not_real_solution
    li $v0, 4
    syscall

end:
    li $v0, 10
    syscall
.end main
