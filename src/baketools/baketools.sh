#!/bin/bash

###########################################################################################################
## Bakery BakeTools                                                                                      ##
## This file will be automatically `source`d in your Bakery by `bake`, do not include it manually.       ##
## This file provides a bash wrapper around the C++ BakeTools, such as one-command compiling and linking ##
###########################################################################################################

declare -A recipes

function new_recipe() {
    recipeName=$1
    recipeFile=$2
    declare -A recipes=( ["$recipeName"]="$recipeFile")
    echo "${recipes[$recipeName]}"
}