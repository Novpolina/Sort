#include <iostream> // TODO ???
#include <stdio.h>
#include <sys/stat.h>

// TODO this is a string not stringS
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

// TODO spaces
int CompareStrings(char* a, char* b);
FILE*  MakeFile();
int CountStrings(text onegin);
static text ReadTextFromFile (FILE * file_with_text, text onegin);
void PrintFile(text onegin);
text BubbleSortForStrings(text onegin);



int CompareInReverseOrder(strings a, strings b ){
    // TODO ints instead of size_t?
    int i = a.string_length;
    int j = b.string_length;
    while( i != 0 && j != 0){
        // TODO you evalute the same function twice, put it into a variable
        if(tolower(a.string_pointer[i]) >= tolower(b.string_pointer[i])){
            return 1;
        }
        // TODO why are they equal? Maybe -1?
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

// TODO comparators return < 0 if a is less than b
//                         = 0 if a equals b
//                         > 0 if a is greater than b
// This function is something like StringEqual and it should return a bool
// TODO           \/ const  \/ const
int CompareStrings(char* a, char* b){

    int i = 0;
    for(; a[i] != '\0' || b[i] != '\0'; i++){
        // TODO you evalute the same function twice, put it into a variable
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

// TODO add spaces between different parts of function logic
FILE*  MakeFile(){
    char filename[50] = ""; // TODO buffer is very small
    FILE* file_pointer = NULL;
    scanf("%s", filename); // TODO there could be a new line here
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

    // TODO why using a flag here? Strang algorythm
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
// TODO why static? I want to know if you know why.
// TODO                            \/ inconsistent code style
static text ReadTextFromFile (FILE * file_with_text, text onegin) {
    struct stat finfo;
    fstat(fileno(file_with_text), &finfo);

    //printf("uhbigvfuc");
    //file_with_text = fopen("Mockingbird.txt", "rb");
    // TODO why ints again?
    onegin.number_of_symbols = (int)finfo.st_size/sizeof(char);
    // TODO is buffer a valid c-string?
    onegin.buffer = (char *)calloc(onegin.number_of_symbols, sizeof(char));


    fread(onegin.buffer, sizeof(char), onegin.number_of_symbols,file_with_text);

    onegin.number_of_strings = CountStrings(onegin);
    onegin.strs_data = (strings*)calloc(onegin.number_of_strings, sizeof(strings));

    // TODO why int? And you can create several variables in for loop
    int j = 0;
    // TODO flags are usually bad practise and there is a better way to do it
    bool is_str_new = 1;

    printf("\n%i\n", onegin.number_of_symbols);

    for (size_t i = 0; i < onegin.number_of_symbols; i++){

        if(is_str_new == true){
            onegin.strs_data[j].string_pointer = &onegin.buffer[i];
            j++;
            is_str_new = 0; // TODO false?
        }

        if (onegin.buffer[i] == '\r'){
            onegin.buffer[i] = ' ';

        }
        if(onegin.buffer[i] == '\n'){
            onegin.buffer[i] = '\0';
            is_str_new = 1; // TODO true?
        }
        onegin.strs_data[j-1].string_length++;

    }
    PrintFile(onegin);
    return onegin;


}
void PrintFile(text onegin){
    // TODO onegin.number_of_strings is size_t, incorrect specifier
    printf("\nText %i:\n", onegin.number_of_strings);

    for(size_t i = 0; i < onegin.number_of_strings; i++){
        printf("%s", onegin.strs_data[i].string_pointer);
        // TODO string_length is size_t, incorrect specifier
        printf("%i \n", onegin.strs_data[i].string_length);

    }
    printf("\nEnd of Text:\n\n\n\n");
}

text BubbleSortForStrings(text onegin, int sort){
    // TODO initialization?
    strings temp;
    bool noSwap;

    // TODO do you really want to assign here?
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

    // TODO why twice?

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



