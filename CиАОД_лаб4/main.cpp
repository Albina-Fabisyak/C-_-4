//СиАОД_ФабисякАА_лаб4_вар2(BMW)
// Сложение двухбайтовых слов; при переполнении к сумме добавляется единица
// Алгоритм умножения
// Алгоритм квадратичных проб
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
using namespace std;

int GetHashTableIndex ( int hash, int p, int m, int n)
{
    int cdvig=1<<m;
    int Index = ( ( ( hash*p)%cdvig )*n )/cdvig;
    return Index;
}

// Сложение двухбайтовых слов
 unsigned int Hash (char * Str )
{
    unsigned short *S=( unsigned short *)Str;
    unsigned int HashValue = 0;
    int ElementCount=strlen(Str)/2;
    if(strlen(Str)%2!=0) ElementCount++;
    for (int i=0; i<ElementCount; i++)
    {
        HashValue+=S[i];
        if (( HashValue &0xFFFF0000) !=0)
            HashValue = (HashValue &0x0000FFFF)+1;
    }
    return  HashValue;
}

void Hashing(char **Str, int CountStr, int *HashTable, int HashTableLenght, int p, int m)
{
    unsigned long long int Index=0, x=0;
    for(int i=0; i<CountStr; i++)
    {
        x=0;
        Index = GetHashTableIndex( Hash(Str[i]),p, m,  HashTableLenght );
       unsigned long long int I = Index;
        if(Index>=HashTableLenght)
        {
            cout<<"Index="<<Index<<"\n";
        }
        else
        {
            while( HashTable[I] !=-1 && x<5*HashTableLenght)
            {
              x++;
              I=(Index+x*x)%HashTableLenght;
            }
            if( HashTable[I]==-1 ) HashTable[I]=i;
        }
     }
   }


bool Poisk (int* HashTable, char* Str, int HashTableLenght, char**StrMas, int p, int m, unsigned long long &PopCount)
{
    bool IsFinded=false;
  unsigned long long int I = 0 ;
  unsigned  long long int Index = 0;
    PopCount = 0;
    Index= GetHashTableIndex ( Hash ( Str ), p, m,  HashTableLenght);
    I = Index;
    while ( !IsFinded && PopCount < 5*HashTableLenght)
    {
        PopCount++;
        if(HashTable[I]==-1) break;
         IsFinded = !strcmp(StrMas[HashTable[I]], Str);
        if (!IsFinded) I = (Index + PopCount*PopCount)%HashTableLenght;
    
    }
    return  IsFinded ;
}

int main()
{
    char FileName[]="/Users/albina/Desktop/СиАОД/CиАОД_лаб4/CиАОД_лаб4/input";
    fstream fin = fstream(FileName, ios::in);
    int CountWord, CountHashTable;
    char** StrMas;
    int *HashTableMas;
    if ( fin.good() )
    {
        fin>>CountWord;
        StrMas= new char*[CountWord];
        for(int i=0; i<CountWord; i++)
        {
            StrMas[i]=new char[31];
            fin>>StrMas[i];
        }
        fin.close();
        
        const int ExperimentCount=11;
                  double MaxCountFull =0.999;
              double MasFull[ExperimentCount] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95, static_cast<double>(MaxCountFull)};
        
              CountHashTable = ceil( ( (CountWord/2)/MaxCountFull ) );
   
        HashTableMas = new int [CountHashTable];
      
       unsigned long long int AttemptsLuck = 0, AttemptsUnluck = 0, CountLuck = 0, CountUnluck = 0, AttemptsCount;
        
        for(int i=0; i<ExperimentCount;i++)
        {
            for(int j=0; j<CountHashTable; j++)
                  {
                      HashTableMas[j]=-1;
                  }
           int  K= (int)((CountWord/2)*MasFull[i]);
              Hashing(StrMas, K, HashTableMas, CountHashTable, 31, 10);
            
            CountLuck = 0; CountUnluck = 0;  AttemptsLuck = 0; AttemptsUnluck = 0;
              for(int j=0; j < K; j++)
              {
                  AttemptsCount=0;
                  if( Poisk(HashTableMas,  StrMas[j], CountHashTable, StrMas, 31, 10, AttemptsCount) )
                  {
                      AttemptsLuck+=AttemptsCount;
                      CountLuck ++;
                  }
                  else
                  {
                       AttemptsUnluck+=AttemptsCount;
                       CountUnluck ++;
                  }
                 
                  AttemptsCount=0;
                                 if( Poisk(HashTableMas,  StrMas[K+j], CountHashTable, StrMas, 31, 10, AttemptsCount) )
                                 {
                                        AttemptsLuck+=AttemptsCount;
                                        CountLuck ++;
                                 }
                                 else
                                 {
                                        AttemptsUnluck+=AttemptsCount;
                                     CountUnluck ++;
                                 }
              }
//             cout<<"L="<<CountLuck<<" "<<"U="<<CountUnluck<<"\n";
            cout<<MasFull[i]<<" "<<CountLuck<<" "<<AttemptsLuck/(double)CountLuck<<" "<<CountUnluck<<" "<<AttemptsUnluck/(double)CountUnluck<<"\n\n";
        }
       
        cout<<CountHashTable<<"\n";
        
        
     /*   for(int i=0; i<CountHashTable; i++)
             {
               cout<<HashTableMas[i]<<"\n";
             }*/
    }
    
  //  char test[5]={static_cast<char>(0x05), static_cast<char>(0xFF), static_cast<char>(0x04),static_cast<char>(0xFF),0};
  //  cout<< Hash(test);
    return 0;
}
