# Generate a multiplication table
# Store and print it

.data
    # 9 * 9 = 81 | 1 byte per number ==> 81 bytes
    table: .space 81

    tab_char: .asciiz "\t"
    nl_char: .asciiz "\n"

.text
.globl main
.ent main
main:
    # $t0 = bytes offset
    # $t1 = i
    # $t2 = j
    and $t0, $0, $0
    li $t1, 1

    for_i:
        bgt $t1, 9, end_i

        li $t2, 1
        for_j:
            bgt $t2, 9, end_j

            multu $t1, $t2
            mflo $t5

            sb $t5, table($t0)
            add $t0, $t0, 1

            move $a0, $t5
            li $v0, 1
            syscall

            la $a0, tab_char
            li $v0, 4
            syscall

            add $t2, $t2, 1
            j for_j
        end_j:

        la $a0, nl_char
        li $v0, 4
        syscall

        addi $t1, $t1, 1
        j for_i
    end_i:
    
li $v0, 10
syscall
.end main
