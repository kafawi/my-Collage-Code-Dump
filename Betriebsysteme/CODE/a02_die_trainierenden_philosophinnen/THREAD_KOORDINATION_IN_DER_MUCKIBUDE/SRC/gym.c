/**
 * @file gym.c
 * @author bibutNkafawi
 * @version V0.7
 * @date 14.11.2016
 * @brief monitor functions and data structures for the synchronisation
 */

#include "gym.h"
#include "philo.h"

typedef struct {
    int kg;        // heavy
    int qty;       // quantity
} Weight_t;

struct{
    Weight_t weights[ NWEIGHTS_T ]; // slots
    int total_kg;                   // total amount of all weights in the gym
    int available_kg;               // amount what is left
} stock;

typedef struct {
    Weight_t weights [ NWEIGHTS_T ];  // slots
    int required_kg;                  // required_kg for a effective trainings
} Weight_bag_t;

Weight_bag_t bags[NPHILO];            // for every philo one bag


char output_buff[NOUTPUT_BUFF];


// SYNC OBJECTS
pthread_mutex_t gym_mtx;
pthread_cond_t gym_cv;

// condition for trapped threads to escape, used in get_weights
int is_quit = FALSE;

/* --------------------------------------------- private function prototypes */

int display_status( void);

/* ******************************************************** INIT AND DESTROY */
/* -------------------------------------------------------------------- init */

void init_stock(int *  kg, int * qty , const int nweights){
    // check if the arrays fit to the length
    int total_kg = 0;
    int i = 0;
    for (i = 0; i < nweights; i++){
        stock.weights[i].kg = kg[i];
        stock.weights[i].qty = qty[i];
        total_kg += qty[i] * kg[i];
    }
    stock.total_kg = total_kg;
    stock.available_kg = total_kg;
    return ;
}

void init_bags(
    int * kg, int nweights, int required_kg, Weight_bag_t * const bag
){
    int i = 0;
    for (i = 0; i < nweights; i++){
        bag->weights[i].kg = kg[i];
        bag->weights[i].qty = 0;
    }
    bag->required_kg = required_kg;
}

int init_gym_obj(){

    int kg[] =WEIGHT_KG;
    int qty[] =WEIGHT_QTY;
    init_stock(kg, qty , NWEIGHTS_T);
    int i;

    int required_kg[] = PHILO_KG;
    for (i = 0; NPHILO > i ; i++){
        init_bags(kg, NWEIGHTS_T, required_kg[i], &bags[i]);
    }
    // sync obj
    int res = EXIT_FAILURE;
    res = pthread_mutex_init(&gym_mtx, NULL);
    handle_error(res, errno,"Ptread mutex init for gym_mtx failed");
    res = pthread_cond_init(&gym_cv, NULL);
    handle_error(res, errno,"Ptread cond init for gym_cv failed");

    return EXIT_SUCCESS;

};

/* -------------------------------------------------------------------- free */
void free_gym_threads(){
    int res = EXIT_FAILURE;
    is_quit = TRUE;
    res = pthread_cond_broadcast( &gym_cv);
    handle_error(res, errno,"Ptread cond signal for gym_mtx failed");
    res = pthread_mutex_unlock( &gym_mtx );
    handle_error(res, errno,"Ptread mutex unlock for gym_mtx failed");
}

int free_gym_obj(){
    int res = EXIT_FAILURE;
    res = pthread_cond_destroy(&gym_cv);
    handle_error(res, errno,"Ptread cond destroy for gym_mtx failed");
    res = pthread_mutex_destroy(&gym_mtx);
    handle_error(res, errno,"Ptread mutex destroy for gym_mtx failed");
    // just display the last result
    printf("LAST STATUS:      --- ");
    display_status();
    return EXIT_SUCCESS;
}

