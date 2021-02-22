#include <iostream>
#include "au_reading.h"
#include "signal.h"
#include <complex.h>    /* Standard Library of Complex Numbers */
#include "csvfile.h"

#include "mfcc.hpp"
#include <vector>
#include <fftw3.h>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;


int main() {
    /* creating all classes */
    std::vector<string> Class={ "blues" , "classical" , "country" , "disco" , "hiphop" , "jazz" , "metal" , "pop" , "reggae" , "rock"};

    /* Opening file */
    std::ostringstream oss_w;
    oss_w << "../Data/dataset1.csv" ;
    std::string path_write = oss_w.str();
    csvfile csv(path_write);

    /* writing path */
    for (int k = 0; k < int(Class.size()); k++) {
        for (int n = 0; n < 100; n++) {
    /* Labelisation csv */
    csv<<"class";    
    int coeff_max = 19;
    for (int feature_number = 0; feature_number < coeff_max+3; feature_number++) {
        std::ostringstream oss_label;
        oss_label << "feature" << feature_number ;
        std::string label = oss_label.str();
        csv << label;
    }
        
    csv<<endrow;

    // FFT creation
    int N = 600000;
    int fft_size = N;
    fftw_complex *in, *out;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fft_size);

    fftw_plan p;
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for (int k = 0; k < Class.size(); k++){
        for (int n = 0; n < 100; n++){
            std::ostringstream oss_r;
            if (n<10)
                oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".0000" << n << ".au" ;
            else
                oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".000" << n << ".au" ;
        
            std::string path_read = oss_r.str();
            // std::cout << path_read << std::endl;
            
            /* extract features */
            DataVector data = readAuFile(path_read);
            
            // Writing class in csv
            csv << Class[k];

            // Computing mean
            double mean = 0.0;
            mean = std::accumulate(data.begin(), data.end(), 0.0);
            mean = mean / data.size();
            csv << mean;

            // Computing std
            double stdev = 0.0;
            stdev = std::transform_reduce(data.cbegin(), data.cend(), 0.0, std::plus<double>(), [=](double x) { return std::pow((x - mean), 2); });
            stdev = std::sqrt(stdev / data.size());
            csv << stdev;

            // Computing Cross-Zero Rate
            double czr = 0.0;
            DataVector result(data.size());
            auto c = std::transform(data.begin()+1, data.end(), data.begin(), result.begin(), std::multiplies<int>());
            czr = std::count_if(result.cbegin(), result.cend(), [](double i) { return i < 0 ; }); 
            czr = czr / data.size();
            csv << czr;

            // Computing energy of the signal
            auto wenergy = std::transform_reduce(data.cbegin(), data.cend(), 0.0, std::plus<double>(), [](double x) { return std::norm(x); });

            //  Creating input signal
            for (int i = 0; i < N; i++) {
                in[i][0] = data[i];
                in[i][1] = 0;
            }

            // Computing output fft
            fftw_execute(p);

            //  Getting real part of the fft
            double spectrum[fft_size];
            for (int i = 0; i < fft_size; i++) {
                spectrum[i] = out[i][0];
            }
            
            // Computing MFCC coefficients from fft
            for (int coeff = 0; coeff < coeff_max; coeff++){
                double mfcc_result = GetCoefficient(spectrum, 22050, 48, int(fft_size/100), coeff);
                csv << mfcc_result;
            }        
            csv << endrow;
        }
    }
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
    
    return 0;
}
