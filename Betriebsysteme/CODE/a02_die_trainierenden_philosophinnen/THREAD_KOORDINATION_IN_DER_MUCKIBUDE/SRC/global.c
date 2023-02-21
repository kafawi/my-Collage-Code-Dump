#include "global.h"
//#include <assert.h>



void handle_error(
    int result, int num, char const *mssge
//    , char const *line, char const *file, char const *func
){
    if ( EXIT_FAILURE == result ){
        errno = num;
        perror(mssge);
//        PRINT_POSITION(line, file, func);
//        assert( result );      //  terminates with abort (it is dirty)
        exit(EXIT_FAILURE);
    }
}
