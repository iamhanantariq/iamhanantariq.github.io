import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import time

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = session["user_id"]
    d = db.execute("SELECT stock, shares FROM stocks WHERE stockid = ?", user)
    g = []

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
    total = cash[0]["cash"]

    for i in d:
        stock = lookup(i["stock"])
        g.append(dict(stock=stock["symbol"], name=stock["name"], shares=i["shares"], price=stock["price"]))
        total += i["shares"] * stock["price"]

    return render_template("index.html", stocks=g, cash=cash, total=total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stks = request.form.get("symbol")
        shares = request.form.get("shares")

        if lookup(stks) == None:
            return apology("Put in da symbol boi", 400)
        if shares == "" or int(shares) <= 0:
            return apology("Don't be cheap, buy more", 400)

        shares = int(shares)
        stock = lookup(stks)
        buyat = stock["price"]

        user = session["user_id"]
        cash = db.execute("SELECT cash from users where id = ?", user)
        #get cash based on user id, do the math and update a table (create it in sql first) for each unique person
        spend = shares*buyat
        if spend > cash[0]["cash"]:
            return apology("You're too poor!", 300)

        db.execute("INSERT INTO orders (orderid, stock, price, shares, time) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)", user, stock["symbol"], buyat, shares)

        #stocks on hand for user X
        z = db.execute("SELECT stock from stocks where stockid = ?", user)
        stocks = [d['stock'] for d in z]

        #if new purchase INSERT elif UPDATE
        if stock["symbol"] not in stocks:
            db.execute("INSERT INTO stocks (stock, shares, stockid) VALUES (?, ?, ?)", stock["symbol"], shares, user)
        else:
            soh = db.execute("SELECT shares from stocks where stockid = ? AND stock = ?", user, stock["symbol"])
            db.execute("UPDATE stocks SET shares = ? WHERE stockid = ? AND stock = ?", soh[0]["shares"] + shares, user, stock["symbol"])

        #update the cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"] - spend, user)
        return redirect("/")

    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock = request.form.get("symbol")
        if lookup(stock) == None:
            return apology("Invalid stock boitoi", 400)
        share = lookup(stock)
        return render_template("quoted.html", sh=share, cost=usd(share["price"]))
    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        z = db.execute("SELECT * FROM users WHERE username = ?", username)
        check = [d['username'] for d in z]
        if username == "" or username in check:
            return apology("Invalid username or already used", 400)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password == "" or password != confirmation:
            return apology("Fix yo password boi", 400)

        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        return redirect("/")

    return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #inputs
    user = session["user_id"]
    stks = request.form.get("symbol")
    shares = request.form.get("shares")

    #pull users stock list
    z = db.execute("SELECT stock from stocks where stockid = ?", user)
    stocks = [d['stock'] for d in z]

    if request.method == "POST":

        shares = int(shares)
        stock = lookup(stks)
        sellat = stock["price"]

        if lookup(stks) == None or stock["symbol"] not in stocks:
            return apology("Put in da symbol boi", 400)
        if shares == "" or int(shares) <= 0:
            return apology("Don't be cheap, buy more", 400)

        cash = db.execute("SELECT cash from users where id = ?", user)
        soh = db.execute("SELECT shares from stocks where stockid = ? AND stock = ?", user, stock["symbol"])
        #get cash based on user id, do the math and update a table (create it in sql first) for each unique person
        sell = shares*sellat
        coh = cash[0]["cash"]

        if soh[0]["shares"] < shares or sell > coh:
            return apology("Too many shares or not enough money!", 400)

        db.execute("INSERT INTO orders (orderid, stock, price, shares, time) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)", user, stock["symbol"], sellat, shares)
        db.execute("UPDATE stocks SET shares = ? WHERE stockid = ? AND stock = ?", soh[0]["shares"] - shares, user, stock["symbol"])

        #update the cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"] + sell, user)
        return redirect("/")

    return render_template("sell.html", stocks=z)
