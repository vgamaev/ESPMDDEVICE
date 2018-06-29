#include "DHT22.h"

#ifdef DHT22

DHT dht(DHTPIN, DHTTYPE);

void dhtInit() 
{
    dht.begin();
}

void dhtRead()
{
    static long previousMillisDHT = 0;                             
    long currentMillis = millis();
     
    if(currentMillis - previousMillisDHT > 2000) 
    {
      previousMillisDHT = currentMillis;  
      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      humDHT = dht.readHumidity();
      // Read temperature as Celsius (the default)
      tempDHT = dht.readTemperature();

       // Check if any reads failed and exit early (to try again).
      if (isnan(humDHT) || isnan(tempDHT)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }
    
      // Compute heat index in Celsius (isFahreheit = false)
      hicDHT = dht.computeHeatIndex(tempDHT, humDHT, false);
    
      Serial.print("Humidity: ");
      Serial.print(humDHT);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(tempDHT);
      Serial.print(" *C ");
      Serial.print("Heat index: ");
      Serial.print(hicDHT);
      Serial.print(" *C ");

      if(tempDHT != tempDHTOld || humDHT != humDHTOld)
      { 
        //String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p=temp&v="+tempDHT;  
        String post = "http://"+Config.serverIP+"/objects/?op=m&object="+Config.name+"&m=ChangeParams&temp="+tempDHT+"&hum="+humDHT+"&hic="+hicDHT;  
        Serial.println(post);
        http.begin(post);
        int httpCode = http.GET(); 

        http.end();
        tempDHTOld = tempDHT;
        humDHTOld = humDHTOld;
      }
    }
}

#endif

