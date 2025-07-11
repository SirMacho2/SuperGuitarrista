.include "hdr.asm"

.section ".rodata1" superfree

tilfont:
.incbin "pvsneslibfont.pic"

palfont:
.incbin "pvsneslibfont.pal"

k7_patterns:
.incbin "res/bg/k7-d.pic"
k7_patterns_end:

creditos_patterns:
.incbin "res/bg/creditos-2.pic"
creditos_patterns_end:

.ends

.section ".rodata2" superfree

k7_map:
.incbin "res/bg/k7-d.map"
k7_map_end:

k7_palette:
.incbin "res/bg/k7-d.pal"
k7_palette_end:

creditos_map:
.incbin "res/bg/creditos-2.map"
creditos_map_end:

creditos_palette:
.incbin "res/bg/creditos-2.pal"
creditos_palette_end:

concert_map:
.incbin "res/bg/concert-2.map"
concert_map_end:

concert_palette:
.incbin "res/bg/concert-2.pal"
concert_palette_end:

bg_musica_map:
.incbin "res/bg/bg_musica-2.map"
bg_musica_map_end:

bg_musica_palette:
.incbin "res/bg/bg_musica-2.pal"
bg_musica_palette_end:

.ends

.section ".rodata3" superfree

concert_patterns:
.incbin "res/bg/concert-2.pic"
concert_patterns_end:

.ends

.section ".rodata4" superfree

bg_musica_patterns:
.incbin "res/bg/bg_musica-2.pic"
bg_musica_patterns_end:

.ends

.section ".rodata5" superfree

vu2_patterns:
.incbin "res/bt/vu-2.pic"
vu2_patterns_end:

vu2_palette:
.incbin "res/bt/vu-2.pal"
vu2_palette_end:

vu2_map:
.incbin "res/bt/vu-2.map"
vu2_map_end:

.ends


.section ".bts" superfree

bt_f1_gfx:
.incbin "res/bt/bt32x32.pic"
bt_f1_gfx_end:

bt_f1_pal:
.incbin "res/bt/bt32x32.pal"
bt_f1_pal_end:

bt_f2_pal:
.incbin "res/bt/amarelo.pal"
bt_f2_pal_end:

bt_f3_pal:
.incbin "res/bt/vermelho.pal"
bt_f3_pal_end:

.ends