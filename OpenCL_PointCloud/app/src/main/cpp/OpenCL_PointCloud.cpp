#include "OpenCL_PointCloud.h"

// We can set a minimum version of tango for our application
constexpr int kTangoCoreMinimumVersion = 9377;

// prints to logcat the current cloud point data
void onPoseAvailable(void*, const TangoPoseData* pose) {
  LOGI("TEST: %f\t%f\%f", pose->translation[0], pose->translation[1], pose->translation[2]);
}


namespace PC {

  void OpenCL_PointCloud::OnCreate(JNIEnv* env, jobject caller_activity) {
    // Check the installed version of the TangoCore.  If it is too old, then
    // it will not support the most up to date features.
    int version = 0;
    TangoErrorType err =
        TangoSupport_GetTangoVersion(env, caller_activity, &version);

    LOGI("Our Tango Core Version: %d", version );

    if (err != TANGO_SUCCESS || version < kTangoCoreMinimumVersion) {
      LOGE("UI_Interface::CheckVersion, Tango Core version is out of date.");
      std::exit(EXIT_SUCCESS);
    }
  }

  void OpenCL_PointCloud::OnTangoServiceConnected(JNIEnv* env, jobject iBinder) {
    if (TangoService_setBinder(env, iBinder) != TANGO_SUCCESS) {
      LOGE("UI_Interface::ConnectTango, TangoService_setBinder error");
      std::exit(EXIT_SUCCESS);
    }

    // TANGO_CONFIG_DEFAULT is enabling Motion Tracking and disabling Depth
    // Perception.
    tango_config_ = TangoService_getConfig(TANGO_CONFIG_DEFAULT);
    if (tango_config_ == nullptr) {
      LOGE("UI_Interface::ConnectTango, TangoService_getConfig error.");
      std::exit(EXIT_SUCCESS);
    }

    // TangoCoordinateFramePair is used to tell Tango Service about the frame of
    // references that the applicaion would like to listen to.
    TangoCoordinateFramePair pair;
    pair.base = TANGO_COORDINATE_FRAME_START_OF_SERVICE;
    pair.target = TANGO_COORDINATE_FRAME_DEVICE;
    if (TangoService_connectOnPoseAvailable(1, &pair, onPoseAvailable) !=
        TANGO_SUCCESS) {
      LOGE("UI_Interface::ConnectTango, connectOnPoseAvailable error.");
      std::exit(EXIT_SUCCESS);
    }

    if (TangoService_connect(nullptr, tango_config_) != TANGO_SUCCESS) {
      LOGE("UI_Interface::ConnectTango, TangoService_connect error.");
      std::exit(EXIT_SUCCESS);
    }
  }

  void OpenCL_PointCloud::OnPause() {
    TangoConfig_free(tango_config_);
    tango_config_ = nullptr;
    TangoService_disconnect();
  }

}  // namespace PC