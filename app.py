import subprocess
from flask import Flask, render_template, request
from subprocess import Popen, PIPE, check_output

def toggle_relay():
    session = subprocess.Popen("./relay", stdout=PIPE, stderr=PIPE, shell=True)
    stdout, stderr = session.communicate()
    if stderr:
        raise Exception("Error "+str(stderr))
    return stdout

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def home():
    if request.method == 'POST':
        if request.form.get("submit_button") == 'Relay on':
            toggle_relay()
    return render_template("index.html")


app.run(host='0.0.0.0', debug=True)

