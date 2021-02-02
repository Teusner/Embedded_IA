#include <iostream>
#include "au_reading.h"
// #include "signal.h"

int main() {
    std::cout << "Hello, Embedded !" << std::endl;
    auto data = readAuFile("disco.00050.au");
    // auto bins = fft_windowing_framing(data);
    return 0;
}
