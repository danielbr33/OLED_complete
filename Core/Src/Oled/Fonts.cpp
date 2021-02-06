#include "Fonts.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
static uint16_t Font6x8[] = {
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	//	 
	0x0,	0x0,	0x5f,	0x0,	0x0,	0x0,	//	!
	0x0,	0x7,	0x0,	0x7,	0x0,	0x0,	//	"
	0x14,	0x7f,	0x14,	0x7f,	0x14,	0x0,	//	#
	0x24,	0x2a,	0x7f,	0x2a,	0x12,	0x0,	//	$
	0x23,	0x13,	0x8,	0x64,	0x62,	0x0,	//	%
	0x36,	0x49,	0x56,	0x20,	0x50,	0x0,	//	&
	0x0,	0x8,	0x7,	0x3,	0x0,	0x0,	//	'
	0x0,	0x1c,	0x22,	0x41,	0x0,	0x0,	//	(
	0x0,	0x41,	0x22,	0x1c,	0x0,	0x0,	//	)
	0x2a,	0x1c,	0x7f,	0x1c,	0x2a,	0x0,	//	*
	0x8,	0x8,	0x3e,	0x8,	0x8,	0x0,	//	+
	0x0,	0x0,	0x70,	0x30,	0x0,	0x0,	//	,
	0x8,	0x8,	0x8,	0x8,	0x8,	0x0,	//	-
	0x0,	0x0,	0x60,	0x60,	0x0,	0x0,	//	.
	0x20,	0x10,	0x8,	0x4,	0x2,	0x0,	//	/
	0x3e,	0x51,	0x49,	0x45,	0x3e,	0x0,	//	0
	0x0,	0x42,	0x7f,	0x40,	0x0,	0x0,	//	1
	0x72,	0x49,	0x49,	0x49,	0x46,	0x0,	//	2
	0x21,	0x41,	0x49,	0x4d,	0x33,	0x0,	//	3
	0x18,	0x14,	0x12,	0x7f,	0x10,	0x0,	//	4
	0x27,	0x45,	0x45,	0x45,	0x39,	0x0,	//	5
	0x3c,	0x4a,	0x49,	0x49,	0x31,	0x0,	//	6
	0x41,	0x21,	0x11,	0x9,	0x7,	0x0,	//	7
	0x36,	0x49,	0x49,	0x49,	0x36,	0x0,	//	8
	0x46,	0x49,	0x49,	0x29,	0x1e,	0x0,	//	9
	0x0,	0x0,	0x14,	0x0,	0x0,	0x0,	//	:
	0x0,	0x40,	0x34,	0x0,	0x0,	0x0,	//	;
	0x0,	0x8,	0x14,	0x22,	0x41,	0x0,	//	<
	0x14,	0x14,	0x14,	0x14,	0x14,	0x0,	//	=
	0x0,	0x41,	0x22,	0x14,	0x8,	0x0,	//	>
	0x2,	0x1,	0x59,	0x9,	0x6,	0x0,	//	?
	0x3e,	0x41,	0x5d,	0x59,	0x4e,	0x0,	//	@
	0x7c,	0x12,	0x11,	0x12,	0x7c,	0x0,	//	A
	0x7f,	0x49,	0x49,	0x49,	0x36,	0x0,	//	B
	0x3e,	0x41,	0x41,	0x41,	0x22,	0x0,	//	C
	0x7f,	0x41,	0x41,	0x41,	0x3e,	0x0,	//	D
	0x7f,	0x49,	0x49,	0x49,	0x41,	0x0,	//	E
	0x7f,	0x9,	0x9,	0x9,	0x1,	0x0,	//	F
	0x3e,	0x41,	0x41,	0x51,	0x73,	0x0,	//	G
	0x7f,	0x8,	0x8,	0x8,	0x7f,	0x0,	//	H
	0x0,	0x41,	0x7f,	0x41,	0x0,	0x0,	//	I
	0x20,	0x40,	0x41,	0x3f,	0x1,	0x0,	//	J
	0x7f,	0x8,	0x14,	0x22,	0x41,	0x0,	//	K
	0x7f,	0x40,	0x40,	0x40,	0x40,	0x0,	//	L
	0x7f,	0x2,	0x1c,	0x2,	0x7f,	0x0,	//	M
	0x7f,	0x4,	0x8,	0x10,	0x7f,	0x0,	//	N
	0x3e,	0x41,	0x41,	0x41,	0x3e,	0x0,	//	O
	0x7f,	0x9,	0x9,	0x9,	0x6,	0x0,	//	P
	0x3e,	0x41,	0x51,	0x21,	0x5e,	0x0,	//	Q
	0x7f,	0x9,	0x19,	0x29,	0x46,	0x0,	//	R
	0x26,	0x49,	0x49,	0x49,	0x32,	0x0,	//	S
	0x3,	0x1,	0x7f,	0x1,	0x3,	0x0,	//	T
	0x3f,	0x40,	0x40,	0x40,	0x3f,	0x0,	//	U
	0x1f,	0x20,	0x40,	0x20,	0x1f,	0x0,	//	V
	0x3f,	0x40,	0x38,	0x40,	0x3f,	0x0,	//	W
	0x63,	0x14,	0x8,	0x14,	0x63,	0x0,	//	X
	0x3,	0x4,	0x78,	0x4,	0x3,	0x0,	//	Y
	0x61,	0x59,	0x49,	0x4d,	0x43,	0x0,	//	Z
	0x0,	0x7f,	0x41,	0x41,	0x41,	0x0,	//	[
	0x2,	0x4,	0x8,	0x10,	0x20,	0x0,	//	/*\*/
	0x0,	0x41,	0x41,	0x41,	0x7f,	0x0,	//	]
	0x4,	0x2,	0x1,	0x2,	0x4,	0x0,	//	^
	0x40,	0x40,	0x40,	0x40,	0x40,	0x0,	//	_
	0x0,	0x3,	0x7,	0x8,	0x0,	0x0,	//	`
	0x20,	0x54,	0x54,	0x78,	0x40,	0x0,	//	a
	0x7f,	0x28,	0x44,	0x44,	0x38,	0x0,	//	b
	0x38,	0x44,	0x44,	0x44,	0x28,	0x0,	//	c
	0x38,	0x44,	0x44,	0x28,	0x7f,	0x0,	//	d
	0x38,	0x54,	0x54,	0x54,	0x18,	0x0,	//	e
	0x0,	0x8,	0x7e,	0x9,	0x2,	0x0,	//	f
	0x18,	0x24,	0x24,	0x1c,	0x78,	0x0,	//	g
	0x7f,	0x8,	0x4,	0x4,	0x78,	0x0,	//	h
	0x0,	0x44,	0x7d,	0x40,	0x0,	0x0,	//	i
	0x20,	0x40,	0x40,	0x3d,	0x0,	0x0,	//	j
	0x7f,	0x10,	0x28,	0x44,	0x0,	0x0,	//	k
	0x0,	0x41,	0x7f,	0x40,	0x0,	0x0,	//	l
	0x7c,	0x4,	0x78,	0x4,	0x78,	0x0,	//	m
	0x7c,	0x8,	0x4,	0x4,	0x78,	0x0,	//	n
	0x38,	0x44,	0x44,	0x44,	0x38,	0x0,	//	o
	0x7c,	0x18,	0x24,	0x24,	0x18,	0x0,	//	p
	0x18,	0x24,	0x24,	0x18,	0x7c,	0x0,	//	q
	0x7c,	0x8,	0x4,	0x4,	0x8,	0x0,	//	r
	0x48,	0x54,	0x54,	0x54,	0x24,	0x0,	//	s
	0x4,	0x4,	0x3f,	0x44,	0x24,	0x0,	//	t
	0x3c,	0x40,	0x40,	0x20,	0x7c,	0x0,	//	u
	0x1c,	0x20,	0x40,	0x20,	0x1c,	0x0,	//	v
	0x3c,	0x40,	0x30,	0x40,	0x3c,	0x0,	//	w
	0x44,	0x28,	0x10,	0x28,	0x44,	0x0,	//	x
	0x4c,	0x10,	0x10,	0x10,	0x7c,	0x0,	//	y
	0x44,	0x64,	0x54,	0x4c,	0x44,	0x0,	//	z
	0x0,	0x8,	0x36,	0x41,	0x0,	0x0,	//	{
	0x0,	0x0,	0x77,	0x0,	0x0,	0x0,	//	|
	0x0,	0x41,	0x36,	0x8,	0x0,	0x0,	//	}
	0x2,	0x1,	0x2,	0x4,	0x2,	0x0		//	~
};
static uint16_t Font7x10[] = {
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	//	 
	0x0,	0x0,	0x0,	0xbf,	0x0,	0x0,	0x0,	//	!
	0x0,	0x0,	0x7,	0x0,	0x7,	0x0,	0x0,	//	"
	0x0,	0xf4,	0x2f,	0x24,	0xf4,	0x2f,	0x0,	//	#
	0x0,	0x66,	0x89,	0x1ff,	0x89,	0x72,	0x0,	//	$
	0x0,	0x26,	0x19,	0x6e,	0x94,	0x62,	0x0,	//	%
	0x0,	0x60,	0x96,	0x99,	0x66,	0x90,	0x0,	//	&
	0x0,	0x0,	0x0,	0x7,	0x0,	0x0,	0x0,	//	'
	0x0,	0x0,	0xfc,	0x102,	0x201,	0x0,	0x0,	//	(
	0x0,	0x0,	0x201,	0x102,	0xfc,	0x0,	0x0,	//	)
	0x0,	0x0,	0xa,	0x7,	0xa,	0x0,	0x0,	//	*
	0x0,	0x10,	0x10,	0x7c,	0x10,	0x10,	0x0,	//	+
	0x0,	0x0,	0x0,	0x380,	0x0,	0x0,	0x0,	//	,
	0x0,	0x0,	0x20,	0x20,	0x20,	0x0,	0x0,	//	-
	0x0,	0x0,	0x0,	0x80,	0x0,	0x0,	0x0,	//	.
	0x0,	0x0,	0xc0,	0x3c,	0x3,	0x0,	0x0,	//	/
	0x0,	0x7e,	0x81,	0x89,	0x81,	0x7e,	0x0,	//	0
	0x0,	0x4,	0x2,	0xff,	0x0,	0x0,	0x0,	//	1
	0x0,	0x86,	0xc1,	0xa1,	0x91,	0x8e,	0x0,	//	2
	0x0,	0x42,	0x81,	0x89,	0x89,	0x76,	0x0,	//	3
	0x0,	0x30,	0x2c,	0x22,	0xff,	0x20,	0x0,	//	4
	0x0,	0x4f,	0x89,	0x89,	0x89,	0x71,	0x0,	//	5
	0x0,	0x7e,	0x89,	0x89,	0x89,	0x72,	0x0,	//	6
	0x0,	0x1,	0xe1,	0x19,	0x5,	0x3,	0x0,	//	7
	0x0,	0x76,	0x89,	0x89,	0x89,	0x76,	0x0,	//	8
	0x0,	0x4e,	0x91,	0x91,	0x91,	0x7e,	0x0,	//	9
	0x0,	0x0,	0x0,	0x84,	0x0,	0x0,	0x0,	//	:
	0x0,	0x0,	0x0,	0x388,	0x0,	0x0,	0x0,	//	;
	0x0,	0x10,	0x28,	0x28,	0x44,	0x44,	0x0,	//	<
	0x0,	0x28,	0x28,	0x28,	0x28,	0x28,	0x0,	//	=
	0x0,	0x44,	0x44,	0x28,	0x28,	0x10,	0x0,	//	>
	0x0,	0x2,	0x1,	0xb1,	0x9,	0x6,	0x0,	//	?
	0x0,	0x7e,	0x81,	0x99,	0x95,	0x1e,	0x0,	//	@
	0x0,	0xe0,	0x3e,	0x21,	0x3e,	0xe0,	0x0,	//	A
	0x0,	0xff,	0x89,	0x89,	0x89,	0x76,	0x0,	//	B
	0x0,	0x7e,	0x81,	0x81,	0x81,	0x42,	0x0,	//	C
	0x0,	0xff,	0x81,	0x81,	0x42,	0x3c,	0x0,	//	D
	0x0,	0xff,	0x89,	0x89,	0x89,	0x89,	0x0,	//	E
	0x0,	0xff,	0x9,	0x9,	0x9,	0x1,	0x0,	//	F
	0x0,	0x7e,	0x81,	0x91,	0x91,	0x72,	0x0,	//	G
	0x0,	0xff,	0x8,	0x8,	0x8,	0xff,	0x0,	//	H
	0x0,	0x0,	0x81,	0xff,	0x81,	0x0,	0x0,	//	I
	0x0,	0x40,	0x80,	0x80,	0x80,	0x7f,	0x0,	//	J
	0x0,	0xff,	0x8,	0x14,	0x62,	0x81,	0x0,	//	K
	0x0,	0xff,	0x80,	0x80,	0x80,	0x80,	0x0,	//	L
	0x0,	0xff,	0x6,	0x8,	0x6,	0xff,	0x0,	//	M
	0x0,	0xff,	0x6,	0x18,	0x60,	0xff,	0x0,	//	N
	0x0,	0x7e,	0x81,	0x81,	0x81,	0x7e,	0x0,	//	O
	0x0,	0xff,	0x11,	0x11,	0x11,	0xe,	0x0,	//	P
	0x0,	0x7e,	0x81,	0xc1,	0x81,	0x17e,	0x0,	//	Q
	0x0,	0xff,	0x11,	0x11,	0x71,	0x8e,	0x0,	//	R
	0x0,	0x46,	0x89,	0x89,	0x91,	0x62,	0x0,	//	S
	0x0,	0x1,	0x1,	0xff,	0x1,	0x1,	0x0,	//	T
	0x0,	0x7f,	0x80,	0x80,	0x80,	0x7f,	0x0,	//	U
	0x0,	0x7,	0x38,	0xc0,	0x38,	0x7,	0x0,	//	V
	0x0,	0x3f,	0xe0,	0x1c,	0xe0,	0x3f,	0x0,	//	W
	0x0,	0x81,	0x66,	0x18,	0x66,	0x81,	0x0,	//	X
	0x0,	0x3,	0xc,	0xf0,	0xc,	0x3,	0x0,	//	Y
	0x0,	0xc1,	0xa1,	0x99,	0x85,	0x83,	0x0,	//	Z
	0x0,	0x0,	0x0,	0x3ff,	0x201,	0x0,	0x0,	//	[
	0x0,	0x0,	0x3,	0x3c,	0xc0,	0x0,	0x0,	//	/*\*/
	0x0,	0x0,	0x201,	0x3ff,	0x0,	0x0,	0x0,	//	]
	0x0,	0x8,	0x6,	0x1,	0x6,	0x8,	0x0,	//	^
	0x200,	0x200,	0x200,	0x200,	0x200,	0x200,	0x200,	//	_
	0x0,	0x0,	0x1,	0x2,	0x0,	0x0,	0x0,	//	`
	0x0,	0x68,	0x94,	0x94,	0x54,	0xf8,	0x0,	//	a
	0x0,	0xff,	0x48,	0x84,	0x84,	0x78,	0x0,	//	b
	0x0,	0x78,	0x84,	0x84,	0x84,	0x48,	0x0,	//	c
	0x0,	0x78,	0x84,	0x84,	0x48,	0xff,	0x0,	//	d
	0x0,	0x78,	0x94,	0x94,	0x94,	0x58,	0x0,	//	e
	0x0,	0x4,	0x4,	0xfe,	0x5,	0x5,	0x0,	//	f
	0x0,	0x278,	0x284,	0x284,	0x248,	0x1fc,	0x0,	//	g
	0x0,	0xff,	0x8,	0x4,	0x4,	0xf8,	0x0,	//	h
	0x0,	0x4,	0x4,	0xfd,	0x0,	0x0,	0x0,	//	i
	0x200,	0x204,	0x204,	0x1fd,	0x0,	0x0,	0x0,	//	j
	0x0,	0xff,	0x10,	0x28,	0x44,	0x80,	0x0,	//	k
	0x0,	0x1,	0x1,	0xff,	0x0,	0x0,	0x0,	//	l
	0x0,	0xfc,	0x4,	0xfc,	0x4,	0xf8,	0x0,	//	m
	0x0,	0xfc,	0x8,	0x4,	0x4,	0xf8,	0x0,	//	n
	0x0,	0x78,	0x84,	0x84,	0x84,	0x78,	0x0,	//	o
	0x0,	0x3fc,	0x48,	0x84,	0x84,	0x78,	0x0,	//	p
	0x0,	0x78,	0x84,	0x84,	0x48,	0x3fc,	0x0,	//	q
	0x0,	0xfc,	0x8,	0x4,	0x4,	0x8,	0x0,	//	r
	0x0,	0x48,	0x94,	0x94,	0xa4,	0x48,	0x0,	//	s
	0x0,	0x4,	0x7f,	0x84,	0x84,	0x0,	0x0,	//	t
	0x0,	0x7c,	0x80,	0x80,	0x40,	0xfc,	0x0,	//	u
	0x0,	0xc,	0x70,	0x80,	0x70,	0xc,	0x0,	//	v
	0x0,	0x3c,	0xe0,	0x1c,	0xe0,	0x3c,	0x0,	//	w
	0x0,	0x84,	0x48,	0x30,	0x48,	0x84,	0x0,	//	x
	0x0,	0x20c,	0x230,	0x1c0,	0x30,	0xc,	0x0,	//	y
	0x0,	0xc4,	0xa4,	0x94,	0x8c,	0x84,	0x0,	//	z
	0x0,	0x0,	0x30,	0x3cf,	0x201,	0x0,	0x0,	//	{
	0x0,	0x0,	0x0,	0x3ff,	0x0,	0x0,	0x0,	//	|
	0x0,	0x0,	0x201,	0x3cf,	0x30,	0x0,	0x0,	//	}
	0x0,	0x18,	0x8,	0x8,	0x10,	0x18,	0x0,	//	~
};
static uint32_t Font11x18[] = {
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	//	 
	0x0,	0x0,	0x0,	0x0,	0x6ffe,	0x6ffe,	0x0,	0x0,	0x0,	0x0,	0x0,	//	!
	0x0,	0x0,	0x0,	0x3e,	0x3e,	0x0,	0x3e,	0x3e,	0x0,	0x0,	0x0,	//	"
	0x0,	0x660,	0x7f60,	0x7ffe,	0x6fe,	0x660,	0x7f60,	0x7ffe,	0x6fe,	0x660,	0x0,	//	#
	0x0,	0x1c38,	0x3c7c,	0x70ee,	0x60c6,	0x1fffe,	0x6186,	0x3f1c,	0x1e18,	0x0,	0x0,	//	$
	0x3c,	0x187e,	0xc42,	0x67e,	0x33c,	0x3d80,	0x7ec0,	0x4260,	0x7e30,	0x3c18,	0x0,	//	%
	0x0,	0x1e00,	0x3f3c,	0x617e,	0x61c6,	0x63c6,	0x367e,	0x1c3c,	0x7f00,	0x2300,	0x0,	//	&
	0x0,	0x0,	0x0,	0x0,	0x3e,	0x3e,	0x0,	0x0,	0x0,	0x0,	0x0,	//	'
	0x0,	0x0,	0x0,	0x0,	0xfc0,	0x7ff8,	0xe01c,	0x18006,	0x20001,	0x0,	0x0,	//	(
	0x0,	0x0,	0x20001,	0x18006,	0xe01c,	0x7ff8,	0xfc0,	0x0,	0x0,	0x0,	0x0,	//	)
	0x0,	0x0,	0x2c,	0x38,	0x1e,	0x1e,	0x38,	0x2c,	0x0,	0x0,	0x0,	//	*
	0x180,	0x180,	0x180,	0x180,	0x1ff8,	0x1ff8,	0x180,	0x180,	0x180,	0x180,	0x0,	//	+
	0x0,	0x0,	0x0,	0x0,	0x26000,	0x1e000,	0x0,	0x0,	0x0,	0x0,	0x0,	//	,
	0x0,	0x0,	0x0,	0x600,	0x600,	0x600,	0x600,	0x0,	0x0,	0x0,	0x0,	//	-
	0x0,	0x0,	0x0,	0x0,	0x6000,	0x6000,	0x0,	0x0,	0x0,	0x0,	0x0,	//	.
	0x0,	0x0,	0x0,	0x7000,	0x7f00,	0xff0,	0xfe,	0xe,	0x0,	0x0,	0x0,	//	/
	0x0,	0xff0,	0x3ffc,	0x700e,	0x6186,	0x6186,	0x700e,	0x3ffc,	0xff0,	0x0,	0x0,	//	0
	0x0,	0x0,	0x30,	0x18,	0xc,	0x7ffe,	0x7ffe,	0x0,	0x0,	0x0,	0x0,	//	1
	0x0,	0x7038,	0x783c,	0x6c0e,	0x6606,	0x6306,	0x618e,	0x60fc,	0x6078,	0x0,	0x0,	//	2
	0x0,	0x1818,	0x381c,	0x7006,	0x60c6,	0x60c6,	0x71fc,	0x3f38,	0x1e00,	0x0,	0x0,	//	3
	0x0,	0xe00,	0xf80,	0xdf0,	0xc3c,	0x7ffe,	0x7ffe,	0xc00,	0xc00,	0x0,	0x0,	//	4
	0x0,	0x19fe,	0x39fe,	0x7086,	0x60c6,	0x60c6,	0x71c6,	0x3f86,	0x1f00,	0x0,	0x0,	//	5
	0x0,	0xff0,	0x3ffc,	0x718e,	0x60c6,	0x60c6,	0x71ce,	0x3f9c,	0x1f18,	0x0,	0x0,	//	6
	0x0,	0x6,	0x6,	0x7006,	0x7f06,	0x7c6,	0xf6,	0x3e,	0xe,	0x0,	0x0,	//	7
	0x0,	0x1e38,	0x3f7c,	0x6186,	0x6186,	0x6186,	0x618e,	0x3f7c,	0x1e38,	0x0,	0x0,	//	8
	0x0,	0x18f8,	0x39fc,	0x738e,	0x6306,	0x6306,	0x718e,	0x3ffc,	0xff0,	0x0,	0x0,	//	9
	0x0,	0x0,	0x0,	0x0,	0x6060,	0x6060,	0x0,	0x0,	0x0,	0x0,	0x0,	//	:
	0x0,	0x0,	0x0,	0x0,	0x260c0,	0x1e0c0,	0x0,	0x0,	0x0,	0x0,	0x0,	//	;
	0x0,	0x100,	0x380,	0x280,	0x6c0,	0x440,	0xc60,	0x820,	0x1830,	0x0,	0x0,	//	<
	0x0,	0x660,	0x660,	0x660,	0x660,	0x660,	0x660,	0x660,	0x660,	0x0,	0x0,	//	=
	0x0,	0x1830,	0x820,	0xc60,	0x440,	0x6c0,	0x280,	0x380,	0x100,	0x0,	0x0,	//	>
	0x0,	0x18,	0x1c,	0xe,	0x6e06,	0x6f06,	0x386,	0x1ce,	0xfc,	0x78,	0x0,	//	?
	0x0,	0xff0,	0x3ffc,	0x701e,	0x63c6,	0x67c6,	0x3666,	0x7fc,	0x7f8,	0x0,	0x0,	//	@
	0x0,	0x7000,	0x7f80,	0xff8,	0x67e,	0x606,	0x67e,	0xff8,	0x7f80,	0x7000,	0x0,	//	A
	0x0,	0x7ffe,	0x7ffe,	0x6186,	0x6186,	0x6186,	0x73fc,	0x3e78,	0x1c00,	0x0,	0x0,	//	B
	0x0,	0xff0,	0x3ffc,	0x700e,	0x6006,	0x6006,	0x6006,	0x381c,	0x1818,	0x0,	0x0,	//	C
	0x0,	0x7ffe,	0x7ffe,	0x6006,	0x6006,	0x6006,	0x381c,	0x1ffc,	0x7f0,	0x0,	0x0,	//	D
	0x0,	0x7ffe,	0x7ffe,	0x6186,	0x6186,	0x6186,	0x6186,	0x6186,	0x6006,	0x0,	0x0,	//	E
	0x0,	0x7ffe,	0x7ffe,	0x186,	0x186,	0x186,	0x186,	0x186,	0x6,	0x0,	0x0,	//	F
	0x0,	0xff0,	0x3ffc,	0x700e,	0x6006,	0x6006,	0x6306,	0x3f1c,	0x3f18,	0x0,	0x0,	//	G
	0x0,	0x7ffe,	0x7ffe,	0x180,	0x180,	0x180,	0x180,	0x7ffe,	0x7ffe,	0x0,	0x0,	//	H
	0x0,	0x0,	0x6006,	0x6006,	0x7ffe,	0x7ffe,	0x6006,	0x6006,	0x0,	0x0,	0x0,	//	I
	0x0,	0x1c00,	0x3c00,	0x7000,	0x6000,	0x6000,	0x7000,	0x3ffe,	0x1ffe,	0x0,	0x0,	//	J
	0x0,	0x7ffe,	0x7ffe,	0x180,	0x1c0,	0x770,	0xe38,	0x380c,	0x7006,	0x4002,	0x0,	//	K
	0x0,	0x7ffe,	0x7ffe,	0x6000,	0x6000,	0x6000,	0x6000,	0x6000,	0x6000,	0x0,	0x0,	//	L
	0x0,	0x7ffe,	0x7ffe,	0x1e,	0xf8,	0x180,	0xf8,	0xe,	0x7ffe,	0x7ffe,	0x0,	//	M
	0x0,	0x7ffe,	0x7ffe,	0x3e,	0x1f8,	0x1fc0,	0x7c00,	0x7ffe,	0x7ffe,	0x0,	0x0,	//	N
	0x0,	0xff0,	0x3ffc,	0x700e,	0x6006,	0x6006,	0x700e,	0x3ffc,	0xff0,	0x0,	0x0,	//	O
	0x0,	0x7ffe,	0x7ffe,	0x306,	0x306,	0x306,	0x38e,	0x1fc,	0xf8,	0x0,	0x0,	//	P
	0x0,	0xff0,	0x3ffc,	0x700e,	0x6006,	0x6c06,	0x780e,	0x3ffc,	0x2ff0,	0x4000,	0x0,	//	Q
	0x0,	0x7ffe,	0x7ffe,	0x186,	0x186,	0x386,	0xfce,	0x3cfc,	0x7078,	0x4000,	0x0,	//	R
	0x0,	0xc00,	0x3c78,	0x70fc,	0x60c6,	0x6186,	0x6386,	0x3f1c,	0x1e18,	0x0,	0x0,	//	S
	0x6,	0x6,	0x6,	0x6,	0x7ffe,	0x7ffe,	0x6,	0x6,	0x6,	0x6,	0x0,	//	T
	0x0,	0x1ffe,	0x3ffe,	0x7000,	0x6000,	0x6000,	0x7000,	0x3ffe,	0x1ffe,	0x0,	0x0,	//	U
	0x0,	0xe,	0x7e,	0x7f0,	0x3f80,	0x7800,	0x3f80,	0x7f0,	0x7e,	0xe,	0x0,	//	V
	0x7e,	0x7ffe,	0x7000,	0x1e00,	0x3c0,	0x3c0,	0x1e00,	0x7000,	0x7ffe,	0x7e,	0x0,	//	W
	0x4002,	0x700e,	0x383c,	0x1e70,	0xfe0,	0x7c0,	0xe70,	0x3c38,	0x700e,	0x4002,	0x0,	//	X
	0x2,	0xe,	0x3c,	0xf0,	0x7fc0,	0x7fc0,	0xf0,	0x3c,	0xe,	0x2,	0x0,	//	Y
	0x0,	0x7000,	0x7806,	0x6e06,	0x6786,	0x61c6,	0x6076,	0x603e,	0x600e,	0x0,	0x0,	//	Z
	0x0,	0x0,	0x0,	0x0,	0x3ffff,	0x3ffff,	0x30003,	0x30003,	0x0,	0x0,	0x0,	//	[
	0x0,	0x0,	0x0,	0xe,	0xfe,	0xff0,	0x7f00,	0x7000,	0x0,	0x0,	0x0,	//	/*\*/
	0x0,	0x0,	0x0,	0x30003,	0x30003,	0x3ffff,	0x3ffff,	0x0,	0x0,	0x0,	0x0,	//	]
	0x0,	0x180,	0x1e0,	0x78,	0xe,	0xe,	0x78,	0x1e0,	0x180,	0x0,	0x0,	//	^
	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	0x10000,	//	_
	0x0,	0x0,	0x2,	0x6,	0xe,	0x8,	0x0,	0x0,	0x0,	0x0,	0x0,	//	`
	0x0,	0x3880,	0x7cc0,	0x6660,	0x6660,	0x2660,	0x3660,	0x3fe0,	0x7fc0,	0x4000,	0x0,	//	a
	0x0,	0x7ffe,	0x7ffe,	0x30c0,	0x6060,	0x6060,	0x70e0,	0x3fc0,	0x1f80,	0x0,	0x0,	//	b
	0x0,	0x1f80,	0x3fc0,	0x70e0,	0x6060,	0x6060,	0x70e0,	0x39c0,	0x1980,	0x0,	0x0,	//	c
	0x0,	0x1f80,	0x3fc0,	0x70e0,	0x6060,	0x6060,	0x30c0,	0x7ffe,	0x7ffe,	0x0,	0x0,	//	d
	0x0,	0x1f80,	0x3fc0,	0x76e0,	0x6660,	0x6660,	0x66e0,	0x37c0,	0x1700,	0x0,	0x0,	//	e
	0x0,	0x60,	0x60,	0x60,	0x7ffc,	0x7ffe,	0x66,	0x66,	0x66,	0x6,	0x0,	//	f
	0x0,	0x18fc0,	0x39fe0,	0x33870,	0x33030,	0x33030,	0x39860,	0x1fff0,	0xfff0,	0x0,	0x0,	//	g
	0x0,	0x7ffe,	0x7ffe,	0xc0,	0x60,	0x60,	0x60,	0x7fe0,	0x7fc0,	0x0,	0x0,	//	h
	0x0,	0x0,	0x60,	0x60,	0x60,	0x7fe6,	0x7fe6,	0x0,	0x0,	0x0,	0x0,	//	i
	0x0,	0x18000,	0x30030,	0x30030,	0x30030,	0x3fff3,	0x1fff3,	0x0,	0x0,	0x0,	0x0,	//	j
	0x0,	0x7ffe,	0x7ffe,	0x600,	0x300,	0x780,	0x1cc0,	0x3860,	0x6020,	0x4000,	0x0,	//	k
	0x0,	0x0,	0x6,	0x6,	0x6,	0x7ffe,	0x7ffe,	0x0,	0x0,	0x0,	0x0,	//	l
	0x7fe0,	0x7fe0,	0x40,	0x60,	0x7fe0,	0x7fe0,	0xc0,	0x60,	0x7fe0,	0x7fc0,	0x0,	//	m
	0x0,	0x7fe0,	0x7fe0,	0xc0,	0x60,	0x60,	0x60,	0x7fe0,	0x7fc0,	0x0,	0x0,	//	n
	0x0,	0x1f80,	0x3fc0,	0x70e0,	0x6060,	0x6060,	0x70e0,	0x3fc0,	0x1f80,	0x0,	0x0,	//	o
	0x0,	0x3fff0,	0x3fff0,	0x1860,	0x3030,	0x3030,	0x3870,	0x1fe0,	0xfc0,	0x0,	0x0,	//	p
	0x0,	0xfc0,	0x1fe0,	0x3870,	0x3030,	0x3030,	0x1860,	0x3fff0,	0x3fff0,	0x0,	0x0,	//	q
	0x0,	0x20,	0x7fe0,	0x7fc0,	0xc0,	0x60,	0x60,	0xe0,	0x40,	0x0,	0x0,	//	r
	0x0,	0x3380,	0x37c0,	0x6660,	0x6660,	0x6660,	0x6660,	0x3ec0,	0x1cc0,	0x0,	0x0,	//	s
	0x0,	0x60,	0x60,	0x3ff8,	0x7ffc,	0x6060,	0x6060,	0x6060,	0x6000,	0x0,	0x0,	//	t
	0x0,	0x3fe0,	0x7fe0,	0x6000,	0x6000,	0x6000,	0x3000,	0x7fe0,	0x7fe0,	0x0,	0x0,	//	u
	0x0,	0x20,	0x1e0,	0xfc0,	0x3e00,	0x7000,	0x7e00,	0xfc0,	0x1e0,	0x20,	0x0,	//	v
	0xe0,	0x1fe0,	0x7800,	0x1fe0,	0xe0,	0x1fe0,	0x7800,	0x1fe0,	0xe0,	0x0,	0x0,	//	w
	0x0,	0x4020,	0x70e0,	0x39c0,	0xf00,	0xf00,	0x39c0,	0x70e0,	0x4020,	0x0,	0x0,	//	x
	0x0,	0x30030,	0x301f0,	0x38fc0,	0x1fe00,	0x1f000,	0x7f80,	0xff0,	0x70,	0x0,	0x0,	//	y
	0x0,	0x6060,	0x7060,	0x7860,	0x6c60,	0x6660,	0x6360,	0x61e0,	0x60e0,	0x6060,	0x0,	//	z
	0x0,	0x0,	0x0,	0x300,	0x780,	0x1fffe,	0x3fcff,	0x30003,	0x30003,	0x0,	0x0,	//	{
	0x0,	0x0,	0x0,	0x0,	0x0,	0x3ffff,	0x3ffff,	0x0,	0x0,	0x0,	0x0,	//	|
	0x0,	0x0,	0x30003,	0x30003,	0x3fcff,	0x1fffe,	0x780,	0x300,	0x0,	0x0,	0x0,	//	}
	0x0,	0x300,	0x180,	0x180,	0x180,	0x300,	0x300,	0x300,	0x180,	0x0,	0x0	//	~
};

