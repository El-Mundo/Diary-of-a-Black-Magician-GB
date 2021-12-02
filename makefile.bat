F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -c -o sky_bkg.o sky_bkg.c
F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -c -o sprites.o sprites.c
F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -c -o background.o background.c
F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -Wf-ba2 -c -o output.o output.c
F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -c -o gbt_player.o gbt_player.s
F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-bo1 -c -o gbt_player_bank1.o gbt_player_bank1.s

F:\EclipseWorkSpaceforC++\gbdk-2020-develop\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yt2 -Wl-yo4 -Wl-ya4 -o Ahoutsukai_Nikki_GB.gb sky_bkg.o sprites.o background.o output.o main.o gbt_player.o gbt_player_bank1.o

del *.o *.lst *.sym *.map

pause
