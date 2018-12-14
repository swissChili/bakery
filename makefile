bake: bakery.go build/build.go
	mkdir target
	go get github.com/BurntSushi/toml
	go build -o target/bake bakery.go
	target/bake