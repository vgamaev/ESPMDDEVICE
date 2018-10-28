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
     
    if(currentMillis - previousMillisDHT > 5000) 
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
        //return;
      }else
      {    
        Serial.print("Humidity: ");
        Serial.print(humDHT);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(tempDHT);
        Serial.print(" *C ");
        Serial.print("Heat index: ");
        Serial.print(hicDHT);
        Serial.println(" *C ");
      }

      // Compute heat index in Celsius (isFahreheit = false)
      hicDHT = dht.computeHeatIndex(tempDHT, humDHT, false);

      float DeltaPlusT = tempDHTOld + 0.3;
      float DeltaMinusT = tempDHTOld - 0.3;
      float DeltaPlusH = humDHTOld + 0.3;
      float DeltaMinusH = humDHTOld - 0.3;

      //if(tempDHT != tempDHTOld || humDHT != humDHTOld)
      if(tempDHT > DeltaPlusT || tempDHT < DeltaMinusT || humDHT > DeltaPlusH || humDHT < DeltaMinusH)
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

