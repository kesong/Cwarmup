package com.song.player;

class PlayerMain{

  PlayerMain(){}
  

  public static void main(String[] argv){

    Team bulls = new Team("Bulls", "Chicago");
    Player jordan = new Player("Jordan", 23, 3000, bulls);

    Team lakers = new Team("Lakers", "Los Angeles");
    Player paul = new Player("Paul", 6, 5000, lakers);

    Team suns = new Team("Suns", "Phx");
    
    jordan.printPlayer();

    paul.changeTeam(suns);
    paul.printPlayer();

    jordan.printPlayerInfor(jordan);
  }
}
