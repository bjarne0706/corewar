.name		"Sonofabitch"
.comment	"You piece of shit!"

live 	%-1
live 	%-1
aff		r1
ld		%255, r2
st		r2, 64
ld		%255, r3
st		r3, 64
add		r2, r3, r4
st		r2, 64
sub		r2, r3, r4
zjmp	%8
st		r2, 64
st		r2, 128
st		r2, 256
