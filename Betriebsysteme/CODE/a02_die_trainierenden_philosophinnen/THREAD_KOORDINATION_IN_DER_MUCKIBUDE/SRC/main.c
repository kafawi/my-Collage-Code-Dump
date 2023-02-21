/**
 * @file    main.c
 * @author  bibut N kafawi
 * @version V0.7
 * @date    14.11.2016
 * @brief   Simulation of 5 philosophers who gain their mussels so
 *          we gain our knowledge of thread coordination.
 */

#include "global.h"
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "philo.h"
#include "gym.h"


#define NCMD_BUFF 4 // 2 for cmd, 1 for '/n' and 1 for '\0'

// global arrry for communication between main and other threads
extern char cmd_arr[];

char cmd_buff[NCMD_BUFF]={'\0'};

/* ------------------------------------------------- helping functions----*/
// INIT AND DESTROY
void init_obj(){
    init_gym_obj();
    init_philo_obj();
}

void free_obj(){
    free_philo_obj();
    free_gym_obj();
}

//  get an command from STDIN and removes the '\n' at the end
void get_cmd_from_stdin(char * const buff){
    void * ptrres=NULL; // result pointer to test success of lib function
    int index = EXIT_FAILURE;     // index where the newline char is
    ptrres = fgets( buff, NCMD_BUFF, stdin );
    handle_error(!ptrres, errno, "fgets failed");
    index = strcspn(buff, "\n");
    if ( 0 < index){
        buff[index]='\0';
    }
    return;
}
// getting the Thread identifier from the command buffer
int get_tid_from_buff(char * const buff){
    int tid=EXIT_FAILURE;
    int i=0;
    for (i = 0; NPHILO > i; i++){
        if( cmd_buff[0] == (i+'0') ){
            tid = i;
        }
    }
    return tid;
}

/* ************************************************************************* */
/* -------------------------------------------------------------------- MAIN */
int main(){
    int res=EXIT_FAILURE;          // result to test success of lib function
    int i = 0;          // loop index
    pthread_t philo_tid[NPHILO] = {0};

    // INITIALIZER
    init_obj();
    // start threads
    int philo_arg[NPHILO]={-1};
    for (i = 0; NPHILO > i; i++){
        philo_arg[i]=i;
        res = pthread_create(&philo_tid[i], NULL, philothread, &philo_arg[i]);
        handle_error(res, errno, "pthread create failed");
    }
    // CONTROLLER
    int running = TRUE;
    while(running){
        get_cmd_from_stdin(cmd_buff);
        if ( strcmp("q",cmd_buff) == 0 || strcmp("Q",cmd_buff) == 0 ){
            running = FALSE;
        } else { // teste ob
                int tid;
                tid = get_tid_from_buff(cmd_buff);
            if ( 0 <= tid ){
                switch (cmd_buff[1]){
                    case 'b': // block the thread tid
                        cmd_arr[tid] = 'b';
                        break;
                    case 'u': // unblock the blocked thread tid
                        cmd_arr[tid] = 'n';
                        unblock_philo(tid);
                        break;
                    case 'p': // jump out of the loop tid
                        cmd_arr[tid] = 'p';
                        break;
                    default:
                        printf("Invalid comand: %s \n", cmd_buff);
                }
            } else {
                printf("Invalid target: %s \n", cmd_buff);
            }
        }
    }
    // terminate all threads politely
    for (i = 0; NPHILO > i; i++){
        cmd_arr[i]='q';
    }
    
    // wake blocked threads
    for(i = 0; NPHILO > i; i++ ){
      unblock_philo(i);
    }
    
    // free trapped threads
    free_gym_threads();
    for (i = 0; NPHILO > i; i++){
        res = pthread_join(philo_tid[i] ,NULL);
        handle_error(res, errno, "pthread join failed");
    }
    free_obj();
    printf("Quit Succeed\n");
    return 0;
}
