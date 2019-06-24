.data
    time_in:  .byte 12, 47
    time_out: .byte 18, 14
    X:        .byte 1
    Y:        .byte 40

.text
.globl main
main:
    la $a0, time_in  # indirizzo di ora_in
    la $a1, time_out # indirizzo di ora_out
    lbu $a2, X
    lbu $a3, Y
    jal getParkingAmount

    move $a0, $v0
    li $v0, 1
    syscall

li $v0, 10
syscall
.end main

getParkingAmount:
    # Time in  = h_in  : m_in
    # Time out = h_out : m_out

    # $t0 = h_in
    # $t1 = m_in
    # $t2 = h_out
    # $t3 = m_out
    lb $t0, 0($a0)
    lb $t1, 1($a0)
    lb $t2, 0($a1)
    lb $t3, 1($a1)

    # Total minutes: (h_out-1 - h_in) * 60 + (60 - m_in) + m_out

    # $s0 = (h_out - h_in) * 60
    sub $s0, $t2, $t0
    subi $s0, $s0, 1
    li $t4, 60
    mul $s0, $s0, $t4

    # $s1 = 60 - m_in
    sub $s1, $t4, $t1

    # $s0 = $s0 + $s1 + m_out (total minutes)
    add $s0, $s0, $s1
    add $s0, $s0, $t3

    # number of blocks = total minutes / minutes of a block
    div $s0, $a3
    mflo $s0
    mfhi $t0
    beq $t0, 0 perfect_time
    addi $s0, $s0, 1

    perfect_time:
    
    # total amount = amount per block * number of blocks
    mul $v0, $a2, $s0

    jr $ra