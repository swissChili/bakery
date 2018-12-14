bake: bakery.go build/build.go
	mkdir target
	go build -o target/bake bakery.go
	target/bake