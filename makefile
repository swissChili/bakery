bake: bakery.go build/build.go bakery
	go build -o target/bake bakery.go


bakery: bake
	target/bake