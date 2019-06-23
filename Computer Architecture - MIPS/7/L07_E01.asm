# Write a procedure "sum" to sum elements passed in $a0 and $a1
# Sum should: - reset registers from $t0 to $t4 and from $s0 to $s4
#             - write $a0 and $a1 in $t2 and $s2
#             - return the sum in $v0

.text
.globl main
.ent main
main:
    li $t0, 15
    li $t1, 16
    li $t2, 17
    li $t3, 18

    li $s0, 223
    li $s1, 224
    li $s2, 225
    li $s3, 226

    move $a0, $t0
    move $a1, $t1

    subu $sp, $sp, 16
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    sw $t2, 8($sp)
    sw $t3, 12($sp)

    jal sum

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    lw $t2, 8($sp)
    lw $t3, 12($sp)
    addu $sp, $sp, 16

    move $a0, $v0
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main

sum:
    subu $sp, $sp, 16
    sw $s0, 0($sp)
    sw $s1, 4($sp)
    sw $s2, 8($sp)
    sw $s3, 12($sp)

    and $t0, $0, $0
    and $t1, $0, $0
    and $t2, $0, $0
    and $t3, $0, $0
    and $t4, $0, $0
    and $s0, $0, $0
    and $s1, $0, $0
    and $s2, $0, $0
    and $s3, $0, $0
    and $s4, $0, $0

    move $t2, $a0
    move $s2, $a1

    add $v0, $t2, $s2

    lw $s0, 0($sp)
    lw $s1, 4($sp)
    lw $s2, 8($sp)
    lw $s3, 12($sp)
    addu $sp, $sp, 16
    jr $ra