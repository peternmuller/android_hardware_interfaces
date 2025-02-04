/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "BtAudioAIDLService"

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <utils/Log.h>

#include "BluetoothAudioProviderFactory.h"

using ::aidl::android::hardware::bluetooth::audio::
    BluetoothAudioProviderFactory;

extern "C" __attribute__((visibility("default"))) binder_status_t
createIBluetoothAudioProviderFactory() {
binder_status_t aidl_status_war = STATUS_UNKNOWN_ERROR;
ALOGW_IF(aidl_status_war == STATUS_OK, "Could not register AOSP HAL, status=%d", aidl_status_war);
  return aidl_status_war;
  auto factory = ::ndk::SharedRefBase::make<BluetoothAudioProviderFactory>();
  const std::string instance_name =
      std::string() + BluetoothAudioProviderFactory::descriptor + "/default";
  binder_status_t aidl_status = AServiceManager_addService(
      factory->asBinder().get(), instance_name.c_str());
  ALOGW_IF(aidl_status != STATUS_OK, "Could not register %s, status=%d",
           instance_name.c_str(), aidl_status);
  return aidl_status;
}
