# Bake
### Bash-based build tool

### Why is it useful?
Bash! its great, we all love it, and now you can more easily use it for building things.

Oh, and you dont need to have a bunch of `build.sh`, `install.sh`, `link.sh` scripts. all in one file!


### Roadmap
- make it actually useful by adding Bakers, background processes used to run things over SSH or other server things

### Usage
`bake` looks for a bakery in your current directory, here is an example bakery:
```sh
# bake
echo "This will be called when `bake` is run"
go get
go build -o coolprogram myprogram.go

# install
echo "this will be called when `bake install` is run"
sudo cp coolprogram /usr/bin/coolprogram
```

