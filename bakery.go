package main

import (
    "fmt"
    "os"
    "./build"
    "./colors"
    "./server"
    "./remote"
)


func main() {
    // Check if there's a bakery
    bakery := build.GetBakery("bakery.toml")

    command := "main"

    if len(os.Args) > 1 {
        if os.Args[1] != "remote" {
            command = os.Args[1]
        } else {
            // this is a remote query, parse remaining args.
            if len(os.Args) > 2 {
                switch os.Args[2] {
                case "serve": server.Serve()
                default: remote.Get(os.Args[2])
                }
            } else {
                fmt.Printf(`%s[Remote]%s command 'remote' requires additional parameters
        Try 'bake -h' for usage instructions
`, colors.Yellow, colors.Reset)
                panic("Incorrect arguments")
            }
        }
    }

    fmt.Printf(`%s[ Bake ]%s Starting to build command %s
`, colors.Cyan, colors.Reset, command)

    build.Run(bakery, command, []string{})

}