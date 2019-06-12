.data
	DIM = 5
	wVett .space 20

	.text
	.globl main
	.ent main
main:
la $t0, wVett

and $t1, $0, $0 # i = 0
li $t5, 5 # n



forIn:	beq $t1, $t5, endForIn

		#print string
		la $a0, aStringIn
		li $v0, 4
		syscall
		#end print string

		#get integer
		li $v0, 5
		syscall	#result in $v0
		sw $v0, ($t1)
		#end get integer

		

		addi $t0, $t0, 4
		addi $t1, $t1, 1
		j forIn

endForIn:

#print string
la $a0, aStringOut
li $v0, 4
syscall
#end print string

la $t0, wVett
and $t1, $0, $0 # i = 0

forOut:	beq $t1, $t5, endForOut

		#print integer
		li $v0, 1
		lw $a0, ($t1)
		syscall	#result in $v0
		#end print string

		addi $t0, $t0, 4
		addi $t1, $t1, 1
		j forOut

endForOut:

li $v0, 10
syscall
.end mail