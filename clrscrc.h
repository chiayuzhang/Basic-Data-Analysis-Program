#if defined(__linux__) || defined(__APPLE__)
    #define clear "clear"
#else
    #define clear "cls"
#endif

void clrscr(){
    system(clear);
}