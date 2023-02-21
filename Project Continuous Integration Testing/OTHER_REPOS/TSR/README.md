# TSR

This is a test dummy to test the analysis toolchain.
It is a extern repo of the CIES project that imitates a customers repo.
The counterparts are the Projects TCDR and TCAC.

set up:
'''
git remote add tcdr https://141.22.27.227/CIES-Team/TCDR.git
'''
start pipeline:
'''
git remote set
git push tcdr
'''

## Directorys
### / 
project description
### /<language_extention>
dummy source code that smells
#### /CPP/HELLO_WORLD/
##### style
mozilla style with indent of 2 spaces
##### main.cpp
style smells:
 - line 3: opening brace of function main is on the wrong line.
 - line 6: indent is wrong

code smells:
 - line 4: var 'dimension' is not init

## TODO
 - code smells have to be tested with analysis tool CIES uses to get the correct output to validate the test.