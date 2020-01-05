import subprocess
from flask import Flask, render_template, request
from subprocess import Popen, PIPE, check_output

def toggle_relay(value):
    session = subprocess.Popen("./relay " + value, stdout=PIPE, stderr=PIPE, shell=True)
    stdout, stderr = session.communicate()
    if stderr:
        raise Exception("Error "+str(stderr))
    return stdout

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def home():
    if request.method == 'POST':
        if request.form.get("espresso_button") == 'Espresso':
            toggle_relay("small")
        if request.form.get("lungo_button") == 'Lungo':
            toggle_relay("big")
    return render_template("index.html")


app.run(host='0.0.0.0', debug=True)

