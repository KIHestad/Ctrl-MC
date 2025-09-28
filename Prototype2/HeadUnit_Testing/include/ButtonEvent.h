#ifndef ButtonEvent_h
#define ButtonEvent_h

class ButtonEvent {
    
    public:
        void action(Data& data, Button& button, Storage& storage) {
            if (button.eventHappening()) {
                data.displayUpdateNeeded = true; // set flag to force update display immediately
            }
            // Reset countdown if not currently button hold
            if (data.displayCountdown > 0 && !button.isLongPressing()) {
                data.displayCountdown = 0;
                data.displayUpdateNeeded = true; // set flag to force update display immediately
            }
            // Page 0 = FUEL page, check for long press to set full tank
            if (data.displayPageSelected == 0 && button.isLongPressing()) {
                // detected button hold on FUEL page, avoid processing click event
                unsigned long holdDuration = button.getLongPressDuration();
                data.displayMenuNameSetMs = data.currentMs; // for auto removing countdown after some time in case cancel long pressing state is not called
                // Calculate countdown to reset
                data.displayCountdown = 5 - (holdDuration / 1000.0);
                if (data.displayCountdown < 0) data.displayCountdown = 0;
                // Reset when countdown is reached
                if (data.displayCountdown == 0) {
                    // Button is hold long enough for resetting trip counter
                    float fuelLevelPercentage = data.fuelLevel / data.fuelTankCapacity;
                    if (fuelLevelPercentage > 0.6)
                        data.fuelLevel = round(data.fuelTankCapacity / 2.0 * 10) / 10; // set half tank, one decimal
                    else if ((fuelLevelPercentage*data.fuelTankCapacity) > (data.fuelTankReserve * 1.1))
                        data.fuelLevel = data.fuelTankReserve; // set to reserve tank
                    else
                        data.fuelLevel = data.fuelTankCapacity; // set full tank
                    data.fuelTripCounter = 0.0;
                    storage.resetFuelLevel(data.fuelLevel);
                    data.displayUpdateNeeded = true; // set flag to force update display immediately
                    button.cancelLongPressingState(); // reset long press state to avoid multiple resets
                    display.menuName(""); // clear menu name since it's also used to show countdown
                }
            }
            // Page 3 = TRIP / TOTAL page, check for long press to reset trip counter
            else if (data.displayPageSelected == 3 && button.isLongPressing()) {
                // detected button hold on TRIP page, avoid processing click event
                unsigned long holdDuration = button.getLongPressDuration();
                data.displayMenuNameSetMs = data.currentMs; // for auto removing countdown after some time in case cancel long pressing state is not called
                // Calculate countdown to reset
                data.displayCountdown = 5 - (holdDuration / 1000.0);
                if (data.displayCountdown < 0) data.displayCountdown = 0;
                // Reset when countdown is reached
                if (data.displayCountdown == 0) {
                    // Button is hold long enough for resetting trip counter
                    data.tripCounter = 0.0;
                    storage.resetTripCounter();
                    data.displayUpdateNeeded = true; // set flag to force update display immediately
                    button.cancelLongPressingState(); // reset long press state to avoid multiple resets
                    display.menuName(""); // clear menu name since it's also used to show countdown
                }
            }
            // Normal button click to change display page
            if (button.isPressed()) {
                // Button is clicked, change display page
                data.displayPageSelected = (data.displayPageSelected + 1) % data.displayPagesTotal;
                data.displayUpdateNeeded = true; // set flag to force update display immediately
            }
        };

};

#endif