#!/usr/bin/env python3
import smtplib
import os.path as op
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.header import Header
from email.message import Message
from email.utils import COMMASPACE, formatdate
from email import encoders, message_from_string


class MailHelper:
    """
    helper class for email actions
    """

    SMTP_PREFIX = "smtp."
    IMAP_PREFIX = "imap."
    POP3_PREFIX = "pop3."

    def __init__(self, user_name, user_email, user_password, host="localhost", smtp_prefix=SMTP_PREFIX,
                 imap_prefix=IMAP_PREFIX):
        """

        :param user_name:
        :param user_email:
        :param user_password:
        :param host:
        :param smtp_prefix:
        :param imap_prefix:
        """
        self.user = (user_name, user_email, user_password)
        self.host = host
        self.smtppf = smtp_prefix
        self.imappf = imap_prefix
        print("init")

    def _pack_msg(self, to, cc, bcc, subject, text, files=[]):
        """

        :param to:
        :param cc:
        :param bcc:
        :param subject:
        :param text:
        :param files:
        :return:
        """
        msg = MIMEMultipart()
        msg['From'] = self.user[1]
        if isinstance(to, list):
            msg['To'] = COMMASPACE.join(to)
        elif isinstance(to, str):
            msg['To'] = to
        if cc:
            if isinstance(cc, list):
                msg['Cc'] = COMMASPACE.join(cc)
            elif isinstance(cc, str):
                msg['Cc'] = cc
        if bcc:
            if isinstance(bcc, list):
                msg['Bcc'] = COMMASPACE.join(bcc)
            elif isinstance(bcc, str):
                msg['Bcc'] = bcc
        msg['Date'] = formatdate(localtime=True)
        msg['Subject'] = Header(subject, 'utf-8')
        msg.attach(MIMEText(text.encode('utf-8'), 'plain', 'utf-8'))
        for path in files:
            part = MIMEBase('application', "octet-stream")
            with open(path, 'rb') as file:
                part.set_payload(file.read())
            encoders.encode_base64(part)
            part.add_header('Content-Disposition',
                            'attachment; filename="{}"'.format(op.basename(path)))
            msg.attach(part)
        return msg

    def send(self, to, subject, text, files=[], port=587, cc=None, bcc=None, debug=False, prefix=False):
        """send an email via smtp

        :param to: reciver mail addr
        :param subject: subject of email
        :param text: body
        :param files: attachment
        :param port: server port
        :param cc: reciever mail addrs in cc
        :param bcc: secret reciever mail addrs
        :param debug: debug message toggle
        :param prefix: prefix toggle
        """
        msg = self._pack_msg(to, cc, bcc, subject, text, files)
        host = self.host
        print(msg)
        if prefix:
            host = self.smtppf + host
        host.strip()
        print(host)
        print(port)
        with smtplib.SMTP(host, port) as server:
            try:
                if debug:
                    server.set_debuglevel(True)
                server.ehlo()
                server.starttls()
                server.ehlo()
                server.login(self.user[0], self.user[2])
                server.sendmail(self.user[1], to, msg.as_string())
            except:
                print('Something went wrong...')

    def _encode_email(self, raw_email):
        """

        :param raw_email:
        :return:
        """
        content = []
        coname = []
        text = None
        email = message_from_string(raw_email)
        if email.is_multipart():
            for part in email.walk():
                charset = part.get_content_charset()
                contype = part.get_content_type()
                if charset:
                    if 'text/' in contype:
                        text = part.get_payload(decode=True).decode(charset)
                elif contype:
                    if 'multipart/' in contype:
                        print('raw_email')
                    elif 'application/octet-stream' in contype:
                        coname.append(part.get_filename())
                        content.append(part.get_payload(decode=True).decode('utf-8'))
        return text, content, coname

    def get(self, subject, textkey, port=993, service='imap', debug=False, prefix=False):
        """retrieves text and attatched files of an email with subject and textkey in body

        :param prefix:
        :param subject:
        :param textkey:
        :param port:
        :param service:
        :param debug:
        :param new:
        :return:
        """
        print(subject, textkey, port)
        txt = None
        content = None
        coname = None
        if service == 'pop3':
            import poplib
            print("using POP3, not implemented yet, using imap")
            service = 'imap'

        if service == 'imap':
            print("using IMAP4")
            import imaplib
            host = self.host
            if prefix:
                host = self.imappf + self.host
            with imaplib.IMAP4_SSL(host, port) as server:
                if debug:
                    server.debug = 4
                server.login(self.user[0], self.user[2])
                server.select()
                msg = Message()
                b = subject
                h = Header(subject, 'utf-8')
                msg['Subject'] = h
                subject = msg.as_string().strip("Subject: ").strip()
                criteria = 'HEADER Subject "'+ subject +'"'
                result, data = server.uid('search', None, criteria)
                if result == 'OK' and len(data[0].split()) == 0:
                    criteria = 'SUBJECT "' + subject + '"'
                    result, data = server.uid('search', None, criteria)
                if result == 'OK':
                    uids = data[0].split()
                    nuids = len(uids)
                    for i in range(nuids):
                        result, data = server.uid('fetch', uids[-1 * i], '(RFC822)')
                        if result == 'OK':
                            raw_email = data[0][i].decode('utf-8')
                            txt, content, coname = self._encode_email(raw_email)
                        if txt:
                            if textkey in txt:
                                break
                        else:
                            txt = None
                            content = None
                            coname = None
                server.logout()
        return txt, content, coname
