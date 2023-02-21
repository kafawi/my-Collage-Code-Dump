#!/bin/bash
# filecount.sh
# Count the number of spacific file types in a directory

AUTHOR="Alex and Kalle"
VERSION="0.4"
UPDATE="16.10.2016"

#initialyse / default

VERBOSE=0
TYPES=''
EMPTY=''
ECHOMODE=0
LSOPTION="-l"
DIRECTORY="."
#------------------------------------------------------------------------------
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
  -f --regular-file  regular files
  -l --symlink       symbolic links
  -D --device        character and block devices
  -d --directory     directories
  -a --all           Include hidden files

Other options:
  -h --help          Display this text
  -e --echo          Print selected files
  -v --verbose       print debugging messages
  -V --version       print Versionsnumber
EOF
}
#------------------------------------------------------------------------------
#sehr gesittetes Programm
version()
{
cat <<EOF
$0:
Version $VERSION, last update $DATE
coded by $AUTHOR
EOF
}
#------------------------------------------------------------------------------
verbose_mode()
{
  VERBOSE=1
  echo -e "verbose mode: es werden Debugging-Nachrichten ausgegeben \n"
}
#------------------------------------------------------------------------------
calc()
{
  if [ $ECHOMODE -eq 1 ]; then
    if [ $VERBOSE -ne 0 ]; then
      echo -e "Choosen files will be summed together and printed out."
    fi
    echo -e "Result:"
  ls $LSOPTION $DIRECTORY | egrep "^[$TYPES]" | tee
  else
    if [ $VERBOSE -ne 0 ]; then
      echo -e "Choosen files will be summed and result gets printed"
    fi
    echo -e "Result:"
    ls $LSOPTION $DIRECTORY | egrep "^[$TYPES]" | wc -l
  fi
}
#------------------------------------------------------------------------------
#
# ########################################################################### #
#                                    main                                     #
# ########################################################################### #
while [ $1 ]
do
  arg=$1
  shift
  case $arg in               # ----------------------------------- CASE beginn
    "-h" | "--help")                                              # HELP
      usage
      exit 1
    ;;
    "-V" | "--version")                                        # VERSION
      version
      exit 1
    ;;
    "-v" | "--verbose")                                        # VERBOSE
      verbose_mode
      continue
    ;;
    "-e" | "--echo")                                              # ECHO
      ECHOMODE=1
      if [ $VERBOSE -ne 0 ]; then
        echo -e "echo mode activ.\n"
      fi
      continue
    ;;
    "-f" | "--regular-file")                             # REGULAR FILES
      TYPES=$TYPES'-'
      if [ $VERBOSE -ne 0 ]; then
        echo -e "Option \"-f\" set"
        echo -e "\"Regular files\" get counted.\n"
      fi
      continue
    ;;
    "-l" | "--symlink")                                        # SymLink
      TYPES=$TYPES'l'
      if [ $VERBOSE -ne 0 ]; then
        echo -e "Option \"-l\" set"
        echo -e " \"symbolic links\" get counted.\n"
      fi
      continue
    ;;
    "-D" | "--device")                                         # DEVICES
      TYPES=$TYPES"cb" #set character and block devices
      if [ $VERBOSE -ne 0 ]; then
        echo -e "Option \"-D\" set"
        echo -e "\"Character and block devices\" get counted.\n"
      fi
      continue
    ;;
    "-d" | "--directory")                                  # DIRECTORIES
      TYPES=$TYPES'd'
      if [ $VERBOSE -ne 0 ]; then
        echo -e "Option \"-d\" set"
        echo -e "\" Directories\" get countet. \n"
      fi
      continue
    ;;
    "-a" | "--all")                                                # ALL
      LSOPTION="-lA"     # almost all flas for all except .. .
      TYPES="?"   # here is missng , cause it doesn't work in a box
      if [ $VERBOSE -ne 0 ]; then
        echo -e "Option \"-a\" set"
        echo -e "\"All files (including hidden)\" get counted.\n"
      fi
      continue
    ;;                         # ---------------------- OPTION CASE end
    *)                                   # anything else should be directory
      if [ -d "$arg" ]; then  # test if it is an valid
        DIRECTORY=$arg
      else
        echo -e "\"$arg\" is not a driectory"
        echo -e "type \"$0 --help\" for more information"
        exit 1
      fi
      if [ "$1" ]; then  # is there an other argument
        echo -e "too much arguments"
        echo -e "type \"$0 --help\" for more information"
        exit 1;
      fi
    ;;
  esac                      # ---------------------------------- CASE END
done
if [[ -z $TYPES ]]; then         # is the length of TYPE 0 (empty)?
  TYPES='-';
fi
echo -e "$TYPES $VERBOSE $ECHOMODE $LSOPTION"
calc                                                    # START THE Calculation
exit 0
