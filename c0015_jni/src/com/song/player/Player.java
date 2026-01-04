package com.song.player;

class Player {
  String name;
  int number;
  int salary;
  Team team;
  
  // 编译jni下面的c文件生成共享库的名字叫做libplayer.so，在Linux中，加载so文件的时候不需要前面的lib,也不需要文件名.so
  // 所以这里加载so库文件的时候，只需要player就行了
  static{
    System.loadLibrary("player");
  }

  public native void printPlayerInfor(Player player);

  Player(String name, int number, int salary, Team tm){
    this.name = name;
    this.number = number;
    this.salary = salary;
    this.team = tm;
  }

  void setName(String strName){
    this.name = strName;
  }

  String getName(){
    return this.name;
  }

  void setNumber(int iNum){
    this.number = iNum;
  }

  int getNumber(){
    return this.number;
  }

  void changeTeam(Team newTeam){
    this.team = newTeam;
  }

  void printPlayer(){
    System.out.println("Player name is " + this.name + " .");
    System.out.println("Number is " + this.number + " .");
    System.out.println("Salary is " + this.salary + " .");
    System.out.println("Team is " + team.tname + "locate in " + team.city);
  }

}
