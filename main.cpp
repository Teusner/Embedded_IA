#include <iostream>
#include "au_reading.h"
#include "signal.h"
#include "csvfile.h"

#include "mfcc.hpp"
#include <vector>
#include <fftw3.h>


using namespace std;


int main() {
    /* creating all classes */
    std::vector<string> Class={ "blues" , "classical" , "country" , "disco" , "hiphop" , "jazz" , "metal" , "pop" , "reggae" , "rock"};
    std::cout << Class[0] << std::endl;

    std::ostringstream oss_w;
    oss_w << "../Data/dataset.csv" ;
    std::string path_write = oss_w.str();
    csvfile csv(path_write);

    /* writing path */
    for (int k = 0; k < Class.size(); k++) {
        for (int n = 0; n < 100; n++) {
            std::ostringstream oss_r;
            if (n<10)
                oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".0000" << n << ".au" ;
            else
                oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".000" << n << ".au" ;
        
            std::string path_read = oss_r.str();
            std::cout << path_read << std::endl;
            
            /* extract features */
            DataVector data = readAuFile(path_read);
            // auto bins = fft_windowing_framing(data);

            // /* creating csv file */
            // csv<<Class[k];
            // for (int i = 0; i < 10; i++) {
            //     for (int j = 0; j < 10; j++)
            //         csv << bins[i][j];
            // }
            
            double spectrum[8192];
            std::copy(data.begin(), data.end(), spectrum);
            
            fftw_complex in[N], out[N];
            fftw_plan p;

            int N = data.size();
            for (int i = 0; i < N; i++) {
                in[i][0] = data[i];
                in[i][1] = 0;
            }

            /* forward Fourier transform, save the result in 'out' */
            p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
            fftw_execute(p);
            for (int i = 0; i < N; i++)
                printf("freq: %3d %+9.5f %+9.5f I\n", i, out[i][0], out[i][1]);
            fftw_destroy_plan(p);

            csv<<Class[k];
            
            int i_max = 25;
            for (int i = 0; i < i_max; i++){
                double mfcc_result = GetCoefficient(spectrum, 44100, 48, 128, i);
                csv << mfcc_result;
            }

            csv << endrow;
        }
    }
    
    return 0;
}
