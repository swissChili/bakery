package main

import (
    "fmt"
    "os"
    "./build"
)


func main() {
    // Check if there's a bakery
    bakery := build.GetBakery("bakery.toml")

    command := "main"

    if len(os.Args) > 1 {
        command = os.Args[1]
    }

    fmt.Printf(`%s[  Go  ]%s Starting to build command %s
`, build.Green, build.Reset, command)

    build.Run(bakery, command, []string{})

}