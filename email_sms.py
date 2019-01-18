import smtplib
import sys
from twilio.rest import Client

def email_sms(method, msg, dest, src, password):
        if method == "email":
                server = smtplib.SMTP('smtp.gmail.com', 587)
                server.starttls()
                server.login(src, password)
 
                server.sendmail(src, dest, msg)
                server.quit()
        if method == "sms":
                account_sid = # sid
                auth_token = # token
                client = Client(account_sid, auth_token)

                message = client.messages \
                        .create(
                                body=msg,
                                from_='+15017122661',
                                to=dest
                        )
                

method = sys.argv[1]
msg = sys.argv[2]
dest = sys.argv[3]
src = sys.argv[4]
password = sys.argv[5]

email_sms(method, msg, dest, src, password)