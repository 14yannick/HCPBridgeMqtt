#include "esphome.h"

class Uap1Hcp : public Component, public Cover {
 public:
  void setup() override {
    // This will be called by App.setup()
    // setup modbus
    hoermannEngine->setup();
  }
  CoverTraits get_traits() override {
    auto traits = CoverTraits();
    traits.set_is_assumed_state(false);
    traits.set_supports_position(true);
    traits.set_supports_tilt(false);
    traits.set_supports_stop(true);
    return traits;
  }
  void control(const CoverCall &call) override {
    // This will be called every time the user requests a state change.
    if (call.get_position().has_value()) {
      float pos = *call.get_position();
      // Write pos (range 0-1) to cover
      // ...
      if (pos == COVER_OPEN) {
        hoermannEngine->openDoor();
      } else if (pos == COVER_CLOSED) {
        hoermannEngine->closeDoor();
      } else {
        ESP_LOGI("somfy", "WAT");
      }

      // Publish new state
      this->position = pos;
      this->publish_state();
    }
    if (call.get_stop()) {
      // User requested cover stop
      hoermannEngine->stopDoor();
    }
  }
};