/* ********************************************************* DISPLAY_STATUS */
// help functions
//  ------------------------------------------------------------ check status
int control_status(){
    int success = EXIT_FAILURE;

    int sum_bag_kg=0;
    int sum_stock_kg=0;
    // index vars for loop iteration
    int iweight = 0;
    int ibag = 0;
    for ( iweight = 0; NWEIGHTS_T > iweight; iweight++ ){
            sum_stock_kg +=
                stock.weights[iweight].qty *
                stock.weights[iweight].kg;
        for ( ibag = 0; NPHILO > ibag; ibag++ ){
            sum_bag_kg +=
                bags[ibag].weights[iweight].qty *
                bags[ibag].weights[iweight].kg;
        }
    }
    if (stock.available_kg != sum_stock_kg ){
        printf("available_kg and sum of stocked weights are different\n");
    }
    success = (sum_bag_kg  + sum_stock_kg) - stock.total_kg;
    return success;
}

/* *************************************************** STRING MANIPULATIONS */
// ------------------------------------ get and convert the cmd status to char
char get_cmd_char(int tid){
    char res='x';
    Cmd_state_t cmd_state = get_cmd_state(tid);
    switch (cmd_state){
        case QUIT :
            res = 'q';
            break;
        case BLOCKED:
            res = 'b';
            break;
        case NORMAL:
            res = 'n';
            break;
        default:
            printf("unknown cmd_state at thread %d\n", tid);
            res='x';
    }
    return res;
}
// ---------------------------------- get and convert the train status to char
char get_train_char(int tid){
    char res='X';
    Train_state_t train_state = get_train_state(tid);
    switch (train_state){
        case GET_WEIGHTS:
            res = 'G';
            break;
        case WORKOUT:
            res = 'W';
            break;
        case PUT_WEIGHTS:
            res = 'P';
            break;
        case REST:
            res = 'R';
            break;
        default:
            printf("unknown train_state at thread %d\n", tid);
            res='X';
    }
    return res;
}

/* -------------------------------------------- put weights info into buffer */
int sprint_weights_qty(char * buff,
                       Weight_t * const weights_arr,
                       int nweights){
    int res= EXIT_FAILURE;
    char weight_buff[NWEIGHT_BUFF]={'\0'};
    int i=0;
    void * ptrres = NULL;

    *buff = '\0';

    for(i=0; i < nweights; i++){
        if (nweights-1 > i ){
            res = sprintf(weight_buff,
                          FORMAT_WEIGHT ", ",
                          weights_arr[i].qty);
            if(0 > res) handle_error(EXIT_FAILURE , errno,"sprintf 2");
        } else {
            res = sprintf(weight_buff,FORMAT_WEIGHT, weights_arr[i].qty);
            if(0 > res) handle_error(EXIT_FAILURE , errno,"sprintf 2");
        }
        ptrres = strcat(buff,weight_buff);
        if (NULL == ptrres) handle_error(EXIT_FAILURE , errno,"strcat ");
    }
    res = sprintf(buff,"%s",buff);
    if(0> res) handle_error( EXIT_FAILURE, errno,"sprintf ");
    return res;
}

/* -------------------------------- put status info per from all into buffer */
void write_status_into_buff( char * const buff ){
    int res = EXIT_FAILURE;
    void * ptrres = NULL;

    char status_s[NSTATUS_BUFF];
    char weight_s[NWEIGHTS_BUFF];
    char supply_s[NSUPPLY_BUFF];
    int i = 0;
    *buff = '\0';

    for (i = 0; NPHILO > i ; i++){
        char cmd_c = get_cmd_char(i);
        char train_c = get_train_char(i);
        sprint_weights_qty(weight_s,bags[i].weights, NWEIGHTS_T);
        res = sprintf( status_s,
                       FORMAT_STATUS,
                       i,
                       bags[i].required_kg,
                       cmd_c, train_c,
                       weight_s );
        if ( 0 > res ) handle_error( EXIT_FAILURE, errno,"sprintf ");
        ptrres = strcat(buff,status_s);
        if (NULL == ptrres) handle_error(EXIT_FAILURE , errno,"strcat ");
    }
    sprint_weights_qty(weight_s, stock.weights, NWEIGHTS_T);
    res = sprintf(supply_s,FORMAT_SUPPLY,weight_s);
    if(-1> res) handle_error( EXIT_FAILURE, errno,"sprintf ");

    ptrres = strcat(buff,supply_s);
    if (NULL == ptrres) handle_error(EXIT_FAILURE , errno,"strcat ");
};

