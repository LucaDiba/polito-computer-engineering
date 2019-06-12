		.data
var1:	.byte 'm'
var2:	.byte 'i'
var3:	.byte 'p'
var4:	.byte 's'
var5:	.byte 0

DELTA = 'A'-'a'

		.text
		.globl main
		.ent main
main:	lb $t1, var1
		addi $t1, $t1, DELTA
		sb $t1, var1
		
		lb $t1, var2		# conversione seconda variabile
		addi $t1, $t1, DELTA
		sb $t1, var2
		
		lb $t1, var3		# conversione terza variabile
		addi $t1, $t1, DELTA
		sb $t1, var3
		
		lb $t1, var4		# conversione quarta variabile
		addi $t1, $t1, DELTA
		sb $t1, var4
		
		la $a0, var1		# stampa
		li $v0, 4
		syscall
		li $v0, 10
		syscall
		.end main
	