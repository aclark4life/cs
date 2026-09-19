; screen.h

;SCREEN_CURSOR_ON	equ	???
;SCREEN_CURSOR_OFF	equ	???
SCREEN_WIDTH		equ	80

SCREEN_TEXT_MODE	equ	03H
SCREEN_GRAPHICS_MODE	equ	06H
SCREEN_GRAPHICS_WIDTH	equ	640
SCREEN_GRAPHICS_HEIGHT	equ	200

	extrn	screen_set_mode:near
	extrn	screen_get_cursor_location:near
	extrn	screen_locate:near
	extrn	screen_read_char:near
	extrn	screen_write_char:near
	extrn	screen_clear_window:near
;	extrn	screen_clear:near
	extrn	screen_write_dot:near
;	extrn	screen_cursor_mode:near
