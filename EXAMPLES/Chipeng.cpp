/**
Demonstration of the chip engine of Pokitto
*/


#include "Pokitto.h"
#include "Synth.h"

Pokitto::Core game;
Pokitto::Display disp;
Pokitto::Sound snd;
Pokitto::Buttons btn;

int tonefreq=33;
uint8_t amplitude = 255;//127;
uint8_t wavetype = 1, arpmode=0;
uint32_t changed = 1;
char notestr[6];
uint8_t sbindx=0,sbx=0,prevy=0;

int main()
{
    game.begin();
    disp.persistence = true;
    disp.color=wavetype+1;
    disp.bgcolor=0;
    uint8_t sbindx=0;

    snd.playTone(1,tonefreq,amplitude,wavetype,arpmode);
    // want to have 2 oscillators 1 octave apart ?
    // snd.playTone(2,tonefreq+12,amplitude,wavetype,arpmode);

    disp.clear();
    disp.print("Frq: ");
    getNoteString(notestr,tonefreq);
    disp.println(notestr);
    disp.print("Vol: ");
    disp.println((int)amplitude);
    disp.print("Wav: ");
    disp.print((int)wavetype);
    switch (wavetype) {
    case 0:
        disp.println(" Off");break;
    case 1:
        disp.println(" Square");break;
    case 2:
        disp.println(" Saw");break;
    case 3:
        disp.println(" Triangle");break;
    case 4:
        disp.println(" Noise");break;
    case 5:
        disp.println(" SqNoise");break;
    }
    disp.print("Arp: ");
    disp.println((int)arpmode);
    disp.lcdRefresh(disp.screenbuffer);

    while (game.isRunning()) {

        #ifdef POK_SIM
            #define DEBOU 2048*32
        #else
            #define DEBOU 256
        #endif
        if (changed == 0) {
            if(btn.released(BTN_C)) { arpmode++; changed = DEBOU*15; }
            if (arpmode>MAX_ARPMODE) arpmode=0;
            if(btn.upBtn()) { amplitude++; changed = DEBOU; }
            if(btn.downBtn()) { amplitude--; changed = DEBOU; }
            if(btn.leftBtn() && (tonefreq > 0)) { tonefreq --; changed = DEBOU; }
            if(btn.rightBtn() &&  (tonefreq < 88)) { tonefreq ++; changed = DEBOU; }
            if(btn.released(BTN_A) && wavetype > 0 ) { wavetype--; changed = DEBOU*10;}
            if(btn.released(BTN_B) && wavetype < 5 ) { wavetype++; changed = DEBOU*10;}

            if (changed) {
                    disp.clear();
                    disp.color=0;//owavetype+1;
                    disp.fillRectangle(0,0,109,34);
                    disp.color=wavetype+1;
                    disp.bgcolor=0;
                    disp.print("Frq: ");
                    getNoteString(notestr,tonefreq);
                    disp.println(notestr);
                    disp.print("Vol: ");
                    disp.println((int)amplitude);
                    disp.print("Wav: ");
                    disp.print((int)wavetype);
                    switch (wavetype) {
                    case 0:
                        disp.println(" Off");break;
                    case 1:
                        disp.println(" Square");break;
                    case 2:
                        disp.println(" Saw");break;
                    case 3:
                        disp.println(" Triangle");break;
                    case 4:
                        disp.println(" Noise");break;
                    case 5:
                        disp.println(" SqNoise");break;
                    }
                    disp.print("Arp: ");
                    disp.println((int)arpmode);
                    snd.playTone(1,tonefreq,amplitude,wavetype,arpmode);
                    // want to have 2 oscillators 1 octave apart ?
                    // snd.playTone(2,tonefreq+12,amplitude,wavetype,arpmode);
            }
        } else changed--;
        disp.color=0;
        disp.drawColumn(sbx,42,88);
        disp.color=wavetype+1;
        uint8_t tindex = sbindx*2;
        uint8_t y = 63+(int8_t)(128-(soundbuf[tindex])>>3);
        disp.drawLine(sbx-1,prevy,sbx,y);
        game.update();
        disp.color=0;
        prevy=y;
        sbx++;sbindx++;
        if (sbx>109) {sbx=0;}
    }
}
