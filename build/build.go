package build


import (
    "github.com/BurntSushi/toml"
    "io/ioutil"
    "fmt"
    "os/exec"
)


const Green = "\033[32m"
const Reset = "\033[0m"
const Red   = "\033[31m"


func stringInSlice(a string, list []string) bool {
    for _, b := range list {
        if b == a {
            return true
        }
    }
    return false
}


type Command struct {
    From      []string `toml="from"`
    Do          string `toml="do"`
    // description string `toml="description`
}

func GetBakery(f string) map[string]Command {
    file, err := ioutil.ReadFile(f)

    if err != nil {
        panic("Failed to read file")
    }

    // Parse file
    var bakery map[string]Command

    if err := toml.Unmarshal([]byte(file), &bakery); err != nil {
        panic(err)
    }


    return bakery
}

func Do(run string) string {
    out, err := exec.Command("sh", "-c", run).Output()
    if err != nil {
        fmt.Printf(`%s[ Fail ]%s Build failed at command 
%s'%s'%s
`, Red, Reset, Red, run, Reset)
        panic("Failed to build")
    }

    return string(out)
}

func Run(full map[string]Command, do string, done []string) {
    bakery := full[do]
    done = append(done, bakery.Do)
    

    for _, from := range bakery.From {
        if !stringInSlice(from, done) {
            fmt.Printf(`         Building dependency '%s'...
`, from)
            Run(full, from, done)
        }
    }

    fmt.Println(Do(bakery.Do))

    fmt.Printf(`%s[ Done ]%s Built '%s' successfully
`, Green, Reset, do)
}
