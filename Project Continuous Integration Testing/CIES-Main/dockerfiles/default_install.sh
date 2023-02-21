#!/usr/bin/bash

# default packages and programs
apt-get update -yqq
apt-get install curl git -yqq
apt-get install python3 -yqq
apt-get install python3-pip -yqq
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade argparse pymongo argparse jinja2
apt-get install ssh -yqq
