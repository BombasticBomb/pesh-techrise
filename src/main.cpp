


// This code should be flashed to the esp32 chip
// using the cooresponding arduino extension!



// include SD STUFF
#include <SPI.h>
#include <SD.h>

// HERE I WILL ADD THE OTHER RTOS functions that Taquee wanted, like sleep, or poweroff (later though)






// make sure everything is working
if (!SD.begin()) {
  Serial.println("You have a problem with your SD card");
  return;
}

// check to make sure file doens't already exist
if (!SD.exists("/data.csv")) {
  File file = SD.open("/data.csv", FILE_WRITE);

  // quickly add headers to columns
  file.println("Time,Temp,Pressure");

  file.close();
}

// recording rate for data into csv
const int RecordRate = 1000;

// write data we have to the file
void sensorToCsv(void *pvParameters) {
  while(true) {
    if(file) {
      file.printf(
        "%lu,%d,%d\n",
        millis(),
        SensorData.rawTemp,
        SensorData.rawPressure
      );
  
      file.close();
    } 
    
    vTaskDelay(pdMS_TO_TICKS(RecordRate));
  }
}

// this sensor class lets us instantiate many different
// sensors directly from setup (:

// also a struct for sensor output
struct SensorDataS = {
  // here we could have someone who knows
  // which sensors to add include stuff
  // For right now I'm assuming just a temp, and pressure
  float rawTemp;
  float rawPressure;
}

// init
// Creating the sensor data struct
SensorDataS SensorData;
// the mutex prevents collisions
SemaphoreHandle_t sensorMutex;
sensorMutex = xSemaphoreCreateMutex();

// class sensor
class Sensor {
public:
  int PIN;
  float* output;
  char name[];
  boolean debugLogging;
  char unit[];
  int msRate;

  Sensor(int p, float* out, char[] n, boolean d, char[] u, int r) {
    PIN = p;
    output = out;
    name = n;
    debugLogging = d;
    unit = u;
    msRate = r;

    // creating RTOS task; func, name, memory, 
    xTaskCreatePinnedToCore(
      // the task starter function ...
      pipe,
      "Task: " + name,
      4096,
      // this is to take all of the objects vars and transfer them into the other function
      // its gross but you won't have to look at it lol
      this,
      2,
      NULL,
      1
    );
    
  }

  // literaly just run task with the Sensor attributes as a parameter
  static void pipe(void* parameter) {
    Sensor* self = static_cast<Sensor*>(parameter);
    self->task();
  }
  // FreeRTOS sensor task
  void SensorTask(void *pvParameters) {
    while(true) {
      // measurement logic 
      
      float temp = analogRead(PIN);
      xSemaphoreTake(sensorMutex, portMAX_DELAY);
      *output = temp;
      xSemaphoreGive(sensorMutex);
      if (debugLogging) {
        Serial.println("The sensor, " + name + ", was read as " + temp + " (" + unit + ")");
      }
      
      // here I would store the data somewhere on the chip

      // .......

      // change rate of data gathering (that func converts ms to
      // some sort of abstract tick rate)
      vTaskDelay(pdMS_TO_TICKS(msRate));
    }
    
  }


};



// Testing function
void testSerial() {
  Serial.println("Hello world");
}



// here is the setup func
void setup() {
  // I had forgotten the boud rate stuff; maybe it needs to be lower?
  Serial.begin(115200);
  // Init sensors 
  // HERE ARE THE PARAMS int p, float* out, char[] n, boolean d, char[] u, int r

  // THE NUMBER TEN IS AN ARBITRARY PIN, PLEASE CHANGE ACCORDING TO DESIGN
  // THE BOOLEAN Enables a debugging serial log 
  // Lowkey idk the unit for the sensor were gonna use; I assume celcius ("C")
  // 1000 is the sample delay in ms
  Sensor Temp(10, &SensorData.rawTemp, "Temp Sensor", true, "C", 1000);
  // If we include an actual pressure sensor please change the units from kilopascals
  Sensor Pressure(20, &SensorData.rawPressure, "Pressure Sensor", true, "kPa", 1000);

  // LOGGING WITH ANOTHER TASK
  xTaskCreatePinnedToCore(
    // the task starter function ...
    sensorToCsv,
    "Logging Sensor Data",
    4096,
    // pass in nada because we only use globals in this task
    NULL,
    2,
    NULL,
    1
  );
}


// AUX data functions

// CLEARING THE CSV

void clearCsv() {

  // pretty much just recreate the file and add the headers again
  
  SD.remove("/data.csv");
  File file = SD.open("/data.csv", FILE_WRITE);
  file.println("Time,Temp,Pressure");
  file.close();
  
}

// this function <------ doesn't get run anywhere; its here just in case 
// we want to clear up junk data at the end of our program


// here is the main loop
// My understanding was that we would want this loop to fire
// higher level code while FreeRTOS handles the sensor stuff.
void loop() {
  // testSerial();
  
}















