#!/bin/bash

###########################################################################################################
## Bakery BakeTools                                                                                      ##
## This file will be automatically `source`d in your Bakery by `bake`, do not include it manually.       ##
## This file provides a bash wrapper around the C++ BakeTools, such as one-command compiling and linking ##
###########################################################################################################

declare -A recipes
declare -A recipe_links
compiler="g++"
c_standard="c++17"
function new_recipe() {
    recipeName="$1"
    recipeFile="$2"
    declare -A recipes=( ["$recipeName"]="$recipeFile")
}
function link_static() {
    recipeName="$1"
    link="$2"
    recipeFile="${recipes[$recipeName]}"
    declare -A recipe_links=( ["$recipeName"]="$link")
}

function bake_all() {
    links=""
    for recipe in "${!recipes[@]}"; do
        if [ "$compiler" == "g++" ]; then
            for link in "${!recipe_links[@]}"; do
                $links="$links -l$link"
            done
            g++ -o $recipe ${recipes[$recipe]} $links
            links=""
            echo "Baked!"
        fi
    done
}