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
- Добавил поддержку выключателей Sonoff T1 двух, трехкнопочный, Sonoff Touch,  розетка Sonoff S20, 
- Поддержка информера на светодиодных матрицах 8x8 на микросхеме MAX7219 с поддержкой русского языка.
- Обновление прошивки через WEB интерфейс на esp8266 c flash памятью больше 1 мб.
- Ихмерение температуры и влажности датчиком DHT22 и ему подобным.
- Управление зановесками (карнизом).

Библиотеки для сборки кода https://github.com/vgamaev/lib
Скрипты интеграции с MajorDomo
https://connect.smartliving.ru/profile/907/objects.html

Управления реле 
http://192.168.1.11/relay?token=12345678&relay=3&state=off  
Строка которую отправляет выключатель для изменения состояния лампы в MajorDoMo.  
http://192.168.43.218/objects/?object=LAMP1&op=set&p=status&v=0   где v=1 лампа включена v=0 лампа выключена.  

Форум выключатель https://majordomo.smartliving.ru/forum/viewtopic.php?f=8&t=3071&p=35666
ИК передатчик https://majordomo.smartliving.ru/forum/viewtopic.php?f=6&t=4670

Информер
Отправка строки на информер 192.168.1.42/informer?token=123456&bright=10&power=0&priority=high&string=привет
	bright - ярость от 0-15
	power  - отключить дисплей 1, включить дисплей 1.
	priority=high  сообщение выводится сразу, не дожидаясь пока закончится отображение предедущегою
Опции можно отправлять отдельно.

23.01.2020
Уравление зановесками (электро карниз)
Прнциа управления, мотор кулючается на время за которое зановеска проходит необходимое растоняние, задается параметром Open time sec: в настройках.

WEB API
Управление положением зановески http://IP_address/karniz?token=token&position=25
Установка текущего положения карниза (калибровка), и время открытия карниза (длина) http://IP_address/karniz?token=token&calibrate=11&opentime=18

Драйвер мотора L298N плата с али.
Редуктор с али червячный на 62 оборота в минуту.
Чертежи миханики прилогаются в исходниках.
Контакты Модуля ESP-12 для управления L298N
IN1 = 16 IN2 = 14

19.04.2019
Пояснения по сборке.
Из этого кода можно с генерировать прошивку для разных девайсов, например выключатели, ик прием-передатчик, информер, управление занавесками и д.р.
Для какого именно девайса и доп функции для девайса, например термометр задаются комментированием строк //
в файле ESPMDDEVICE.h https://github.com/vgamaev/ESPMDDEVICE/ ... MDDEVICE.h
Пины которые требуются для девайса задаются в файле MAINVARIABLE.h https://github.com/vgamaev/ESPMDDEVICE/ ... VARIABLE.h
Либо в *.H файлах связанных с функционалом конкретного девайса (исторически сложилось, код пишу не один год)

Пароль от точки доступа wi-fi 66666666
Логин для доступа к web интерфейсу admin
Пароль esp8266
