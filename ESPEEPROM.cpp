#include "ESPEEPROM.h"

ConfigMy Config;

//Записать стррку в EEPROM
int SaveStringEEPROM(int addr, String string)
{
  for(int i=0; i<= string.length(); i++)
  {
    EEPROM.write(addr,string.charAt(i));
    addr++ ;
  }
  EEPROM.write(addr,'&');
  addr ++;
  return addr;
}


// Получить строку EEPROM

int GetStringEEPROM(int addr, String &getString)
{
  char symvol ='a';
  int addrStr =0;
  char buf[30];
  while(symvol != '&')
  {
    if(addrStr == 30) return 1;
    symvol=EEPROM.read(addr);
    buf[addrStr]=symvol;
    addrStr ++;
    addr++;
  }
  getString=buf;
  //Serial.println(getString);
  return addr;
}

// сохраняем конфиг в EEPROM
void ConfigSave()
{
  int addr =3;
  EEPROM.begin(512);
  addr= SaveStringEEPROM(addr, Config.ssid);
  addr= SaveStringEEPROM(addr, Config.password);

  addr= SaveStringEEPROM(addr, Config.wwwpass);
  addr= SaveStringEEPROM(addr, Config.www_username);
  addr= SaveStringEEPROM(addr, Config.www_password);
  addr= SaveStringEEPROM(addr, Config.serverIP);

  addr= SaveStringEEPROM(addr, Config.name);
  addr= SaveStringEEPROM(addr, Config.property);
  addr= SaveStringEEPROM(addr, Config.dhcp);
  
  addr= SaveStringEEPROM(addr, Config.ip);
  addr= SaveStringEEPROM(addr, Config.mask);
  addr= SaveStringEEPROM(addr, Config.gw);
  addr= SaveStringEEPROM(addr, Config.dns);
  addr= SaveStringEEPROM(addr, Config.ap);
  addr= SaveStringEEPROM(addr, Config.ipap);

  addr= SaveStringEEPROM(addr, Config.name2);
  addr= SaveStringEEPROM(addr, Config.name3);

  addr= SaveStringEEPROM(addr, Config.KarnizLength);
  
  EEPROM.write(1,8);
  EEPROM.commit();
}

// Читаем конфиг с EEPROM
void ConfigRead()
{
  int addr =3;
  int a=0;
  
  EEPROM.begin(512);
  a= EEPROM.read(1);
  if(a==8)
  {
    addr= GetStringEEPROM(addr, Config.ssid);
    addr= GetStringEEPROM(addr, Config.password);
  
    addr= GetStringEEPROM(addr, Config.wwwpass);
    addr= GetStringEEPROM(addr, Config.www_username);
    addr= GetStringEEPROM(addr, Config.www_password);
    addr= GetStringEEPROM(addr, Config.serverIP);
  
    addr= GetStringEEPROM(addr, Config.name);
    addr= GetStringEEPROM(addr, Config.property);
    addr= GetStringEEPROM(addr, Config.dhcp);
    
    addr= GetStringEEPROM(addr, Config.ip);
    addr= GetStringEEPROM(addr, Config.mask);
    addr= GetStringEEPROM(addr, Config.gw);
    addr= GetStringEEPROM(addr, Config.dns);
    
    addr= GetStringEEPROM(addr, Config.ap);
    addr= GetStringEEPROM(addr, Config.ipap);

    addr= GetStringEEPROM(addr, Config.name2);
    addr= GetStringEEPROM(addr, Config.name3);

    addr= GetStringEEPROM(addr, Config.KarnizLength);
  }
  EEPROM.commit();
}

// Функция записи настроек по умолчанию
void DeraultConfig()
{
  int a=0;
  EEPROM.begin(5);
  a= EEPROM.read(1);
  EEPROM.commit();
  if(a!=8)
  {
    Config.ssid         = "dd-wrt";      // Имя сети WiFi
    Config.password     = "8849884988";     // Пароль WiFi
    Config.wwwpass      = "on";             // Включить авторизацию в WEB интерфейсе
    Config.www_username = "admin";          // Имя пользователя в WEB интерфейсе
    Config.www_password = "esp8266";        // Пароль в WEB интерфейсе
    Config.serverIP     = "192.168.1.146"; // ИМЯ или IP адрес сервера MojorDomo
    Config.name         = "IR_Resiver";          // Имя объекта в MojorDomo
    Config.property     = "Code";         // Значение свойства объекта в MojorDomo
    Config.dhcp         = "on";             // Использовать DHCP
    Config.ip           = "192.168.1.2";
    Config.mask         = "255.255.255.0";
    Config.gw           = "192.168.1.1";       
    Config.dns          = "192.168.1.1";
    Config.ap           = "on";             // Включаем точку доступа для конфигурации устройства
    Config.ipap         = "192.168.4.1";     // Ip адресс ВЭБ интерфейса конфигурации устройства в режиме  точки доступа
    Config.name2        = "Code2";           // Значение свойства объекта в MojorDomo
    Config.name3        = "Code3";         // Значение свойства объекта в MojorDomo
    Config.KarnizLength = "3";
    
  
    ConfigSave();
    }
}
