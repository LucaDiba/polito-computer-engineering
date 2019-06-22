# Check whether a string is palindrome

.data
    msg_ins: .asciiz "\nInsert your string, then press enter\n>> "
    msg_yes: .asciiz "\nThe string is palindrome\n"
    msg_no: .asciiz "\nThe string is NOT palindrome\n"

.text
.globl main
.ent main
main:
    la $a0, msg_ins
    li $v0, 4
    syscall

    move $t0, $sp
    subu $t0, $t0, 4
    move $t9, $t0

char_loop:
    li $v0, 12
    syscall

    beq $v0, '\n', char_loop_end

    subu $sp, $sp, 4
    sw $v0, ($sp)

    j char_loop
char_loop_end:

char_check:

    lw $t1, ($sp)
    addu $sp, $sp, 4
    lw $t2, ($t0)
    subu $t0, $t0, 4

    bne $t1, $t2, not_palindrome_string
    subu $t5, $t0, $sp
    ble $t5, 4, palindrome_string
    j char_check


palindrome_string:
    la $a0, msg_yes
    li $v0, 4
    syscall
    j end

not_palindrome_string:
    la $a0, msg_no
    li $v0, 4
    syscall

end:
    move $sp, $t9

    li $v0, 10
    syscall
.ent main