.name		"Sonofabitch"
.comment	"You piece of shit!"

live 	%-1
aff		r1
ld		%16, r2
st		r2, 64
ld		%-32, r3
st		r3, 64
add		r2, r3, r4
st		r2, 64
sub		r2, r3, r4
zjmp	%8
st		r2, 64
st		r2, -320
st		r2, 510
ldi		-64, %-4294967295, r4
aff		r4
st		r4, 128
