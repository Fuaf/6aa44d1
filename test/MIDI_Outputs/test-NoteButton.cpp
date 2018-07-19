#include <MIDI_Outputs/NoteButton.hpp>
#include <MockMIDI_Interface.hpp>
#include <gmock/gmock.h>

using namespace ::testing;

TEST(NoteButton, pressAndRelease) {
    MockMIDI_Interface midi;
    Control_Surface.setMIDI_Interface(midi);

    EXPECT_CALL(ArduinoMock::getInstance(), pinMode(2, INPUT_PULLUP));
    NoteButton button(2, 0x3C, 7);

    // Still released
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(1000));
    button.update();

    // Pressing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(2000));
    EXPECT_CALL(midi, sendImpl(NOTE_ON, 6, 0x3C, 0x7F));
    button.update();

    // Still pressed
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(3000));
    button.update();

    // Releasing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(4000));
    EXPECT_CALL(midi, sendImpl(NOTE_OFF, 6, 0x3C, 0x7F));
    button.update();
}

// -------------------------------------------------------------------------- //

TEST(NoteButtonBankable, pressAndRelease) {
    MockMIDI_Interface midi;
    Control_Surface.setMIDI_Interface(midi);

    EXPECT_CALL(ArduinoMock::getInstance(), pinMode(2, INPUT_PULLUP));
    BankableNS::NoteButton button(2, 0x3C, 7);

    Bank bank(4);
    bank.add(button);

    // Still released
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(1000));
    button.update();

    // Pressing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(2000));
    EXPECT_CALL(midi, sendImpl(NOTE_ON, 6, 0x3C, 0x7F));
    button.update();

    // Still pressed
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(3000));
    button.update();

    // Releasing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(4000));
    EXPECT_CALL(midi, sendImpl(NOTE_OFF, 6, 0x3C, 0x7F));
    button.update();
}

TEST(NoteButtonBankable, changeSettingAndPressAndRelease) {
    MockMIDI_Interface midi;
    Control_Surface.setMIDI_Interface(midi);

    EXPECT_CALL(ArduinoMock::getInstance(), pinMode(2, INPUT_PULLUP));
    BankableNS::NoteButton button(2, 0x3C, 7);

    Bank bank(4);
    // Change bank setting
    bank.setBankSetting(1);
    bank.add(button);

    // Still released
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(1000));
    button.update();

    // Pressing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(2000));
    EXPECT_CALL(midi, sendImpl(NOTE_ON, 6, 0x3C + 4, 0x7F));
    button.update();

    // Still pressed
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(3000));
    button.update();

    // Releasing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(4000));
    EXPECT_CALL(midi, sendImpl(NOTE_OFF, 6, 0x3C + 4, 0x7F));
    button.update();
}

TEST(NoteButtonBankable, pressAndChangeSettingAndRelease) {
    MockMIDI_Interface midi;
    Control_Surface.setMIDI_Interface(midi);

    EXPECT_CALL(ArduinoMock::getInstance(), pinMode(2, INPUT_PULLUP));
    BankableNS::NoteButton button(2, 0x3C, 7);

    Bank bank(4);
    bank.add(button);

    // Still released
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(1000));
    button.update();

    // Pressing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(2000));
    EXPECT_CALL(midi, sendImpl(NOTE_ON, 6, 0x3C, 0x7F));
    button.update();

    // Change bank setting
    bank.setBankSetting(1);

    // Still pressed
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(3000));
    button.update();

    // Releasing
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(4000));
    EXPECT_CALL(midi, sendImpl(NOTE_OFF, 6, 0x3C, 0x7F));
    button.update();

    // Pressing again (with new bank setting)
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(LOW));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(5000));
    EXPECT_CALL(midi, sendImpl(NOTE_ON, 6, 0x3C + 4, 0x7F));
    button.update();

    // Releasing again (with new bank setting)
    EXPECT_CALL(ArduinoMock::getInstance(), digitalRead(2))
        .WillOnce(Return(HIGH));
    EXPECT_CALL(ArduinoMock::getInstance(), millis()).WillOnce(Return(6000));
    EXPECT_CALL(midi, sendImpl(NOTE_OFF, 6, 0x3C + 4, 0x7F));
    button.update();
}