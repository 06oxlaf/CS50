import os
import sqlite3
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure sesgsion to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
#if not os.environ.get("API_KEY"):
#    raise RuntimeError("API_KEY not set")


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
    user = session["user_id"]
    index = db.execute("SELECT * FROM shares WHERE id = ?", user)
    return render_template("index.html", index=index)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("Shares must be positive")
        try:
            Quote = lookup(symbol)
            name = Quote["name"]
            price = int(Quote["price"])
            user = session["user_id"]
            cash = (db.execute("SELECT cash FROM users WHERE id = ?", user))
            cash =  cash[0]["cash"] - (shares*price)
            n = db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user)
            db.execute("INSERT INTO shares (id, symbol, name, price, total) VALUES (?, ?, ?, ?, ?)", user, symbol, name, price, (shares*price))
            if cash < 0:
                return apology("Sorry you dont have enough cash")
            return redirect("/")
        except:
            return apology("Symbol is not valid")
    else:
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            Quote = lookup(symbol)
            name = Quote["name"]
            price = Quote["price"]
            return render_template("quoted.html", name=name, price=price)
        except:
            return apology("Symbol is not valid")
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("You have not entered a username")
        if not password:
            return apology("You have not entered a password")
        if confirmation != password:
            return apology("Your passwords do not match")
        hash = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return redirect("/login")
        except:
            return apology("Username exist")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("Shares must be positive")
        Quote = lookup(symbol)
        name = Quote["name"]
        price = int(Quote["price"])
        user = session["user_id"]
        try:
            Numshares = (db.execute("SELECT symbol FROM shares WHERE id = ? AND symbol = ?", user, symbol))
            cash =  cash[0]["cash"] - (shares*price)
            n = db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user)
            db.execute("INSERT INTO shares (id, symbol, name, price, total) VALUES (?, ?, ?, ?, ?)", user, symbol, name, price, (shares*price))
            if cash < 0:
                return apology("Sorry you dont have enough cash")
            return redirect("/")
        except:
            return apology("You do not have enough shares")
    else:
        return render_template("buy.html")
    return apology("TODO")