#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"
#include "cstring"
#include "string.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"

FATFS fs;  // file system
FIL fil; // File
FRESULT fresult;  // result
FILINFO fno;
UINT br, bw;  // File read/write count

void Fonts::send_uart (char *string)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen (string), HAL_MAX_DELAY);  //TODO change uart
}

void Fonts::createFont11x18() {
	this->width = 11;
	this->height = 18;
	Font_11x18 = new Letter * [95];
	for (uint8_t i = 0; i < 95; i++) {
		Font_11x18[i] = new Letter(&Font11x18[i * width], height, width);
	}	
}

void Fonts::createFont6x8() {
	this->width = 6;
	this->height = 8;
	Font_6x8 = new Letter* [95];
	for (uint8_t i = 0; i < 95; i++) {
		Font_6x8[i] = new Letter(&Font6x8[i * width], height, width);
	}
}

void Fonts::createFont7x10() {
	char* read_data;
	char name[20];
	uint32_t size;
	uint8_t width=7;
	uint8_t height=10;
	sprintf(name, "Font7x10.txt");
	fresult = f_mount(&fs, (const TCHAR*)"/", 1);
	if (fresult != FR_OK)
		send_uart ("ERROR!!! in mounting SD CARD...\n\n");
	else
		send_uart("SD CARD mounted successfully...\n");
	fresult = f_stat (name, &fno);
	if (fresult != FR_OK)
		send_uart ("ERRROR!!! file does not exists\n\n");
	else {
		fresult = f_open(&fil, name, FA_READ);		/* Open file to read */
		if (fresult != FR_OK)
			send_uart ("ERROR!!! File not opened...\n\n");
		size = f_size(&fil);
	  	read_data = (char*)malloc(size);
	  	fresult = f_read (&fil,read_data, size, &br);	  	//Read data from the file

	  	char *buf = (char*)malloc(100*sizeof(char));
	  	sprintf(buf, "%s", read_data);
	  	send_uart(buf);
	  	free(buf);
	  	if (fresult != FR_OK) {
	 		free(read_data);
	 		send_uart ("ERROR!!! Problem with reading...\n\n");
		}

  		else  {
  			free(read_data);
	  		/* Close file */
  			fresult = f_close(&fil);
  			if (fresult != FR_OK)
  				send_uart ("ERROR!!! not closed...\n\n");
	  		else
	  			send_uart ("ERROR!!! closed succesfully...\n\n");
	  	}
	}
	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	if (fresult == FR_OK) send_uart ("SD CARD UNMOUNTED successfully...\n\n\n");
	else send_uart("ERROR!!! in UNMOUNTING SD CARD\n\n\n");;

	this->width = 7;
	this->height = 10;
	Font_7x10 = new Letter* [95];
	for (uint8_t i = 0; i < 95; i++) {
		Font_7x10[i] = new Letter(&Font7x10[i * width], height, width);
	}
}

uint32_t* Fonts::getLetter(uint8_t letter) {
	if (this->height == 8)
		return Font_6x8[letter - 32]->getLetter();
	else if (this->height == 10)
		return Font_7x10[letter - 32]->getLetter();
	else if (this->height == 18)
		return Font_11x18[letter - 32]->getLetter();
}

uint8_t Fonts::getWidth() {
	return this->width;
}

uint8_t Fonts::getHeight() {
	return this->height;
}
