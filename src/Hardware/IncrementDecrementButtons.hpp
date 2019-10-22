/* ✔ */

#pragma once

#include "Button.hpp"

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for buttons that increment and decrement some counter or 
 *          setting.
 * 
 * It behaves the same way as a computer keyboard: when you press the increment
 * (decrement) button, it increments (decrements) the counter once. 
 * If you keep on pressing it for longer than a certain threshold, it keeps on 
 * incrementing (decrementing) at a faster rate, until you release it.  
 * If both the increment and the decrement button are pressed at once, it resets
 * the counter.
 * 
 * @ingroup HardwareUtils
 */
class IncrementDecrementButtons {
  public:
    /** 
     * @brief   Create a IncrementDecrementButtons object.
     * 
     * @param   incrementButton
     *          The button to increment the counter.  
     *          The button is copied.
     * @param   decrementButton
     *          The button to decrement the counter.  
     *          The button is copied.
     */
    IncrementDecrementButtons(const Button &incrementButton,
                              const Button &decrementButton)
        : incrementButton(incrementButton), decrementButton(decrementButton) {}

    /// @see     Button::begin
    void begin() {
        incrementButton.begin();
        decrementButton.begin();
    }

    /**
     * @brief   An enumeration of the different actions to be performed by the
     *          counter.
     * @todo    Add states for initial press.
     */
    enum State {
        Nothing = 0, ///< The counter should not be incremented.
        Increment,   ///< The counter should be incremented.
        Decrement,   ///< The counter should be decremented.
        Reset,       ///< The counter should be reset to the initial value.
    };

    /**
     * @brief   Get the state of the increment button.
     */
    State getState();

#ifdef INDIVIDUAL_BUTTON_INVERT
    /// @see    Button::invert
    void invert() {
        incrementButton.invert();
        decrementButton.invert();
    }
#endif

  private:
    Button incrementButton;
    Button decrementButton;

    enum {
        Initial,
        LongPress,
        AfterReset,
    } longPressState = Initial;
    unsigned long longPressRepeat;
};

END_CS_NAMESPACE