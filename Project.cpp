#include <iostream>
#include <time.h>

using namespace std;





class Page
{
private:
    int content;
    int last_recently_used;
public:
    Page()                                     // Default Constructor
    {
        content = 0;
        last_recently_used = 100;              // set to a really high value


    }
     Page(int acontent)                         // Constructor
    {
        content = acontent;
        last_recently_used = 100;
    }

    int get_content()
    {
        return content;
    }

    int set_content(int acontent)
    {
         content = acontent;
    }

    void show_content()
    {
        cout << content;
    }

   void set_last_recently_used(int alast_recently_used)
   {
       last_recently_used = alast_recently_used;
   }

   int get_last_recently_used()
   {
       return last_recently_used;
   }

   void increase_LRU_Value()
   {
       last_recently_used++;
   }


};

void Random_Replacement(Page Cache [],int cache_size, Page Pagelog [], int pagelog_size, int &hit_counter, int &miss_counter);
void LRU_Replacement(Page Cache [],int cache_size, Page Pagelog [], int pagelog_size, int &hit_counter, int &miss_counter);
void Oldest_Page_Replacement(Page Cache [],int cache_size, Page Pagelog [], int pagelog_size, int &hit_counter, int &miss_counter);
void print_Page_array(Page arr [],int size);
void increase_LRU_Arr( Page arr [], int size);

void Random_Replacement(Page Cache [],int cache_size, Page Pagelog [],int pagelog_size, int &hit_counter, int &miss_counter)
{
    int random_location;
    int j;                                      // defined it outside so i can check if the whole cache is checked


    for(int i = 0; i < pagelog_size; i++)                  // for loop for the page log
    {
        for(j =0; j < cache_size; j++)                   // for loop for the cache
        {



            if(Pagelog[i].get_content() == Cache[j].get_content())
            {
                hit_counter++;
                break;
            }



            if(j ==cache_size -1)                           // if the whole cache is checked, then it is a miss
            {
                miss_counter++;
                random_location = rand() % 6;
                Cache[random_location] = Pagelog[i].get_content();

            }
        }

    }
}

void LRU_Replacement(Page Cache [],int cache_size , Page Pagelog [], int pagelog_size, int &hit_counter, int &miss_counter)
{
    int max_LRU;                                // variable will be used to check for the max LRU, and then it will be swapped
    int max_index;
    int j;
    for(int i = 0; i < pagelog_size; i++)                  // for loop for the page log
    {
        for(j =0; j < cache_size; j++)                   // for loop for the cache
        {



            if(Pagelog[i].get_content() == Cache[j].get_content())
            {
                hit_counter++;
                increase_LRU_Arr(Cache, cache_size);
                break;
            }



            if(j ==cache_size -1)                           // if the whole cache is checked, then it is a miss
            {
                miss_counter++;
                max_LRU = Cache[0].get_last_recently_used();
                max_index =0;
                for(int k = 1; k < cache_size; k++)
                {
                    if(Cache[k].get_last_recently_used() > max_LRU)
                    {
                        max_LRU = Cache[k].get_last_recently_used();
                        max_index =k;
                    }

                }
                increase_LRU_Arr(Cache, cache_size);
                Cache[max_index] = Pagelog[i].get_content();
                Cache[max_index].set_last_recently_used(1);



            }
        }

    }
}

void Oldest_Page_Replacement(Page Cache [],int cache_size, Page Pagelog [], int pagelog_size, int &hit_counter, int &miss_counter)
{
    int j;
    for(int i = 0; i < pagelog_size; i++)                  // for loop for the page log
    {
        for(j =0; j < cache_size; j++)                   // for loop for the cache
        {



            if(Pagelog[i].get_content() == Cache[j].get_content())
            {
                hit_counter++;
                increase_LRU_Arr(Cache, cache_size);
                break;
            }



            if(j ==cache_size -1)                           // if the whole cache is checked, then it is a miss
            {
                miss_counter++;

                for(int k =cache_size-1; k > 0; k = k -1)
                {
                    Cache[k] = Cache[k-1];
                }
                Cache[0]= Pagelog[i].get_content();



            }
        }

    }

}
void print_Page_array(Page arr [],int size)
{
    for(int i = 0; i < size; i++)
    {
        arr[i].show_content();
        cout << " ";
    }
    cout <<"\n";
}

void increase_LRU_Arr( Page arr [], int size)
{
    for(int i = 0; i < size; i++)
    {
        arr[i].increase_LRU_Value();
    }

}
// global variables


int main()
{

    int miss_counter_random =0;
    int hit_counter_random = 0;

    int miss_counter_LRU =0;
    int hit_counter_LRU = 0;

    int miss_counter_oldest =0;
    int hit_counter_oldest = 0;

    Page Cache [3];

    Page Pagelog [7];

    srand(time(nullptr));
    Pagelog[0].set_content(1);
    Pagelog[1].set_content(3);
    Pagelog[2].set_content(0);
    Pagelog[3].set_content(3);
    Pagelog[4].set_content(5);
    Pagelog[5].set_content(6);
    Pagelog[6].set_content(3);
    /*
    Pagelog[7].set_content(4);
    Pagelog[8].set_content(2);
    Pagelog[9].set_content(3);
    Pagelog[10].set_content(0);
    Pagelog[11].set_content(3);
    Pagelog[12].set_content(2);
    */

    /*

    print_Page_array(Pagelog, 10);
    print_Page_array(Cache, 6);

    cout << "The amount of hits before random replacement are " << hit_counter_random << endl;
    cout << "The amount of misses before random replacement are " << miss_counter_random << endl;


    srand(time(nullptr));

    Random_Replacement(Cache,6, Pagelog,10, hit_counter_random, miss_counter_random);

    cout << "The amount of hits for random replacement are " << hit_counter_random << endl;
    cout << "The amount of misses for random replacement are " << miss_counter_random << endl;


    */
    /*
    print_Page_array(Pagelog, 13);
    print_Page_array(Cache, 4);

    cout << "The amount of hits before LRU replacement are: " << hit_counter_random << endl;
    cout << "The amount of misses before LRU replacement are: " << miss_counter_random << endl;


    srand(time(nullptr));

    LRU_Replacement(Cache,4, Pagelog,13, hit_counter_random, miss_counter_random);

    cout << "The amount of hits for LRU replacement are: " << hit_counter_random << endl;
    cout << "The amount of misses for LRU replacement are: " << miss_counter_random << endl;

    cout << "The final contents inside the cache are: ";
    print_Page_array(Cache, 4);
    */

    Oldest_Page_Replacement(Cache, 3,Pagelog, 7, hit_counter_oldest,miss_counter_oldest);

    cout << "The amount of hits for oldest replacement are: " << hit_counter_oldest << endl;
    cout << "The amount of misses for oldest replacement are: " << miss_counter_oldest << endl;

    cout << "The final contents inside the cache are: ";
    print_Page_array(Cache, 3);

    return 0;
}
