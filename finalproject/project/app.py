import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import time


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///list.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    """Show bucklist of locations"""

    if request.method == "POST":
        new = request.form.get("location")
        l = db.execute ("SELECT location FROM locations")
        lo = [d['location'] for d in l]
        if new != "":
            if new not in lo:
                db.execute("INSERT INTO locations (location) VALUES (?)", new)

    bucketlist = db.execute ("SELECT * FROM locations")

    return render_template("index.html", bl = bucketlist)

@app.route("/weather", methods=["GET", "POST"])
def weather():
    """show weather for searched locations via integrated API"""
       # return redirect("/")

    return render_template("weather.html")

@app.route("/maps", methods=["GET", "POST"])
def maps():
    """show google maps for searched locations via integrated API"""
       # return redirect("/")
    Q = "Brampton"
    if request.method == "POST":
        new = request.form.get("location")
        if new != "":
            Q = new
    print(Q)

    return render_template("maps.html", q=Q)
