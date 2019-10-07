import lyfe
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/search', methods=['GET', 'POST'])
def lyr():
    song_names = lyfe.run(request.form['song'])
    return render_template("search.html", song_name=song_names)

@app.route('/', methods=['GET', 'POST'])
def index():
    return render_template("index.html")
