#!/bin/bash

###########################################################################################################
## Bakery BakeTools                                                                                      ##
## This file will be automatically `source`d in your Bakery by `bake`, do not include it manually.       ##
###########################################################################################################

declare -A ingredients
declare -A ingredient_links
declare -A flags
compiler="g++"
c_standard="c++17"
function new_ingredient() {
    ingredientName="$1"
    ingredientFile="$2"
    ingredients["$ingredientName"]="$ingredientFile"
}
function link_static() {
    ingredientName="$1"
    link="$2"
    ingredientFile="${ingredients[$ingredientName]}"
    ingredient_links["$ingredientName"]="$link"
}
function bake_ingredient() {
    links=" "
    ingredient="$1"
    if [ "$compiler" == "g++" ]; then
        for link in "${!ingredient_links[@]}"; do
            $links="$links -l$link"
        done
        g++ -o $ingredient ${ingredients[$ingredient]} $links -std=$c_standard
        links=" "
    fi
}
function bake_all() {
    for ingredient in "${!ingredients[@]}"; do
        bake_ingredient "$ingredient"
    done
}