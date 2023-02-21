#!/bin/bash
# filecount.sh
# Count the number of spacific file types in a directory

AUTHOR="Alex and Kalle"
VERSION="1.1"
UPDATE="20.10.2016"

#initialyse / default
# flags
VERBOSE=0
ECHOMODE=0
# vars
TYPES=''
LSOPTION="-l"
DIRECTORY="."

# Constants for getopt
SHORT_OPT=hVveflDda
LONG_OPT="help,version,verbose,echo,regular-file,symlink,device,directory,all"

#-----------------------------------------------------------------------------
usage()
{
cat<<EOF
usage :
  $0 [ OPTIONS ] DIRECTORY

    Print the number of files in DIRECTORY
    of types given in OPTIONS

    Default: Print numbers of regular files
    in current directory

OPTIONS :
FILE type options:
    -f --regular-file regular files
    -l --symlink      symbolic links
    -D --device       character and block devices
    -d --directory    directories
    -a --all          Include hidden files

Other options:
    -h --help     Display this text
    -e --echo     Print selected files
    -v --verbose  print debugging messages
    -V --version  print Versionsnumber
EOF
}
#-----------------------------------------------------------------------------
#sehr gesittetes Programm
version()
{
cat <<EOF
$0:
Version $VERSION, last update $DATE
coded by $AUTHOR
EOF
}
#-----------------------------------------------------------------------------
verbose_mode()
{
    VERBOSE=1
    echo -e "verbose mode activ: print debugging messages\n";
}
#-----------------------------------------------------------------------------
calc()
{
    if [ $ECHOMODE -eq 1 ]; then                             # ECHO MODE START
        if [ $VERBOSE -ne 0 ]; then
            echo -e "Choosen files will be printed. \n";
        fi
        ls $LSOPTION $DIRECTORY | egrep "^[$TYPES]" | tee      # ECHO MODE END
    else
        if [ $VERBOSE -ne 0 ]; then
            echo -e "Choosen files will be summed. \n";
        fi
    fi
    # Here is the magic
    ls $LSOPTION $DIRECTORY | egrep "^[$TYPES]" | wc -l
}
#-----------------------------------------------------------------------------
# ########################################################################## #
#                               main                                         #
# ########################################################################## #

# define getopt
ARGS=$(getopt -o $SHORT_OPT -l $LONG_OPT -n "filecount.sh" -- "$@");

# execute getopt with eval
eval set -- "$ARGS";

while true; do
    case "$1" in              # ---------------------------------- CASE beginn
        "-h" | "--help")                                                # HELP
            usage
            exit 0;
        ;;
        "-V" | "--version")                                          # VERSION
            version
            exit 0;
        ;;
        "-v" | "--verbose")                                          # VERBOSE
            verbose_mode
            shift
        ;;
        "-e" | "--echo")                                                # ECHO
            ECHOMODE=1
            if [ $VERBOSE -ne 0 ]; then
                echo -e "echo mode activ.\n";
            fi
            shift
        ;;
        "-f" | "--regular-file")                               # REGULAR FILES
            TYPES=$TYPES'-'
            if [ $VERBOSE -ne 0 ]; then
                echo -e "Option \"-f\" set";
                echo -e "\"Regular files\" get counted.\n";
            fi
            shift
        ;;
        "-l" | "--symlink")                                          # SymLink
            TYPES=$TYPES'l'
            if [ $VERBOSE -ne 0 ]; then
                echo -e "Option \"-l\" set";
                echo -e " \"symbolic links\" get counted.\n";
            fi
            shift
        ;;
        "-D" | "--device")                                           # DEVICES
            TYPES=$TYPES"cb" #set character and block devices
            if [ $VERBOSE -ne 0 ]; then
                echo -e "Option \"-D\" set";
                echo -e "\"Character and block devices\" get counted.\n";
            fi
            shift
        ;;
        "-d" | "--directory")                                    # DIRECTORIES
            TYPES=$TYPES'd'
            if [ $VERBOSE -ne 0 ]; then
                echo -e "Option \"-d\" set";
                echo -e "\" Directories\" get countet. \n";
            fi
            shift
        ;;
        "-a" | "--all")                                                  # ALL
            LSOPTION="-lA"        # almost all flags for all except .. .
            TYPES="-bcCdDlMnpPs?" # asterix doesnt work in a box
            if [ $VERBOSE -ne 0 ]; then
                echo -e "Option \"-a\" set"
                echo -e "\"All files (including hidden)\" get counted.\n";
            fi
            shift;
        ;;
        --)                                                       # OPTGET END
            shift;
            break;
    esac
done                                    # ---------------------OPTION CASE end

if [ ! -z $1  ]; then # is there anything else ?
# anything else should be directory
  if [ -d $1 ]; then    # test if it is an valid
      DIRECTORY=$1
  else
    echo -e "\"$1\" is not a driectory";
    echo -e "type \"$0 --help\" for more information\n";
    exit 1;
  fi
  if [ $2 ]; then    # is there an other argument
    echo -e "too many arguments"
    echo -e "type \"$0 --help\" for more information\n"
    exit 1;
  fi
fi

if [ -z $TYPES ]; then  # is the length of TYPE 0 (empty)?
    TYPES='-';
fi

# This is just for debug purpose
if [ $VERBOSE -ne 0 ]; then
    echo -e "Arguments for calc are:";
    echo -e "DIRECTORY: $DIRECTORY";
    echo -e "VERBOSE:  $VERBOSE   TYPES:    $TYPES"
    echo -e "ECHOMODE: $ECHOMODE  LSOPTION: $LSOPTION \n"
fi
calc                                                   # START THE Calculation
exit 0
