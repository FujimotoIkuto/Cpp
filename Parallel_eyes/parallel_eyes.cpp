#include <iostream>
#include <cmath>

int main()
{
    unsigned int object;
    std::cout << "数値を入力してください" << std::endl;
    std::cin >> object;
    
    int number[12], parallel_eyes_number[12];
    int digits, parallel_eyes_digits;
    bool is_first = true;
    int number_maximam = 1;
    int parallel_eyes_maximam = 1;
    bool is_parallel_eyes = true;
    int check;
 
    for(int i=0; i<13; i++)
    {
        number[i] = object%(int)(pow(10, i));
        // std::cout << number[i] << "\t";
        
    }

    for(int i=0; i<12; i++)
    {
        if(number[i] == number[12] && is_first)
        {
            digits = i;
            is_first = false;
        }
    }
    
    std::cout << std::endl;
    
    for(int i=digits; i>0; i--)
    {
        number[i] = number[i]-number[i-1];
        number[i] = number[i]/(int)(pow(10, i-1));
        // std::cout << number[i] << "\t";
        if(number[i] > number_maximam)
        {
            number_maximam = number[i];
        }
        
    }
    // std::cout << std::endl;


    // std::cout << digits << std::endl;

    // std::cout << std::endl;

    unsigned long long parallel_eyes = 0;
    for(int j=number_maximam+1; j<9667; j++)
    {
        for(int i=digits; i>=0; i--)
        {
            parallel_eyes += number[i]*pow(j,i-1);
        }
        std::cout << j << "進数: " << parallel_eyes << std::endl;

        /////////
        is_first = true;

        for(int i=0; i<23; i++)
        {
            parallel_eyes_number[i] = parallel_eyes%(int)(pow(10, i));
            // std::cout << parallel_eyes_number[i] << "\t";   
        }
        for(int i=0; i<22; i++)
        {
            if(parallel_eyes_number[i] == parallel_eyes_number[22] && is_first)
            {
                parallel_eyes_digits = i;
                is_first = false;
            }
        }

        std::cout << std::endl;
        
        for(int i=parallel_eyes_digits; i>0; i--)
        {
            parallel_eyes_number[i] = parallel_eyes_number[i]-parallel_eyes_number[i-1];
            parallel_eyes_number[i] = parallel_eyes_number[i]/(int)(pow(10, i-1));
            // std::cout << parallel_eyes_number[i] << "\t";
            if(number[i] > parallel_eyes_maximam)
            {
                parallel_eyes_maximam = parallel_eyes_number[i];
            }
        }
        // std::cout << std::endl;
        /////

        is_first = true;

        for(int i=parallel_eyes_digits; i>0; i--)
        {
            if(is_first)
            {
                check = parallel_eyes_number[i];
                is_first = false;
            }
            if(check != parallel_eyes_number[i])
            {
                is_parallel_eyes = false;
            }
        }


        if(is_parallel_eyes)
        {
            std::cout << j << "進数で" << object << "をゾロ目にできました" << parallel_eyes << std::endl;
            return 0;
        }

        parallel_eyes = 0;
        is_parallel_eyes = true;
    }

    std::cout << "範囲を超えましあ" << std::endl;
    std::cout << object  << "をゾロ目にできませんでした" << std::endl;

    return 0;
}