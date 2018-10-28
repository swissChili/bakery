from flask import Flask
app = Flask(__name__)

@app.route("/")
def root():
    return "Hello, Bake CD!"

if __name__ == "__main__":
    print("Running!")
    app.run("0.0.0.0", 80)