import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
import datetime

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
    user_id = session["user_id"]
    transactions = db.execute("SElECT * FROM transactions WHERE user_id = ?", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)
    # [{"date":"2022-11-25 10:51:48","id":1,"price":291.5,"shares":1,"symbol":"NFLX","user_id":1}]
    return render_template("index.html", transactions=transactions, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except:
            return apology("Invalid Input")
        if not symbol:
            return apology("Must Provide Input")
        stock = lookup(symbol.upper())

        if stock == None:
            return apology("No Such Stock Exists")

        if shares <= 0:
            return apology("Shares Must Be Greater Than 0")

        amount_required_to_buy = shares * stock["price"]
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM USERS WHERE ID = ? ;", user_id)
        user_cash = cash[0]["cash"]

        if (user_cash < amount_required_to_buy):
            return apology("You Don't have Enough Money!!")

        updated_cash = user_cash - amount_required_to_buy
        db.execute("UPDATE users SET CASH = ? WHERE ID = ? ", updated_cash, user_id)
        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id,symbol,shares,price,date,Name) VALUES(?,?,?,?,?,?)",
                   user_id, stock["symbol"], shares, stock["price"], date, stock["name"])
        db.execute("INSERT INTO history (user_id,symbol,shares,price,date,name,type) VALUES(?,?,?,?,?,?,?)",
                   user_id, stock["symbol"], shares, stock["price"], date, stock["name"], "BUY")
        flash("Transaction Successful!!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        user_id = session["user_id"]
        history = db.execute("SElECT * FROM history WHERE user_id = ?", user_id)
        return render_template("history.html", history=history)


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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        quote = request.form.get("symbol")
        if not quote:
            return apology("Input Required")

        stock = lookup(quote.upper())
        if stock == None:
            return apology("Stock does not Exist")
        else:
            return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_pass = request.form.get("confirmation")
        if not username:
            return apology("A username Must be Provided")
        if not password:
            return apology("A Password Must be Provided")
        if not confirm_pass:
            return apology("A Confirmation Password Must be Provided")
        if password != confirm_pass:
            return apology("Different Passwords Entered")
        else:
            hash = generate_password_hash(password)
            try:
                db.execute("INSERT INTO users (username,hash) VALUES(?,?);", username, hash)
                return redirect("/login")
            except:
                return apology("Username Already Exists")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols_dict = db.execute("SELECT symbol FROM transactions WHERE user_id = ? ", user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_dict])

    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if (shares < 0):
            return apology("Shares Must be Greater Than 0 !")

        user_id = session["user_id"]
        user_shares = db.execute("SELECT shares FROM transactions WHERE user_id=? AND symbol=?", user_id, symbol)
        actual_shares = user_shares[0]["shares"]
        if (shares > actual_shares):
            return apology("You don't have that many shares !")

        shares_left = actual_shares - shares
        stock = lookup(symbol)
        pice = stock["price"]
        gain = shares * pice
        user_cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)
        actual_cash = user_cash[0]["cash"]
        updated_cash = actual_cash + gain
        db.execute("UPDATE users SET cash=? WHERE id=?", updated_cash, user_id)
        date = datetime.datetime.now()
        db.execute("UPDATE transactions SET shares=? WHERE user_id=?", shares_left, user_id)
        db.execute("INSERT INTO history (user_id,symbol,shares,price,date,name,type) VALUES(?,?,?,?,?,?,?)",
                   user_id, stock["symbol"], shares, stock["price"], date, stock["name"], "SELL")
        return redirect("/")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "GET":
        return render_template("change_password.html")

    password = request.form.get("password")
    confirm_pass = request.form.get("confirm_password")

    if (password != confirm_pass):
        return apology("Passwords Do Not Match!")

    hash = generate_password_hash(password)
    user_id = session["user_id"]
    db.execute("UPDATE users SET hash = ? WHERE id=?", hash, user_id)
    flash("Password Changed!")
    return redirect("/login")