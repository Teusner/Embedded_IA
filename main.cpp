#include <iostream>
#include "au_reading.h"
#include "signal.h"
using namespace std;
int main() {
    std::cout << "Hello, Embedded !" << std::endl;
    auto data = readAuFile("disco.00050.au");
    auto bins = fft_windowing_framing(data);
    cout<<bins[0].size()<<endl;
    return 0;
}
