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