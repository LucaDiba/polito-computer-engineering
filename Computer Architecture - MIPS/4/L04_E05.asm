# Given the following table of words:

# 154 | 123 |  109 | 86 | 4  | ?
# 412 | -23 | -231 | 9  | 50 | ?
# 123 | -24 |  12  | 55 |-45 | ?
#  ?  |  ?  |  ?   | ?  | ?  | ?

# Sum each row and column and store the relative amount at the end of the row/column

.data
    # N = 4 # rows
    # M = 6 # columns
    .eqv N 4
    .eqv M 6
    table: .word 154 123 109 86 4 0 412 -23 -231 9 50 0 123 -24 12 55 -45 0 0 0 0 0 0 0

.text
    # $t0 = table offset
    # $t1 = i (row iterator)
    # $t2 = j (column iterator)
    and $t0, $0, $0
    li $t1, 1

    for_i:
        bge $t1, N, end_i

        li $t2, 1
        # sum row elements in $t3
        and $t3, $0, $0

        for_j:
            bge $t2, M end_j

            # add row elements
            lw $t4, table($t0)
            add $t3, $t3, $t4
            addi $t0, $t0, 4

            # add column elements
            # but first we need to know the offset for the last row's element on the same column
            li $t5, N
            sub $t5, $t5, $t1 # (rows - current row)
            li $t7, 4
            li $t6, M
            mul $t6, $t6, $t7
            multu $t5, $t6
            mflo $t5
            add $t5, $t5, $t0

            lw $t6, table($t5)
            add $t6, $t6, $t4
            sw $t6, table($t5) 

            add $t2, $t2, 1
            j for_j
        end_j:

        # write sum row elements
        lw $t4, table($t0)
        add $t4, $t4, $t3
        sw $t4, table($t0)
        addi $t0, $t0, 4

        addi $t1, $t1, 1
        j for_i
    end_i:
