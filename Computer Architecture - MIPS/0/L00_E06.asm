.data
	aStringIn: .asciiz "Inserire numero:\n"
	aStringOut: .asciiz "Numeri inseriti:\n"

	wVett: .space 20

	.text
	.globl main
	.ent main
main:
la $t2, wVett

and $t0, $0, $0 # i = 0
li $t1, 5 # n

forIn:	beq $t1, $t0, endForIn

		#print string
		la $a0, aStringIn
		li $v0, 4
		syscall
		#end print string

		#get integer
		li $v0, 5
		syscall	#result in $v0
		sw $v0, ($t2)
		#end get integer

		addi $t2, $t2, 4
		addi $t0, $t0, 1
		j forIn

endForIn:

#print string
la $a0, aStringOut
li $v0, 4
syscall
#end print string

la $t2, wVett
and $t0, $0, $0 # i = 0

forOut:	beq $t1, $t0, endForOut

		#print integer
		li $v0, 1
		lw $a0, ($t2)
		syscall	#result in $v0
		#end print string

		addi $t2, $t2, 4
		addi $t0, $t0, 1
		j forOut

endForOut:

li $v0, 10
syscall
.end mail