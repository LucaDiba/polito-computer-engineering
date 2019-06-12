.data
    ins_int:  .asciiz "Inserire un intero: "
    err_mess: .asciiz "Inserire un valore compreso tra -127 e 128"

.text
.globl main
.ent main

main:   
        li $v0, 4
        la $a0, ins_int
        syscall

        li $v0, 5
        syscall

        or $t0, $v0, $0

        li $t1, 0xFFFFFF00
        and $t1, $t1, $v0
        bne $t1, $0, errore


        li $v0, 4
        la $a0, ins_int
        syscall

        li $v0, 5
        syscall

        or $t1, $v0, $0

        li $t2, 0xFFFFFF00
        and $t2, $t2, $v0
        bne $t2, 0, errore

        xor $t5, $t0, $t1
        not $t6, $t1
        and $t6, $t6, $t0
        not $t6, $t6
        or $t5, $t5, $t6
        j end

errore: li $v0, 8
        la $a0, err_mess

end:    li $v0, 10
        syscall
.end main


19:36 47% (76, 38)