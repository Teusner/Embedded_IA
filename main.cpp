#include <iostream>
#include "au_reading.h"
#include "signal.h"
#include <complex.h>    /* Standard Library of Complex Numbers */
#include "csvfile.h"

#include "mfcc.hpp"
#include <vector>
#include <fftw3.h>


using namespace std;


int main() {
    /* creating all classes */
    std::vector<string> Class={ "blues" , "classical" , "country" , "disco" , "hiphop" , "jazz" , "metal" , "pop" , "reggae" , "rock"};
    std::cout << Class[0] << std::endl;

    /* Opening file */
    std::ostringstream oss_w;
    oss_w << "../Data/dataset1.csv" ;
    std::string path_write = oss_w.str();
    csvfile csv(path_write);

    /* Labelisation csv */
    csv<<"class";    
    int coeff_max = 40;
    for (int feature_number = 0; feature_number < coeff_max; feature_number++) {
        std::ostringstream oss_label;
        oss_label << "feature" << feature_number ;
        std::string label = oss_label.str();
        csv << label;
    }
        
    csv<<endrow;

    for (int k = 0; k < Class.size(); k++){
        for (int n = 0; n < 100; n++){
            std::ostringstream oss_r;
            if (n<10)
                oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".0000" << n << ".au" ;
            else
                oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".000" << n << ".au" ;
        
            std::string path_read = oss_r.str();
            std::cout << path_read << std::endl;
            
            /* extract features */
            DataVector data = readAuFile(path_read);
            
            // Writing class in csv
            csv<<Class[k];

            // Computing fft
            int N = data.size();
            fftw_complex *in, *out;

            in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
            out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

            fftw_plan p;
            
            //  Creating input signal
            for (int i = 0; i < N; i++) {
                in[i][0] = data[i];
                in[i][1] = 0;
            }

            // Computing output fft
            p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
            fftw_execute(p);

            //  Getting real part of the fft
            double spectrum[N];
            for (int i = 0; i < N; i++) {
                spectrum[i] = out[i][0];
            }
            
            // Computing MFCC coefficients from fft
            for (int coeff = 0; coeff < coeff_max; coeff++){
                double mfcc_result = GetCoefficient(spectrum, 44100, 48, 128, coeff);
                csv << mfcc_result;
            }        

            fftw_free(in);
            fftw_free(out);
            fftw_destroy_plan(p);
            csv << endrow;
        }
    }
    
    return 0;
}
