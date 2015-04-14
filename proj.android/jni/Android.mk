LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/BGTTile.cpp \
                   ../../Classes/BGTMap.cpp \
                   ../../Classes/WaveManager.cpp \
                   ../../Classes/Wave.cpp \
                   ../../Classes/Troop.cpp \
                   ../../Classes/Util.cpp \
                   ../../Classes/UserData.cpp \
                   ../../Classes/GameManager.cpp \
                   ../../Classes/UILayer.cpp \
                   ../../Classes/BGTWorld.cpp \
                   ../../Classes/GameEntity.cpp \
                   ../../Classes/BGTWall.cpp \
                   ../../Classes/Character.cpp \
                   ../../Classes/GameEntityManager.cpp \
                   ../../Classes/MessageDispatcher.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/MoveState.cpp \
                   ../../Classes/StandState.cpp \
                   ../../Classes/AttackState.cpp \
                   ../../Classes/FallDownState.cpp \
                   ../../Classes/DizzyState.cpp \
                   ../../Classes/InjureState.cpp \
                   ../../Classes/StandUpState.cpp \
                   ../../Classes/StiffState.cpp \
                   ../../Classes/RollBackState.cpp \
                   ../../Classes/DieState.cpp \
                   ../../Classes/LieDownState.cpp \
                   ../../Classes/WeaponState.cpp \
                   ../../Classes/FlowState.cpp \
                   ../../Classes/Pistol.cpp \
                   ../../Classes/Knife.cpp \
                   ../../Classes/Weapon.cpp \
                   ../../Classes/LoadScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
