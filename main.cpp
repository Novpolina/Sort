#include <iostream>
#include <stdio.h>
#include <sys/stat.h>

struct strings{
    char* string_pointer;
    int string_length;

};


struct text{
    size_t number_of_symbols;
    size_t number_of_strings;
    //char** text_pointers_with_no_sort;
    //char** text_pointers;
    strings* strs_data;

    char* buffer;
};

int CompareStrings(char* a, char* b);
FILE*  MakeFile();
int CountStrings(text onegin);
static text ReadTextFromFile (FILE * file_with_text, text onegin);
void PrintFile(text onegin);
text BubbleSortForStrings(text onegin);



int CompareInReverseOrder(strings a, strings b ){
    int i = a.string_length;
    int j = b.string_length;
    while( i != 0 && j != 0){
        if(tolower(a.string_pointer[i]) >= tolower(b.string_pointer[i])){
            return 1;
        }
        else if(tolower(b.string_pointer[i]) >= tolower(a.string_pointer[i])){
            return 0;
        }
        i--;
        j--;
        
    }
    if(i == 0){
        return 0;
    }
    return 1;

}

int CompareStrings(char* a, char* b){

    int i = 0;
    for(; a[i] != '\0' || b[i] != '\0'; i++){
        if(tolower(a[i]) >= tolower(b[i])){
            return 1;
        }
        else if(tolower(a[i]) <= tolower(b[i])){
            return 0;
        }

    }
    if (a[i] == '\0'){
        return 0;
    }


    return 1;

}

FILE*  MakeFile(){
    char filename[50] = "";
    FILE* file_pointer = NULL;
    scanf("%s", filename);
    file_pointer = fopen(filename, "rb");
    printf("%s", filename);
    while(file_pointer == NULL){
        printf("Enter the correct name \n");
        scanf("%s", filename);
        printf("%s", filename);
        file_pointer = fopen(filename, "rb");
    }
    return file_pointer; 

}

int CountStrings(text onegin){
    bool is_str_new = true;
    int number_of_strings = 0;
    for(size_t i = 0; i < onegin.number_of_symbols; i++){
        if(is_str_new == true){
            number_of_strings++;
            is_str_new = false;
        }

        if (onegin.buffer[i] == '\n'){
            is_str_new = true;

        }
    }
    return number_of_strings;
}

static text ReadTextFromFile (FILE * file_with_text, text onegin) {
    struct stat finfo;
    fstat(fileno(file_with_text), &finfo); 

    //printf("uhbigvfuc");
    //file_with_text = fopen("Mockingbird.txt", "rb");
    onegin.number_of_symbols = (int)finfo.st_size/sizeof(char);
    onegin.buffer = (char *)calloc(onegin.number_of_symbols, sizeof(char));


    fread(onegin.buffer, sizeof(char), onegin.number_of_symbols,file_with_text);  

    onegin.number_of_strings = CountStrings(onegin);
    onegin.strs_data = (strings*)calloc(onegin.number_of_strings, sizeof(strings));

    int j = 0;
    bool is_str_new = 1;

    printf("\n%i\n", onegin.number_of_symbols);

    for (size_t i = 0; i < onegin.number_of_symbols; i++){ 

        if(is_str_new == true){
            onegin.strs_data[j].string_pointer = &onegin.buffer[i]; 
            j++;
            is_str_new = 0;
        }

        if (onegin.buffer[i] == '\r'){
            onegin.buffer[i] = ' ';

        }
        if(onegin.buffer[i] == '\n'){ 
            onegin.buffer[i] = '\0';
            is_str_new = 1;
        }
        onegin.strs_data[j-1].string_length++;

    }
    PrintFile(onegin);
    return onegin;


}
void PrintFile(text onegin){
    printf("\nText %i:\n", onegin.number_of_strings);

    for(size_t i = 0; i < onegin.number_of_strings; i++){
        printf("%s", onegin.strs_data[i].string_pointer);
        printf("%i \n", onegin.strs_data[i].string_length);

    }
    printf("\nEnd of Text:\n\n\n\n");
}

text BubbleSortForStrings(text onegin, int sort){
    
    strings temp;
    bool noSwap;

    if(sort = 1){
        for (int i = 0; i < onegin.number_of_strings - 1; i++) {

            for (int j = (onegin.number_of_strings - 1); j > i; j--)  {
                if (CompareStrings(onegin.strs_data[j - 1].string_pointer, onegin.strs_data[j].string_pointer)) {
                    temp = onegin.strs_data[j - 1]; // меняем их местами
                    onegin.strs_data[j - 1] = onegin.strs_data[j];
                    onegin.strs_data[j] = temp;
                }
            }
        }



    }
    

    for (int i = 0; i < onegin.number_of_strings - 1; i++)
    {
        for (int j = (onegin.number_of_strings - 1); j > i; j--) // для всех элементов после i-ого
        {
            if (CompareStrings(onegin.strs_data[j - 1].string_pointer, onegin.strs_data[j].string_pointer)) // если текущий элемент меньше предыдущего
            {
                temp = onegin.strs_data[j - 1]; // меняем их местами
                onegin.strs_data[j - 1] = onegin.strs_data[j];
                onegin.strs_data[j] = temp;
            }
        }
    }
    return onegin;
}


int main(){
    text onegin = {};
    FILE* filepointer = fopen("Mockingbird.txt", "rb");
    onegin = ReadTextFromFile(filepointer, onegin);
    onegin = BubbleSortForStrings(onegin);
    PrintFile(onegin);
    free(onegin.buffer);
    free(onegin.strs_data);
    
    return 0; 

}



