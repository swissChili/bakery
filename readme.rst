=========
Bakery v2
=========

.. image :: https://travis-ci.org/swissChili/bakery.svg?branch=v2

Building
--------
.. code-block :: bash

    mkdir target
    go build -o target/bake bakery.go
    sudo cp target/bake /usr/bin/bake

Usage
-----
.. code-block :: toml

    [main]
    from = ["get"]
    do = "go build -o target/bake bakery.go"

    [get]
    from = ["main"]
    do = "go get"

    [install]
    from = ["main"]
    do = "sudo cp target/bake /usr/bin/bake"

Note that two recipes can reference each other and they won't get stuck in a loop of
installing each other. 

Recipes are defined with ``[name]``, main is the default recipe name if no recipe is
provided as the first argument to ``bake``. 