#
# fork.s
#

.name "aff"
.comment "A basic ldi program"

main:
	ld 34, r3
	aff r3
	zjmp %:main
