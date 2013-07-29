// Copyright 2013 Software Freedom Conservancy
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WEBDRIVER_IE_PROXYMANAGER_H_
#define WEBDRIVER_IE_PROXYMANAGER_H_

#include <string>
#include "json.h"

namespace webdriver {

struct ProxySettings {
  bool use_per_process_proxy;
  std::string proxy_type;
  std::string http_proxy;
  std::string ftp_proxy;
  std::string ssl_proxy;
};

class ProxyManager {
 public:
  ProxyManager(void);
  virtual ~ProxyManager(void);

  void Initialize(ProxySettings settings);
  void SetProxySettings(HWND browser_window_handle);
  Json::Value GetProxyAsJson(void);

  bool is_proxy_set(void) const { return this->proxy_type_.size() > 0; }
  bool use_per_process_proxy(void) const { return this->use_per_process_proxy_; }

 private:
  void SetPerProcessProxySettings(HWND browser_window_handle);
  void SetGlobalProxySettings(void);
  void GetCurrentProxySettings(void);
  void GetCurrentProxyType(void);
  void RestoreProxySettings(void);

  std::wstring BuildProxySettingsString(void);

  static bool InstallWindowsHook(HWND window_handle);
  static void UninstallWindowsHook(void);

  unsigned long current_proxy_type_;
  unsigned long current_proxy_auto_detect_flags_;
  std::wstring current_autoconfig_url_;
  std::wstring current_proxy_server_;
  std::wstring current_proxy_bypass_list_;

  //std::string proxy_settings_;
  std::string proxy_type_;
  std::string http_proxy_;
  std::string ftp_proxy_;
  std::string ssl_proxy_;
  bool use_per_process_proxy_;
  bool is_proxy_modified_;
};

} // namespace webdriver

#endif // WEBDRIVER_IE_PROXYMANAGER_H_
