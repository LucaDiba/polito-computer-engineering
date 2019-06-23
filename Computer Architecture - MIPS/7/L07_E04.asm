# Get 2x2 matrix determinant

.data
    msg_res: .asciiz "\nMatrix determinant: "

.text
.globl main
.ent main
main:
    # [ To avoid syscall 10 - QtSpim ASSEMBLER]
    # subu $sp, $sp, 4
    # sw $ra, ($sp)

    li $a0, 2
    li $a1, 3
    li $a2, 12
    li $a3, 5

    jal getDeterminant_2x2

    move $t1, $v0

    la $a0, msg_res
    li $v0, 4
    syscall

    move $a0, $t1
    li $v0, 1
    syscall


    # [ To avoid syscall 10 - QtSpim ASSEMBLER]
    # lw $ra, ($sp)
    # addu $sp, $sp, 4
    # jr $ra

    # On Mars:
    li $v0, 10
    syscall

getDeterminant_2x2:

    mul $t0, $a0, $a3
    mul $t1, $a1, $a2
    sub $v0, $t0, $t1

    jr $ra