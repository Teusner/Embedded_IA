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
    auto data = readAuFile("../label.au");
    auto bins = fft_windowing_framing(data);
    csv<<"class";
    int count=0;
    
    for (int j = 0; j < 50*2; j++)
        {   count+=1;
            std::ostringstream oss_label;
            oss_label << "feature"<<count ;
            std::string label = oss_label.str();
            csv<<label;
        }
            
        
    csv<<endrow;

    for (int k = 0; k < Class.size(); k++)
    {
        for (int n = 0; n < 100; n++)
    {
        std::ostringstream oss_r;
        if (n<10)
        {
            oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".0000" << n << ".au" ;
        }
        else
        {
            oss_r << "../archive/genres/"<<Class[k]<<"/"<<Class[k]<<".000" << n << ".au" ;
        }
        
        std::string path_read = oss_r.str();
        cout<<path_read<<endl;
        
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

<<<<<<< HEAD

        /* extract features */
        auto data = readAuFile(path_read);
        auto bins = fft_windowing_framing(data);

        /* creating csv file */
        for (int i = 0; i < (int)bins.size()/20; i++)
        {   
            csv<<Class[k];
            for (int j = 0; j < 50; j++)
            {   double x,y;
                x=std::real(bins[i][j]);
                y=std::imag(bins[i][j]);
                csv << x;
                csv << y;

=======
            csv<<Class[k];
            
            int i_max = 25;
            for (int i = 0; i < i_max; i++){
                double mfcc_result = GetCoefficient(spectrum, 44100, 48, 128, i);
                csv << mfcc_result;
>>>>>>> 7fa3e6acb8449c5677f370c01af8c14bf6dc18c2
            }
            csv<<endrow;
        }
        

            csv << endrow;
        }
    }
    
    return 0;
}
