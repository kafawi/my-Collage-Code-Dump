#!/usr/bin/bash

# template for the analyze bash job
SRCDIR="{{projectroot}}"
{% if (lang == "cpp" or not lang ) -%}
echo $SRCDIR
src=$(find $SRCDIR -name "*.cpp")
altsrc=$(find $SRCDIR -name "*.cc")
headers=$(find $SRCDIR -name "*.h")
altheaders=$(find $SRCDIR -name "*.hpp")
echo $src
echo $altsrc
plists=$(find $SRCDIR -name "*.plist")
clang++ -Wextra -pedantic --analyze ${src} ${altsrc} ${headers} ${altheaders} 2> compile_report.txt
clang++ -Wextra -pedantic -fsyntax-only --analyze ${src} ${altsrc} ${headers} ${altheaders} 2> syntax_report.txt
cat compile_report.txt syntax_report.txt >> report.txt
rm -f syntax_report.txt compile_report.txt

cat ${src} ${altsrc} ${headers} ${altheaders} > total.txt
linesTotal=$(wc -l < total.txt)
rm total.txt

javac /pyscripts/JsonCreator.java
java JsonCreator ${linesTotal} $SRCDIR
rm report.txt
rm JsonCreator.class
rm -f ${plists}
{%- endif %}

