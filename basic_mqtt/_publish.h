#include <MqttConnector.h>

extern int relayPinState;
extern MqttConnector* mqtt;
extern int relayPin;
extern char myName[];

static void readSensor();

float sensorValue1;
float sensorValue2;

extern String DEVICE_NAME;
extern int PUBLISH_EVERY;

void register_publish_hooks() {
  strcpy(myName, DEVICE_NAME.c_str());
  mqtt->on_prepare_data_once([&](void) {
    sensorValue1 = -1.0;
    sensorValue1 = -1.0;
  });

  mqtt->on_before_prepare_data([&](void) {
    readSensor();
  });

  mqtt->on_prepare_data([&](JsonObject *root) {
    JsonObject& data = (*root)["d"];
    JsonObject& info = (*root)["info"];
    data["myName"] = myName;
    data["millis"] = millis();
    data["sensorValue1"] = sensorValue1;
    data["sensorValue2"] = sensorValue2;
    data["state"] = relayPinState;
  }, PUBLISH_EVERY);

  mqtt->on_after_prepare_data([&](JsonObject * root) {
    /**************
      JsonObject& data = (*root)["d"];
      data.remove("version");
      data.remove("subscription");
    **************/
  });
}

static void readSensor() {
  sensorValue1 = millis()*0.5;
  sensorValue2 = millis()*0.75;
}
