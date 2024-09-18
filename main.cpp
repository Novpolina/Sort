#include <iostream>
#include <stdio.h>
#include <sys/stat.h>

struct text{
    size_t number_of_symbols;
    size_t number_of_strings;
    char** text_pointers;
    char* buffer;
};

int CompareStrings(char* a, char* b, int size_a, int size_b){

    int i = 0;
    for(; a[i] != '\n' || b[i] != '\n'; i++){
        if(tolower(a[i]) >= tolower(b[i])){
            return 1;
        }
        else if(tolower(a[i]) <= tolower(b[i])){
            return -1;
        }

    }
    if (a[i] == '\n'){
        return -1;
    }


    return 1;

}

FILE*  MakeFile(text onegin){
    char* filename;
    FILE* file_pointer = NULL;
    scanf("%s", &filename);
    file_pointer = fopen(filename, "b");
    while(file_pointer == NULL){
        printf("Enter the correct name");
        scanf("%s", &filename);
        file_pointer = fopen(filename, "b");
    }
    return file_pointer; 

}

int CountStrings(text onegin){
    bool is_str_new = true;
    int number_of_strings = 0;
    for(int i = 0; i < onegin.number_of_symbols; i++){
        if(is_str_new == true){
            number_of_strings++;
            is_str_new = false;
        }

        if (onegin.buffer[i] == '\r' || onegin.buffer[i] == '\n'){
            is_str_new = true;

        }


    }
}

static void ReadTextFromFile (FILE * file_with_text, text onegin) {
    struct stat finfo;
    fstat(fileno(file_with_text), &finfo); 
    onegin.number_of_symbols = (int)finfo.st_size/sizeof(char);
    onegin.buffer = (char*)calloc(onegin.number_of_symbols, sizeof(char));


    fread(onegin.buffer, sizeof(char), onegin.number_of_symbols,file_with_text);  

    onegin.number_of_strings = CountStrings(onegin);

    int j = 0;
    bool is_str_new = 1;

    for (int i = 0; i < onegin.number_of_strings; i++){ 

        if(is_str_new == true){
            onegin.text_pointers[j] = &onegin.buffer[i]; 
            j++;
            is_str_new = 0;
        }

        if (onegin.buffer[i] == '\r' || onegin.buffer[i] == '\n'){
            is_str_new = 1;

        }
        

    }


}

void BubbleSortForStrings(text onegin){
    char* tmp;
    bool noSwap;

    for (int i = onegin.number_of_strings - 1; i >= 0; i--)
    {
        noSwap = 1;
        for (int j = 0; j < i; j++)
        {
            
            if (strcmp(onegin.text_pointers[j], onegin.text_pointers[j+1]))
            {
                tmp = onegin.text_pointers[j];
                onegin.text_pointers[j] = onegin.text_pointers[j + 1];
                onegin.text_pointers[j + 1] = tmp;
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }
}


int main(){

    
    return 0; 

}
