// ideen
// weight_type
typedef struct weight {
    const int kg;
    int amount
} weight_t;

// philo_thread_bag_type
typedef struct philo_tread_bag {
    const int workout_weigth_kg;
    const int threadnum;
  //const char name[6];
    mutex myMutex
} philo_tread_bag_t;


// globales char array für fgets
#define NCMD_ARR 3
export char cmd_arr[NCMD_ARR];
// 


// 
// we start at 10 to avoid other constants
enum { 
    GET_WEIGHTS = 10,
    WORKOUT,
    PUT_WEIGHTS,
    REST
} state_philo;

enum {
    NORMAL=20,
    BLOCKED,
    QUIT
}

#define REST_LOOP   10000000000
#define WORKOUT_LOOP  500000000
