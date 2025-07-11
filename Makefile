ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := SuperGuitarrista

all: bitmaps $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx

#---------------------------------------------------------------------------------
k7.pic: res/bg/k7-d.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCON V) -u 16 -o 16  -s 8 -e 0 -m -i $<

creditos.pic: res/bg/creditos-2.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCON V) -u 16 -o 16 -s 8 -e 0 -m -i $<

concert.pic: res/bg/concert-2.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCON V) -u 16 -o 16 -s 8 -e 0 -m -i $<

bg_musica.pic: res/bg/bg_musica-2.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCON V) -u 16 -o 16  -s 8 -e 0   -m -i $<

vu-2.pic: res/bt/vu-2.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCON V) -u 16 -o 16  -s 8 -e 0   -m -ip $<

pvsneslibfont.pic: pvsneslibfont.png
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -s 8 -o 16 -u 16 -e 0 -p -m -i $<

bt32x32.pic: res/bt/bt32x32.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -gs 32 -u 16 -o 16 -i $<

amarelo.pic: res/bt/amarelo.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -gs 32 -u 16 -o 16 -i $<

vermelho.pic: res/bt/vermelho.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -gs 32 -u 16 -o 16 -i $<



bitmaps : creditos.pic k7.pic concert.pic bg_musica.pic vu-2.pic pvsneslibfont.pic bt32x32.pic amarelo.pic vermelho.pic

