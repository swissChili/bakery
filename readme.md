# Bake
### Bash-based build tool

### Why is it useful?
It's really not yet. But its easier than learning `Makefile` so thats something.

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
Bakeries consist of recipes, and recipes are defined just like bash comments, so they are completely valid bash code.

Recipe definition can look like any of the following:
```sh
#bake
echo "code here!"
# bake
echo "this also works"
```
One space after the `#` is allowed, but no more. 

