#!/bin/bash
#############################################################################################################
## Bakery BakeTools                                                                                        ##
## This file will be automatically `source`d in your Bakery by `bake`, don't need to include it manually.  ##
#############################################################################################################

declare -A ingredients
declare -A ingredient_links
declare -A flags
compiler="g++"
c_standard="c++17"
target="bin"
baketools_cpp="/usr/bin/baketools"
name="unnamed-bake-container"
image="ubuntu:18.04"
container_location="/app"
port="4000"
tests_failed="0"
function new_ingredient() {
    ingredientName="$1"
    ingredientFile="$2"
    ingredients["$ingredientName"]="$ingredientFile"
}
function define_all() {
    definition="$1"
    value="$2"
    for ingredient in "${!ingredients[@]}"; do
        sed -i -e "s/%%${definition}%%/$value/g" ${ingredients["$ingredient"]}
    done
}
function link() {
    ingredientName="$1"
    link="$2"
    ingredientFile="${ingredients[$ingredientName]}"
    ingredient_links["$ingredientName"]="${ingredient_links["$ingredientName"]} -l$link"
}

function bake_ingredient() {
    links=" "
    ingredient="$1"
    if [ "$compiler" == "g++" ]; then
        for link in "${!ingredient_links[@]}"; do
            links="$links -l$link"
        done
        g++ -o $ingredient ${ingredients[$ingredient]} $links -std=$c_standard
        links=" "
    elif [ "$compiler" == "valac" ]; then
        links="--pkg"
        links="$links ${ingredient_links[$ingredient]}"
        valac -o $ingredient ${ingredients[$ingredient]} $links
        links=" "
    elif [ "$compiler" == "gcc" ]; then
        for link in "${!ingredient_links[@]}"; do
            links="$links -l$link"
        done
        gcc -o $ingredient ${ingredients[$ingredient]} $links
        links=" "
    fi
}
function bake_all() {
    for ingredient in "${!ingredients[@]}"; do
        bake_ingredient "$ingredient"
    done
}

function bake_container() {
    local bake_bin=".bake/bake"
    local baketools=".bake/baketools.sh"
    local base_container="
FROM $image

WORKDIR $container_location
COPY . $container_location
COPY $bake_bin /usr/bin/bake
COPY $baketools /usr/bin/baketools.sh

EXPOSE 80

RUN /usr/bin/bake
CMD [\"/usr/bin/bake\", \"deploy\"]"

    mkdir ./.bake
    cp /usr/bin/bake ./.bake/bake
    cp /usr/bin/baketools.sh ./.bake/baketools.sh

    echo "RUNNING ON NAME $name"

    echo "$base_container" > Dockerfile
    sudo docker build -t $name .
    echo "built"
    local cname=$(head /dev/urandom | tr -dc A-Za-z0-9 | head -c 24 ; echo '')
    sudo docker run -p $port:80 -a STDOUT --name $cname $name &

    echo "PID $!"
    containerid=$!
    echo "$containerid" >> .container.pid
    echo "$cname" >> .container.name
    rm Dockerfile
    rm -rf .bake
}
test_command() {
    local green="\033[38;5;43m"
    local red="\033[38;5;203m"
    local reset="\033[0m"
    local code="$1"
    if [ "$code" -eq "0" ]; then
        echo -e "$green✓ Done$reset"
    else
        echo -e "$red🗴 Failed$reset"
        tests_failed=$((tests_failed+1))
    fi
}
tests_passed() {
    exit $tests_failed
}
