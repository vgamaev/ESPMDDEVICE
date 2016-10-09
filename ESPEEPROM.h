//================== EEPROM ==========================================

#ifndef ESPEEPROM_h
#define ESPEEPROM_h

#include <EEPROM.h>
#include <Arduino.h>

extern struct ConfigMy{
  String ssid;
  String password;
  String wwwpass;
  String www_username;
  String www_password;
  String serverIP;
  String name;
  String property;
  String dhcp;
  String ip;
  String mask;
  String gw;
  String dns;
  String ap;
  String ipap;
}Config;

// сохраняем конфиг в EEPROM
void ConfigSave();

// Читаем конфиг в EEPROM
void ConfigRead();

// Функция записи настроек по умолчанию
void DeraultConfig();

#endif
