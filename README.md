# LinkIt7697_IOT_Smart_House
SmartIOT
* 該範例程式是針對各感測器讀取並顯示在OLED上，並具有雨水、火焰感測警報與黑夜自動照明功能。

SmartIOT_MCS
* 該範例程式需自行註冊並設定MCS，MCS依照下圖設定5個顯示項與3個控制項：

* 設定每個項目時都會設定各自的ID，將每個ID替換掉下列程式碼中的字串項
MCSDisplayInteger Data1("Data1");
MCSDisplayInteger Data2("Data2");
MCSDisplayInteger Data3("Data3");
MCSDisplayFloat Data4("Data4");
MCSDisplayInteger Data5("Data5");
MCSControllerInteger Slider1("Slider1");
MCSControllerInteger Slider2("Slider2");
MCSControllerInteger Slider3("Slider3");

* 在MCS新增測試裝置會獲得該裝置的device id與device key，將自己的device id與device key取代程式中MCSDevice mcs("D2OdLkjh", "bL6L0ie7nrDuBLiE");內的字串。
* 以及所使用的Wi-Fi SSID 填入char _lwifi_ssid[] = "MakerLab_2.4G";，密碼填入char _lwifi_pass[] = "53574722";。
