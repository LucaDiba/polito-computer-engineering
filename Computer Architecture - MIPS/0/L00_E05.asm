.data
	wVett: .word 5, 7, 3, 4,
	wResult: .space 4

	.text
	.globl main
	.ent main
main:

and $t1, $0, $0 #accumulatore
la $t0, wVett 	#address attuale
and $t2, $0, $0 #tmp val

li $t3, 0
li $t4, 4

for:	beq $t3, $t4, end
		lw $t2, ($t0)
		add $t1, $t1, $t2
		addi $t0, $t0, 4
		add $t3, $t3, 1
		j for

end:	sw $t1, wResult

li $v0, 10
syscall
.end mail