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

btY_gfx:
.incbin "res/bt/bt0.pic"
btY_gfx_end:

btY_pal:
.incbin "res/bt/bt0.pal"
btY_pal_end:

.ends