# Given a number of days, hours and minutes
# calculate the total number of minutes

.data
    dd: .byte 20
    hh: .byte 12
    mm: .byte 30
    result: .space 4 # byte

.text
.globl main
.ent main
main:
    # $t0 = res
    # $t9 = temp
    lbu $t1, dd
    lbu $t2, hh
    lbu $t3, mm

    # 1440 minutes in one day
    mul $t0, $t1, 1440

    # 60 minutes in one hour
    mul $t9, $t1, 60
    addu $t0, $t0, $t9

    # 1 minute in one minute
    addu $t0, $t0, $t3

    sw $t0, result

    la $a0, result
    li $v0, 1
    syscall
    
    li $v0, 10
    syscall
.end main