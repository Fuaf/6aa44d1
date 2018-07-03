#pragma once

#include "../Hardware/Button.h"
#include "Abstract/NoteOut.h"

class NoteButtonLatching : public NoteOut {
  public:
    NoteButtonLatching(pin_t pin, uint8_t address, uint8_t channel,
                       uint8_t velocity = 127)
        : NoteOut(address, channel, velocity), button{pin} {}

  private:
    void refresh() {
        Button::State state = button.getState();
        if (state == Button::Falling || state == Button::Rising) {
            sendOn();
            sendOff();
        }
    }

    Button button;
};