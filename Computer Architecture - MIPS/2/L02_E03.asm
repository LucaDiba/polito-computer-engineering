.data
    w1: .word 30
    w2: .word 20
    w3: .word 10

.text
.globl main
.ent main
main:

    lw $t1, w1
    lw $t2, w2
    lw $t3, w3

    blt $t1, $t2, lab1
    move $t5, $t1
    move $t1, $t2
    move $t2, $t5

lab1:
    blt $t1, $t3, lab2
    move $t5, $t1
    move $t1, $t3
    move $t3, $t5

lab2:
    blt $t2, $t3, lab3
    move $t5, $t2
    move $t2, $t3
    move $t3, $t5

lab3:
    move $a0, $t1
    li $v0, 1
    syscall

    move $a0, $t2
    li $v0, 1
    syscall
    
    move $a0, $t3
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main
