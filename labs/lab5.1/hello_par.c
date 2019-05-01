#include <omp.h>
#include <stdio.h>

int main ()
{
    int ID, i;

    //omp_set_num_threads(1);
    
    #pragma omp parallel num_threads(1)
    {
       for(int i = 0; i < 5 ; i++)
            infof("Hello World num : %d\n",i);
    ID = omp_get_num_threads();
    
    infof("Num of threads : %d\n",ID);
    }
}
