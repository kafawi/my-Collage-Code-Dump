#!/usr/bin/bash

UEMAIL=$1
UNAME=$2
CUSTOMER_ID=$3
CDR_ID=$4
CDR_NAME=$5
CAC_NAME=$6
ACCESS_TOKEN=$7
TSR_NAME=$8
CAC_ID=$9
REFREPORT=${10}
GITLAB_PATH=${11}

cd ..
git config --global user.email $EMAIL_USER
git config --global user.name $NEXUS_USER 
touch timer.txt
python3 ./CIES-Main/pyscripts/timestamp.py timer.txt
export TS=$(cat timer.txt) 
    # update gitlab-ci yaml (rm old, cp new)
cd ./CIES-Main/pyscripts 
python3 yaml_generator.py $CUSTOMER_ID $CDR_ID 
cd ../../
git clone "https://oauth2:"$ACCESS_TOKEN"@"$GITLAB_PATH/"CIES"/$TCAC".git"
cd $CAC_NAME
DIFF=$(diff .gitlab-ci.yml ../CIES-Main/pyscripts/.gitlab-ci.yml) || true
echo $DIFF
if [ "$DIFF" != "" ]; then
  rm -f .gitlab-ci.yaml
  /bin/cp ../CIES-Main/pyscripts/.gitlab-ci.yml .
  git add .gitlab-ci.yml
  git commit -m "UPDATE .gitlab-ci.yaml" -n
  git remote add tcac "https://"$GITLAB_PATH/$TCAC
  git remote set-url tcac "https://oauth2:"$ACCESS_TOKEN"@"$GITLAB_PATH/"CIES/"$CAC_NAME".git"
  git push tcac master
fi
cd ..
    # start trigger and reg test clone, add, commit push
    #  -> webhook to TCAC
git clone "https://oauth2:"$ACCESS_TOKEN"@"$GITLAB_PATH/"CIES"/$TSR_NAME".git"
cd $TSR_NAME
git remote add cdr "https://"$GITLAB_PATH/"CIES"/$CDR_NAME".git"
git remote set-url cdr "https://oauth2:"$ACCESS_TOKEN"@"$GITLAB_PATH/"CIES"/$CDR".git"
git pull tcdr master
ls
/bin/cp ../timer.txt timer.txt 
cat timer.txt
git add timer.txt
git commit -m "regtest" 
git push tcdr master
python3 ../CIES-Main/pyscripts/poll_pipeline.py $CAC_ID . master $ACCESS_TOKEN 10
GITSHA=$(git rev-parse HEAD)
python3 ../CIES-Main/pyscripts/validate_testreports.py $TCDR_ID $GITSHA /CIES/CIES-Main/regtest_ref/$REFREPORT