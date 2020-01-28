import lyfe
from flask import Flask, render_template, request

app = Flask(__name__)
song_names = []

@app.route('/search', methods=['GET', 'POST'])
def lyr():
    global song_names
    song_names, list_names = lyfe.run(request.form['song'])
    return render_template("search.html", song_name=list_names)

@app.route('/', methods=['GET', 'POST'])
def index():
    return render_template("index.html")

@app.route('/result/<int:number>/', methods=['GET', 'POST'])
def result(number):
    global song_names
    lyrics = lyfe.fetch_lyrics(song_names, number)
    return render_template("result.html", song=lyrics)
