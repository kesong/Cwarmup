package com.song.player;

import java.lang.System;

class GetSystemProperties{

  void printProperties(){
    System.out.println("******Get system propterties as below:");
    System.out.println(System.getProperty("os.name"));
    System.out.println(System.getProperty("os.arch"));
    System.out.println(System.getProperty("os.version"));
    System.out.println(System.getProperty("java.library.path"));
    System.out.println(System.getProperty("user.name"));
    System.out.println(System.getProperty(("user.home")));
    System.out.println(System.getProperty("user.dir"));
  }
}
