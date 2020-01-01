import subprocess
from flask import Flask, render_template, request
from subprocess import Popen, PIPE, check_output

def turn_relay(value):
    session = subprocess.Popen("./relay "+ value, stdout=PIPE, stderr=PIPE, shell=True)
    stdout, stderr = session.communicate()
    if stderr:
        raise Exception("Error "+str(stderr))
    return stdout

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def home():
    if request.method == 'POST':
        if request.form.get("submit_button_on") == 'Relay on':
            turn_relay("on")
        if request.form.get("submit_button_off") == 'Relay off':
            turn_relay("off")    
    return render_template("index.html", title="blaaa")


app.run(host='0.0.0.0', debug=True)