/* --------------------------------------------  display the current status */
int display_status(){
    int  success =  EXIT_FAILURE;

    success = control_status();
    if ( EXIT_FAILURE == success ){
        printf("Something went wrong: We have quantum tunneling!\n");
    }
    write_status_into_buff(output_buff);
    printf(output_buff);
    return success;
}

/* **************************************************************** MONITOR */
// helping function
/*--------------------------------------------------------- FLUSH BAG ------*/
void flush_bag(Weight_bag_t * bag){
    int i=0;
    for (i = 0; NWEIGHTS_T > i; i++){
        stock.weights[i].qty += bag->weights[i].qty;
        bag->weights[i].qty=0;
    }
    stock.available_kg += bag->required_kg;
    return;
}
/*---------------------------------------------------------- FILL BAG ------*/
int fill_bag_recu( const int required_kg,
                   const int index,
                   Weight_bag_t * const bag){

    int remain_kg = required_kg;
    int success = EXIT_FAILURE;

    int qty = required_kg/ stock.weights[index].kg;
    if ( stock.weights[index].qty < qty ){
        qty = stock.weights[index].qty;
    }

    while ( 0 <= qty){

        remain_kg = required_kg - stock.weights[index].kg * qty;
        if ( 0 == remain_kg ){
            success = EXIT_SUCCESS;
        } else {
            if ( 0 < index ){
                success = fill_bag_recu(remain_kg, index - 1, bag);
            } else {
                success = EXIT_FAILURE;
            }
        }

        if ( EXIT_SUCCESS == success ){
            bag->weights[index].qty = qty;
            stock.weights[index].qty -= qty;
            stock.available_kg -= qty * stock.weights[index].kg;
            break;
        } else if ( EXIT_FAILURE == success ){
            qty--;
        }
    }
    return success;
}
/* ------------------------------------------------- fill_bag wrapper ----- */
int fill_bag(Weight_bag_t * bag){
    int success = EXIT_FAILURE;
    int required_kg= bag->required_kg;
    if (stock.available_kg >= required_kg && 0 < required_kg){
    int weights_len = NWEIGHTS_T;
        success = fill_bag_recu(required_kg, weights_len--, bag);
    }
    return success;
}
//----------------------------------------------------------------------------
// main monitor functions
/* -------------------------------------------------------------GET_WEIGHTS */
int get_weights(int tid){

    int res = EXIT_FAILURE;
    int no_weights_fit_cond; // condition for the failure of fill_bag

    res = pthread_mutex_lock( &gym_mtx );
    handle_error(res, errno, "phtread_mutex_lock ");

    set_train_status(GET_WEIGHTS, tid);
    printf("Tid %d GET_WEIGHTS --- ", tid  );
    display_status();

    no_weights_fit_cond = fill_bag( &bags[tid] );
    while( no_weights_fit_cond && !is_quit ){
        res = pthread_cond_wait( &gym_cv, &gym_mtx);
        handle_error(res, errno, "phtread_cond_wait ");
        no_weights_fit_cond = fill_bag( &bags[tid] );
    }

    set_train_status(WORKOUT, tid);
    printf("Tid %d WORKOUT     --- ", tid  );
    display_status();

    res = pthread_mutex_unlock( &gym_mtx );
    handle_error(res, errno, "phtread_mutex_unlock ");
    return EXIT_SUCCESS;
}

/* -------------------------------------------------------------PUT_WEIGHTS */
int put_weights(int tid){
    int res= EXIT_FAILURE;
    res = pthread_mutex_lock( &gym_mtx );
    handle_error( res, errno,"pthread_mutex_lock ");

    set_train_status(PUT_WEIGHTS, tid);
    printf("Tid %d PUT_WEIGHTS --- ", tid  );
    display_status();

    flush_bag(&bags[tid]);

    res = pthread_cond_broadcast( &gym_cv );
    handle_error( res, errno,"pthread_cond_broadcast ");

    set_train_status(REST, tid);
    printf("Tid %d REST        --- ", tid  );
    display_status();

    res = pthread_mutex_unlock( &gym_mtx );
    handle_error( res, errno,"pthread_mutex_unlock ");
    return EXIT_SUCCESS;
}
