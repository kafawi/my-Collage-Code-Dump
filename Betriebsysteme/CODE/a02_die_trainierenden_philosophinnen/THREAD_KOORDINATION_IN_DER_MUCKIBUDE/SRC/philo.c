/**
 * @file    philo.c
 * @author  bibut and kafawi
 * @version V0.7
 * @date    13.11.2016
 * @breif   functions, data and controlobjects for philosophen (threads)
 */

#include "philo.h"
#include "gym.h"


char cmd_arr[NPHILO]= {'n'}; // defines the global array and set it to normal

Philo_t philo_data[NPHILO]; // Data and controlobjects

/* ----- helping functions -------------- */
/**
 * Helping function for the complex handle, if the thread is asked to block
 * itself
 * @param  tid
 */
void cmd_block(int tid){ // --------------------------------------- CMD_BLOCK
    int res=0;
    philo_data[tid].cmd_state = BLOCKED;
    res = sem_wait( &(philo_data[tid].block_sem));
    handle_error(res, errno,"BLOCK on one philo thread failed.");
    philo_data[tid].cmd_state=NORMAL;
    return;
}

/* -------------------------------------------------------------- ACTIVITY */
void workout(int tid){ // ------------------------------------------- WORKOUT
    int i = 0;
    for (i=0; WORKOUT_LOOP > i; i++){
        if ( 'b' == cmd_arr[tid]){
            cmd_block(tid);
        } else if ( 'p' == cmd_arr[tid]){
            cmd_arr[tid]='n';
            return;

        } else if ( 'q' == cmd_arr[tid]){
            philo_data[tid].cmd_state = QUIT;
            return;
        }
    }
    return;
}

void rest(int tid){ // ------------------------------------------------- REST
    int i=0;
    for (i = 0; REST_LOOP > i; i++){
        if ( 'b' == cmd_arr[tid]){
            cmd_block(tid);
        } else if ( 'p' == cmd_arr[tid]){
            cmd_arr[tid]='n';
            return;
        } else if ( 'q' == cmd_arr[tid]){
            philo_data[tid].cmd_state = QUIT;
            return;
        }
    }
    return;
}
// ----------------------------------------------------------- THREAD FUNC */
void * philothread (void * arg){ // ----------------------------- PHILOTHREAD
    int tid = * (int*) arg;

    while(philo_data[tid].cmd_state != QUIT){

        get_weights(tid);


        workout(tid);
        if (philo_data[tid].cmd_state == QUIT){
            break;
        }

        put_weights(tid);

        rest(tid);
    }
    pthread_exit(NULL);
}

/* ------------------------------------------------------ INIT AND DESTROY */
void init_philo_obj(){ // ------------------------------------ INIT_PHILO_OBJ
    int res=0;
    int i=0;
    for (i=0; NPHILO > i; i++ ){

        res = sem_init( &(philo_data[i].block_sem), 0, 1);
        handle_error(res, errno,"Semaphore init for philo thread failed.");

        philo_data[i].cmd_state=NORMAL;
        philo_data[i].train_state=GET_WEIGHTS;

        philo_data[i].tid=i;
        cmd_arr[i]='n';
    }
    return;
}

void free_philo_obj(){ // ------------------------------------ FREE_PHILO_OBJ
    int res=EXIT_FAILURE;
    int i=0;
    for (i=0; NPHILO > i; i++ ){
        res = sem_destroy( &(philo_data[i].block_sem));
        handle_error(res, errno,"Semaphore destroy for philo thread failed.");
    }
    return;
}

/* ------------------------------------------------------------- GET_N_SET */
Cmd_state_t get_cmd_state(int tid){ // ------------------------ GET_CMD_STATE
    return philo_data[tid].cmd_state;
}

Train_state_t get_train_state(int tid){ // ------------------ GET_TRAIN_STATE
    return philo_data[tid].train_state;
}

void set_train_status(Train_state_t train_state, int tid){// SET_TRAIN_STATUS
    philo_data[tid].train_state = train_state;
    return;
}

// ********************************************************** SOMETHING TO SAY
// ------------------------------------------------------------ for termination
// befor refactoring quid_philo
// but we dont this fiunktio so coment out
/*
void quit_philo(){
  int i=0;
    for (i = 0; NPHILO > i; i++){
        cmd_arr[i] = 'q';
    }
}
*/

void unblock_philo(int tid){ // ------------------------------- UNBLOCK_PHILO
    int res=EXIT_FAILURE;
    res = sem_post( &(philo_data[tid].block_sem));
    handle_error(res, errno,"CMD Unblock for one philo thread failed.");
}
