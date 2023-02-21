#!/usr/bin/env python3
"""Generate report-delivery.sh or analyze.sh for anaylsis pipeline in cac
"""
__author__ = "kafawi"

import argparse
import json
from jinja2 import Template
from data_handler import CiesData

DEFAULT_OUT_SEND_PATH = "./report-delivery.sh"
DEFAULT_IN_SEND_TEMP = "./Templates/tpl-report-delivery.sh"
DEFAULT_OUT_ANALYZE_PATH = "./analyze.sh"
DEFAULT_IN_ANALYZE_TEMP = "./Templates/tpl-analyze.sh"

PROJECT_DIR = "./PROJECT/"
REPORT_DIR = "./REPORTS/"
SCRIPT_DIR = "./SCRIPTS/"

USER_PUBKEY = """ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAAAgQDDmkK5KGxCrAgXe+fcWxfjAPAZd5CLrGPqzUSDnjo1z7nkFEwkxPaiR9ckYmuYOChLQhI8XInkntkio51GhzfNpbwssB6sg1x55l7y+bE0p/NojDfPxRwdzaARhj6btU6cs3CAAxZJmnfKEbe+P4uDyb5qAiOuREho5cCknGFPbQ== phpseclib-generated-key""" 
USER_PRIKEY = """-----BEGIN RSA PRIVATE KEY-----
MIICWwIBAAKBgQDDmkK5KGxCrAgXe+fcWxfjAPAZd5CLrGPqzUSDnjo1z7nkFEwk
xPaiR9ckYmuYOChLQhI8XInkntkio51GhzfNpbwssB6sg1x55l7y+bE0p/NojDfP
xRwdzaARhj6btU6cs3CAAxZJmnfKEbe+P4uDyb5qAiOuREho5cCknGFPbQIDAQAB
AoGAD/SrcLMtcZra5h+DYGRF5IyVCV7JebtMQ0EPT7U+hlk1jrdhJrayb7ZwhFVK
9ZXPI6R2HFpoHTAgAkVadQBeutEiWFNkABwVKNHxyKu9PDDbGwcGZsi+VlosEdUl
VHalA+a85heXEGeniaQVtWBbEdHeucXBC1n7ugtrdMdyszkCQQDzBczxDpMSTyN8
gASWrmxnjiYz9LiBm8aof47IYX/2mtBZ8QN+GbyJwavrFOvu+U7RSMJ5nBDBt5cB
lpLIQJMzAkEAzgw2ShvnQLjSrGdgqo61klCT7800Ollnf2uYnYheTt1u4y47RmRF
3zMiepBc/YPVJyujrfAM2CJ9E+IKBxqS3wJARNtq4w43G6PysQ7wveTz8C91oZkA
QjDqC8oAocQGZtAcoq9IRw1xvzJxzKzj4JUhAOl1uNFAajLjhV6tfjHVwwJAcl5y
7/XHCbTNM2b6UBGAlWNmig+z8sNXYHG/t4lPF6VvfGhX/H2CDx8Z/0AMbad0dBaT
9uMsrfeOx6+K82B7rwJANJ8LT3/qkNrUlUWom53tIotp1FbxKCDddh1G4UWdH9c8
09UKLpj36sKfopTP0fCCso8K54g2XNqQgoDmeCPjtw==
-----END RSA PRIVATE KEY-----"""
CDR_PUSH_PUBKEY = """ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAAAgQCowAnsy7tlQDG1935Y/w2lLK+6ONeF2yMS5ZmbxCQ4wPNFks3rRlzR/kYVRAMMJDBlt0BTn9bFK55Xjc6IMX4wF7+kdp4O6B4Txq2WNGsjPg5JQ5cH1lXliiOKz5Gi+qhT86SH150w3acVOa2SLlkagNgi8ctO2aov9NWlWZXRgw== phpseclib-generated-key"""
CDR_PUSH_PRIKEY = """-----BEGIN RSA PRIVATE KEY-----
MIICXQIBAAKBgQCowAnsy7tlQDG1935Y/w2lLK+6ONeF2yMS5ZmbxCQ4wPNFks3r
RlzR/kYVRAMMJDBlt0BTn9bFK55Xjc6IMX4wF7+kdp4O6B4Txq2WNGsjPg5JQ5cH
1lXliiOKz5Gi+qhT86SH150w3acVOa2SLlkagNgi8ctO2aov9NWlWZXRgwIDAQAB
AoGAQIlxQkaIXKi4WkdU4uRoa4sziZzDkEXGnCuDG7dfwvTIFQuYBSrbxNPiKa/h
Gnucpsn2qASxNqb/36w0GJIVF+ArL8jRPQIyXM4Wrei/lpRyA713wLE9cYY452UK
MFJEs+iu8+ktw19GweO0Ydd5AkDp/MQvauqNyaa0Bw+qJwECQQDd52mZCptbZgWN
l0riq35gPZEfezZigycFLIqFY53BUivOuuSslNAZ8XieNp2BNnNMHbXoBW5/MlQ8
xitYdo5zAkEAwq3Sj8beozIkR8JrB2rVxSHwHkWCbYzvWFNwvq7nwzaNp92pIbNa
LRg5jHKRhY7nAKKXDmNCtoyR42QR8uRcsQJBALcMBqqs+jyp6tjCvY4/ow7mmoja
jaEzyQNWm6mu49ot2188Ahhu5T8RVstECCcncHKQa5bKrDyWmrBLVEQ0AAsCQDvJ
pFPxkGhwOsIrDDGv9sze+l5hnIfGc68dmQ+GqbjDJUf7hDjMWxJkUTA380cgNwNz
645In7FuhFNgZT7CMVECQQC26KL6daNDyua4hiAiKcNvGFj7kB7xkFisc42zCrH0
TG6EM5VFOzLC23FflJ6xZhHxVZX9HJGUU1gqtgaHIB8k
-----END RSA PRIVATE KEY-----"""
CLONE_CDR_PUBKEY = """ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAAAgQC7MJuOWXyo7u925+Q+fohcONf5k6dQ7fqpiD/UMjzPzo59wc+l2uKi6paeE3oyUkpS/wnjwYDNMJ+aQPnGRAtDas/fgotyS/khh6Im8s9fyMuoVCzcpMndPoqNS+fXP8R4nKInonsm4ND+vN4MdcfPDbdDW3IBCZIGLMsUi9+lWw== phpseclib-generated-key"""
CLONE_CDR_PRIKEY = """-----BEGIN RSA PRIVATE KEY-----
MIICXAIBAAKBgQC7MJuOWXyo7u925+Q+fohcONf5k6dQ7fqpiD/UMjzPzo59wc+l
2uKi6paeE3oyUkpS/wnjwYDNMJ+aQPnGRAtDas/fgotyS/khh6Im8s9fyMuoVCzc
pMndPoqNS+fXP8R4nKInonsm4ND+vN4MdcfPDbdDW3IBCZIGLMsUi9+lWwIDAQAB
AoGAXAug0jSKqf8j3VJV160cnEyPVvgWFCORWH/Y8xzo7j5hrtD4rFOfkgDMo1ps
ggYY6gri8A2cqkk4kf9VUvrulhaWEf2dsyzVhQ0EYkO5UgCGvxvsz39iw9XSe63n
8stKxeaP+t6VKvKupKYh9UD2KxgabwRgMCdlGDzWsOaX6/ECQQDk1SociW1o7cpo
weGovBjevQJh9d9p613EI4Sx91Vxg+Q6dv8EFpK5gtjUobFtRtjsX6Ufp3l8AQp/
JqvCZw8FAkEA0WnOra4gERDSkIKR9oZSm+IiLvBG9rFJmRRLP1265YPzRUkYhRlm
w2f0hZFYImO6OynmZ8Zc2ZRasBThjkhQ3wJAJ0DRqneAhyFTOUkY1oL9mSe/AuLU
Yiz3tq+JEaYlyAUh302OTTs6DAx/+WmLL/2ZNGLrxlRKKJVdIZaWnBBlqQJAW9zr
YjsJLBNSGzx75UYFRQaM8kRLDPq2i2VgoPpv+zDH7bPkArci4kNe+5zHqcZPspZt
0UYuAvBWW/m8/FpyxwJBAKi462jWHVfmmM/I92RoJljFI/CppoMlUd7sygKThF8m
Z+AJaJP8m8abap7ByzjJggMs+Csx8oFkMBiUKxUVgZQ=
-----END RSA PRIVATE KEY-----"""
UPDATE_CAC_PUBKEY = """ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAAAgQCpsBSj2i7qj+T9bXUXIVhDDW2OOTVgsVVLZptTpffLowUlS4nv41jteqjwwHtBGjtigUw7/iHRNckrsfLyC4t+tQfJWQutq4dDntGrqbdXNLsu/BLQ19BDYt1B6tt9c924ccby5Qb+Uq6o0U7qukkhqWAMcmdfDGQrhBGJRGEC7w== phpseclib-generated-key"""
UPDATE_CAC_PRIKEY = """-----BEGIN RSA PRIVATE KEY-----
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

def init_test(cdr_id, pip_id, gitsha, email):
    print("init_test(", cdr_id, ", ", pip_id, ", ", gitsha, ", ", email,")")
    db = CiesData()
    db.get_project(cdr_id)
    SET_DIC = {
        'projectpublickey'     : USER_PUBKEY,
        'cdrprivatekey'        : USER_PRIKEY,
        'cacprivatekey'        : CDR_PUSH_PRIKEY,
        'cacpublickey'         : CDR_PUSH_PUBKEY,
        'clone_cdr_publickey'  : CLONE_CDR_PUBKEY,
        'clone_cdr_privatekey' : CLONE_CDR_PRIKEY,
        'update_cac_publickey' : UPDATE_CAC_PUBKEY,
        'update_cac_privatekey': UPDATE_CAC_PRIKEY,
    }
    db.update_project(cdr_id, SET_DIC)
    db.get_project(cdr_id)
    
def clean_test(cdr_id, pip_id, gitsha, email):
    print("clean_test(", cdr_id, ", ", pip_id, ", ", gitsha, ", ", email,")")
    db = CiesData()

    #db.rm_credential(rmail)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="generates bash script for analyse")
    parser.add_argument("-i", nargs=4, metavar=('cdr_id', 'pip_id', 'gitsha', 'email'),
                        help="init tests with project etc")
    parser.add_argument("-c", nargs=4, metavar=('cdr_id', 'pip_id', 'gitsha', 'email'),
                        help="clean up tests residuals")
    args = parser.parse_args()
    if not args.i and not args.c:
        parser.print_help()
    else:
    	if args.i:
    	   #for e in args.i:
    	   #    print(type(e), e)
           init_test(int(args.i[0]), int(args.i[1]), str(args.i[2]), str(args.i[3]))

    	#if args.c:
           #clean_test(int(args.c[0]), int(args.c[1]), str(args.c[2]), str(args.c[3]))