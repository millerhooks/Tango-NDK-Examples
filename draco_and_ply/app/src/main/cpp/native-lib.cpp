#include <jni.h>
#include "DracoPly.h"

static draco::DracoPly app;

#ifdef __cplusplus
extern "C" {
#endif

/* Format:
 JNIEXPORT < Return_Type > JNICALL
 < Package_Name + Java_Class_Name + Function_Name > (
    JNIEnv* env, jobject obj, < Parameter_of_Native_Function > , ...
 )
*/

JNIEXPORT void JNICALL
Java_com_spencerfricke_draco_1and_1ply_TangoJniNative_onCreate(
    JNIEnv* env, jobject, jobject caller_activity) {
  app.OnCreate(env, caller_activity);
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_draco_1and_1ply_TangoJniNative_onTangoServiceConnected(
    JNIEnv* env, jobject, jobject iBinder) {
  app.OnTangoServiceConnected(env, iBinder);
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_draco_1and_1ply_TangoJniNative_onPause(
    JNIEnv*, jobject) {
  app.OnPause();
}

static bool set_file_name_already = false;

JNIEXPORT jstring JNICALL
Java_com_spencerfricke_draco_1and_1ply_TangoJniNative_getPointCloudSingleFrame(
    JNIEnv* env, jobject, jstring directory_path) {

  const char* internalStoragePath = env->GetStringUTFChars(directory_path, 0);

  if (set_file_name_already == false) {
    app.SetSaveFileDirectory(internalStoragePath);
    set_file_name_already = true;
  }

  app.SetFrameCount(10);

  return env->NewStringUTF(internalStoragePath);
}

#ifdef __cplusplus
}
#endif
