#!/usr/bin/env bash

echo "[TeSSA:Codeanalyse] Neuer Report Projekt:{{ p.cdr_name }} Commit:{{ r.gitsha }}" > mailhead.txt
cat > mailbody.txt << EOF
Hallo {{ c.name }},

Ihr Code wurde von uns analysiert. Der Bericht ist angehängt.

Durchführung: {{ r.timestamp }}
Projekt: {{ p.cdr_name }}
Commit: {{ r.gitsha }}

Mit freundlichem Gruß, Ihr TeSSA BreakIT TEAM
EOF

sendEmail -v \
-f "{{ e.email }}" \
-s {{ e.server }}:{{ e.port }} \
-o tls=yes \
-xu "{{ e.email }}" -xp "{{ e.pw }}" \
-o message-charset=utf-8 \
-t "{{ p.email }}" \
-u $(cat ./mailhead.txt) \
-o message-file="./mailbody.txt" \
-a ./report.json


PT91dGYtOD9xPzIwMTgtMDUtMjVfMjA9M0E0OT0zQTU3PTJFMjk3Mjg2Pz0=
dXRmODogMjAxOC0wNS0yNSAyMDo0OTo1Ny4yOTcyODYgw7bDtsO2ZmZnZw==