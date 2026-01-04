#include "log.h"
#include "print_player.h"
#include <jni.h>
#include <stdlib.h>

int call_Player_printPlayer(JNIEnv *env) { 
  // 构造C侧的数据，将数据发往java端
  Team *team = (Team *)malloc(sizeof(Team));
  team->tname = "warriors";
  team->city = "Golden State";

  Player *curry = (Player *)malloc(sizeof(Player));
  curry->pname = "Curry";
  curry->pnumber = 30;
  curry->salary = 6000;
  curry->tm = team;

  // Find Java classes
  jclass playerClass = (*env)->FindClass(env, "com/song/player/Player");
  if (playerClass == NULL) {
    log_i("Failed to find Player class");
    if ((*env)->ExceptionCheck(env)) {
      (*env)->ExceptionDescribe(env);
      (*env)->ExceptionClear(env);
    }
    return -1;
  }

  jclass teamClass = (*env)->FindClass(env, "com/song/player/Team");
  if (teamClass == NULL) {
    log_i("Failed to find Team class");
    return -1;
  }

  // Create Team object first
  jmethodID teamInitId = (*env)->GetMethodID(
      env, teamClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
  if (teamInitId == NULL) {
    log_i("Failed to find Team constructor");
    return -1;
  }

  // 为Team类的两个字段赋值
  jstring teamName = (*env)->NewStringUTF(env, curry->tm->tname);
  jstring cityName = (*env)->NewStringUTF(env, curry->tm->city);
  jobject teamObj =
      (*env)->NewObject(env, teamClass, teamInitId, teamName, cityName);

  // Now create Player object with correct signature
  // GetMethodID函数第三个参数<init>表示这是个构造器，按照java的方式构造一个Player类
  // GetMethodID最后一个参数就是Player类构造器的所有参数，在java中这个叫函数签名，这里列出的就是签名类型，四个参数分别是String，整型，整型，Team类型
  jmethodID playerInitId =
      (*env)->GetMethodID(env, playerClass, "<init>",
                          "(Ljava/lang/String;IILcom/song/player/Team;)V");
  if (playerInitId == NULL) {
    log_i("Failed to find Player constructor");
    return -1;
  }

  // 构造Player对象,为Player类输入对象
  jstring playerNameStr = (*env)->NewStringUTF(env, curry->pname);
  jobject obj = (*env)->NewObject(env, playerClass, playerInitId, playerNameStr,
                                  curry->pnumber, curry->salary, teamObj);

  // Clean up local references
  (*env)->DeleteLocalRef(env, playerNameStr);
  (*env)->DeleteLocalRef(env, teamName);
  (*env)->DeleteLocalRef(env, cityName);

  jmethodID methodId =
      (*env)->GetMethodID(env, playerClass, "printPlayer", "()V");
  if (methodId == NULL) {
    log_i("Failed to find printPlayer method");
    return -1;
  }
  (*env)->CallVoidMethod(env, obj, methodId);
}

int call_GetSystemProperties_printProperties(JNIEnv *jnienv) {
  jclass getSysPropClass =
      (*jnienv)->FindClass(jnienv, "com/song/player/GetSystemProperties");
  if (getSysPropClass == NULL) {
    return -1;
  }
  // 创建构造器，GetSystemProperties类没有构造器，java编译器会给他创建一个默认的无参构造器，这里也创建一个无参构造器。
  jmethodID emptyConstructor = (*jnienv)->GetMethodID(jnienv, getSysPropClass, "<init>", "()V");
  jobject obj = (*jnienv)->NewObject(jnienv, getSysPropClass, emptyConstructor);
  jmethodID print_prop =
      (*jnienv)->GetMethodID(jnienv, getSysPropClass, "printProperties", "()V");
  if(print_prop == NULL){
    return -1;
  }
  (*jnienv)->CallVoidMethod(jnienv, obj, print_prop);
}

int main(int argc, char **argv) {
  JavaVM *jvm = NULL;
  JNIEnv *env = NULL;
  JavaVMInitArgs vm_args = {0};
  JavaVMOption options[4] = {NULL};
  int res = 0;

  // java.class.path，指定为C语言调用的java方法所在java文件编译成class文件的路径
  options[0].optionString = "-Djava.compiler=NONE";
  options[1].optionString = "-Djava.class.path=build";
  options[2].optionString = "-Djava.library.path=build";

  vm_args.version = JNI_VERSION_1_6;
  vm_args.nOptions = 3;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = JNI_TRUE;

  res = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
  if (res == JNI_OK) {
    log_i("Java VM created successfully.");
  } else {
    log_i("Java VM creation failed with code: %d", res);
    return -1;
  }

  call_Player_printPlayer(env);
  
  call_GetSystemProperties_printProperties(env);

  (*jvm)->DestroyJavaVM(jvm);
}
