import subprocess

def _bash_invoke(invoke_arr):
    with subprocess.Popen(invoke_arr, stdout=subprocess.PIPE, shell=True) as proc:
        ret = proc.stdout.read()
    return ret

KEY = """-----BEGIN RSA PRIVATE KEY-----
MIICXAIBAAKBgQCpsBSj2i7qj+T9bXUXIVhDDW2OOTVgsVVLZptTpffLowUlS4nv
41jteqjwwHtBGjtigUw7/iHRNckrsfLyC4t+tQfJWQutq4dDntGrqbdXNLsu/BLQ
19BDYt1B6tt9c924ccby5Qb+Uq6o0U7qukkhqWAMcmdfDGQrhBGJRGEC7wIDAQAB
AoGAGEAX0wrdZZxG54j7EOEtEfgbThYS8MynGe2CCURQ04Nqute+0M+258l911pK
wxUSo5NC59f70UBUjbASvlC0EJ4KUCVvjFpMPOBWsg9zRLzh4CKx21evvWO1Y5o/
1KxI2T2JvsZZOKg8Pabx0iFZFBv/HEEHgj879EMLQUoK/BECQQDWHt1nwBqi1BRX
WrbYF2j0ilM6x1UUwT9kF6GpSsrk90wzp1pB+mEJBqYy2Fj7TxP4aPcwCwKKA+NL
7uzq0ogbAkEAyuBxf31Fd6fIN+WIy5M+OQNLQfp3uqpKsXQHXZ/QkQuNzAJJbHAw
IouySFMB1WlQMK+SxKLKbAMlNLRXN34FvQJABJcizf+bUpRTX1ANjXJrCJsSj7cI
Ruqhrkana5az5Na8ZnsW/0Ub4XKoC30B41ldpzyw1/HUexr8O3uCzsH2swJBAIsI
b5/QSPgsisEL08i3us+1mzC3JrBNHe0ouBeIe5W7Vky2UH05ETPLir2X7UzE5IjI
+gs6CQEm0qug35iPC/0CQByZ0qq6xOgJoXWwm97hL/hNIdDG5GHqZR1OJkTBeOCX
KzItq1rrKmd9WtsBLGM1TESy+Ed8UvlxuM6HNWvSEHk=
-----END RSA PRIVATE KEY-----"""


print(KEY)

bash_cmd = ['echo', '$(echo', '"'+KEY+'"',')']
#print(bash_cmd)
print(_bash_invoke(bash_cmd))

git clone git@gitlab.informatik.haw-hamburg.de:CIES/TCDR.git ~/TESTPROJECTTCDR/