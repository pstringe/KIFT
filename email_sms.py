import smtplib
import sys

def email_sms(method, msg, dest, email, password):
        if method == "email":
                server = smtplib.SMTP('smtp.gmail.com', 587)
                server.starttls()
                server.login(email, password)
 
                server.sendmail(email, dest, msg)
                server.quit()
                

method = sys.argv[1]
msg = sys.argv[2]
dest = sys.argv[3]
email = sys.argv[4]
password = sys.argv[5]

email_sms(method, msg, dest, email, password)