#ifndef UTILITY_H
#define UTILITY_H

#include<map>
#include<windows.h>

struct KEY{
    bool SHIFT ;
    int V_Key;
    KEY(bool sft,int key)
    {
        SHIFT = sft;
        V_Key = key;
    }
};
std::map<char,KEY> mapper;


void Swap(char &a,char &b)
{
    char temp = a;
    a = b;b = temp;
}

void SwitchEndiness(char *beg, int size)
{
    for(int i = 0;i<size/2;++i)
        Swap(beg[i],beg[size-1-i]);
}

class Queue{

    private:
        int Size;
        float *array;
        int index;
    public:
        Queue(int size) {
        array = new float[size];
        Size = size;index = 0;
        }
        void insert(float value)
        {
            array[index++] = value;
            index = index % Size;
        }
        float get(int i)
        {
            return array[(index+i)%Size];
        }
        float getMean()
        {
            float sum = 0;
            for(int i = 0;i<Size;++i) sum += array[i];
            return sum/Size;
        }
        float WMean()
        {
            float sum = 0;
            int i = 0;
            for(;i<30;++i) sum += array[(index+i) % Size];
            for(;i<40;++i) sum += 3*array[ (index+i) %Size];
            for(;i<50;++i) sum += 4*array[ (index+i) %Size];
            return sum/(Size+50);

        }
};


void Bindings(void)
    {
            //KEY k(true,48);
            mapper.insert(std::make_pair(')', KEY(true,48)));/*KEY(true,48);*/
            mapper.insert(std::make_pair('!',KEY(true,49)));
            mapper.insert(std::make_pair('@',KEY(true,50)));
            mapper.insert(std::make_pair('#',KEY(true,51)));
            mapper.insert(std::make_pair('$',KEY(true,52)));
            mapper.insert(std::make_pair('%',KEY(true,53)));
            mapper.insert(std::make_pair('^',KEY(true,54)));
            mapper.insert(std::make_pair('&',KEY(true,55)));
            mapper.insert(std::make_pair('*',KEY(true,56)));
            mapper.insert(std::make_pair('(',KEY(true,57)));
            mapper.insert(std::make_pair('-',KEY(false,VK_OEM_MINUS)));
            mapper.insert(std::make_pair('_',KEY(true,VK_OEM_MINUS)));
            mapper.insert(std::make_pair('=',KEY(false,VK_OEM_PLUS)));
            mapper.insert(std::make_pair('+',KEY(true,VK_OEM_PLUS)));
            mapper.insert(std::make_pair('[',KEY(false,VK_OEM_4)));
            mapper.insert(std::make_pair('{',KEY(true,VK_OEM_4)));
            mapper.insert(std::make_pair(']',KEY(false,VK_OEM_6)));
            mapper.insert(std::make_pair('}',KEY(true,VK_OEM_6)));
            mapper.insert(std::make_pair('\\',KEY(false,VK_OEM_5)));
            mapper.insert(std::make_pair('|',KEY(true,VK_OEM_5)));
            mapper.insert(std::make_pair(';',KEY(false,VK_OEM_1)));
            mapper.insert(std::make_pair(':',KEY(true,VK_OEM_1)));
            mapper.insert(std::make_pair('\'',KEY(false,VK_OEM_7)));
            mapper.insert(std::make_pair('"',KEY(true,VK_OEM_7)));
            mapper.insert(std::make_pair(',',KEY(false,VK_OEM_COMMA)));
            mapper.insert(std::make_pair('<',KEY(true,VK_OEM_COMMA)));
            mapper.insert(std::make_pair('.',KEY(false,VK_OEM_PERIOD)));
            mapper.insert(std::make_pair('>',KEY(true,VK_OEM_PERIOD)));
            mapper.insert(std::make_pair('/',KEY(false,VK_OEM_2)));
            mapper.insert(std::make_pair('?',KEY(true,VK_OEM_2)));
            mapper.insert(std::make_pair('`',KEY(false,VK_OEM_3)));
            mapper.insert(std::make_pair('~',KEY(true,VK_OEM_3)));
            /**/
            return;
    }

#endif // UTILITY_H
