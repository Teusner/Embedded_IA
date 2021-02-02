#include <iostream>
#include "au_reading.h"
#include "signal.h"
#include "csvfile.h"
using namespace std;
int main() {
    /* creating all classes */
    std::vector<string> Class={ "blues" , "classical" , "country" , "disco" , "hiphop" , "jazz" , "metal" , "pop" , "reggae" , "rock"};
    cout<<Class[0]<<endl;

    std::ostringstream oss_w;
    oss_w << "../Data/dataset.csv" ;
    std::string path_write = oss_w.str();
    csvfile csv(path_write);
    /* writing path */
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
        


        /* extract features */
        auto data = readAuFile(path_read);
        auto bins = fft_windowing_framing(data);

        /* creating csv file */
        csv<<Class[k];
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                csv << bins[i][j];

            }
            
        }
        csv<<endrow;

    }
    }
    
    
    
    
    return 0;
}
