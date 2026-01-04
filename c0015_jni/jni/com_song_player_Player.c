#include "com_song_player_Player.h"
#include "log.h"
#include "print_player.h"
#include <string.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_song_player_Player_printPlayerInfor(
    JNIEnv *env, jobject thisobj, jobject jplayer) {
  if (jplayer == NULL) {
    return;
  }

  Team *team = (Team *)malloc(sizeof(Team));
  if (team == NULL)
    return;
  memset(team, 0, sizeof(Team));

  Player *player = (Player *)malloc(sizeof(Player));
  if (player == NULL) {
    free(team);
    return;
  }
  memset(player, 0, sizeof(Player));

  jclass player_class = (*env)->GetObjectClass(env, jplayer);
  if (player_class == NULL) {
    free(team);
    free(player);
    return;
  }

  jfieldID name_field =
      (*env)->GetFieldID(env, player_class, "name", "Ljava/lang/String;");
  if (name_field == NULL) {
    free(team);
    free(player);
    return;
  }

  jobject name_obj = (*env)->GetObjectField(env, jplayer, name_field);
  const char *name = NULL;
  if (name_obj != NULL) {
    name = (*env)->GetStringUTFChars(env, name_obj, NULL);
  }

  jfieldID number_field = (*env)->GetFieldID(env, player_class, "number", "I");
  jint pnumber = 0;
  if (number_field != NULL) {
    pnumber = (*env)->GetIntField(env, jplayer, number_field);
  }

  jfieldID salary_field = (*env)->GetFieldID(env, player_class, "salary", "I");
  jint psalary = 0;
  if (salary_field != NULL) {
    psalary = (*env)->GetIntField(env, jplayer, salary_field);
  }

  // 这里的类型用的是java里面的Team类的名字，自定义的类型
  jfieldID team_field =
      (*env)->GetFieldID(env, player_class, "team", "Lcom/song/player/Team;");
  if (team_field == NULL) {
    if (name != NULL)
      (*env)->ReleaseStringUTFChars(env, name_obj, name);
    free(team);
    free(player);
    return;
  }

  jobject team_obj = (*env)->GetObjectField(env, jplayer, team_field);
  if (team_obj == NULL) {
    if (name != NULL)
      (*env)->ReleaseStringUTFChars(env, name_obj, name);
    free(team);
    free(player);
    return;
  }

  jclass team_class = (*env)->GetObjectClass(env, team_obj);
  if (team_class == NULL) {
    if (name != NULL)
      (*env)->ReleaseStringUTFChars(env, name_obj, name);
    free(team);
    free(player);
    return;
  }

  jfieldID tname_field =
      (*env)->GetFieldID(env, team_class, "tname", "Ljava/lang/String;");
  const char *tname = NULL;
  jobject tname_obj = NULL;
  if (tname_field != NULL) {
    tname_obj = (*env)->GetObjectField(env, team_obj, tname_field);
    if (tname_obj != NULL) {
      tname = (*env)->GetStringUTFChars(env, tname_obj, NULL);
    }
  }

  jfieldID city_field =
      (*env)->GetFieldID(env, team_class, "city", "Ljava/lang/String;");
  const char *city = NULL;
  jobject city_obj = NULL;
  if (city_field != NULL) {
    city_obj = (*env)->GetObjectField(env, team_obj, city_field);
    if (city_obj != NULL) {
      city = (*env)->GetStringUTFChars(env, city_obj, NULL);
    }
  }

  team->tname = (char *)tname;
  team->city = (char *)city;

  player->pname = (char *)name;
  player->pnumber = pnumber;
  player->salary = psalary;
  player->tm = team;

  print_player(player);

  // Clean up resources
  if (name != NULL)
    (*env)->ReleaseStringUTFChars(env, name_obj, name);
  if (tname != NULL)
    (*env)->ReleaseStringUTFChars(env, tname_obj, tname);
  if (city != NULL)
    (*env)->ReleaseStringUTFChars(env, city_obj, city);
  free(team);
  free(player);
}

void print_player(Player *ptr_player) {
  if (ptr_player == NULL) {
    return;
  }
  log_i("Player name is %s.", ptr_player->pname);
  log_i("number is %d.", ptr_player->pnumber);
  log_i("salary is %d.", ptr_player->salary);
  log_i("team is %s, locate in %s", ptr_player->tm->tname,
        ptr_player->tm->city);
}
