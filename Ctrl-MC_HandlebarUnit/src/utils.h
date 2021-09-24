
/***  Ctrl-MC // An open source Motorcycle Controller Arduino project by KI Hestad: https://github.com/KIHestad/Ctrl-MC  ***/

bool readInput(Input input) {
    if (!input.enabled)
        return false;
    return (digitalRead(input.pin) == 0);
}