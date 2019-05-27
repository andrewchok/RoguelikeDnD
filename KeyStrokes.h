#pragma once
#ifndef KEYSTROKES
#define KEYSTROKES

// ^Letters (CTRL + letter char)
#define KEY_CTRL_A		1
#define KEY_CTRL_B		2
#define KEY_CTRL_C		3
#define KEY_CTRL_D		4
#define KEY_CTRL_E		5
#define KEY_CTRL_F		6 
#define KEY_CTRL_G		7
#define KEY_CTRL_H		8	// also KEY_BACKSPACE
#define KEY_CTRL_I		9	// also KEY_TAB
#define KEY_CTRL_J		10	// also EOF
#define KEY_CTRL_K		11
#define KEY_CTRL_L		12
#define KEY_CTRL_M		13
#define KEY_CTRL_N		14
#define KEY_CTRL_O		15
#define KEY_CTRL_P		16
#define KEY_CTRL_Q		17
#define KEY_CTRL_R		18
#define KEY_CTRL_S		19
#define KEY_CTRL_T		20
#define KEY_CTRL_U		21
#define KEY_CTRL_V		22
#define KEY_CTRL_W		23
#define KEY_CTRL_X		24 
#define KEY_CTRL_Y		25
#define KEY_CTRL_Z		26

// Special Character Keys
#define KEY_SPACE		32
#define KEY_ASTERISK	42
#define KEY_STAR		42
#define KEY_LESSTHAN	60
#define KEY_GREATERTHAN	62
#define KEY_QUESTION	63

// Digits
#define KEY_0			48
#define KEY_1			49
#define KEY_2			50
#define KEY_3			51
#define KEY_4			52
#define KEY_5			53
#define KEY_6			54
#define KEY_7			55
#define KEY_8			56
#define KEY_9			57

// Upper Case Letters (SHIFT + letter char)
#define KEY_A			65
#define KEY_B			66
#define KEY_C			67
#define KEY_D			68
#define KEY_E			69
#define KEY_F			70
#define KEY_G			71
#define KEY_H			72
#define KEY_I			73
#define KEY_J			74
#define KEY_K			75
#define KEY_L			76
#define KEY_M			77
#define KEY_N			78
#define KEY_O			79
#define KEY_P			80
#define KEY_Q			81
#define KEY_R			82
#define KEY_S			83
#define KEY_T			84
#define KEY_U			85
#define KEY_V			86
#define KEY_W			87
#define KEY_X			88 
#define KEY_Y			89
#define KEY_Z			90

// Lower Case Letters
#define KEY_a			97
#define KEY_b			98
#define KEY_c			99
#define KEY_d			100
#define KEY_e			101
#define KEY_f			102
#define KEY_g			103
#define KEY_h			104
#define KEY_i			105
#define KEY_j			106
#define KEY_k			107
#define KEY_l			108
#define KEY_m			109
#define KEY_n			110
#define KEY_o			111
#define KEY_p			112
#define KEY_q			113
#define KEY_r			114
#define KEY_s			115
#define KEY_t			116
#define KEY_u			117
#define KEY_v			118
#define KEY_w			119
#define KEY_x			120
#define KEY_y			121
#define KEY_z			122

// Branch into additional getchar() check
#define KEY_BRANCH_244	224
#define KEY_BRANCH_0	0

// Special Keys after (KEY_BRANCH_244 || KEY_BRANCH_0)
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_F11			133
#define KEY_F12			134

#define KEY_ARROW_UP	72
#define KEY_ARROW_LEFT	75
#define KEY_ARROW_RIGHT	77
#define KEY_ARROW_DOWN	80

#define KEY_HOME		71
#define KEY_PGUP		73
#define KEY_PAGEUP		73
#define KEY_END			79
#define KEY_PGDN		81
#define KEY_PAGEDOWN	81

#endif


