#pragma once

#include <Mmsystem.h>
#include <al.h>
//#include <mciapi.h>
/*	PlaySound("01_FRIENDS.wav",NULL,SND_FILENAME);
	mciSendString("open \"01_FRIENDS .flac\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);*/

class RG_AudioPlayer{
//  RG_Array<thread> AudioThreads;
    //WAVEFORMATEX Audio;

public:
  void play_wav(string path){
    
  }

  void play_other(string path){

  }


  /*void clean(){
    for(int i = 0; i< AudioThreads.size();i++){
      AudioThreads[i].join();
    }
  }
  ~RG_AudioPlayer(){
    clean();
  }*/
};