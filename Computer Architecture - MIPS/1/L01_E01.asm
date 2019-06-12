.data
	var1: .byte 'm'
	var2: .byte 'i'
	var3: .byte 'p'
	var4: .byte 's'
	var5: .byte 0
.text
.globl main
.ent main
main:
		li $t0, 'A'
		li $t1, 'a'
		sub $t0, $t0, $t1

		lb $t1, var1
		add $t1, $t1, $t0
		sb $t1, var1

		lb $t1, var2
		add $t1, $t1, $t0
		sb $t1, var2

		lb $t1, var3
		add $t1, $t1, $t0
		sb $t1, var3

		lb $t1, var4
		add $t1, $t1, $t0
		sb $t1, var4

		la $a0, var1
		li $v0, 4
		syscall

li $v0, 10
syscall
.end main