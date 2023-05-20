import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

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

    x = db.execute("SELECT symbol,amount FROM stocklist where id==?",session["user_id"])
    cash = db.execute("SELECT cash from users where id==?",session["user_id"])
    cash = cash[0]['cash']
    sum = cash
    L = []
    for i in x:
        D = {}
        a = lookup(i["symbol"])
        D["symbol"] = i["symbol"]
        D["shares"] = i["amount"]
        D["TOTAL"] = a["price"] * i["amount"]
        D["price"] = a["price"]
        D["name"] = a["name"]
        sum += D["TOTAL"]
        D["TOTAL"] = usd(D["TOTAL"])
        D["price"] = usd(D["price"])
        L.append(D)
    return render_template("index.html",x=L,y=usd(cash),z=usd(sum))


    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method== "POST":
        x = request.form.get("symbol")
        y = request.form.get("shares")
        z = lookup(x)
        if z==None:
            return apology("Invalid Symbol",400)
        if not y:
            return apology("Blank Shares", 400)
        if "-" in y or "." in y or "/" in y:
            return apology("INvalid",400)
        try:
            y = int(float(y))
        except ValueError:
            return apology("Invalid Share", 400)

        cash = db.execute("SELECT cash from users where id = ?",session["user_id"])
        cash = cash[0]["cash"]
        price = z["price"]
        cost = price * y
        remainder = cash - cost
        if remainder < 0:
            return apology("Insufficient funds",400)
        check = db.execute("SELECT * from stocklist where id = ? and symbol = ?",session["user_id"],x)
        if len(check)==0:
            db.execute("INSERT INTO stocklist(id,symbol,amount) VALUES(?,?,?)",session["user_id"],x,0)

        old = db.execute("SELECT amount from stocklist where id = ? AND symbol = ?",session["user_id"],x)
        old = old[0]["amount"]
        new = old + y
        db.execute("UPDATE stocklist SET amount = ? WHERE id = ? AND symbol = ?",new,session["user_id"],x)
        db.execute("UPDATE users SET cash = ? WHERE id = ?",remainder,session["user_id"])

        return redirect("/")

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
    """Get stock quote."""
    if request.method=="POST":
        x = request.form.get("symbol")
        y = lookup(x)
        if y== None:
            return apology("Invalid Symbol",400)

        return render_template("quoted.html",name=y['name'],symbol=y['symbol'],price=y['price'])

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method=="POST":
        if not request.form.get("username"):
            return apology("must provide username",400)

        elif not request.form.get("password"):
            return apology("must provide password",400)

        elif not request.form.get("confirmation"):
            return apology("must verify password",400)

        elif request.form.get("password") !=request.form.get("confirmation"):
            return apology("password must match",400)

        x = generate_password_hash(request.form.get("password"))
        y = request.form.get("username")
        z = db.execute("SELECT * FROM users WHERE username = ?", y)
        if len(z)!=0:
            return apology("Username taken")
        db.execute("INSERT INTO users(username,hash) VALUES(?,?)",y,x)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        x = request.form.get("symbol")
        y = request.form.get("share")
        z = lookup(x)
        if not y:
            return apology("Blank Shares", 400)
        if "-" in y or "." in y or "/" in y:
            return apology("INvalid",400)
        try:
            y = int(float(y))
        except ValueError:
            return apology("Invalid Share", 400)
        stock = db.execute("SELECT amount from stocklist where id = ? and symbol = ?",session["user_id"],x)
        stock = stock[0]["amount"]
        if y > stock:
            return apology("greater than owned shares",400)
        stock = stock - y
        cash = db.execute("SELECT cash FROM users where id = ?",session["user_id"])
        cash = cash[0]["cash"]
        cash = cash + (z["price"]*y)
        if stock==0:
            db.execute("DELETE from stocklist where id = ? and symbol = ?",session["user_id"],x)
        else:
            db.execute("UPDATE stocklist set amount = ? where id = ? and symbol = ?",stock,session["user_id"],x)

        db.execute("UPDATE users set cash = ? where id = ?",cash,session["user_id"])

        return redirect("/")

    else:
        x = db.execute("SELECT symbol from stocklist where id = ?",session["user_id"])
        return render_template("sell.html",x=x)
