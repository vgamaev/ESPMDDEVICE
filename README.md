ESPMDDEVICE
Developed ESP8266 MajorDomo device

ESPMDDEVICE  
  Developed ESP8266 MajorDomo device  
Что реализовано.  
- Включение выключение лампочки через MojorDoMo, встроенную вэб страницу, кнопкой на устройстве.  
- Передача состояния лампы в MojorDoMo.  
- Конфигурация устройства через встроенный вэб интерфейс  
- Начальная конфигурация через встроенную точку доступа.  
- Запись конфигурации во внутреннею  EEPROM  
- Запрос логина и пароля для доступа к встроенной вэб странице. 
- ИК пприемник.передатчик.
- Измерение уровня освещености.
- Добавил поддержку выключателей Sonoff T1 трехкнопочный, Sonoff Touch,  розетка Sonoff S20,  

Управления реле 
http://192.168.1.11/relay?token=12345678&relay=3&state=off  
Строка которую отправляет выключатель для изменения состояния лампы в MajorDoMo.  
http://192.168.43.218/objects/?object=LAMP1&op=set&p=status&v=0   где v=1 лампа включена v=0 лампа выключена.  

Форум выключатель https://majordomo.smartliving.ru/forum/viewtopic.php?f=8&t=3071&p=35666
ИК передатчик https://majordomo.smartliving.ru/forum/viewtopic.php?f=6&t=4670
