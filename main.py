import os
from flask import Flask, jsonify, request, send_from_directory, render_template, abort, json, make_response, flash, session, redirect, url_for
from flask_cors import CORS, cross_origin
import codecs

app = Flask(__name__)
app.config['SECRET_KEY'] = 'gdAJL5239,as$<:dsagsj21'
CORS(app)

# Основная страница
@app.route('/')
def index():
    return render_template('index.html', title='Timeline')

# Загрузка файла на сервер
@app.route('/upload', methods=['POST', 'GET'])
def upload():
    txt = ""
    if request.method == 'POST':
        file = request.files['file']
        if file:
            try:
                txt = file.read()
                flash("Файл успешно загружен", 'success')
            except FileNotFoundError as e:
                flash("Ошибка загрузки файла", 'error')
        else:
            flash("Ошибка загрузки файла", 'error')

    file = open("data.txt", "w")
    txt = txt.decode('utf-8')
    file.write(txt)
    file.close()
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True, port=80)