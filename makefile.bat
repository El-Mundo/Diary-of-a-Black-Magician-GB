set lcc=F:\EclipseWorkSpaceforC++\GameBoyWorkSapce\gbdk-2020\bin\lcc
set gbt=F:\EclipseWorkSpaceforC++\GameBoyWorkSapce\DEMO\Gameboy

lcc -Wa-l -Wl-m -Wl-j -c -o sky_bkg.o sky_bkg.c
lcc -Wa-l -Wl-m -Wl-j -c -o sprites.o sprites.c
lcc -Wa-l -Wl-m -Wl-j -c -o background.o background.c
lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -Wf-ba2 -c -o output.o output.c
lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
lcc -Wa-l -Wl-m -Wl-j -c -o gbt_player.o gbt\gbt_player.s
lcc -Wa-l -Wl-m -Wl-j -Wf-bo1 -c -o gbt_player_bank1.o gbt\gbt_player_bank1.s

lcc -Wa-l -Wl-m -Wl-j -Wl-yt2 -Wl-yo4 -Wl-ya4 -o Ahoutsukai_Nikki_GB.gb sky_bkg.o sprites.o background.o output.o main.o gbt_player.o gbt_player_bank1.o

del *.o *.lst *.sym *.map

pause
