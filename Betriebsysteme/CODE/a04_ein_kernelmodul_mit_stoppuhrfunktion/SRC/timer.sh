#!/bin/bash 

#
#
# ###################################################################### VARS
TIMER_NAME="timer"
major="0"
TIMERF_NAME="timerf";
TIMERF_MINOR="0"
TIMERR_NAME="timerr";
TIMERR_MINOR="1"

group=""
USER="root"
GROUP1="staff"
GROUP2="users"
MODE="777"

# --------------------------------------------------------------------- FLAGS
LOAD_TIMER=0;
UNLD_TIMER=0;


# ----------------------------------------------------------------- testvalues
wt_s=3;
# --------------------------------------------------------------------- usage
usage()
{
cat << EOF
USAGE:
  $0 [OPTIONS] 

  load or unload $TIMER_NAME kernel module
  also
  create or delete device nodes $TIMERF_NAME and $TIMERR_NAME

  also set up two terminals with one is showing debug messages

  OPTIONS:
    -l --load    Load module and create device nodes
    -u --unload  Unload module and delete device nodes
    -s --setup   open two terminals, one to observe the kernel log and 
                 the other to make more commands like 'echo r > /dev/timerr'
    -h --help    Display this text
EOF
}
# --------------------------------------------------------------------- setup
setup()
{
    xterm -geometry 160x50+504+0 -title "log" -e "sudo \
        tail -f /var/log/messages | \
        awk -v FS='kernel: '  '/timer:/ { print \$2 }' " &

    xterm -geometry 80x50+0+0 -title cmd -e "su" &
    return 0
}
# ---------------------------------------------------------------- timer_test
timer_test()
{
     echo "++++++++++++++++++++++++++++++++++++++++++ /dev/$TIMERF_NAME test"
     echo "+++++ cat +++++"
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo l - l 20000 - kaudawelsch - p - c - r +++++"
     echo l > /dev/$TIMERF_NAME
     echo l 20000 > /dev/$TIMERF_NAME
     echo kaudawelsch > /dev/$TIMERF_NAME
     echo p > /dev/$TIMERF_NAME
     echo c > /dev/$TIMERF_NAME
     echo r > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo s -> cat 3 times   +++++"
     echo s > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo l 100 - c - s      +++++"
     echo l 100 > /dev/$TIMERF_NAME
     echo c > /dev/$TIMERF_NAME
     echo s > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo p -> cat 3 times in 3 sec +++++"
     echo p > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo l 100 - p - s      +++++"
     echo l 100 > /dev/$TIMERF_NAME
     echo p > /dev/$TIMERF_NAME
     echo s > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo c -> cat 3 times   +++++"
     echo c > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep 1
     cat /dev/$TIMERF_NAME
     sleep $wt_s
     echo "+++++ echo r                  +++++"
     echo r > /dev/$TIMERF_NAME
     cat /dev/$TIMERF_NAME
     echo "++++++++++++++++++++++++++++++++++++++ /dev/$TIMERF_NAME test end"
     echo "------------------------------------------ /dev/$TIMERR_NAME test"
     echo "----- cat                     -----"
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo s - l - kaudawelsch - p - c - r -----"
     echo s > /dev/$TIMERR_NAME
     echo l > /dev/$TIMERR_NAME
     echo kaudawelsch > /dev/$TIMERR_NAME
     echo p > /dev/$TIMERR_NAME
     echo c > /dev/$TIMERR_NAME
     echo r > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo l 200000           -----"
     echo l 200000 > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo l 33333 - p - c    -----"
     echo l 33333 > /dev/$TIMERR_NAME
     echo p > /dev/$TIMERR_NAME
     echo c > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo s -> cat 3 times   -----"
     echo s > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo l 100 - c - s      -----"
     echo l 100 > /dev/$TIMERR_NAME
     echo c > /dev/$TIMERR_NAME
     echo s > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo p -> cat 3 times   -----"
     echo p > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo l 100 - p - s      -----"
     echo l 100 > /dev/$TIMERR_NAME
     echo p > /dev/$TIMERR_NAME
     echo s > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo c -> cat 3 times   -----"
     echo c > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo r -----"
     echo r > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- RUN OUT TEST :  echo  l 5000 - s (5 sec) -----"
     echo l 5000 > /dev/$TIMERR_NAME
     echo s > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep 1
     cat /dev/$TIMERR_NAME
     sleep $wt_s
     echo "----- echo s - l 100 - p - c - r -----"
     echo s > /dev/$TIMERR_NAME
     echo l 100 > /dev/$TIMERR_NAME
     echo p > /dev/$TIMERR_NAME
     echo c > /dev/$TIMERR_NAME
     echo r > /dev/$TIMERR_NAME
     cat /dev/$TIMERR_NAME
     echo "------------------------------------- /dev/$TIMERR_NAME test end"
}

# ---------------------------------------------------------------------- load
load()
{
    
    #delete old divice nodes and remove kernel module hide errors
    unload 2> /dev/null
    # load new kernel module
    #echo -e "load $TIMER_NAME.ko\n"

    /sbin/insmod $TIMER_NAME.ko
    
    # get major number
    #major=$( awk "\\$2==\"$TIMER_NAME\" {print \\$1}" /proc/devices )
    major=$( cat /proc/devices | grep $TIMER_NAME | cut -d " " -f 1 );
    #create device nodes
    echo -e "-- ${major} ${TIMERF_MINOR} --\n"
    mknod /dev/$TIMERF_NAME c ${major} ${TIMERF_MINOR}
    mknod /dev/$TIMERR_NAME c ${major} ${TIMERR_MINOR}

    # give appropriate groupe/permissions, and change the group.
    # Not all distributions have 'staff', some have 'wheel' instead
    group=GROUP1

    grep -q ^$GROUPE1: /etc/group || group=$GROUP2
    chown $USER /dev/${TIMER_NAME}?
    chgrp $group /dev/${TIMER_NAME}?
    chmod $MODE /dev/${TIMER_NAME}?

    return 0
}
# ------------------------------------------------------------------- unload 
unload()
{
    # delete device nodes
    rm -f /dev/$TIMERF_NAME
    rm -f /dev/$TIMERR_NAME
    # remove kernel module
    /sbin/rmmod $TIMER_NAME.ko

    return 0
}
# ######################################################################### #
#                                                                      MAIN #
# ######################################################################### #

ARGS=$(getopt -o hstlu -l help,setup,test,load,unload -n 'timer.sh' -- "$@");

eval set -- "$ARGS";

while true; do
    case "$1" in
        -h | --help)
            usage;
            exit 0;
            ;;
        -s | --setup)
            setup;
            exit 0;
            ;;
        -t | --test)
            timer_test;
            exit 0;
            ;;
        -l | --load)
            LOAD_TIMER=1;
            shift;
            ;;
        -u | --unload)
            UNLD_TIMER=1;
            shift;
            ;;
        --)
            shift;
            break;
            ;;
        "")
            echo -e "Nothing to do\n";
            usage;
            exit -2;
            ;;
        *)
            echo -e "Invalid argumet:  $1 \n";
            exit -3;
            ;;
    esac;
done

#echo -e "LOAD $LOAD_TIMER UNLOAD $UNLD_TIMER \n"

if [ 0 -ne $LOAD_TIMER ] && [ 0 -ne $UNLD_TIMER ]; then
    echo -e "Either load or unload $TIMER_NAME \n";
elif [ 0 -ne $LOAD_TIMER ]; then
    load 
elif [ 0 -ne $UNLD_TIMER ]; then
    unload 
fi

exit 0
# EOF
