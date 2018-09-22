.PHONY: test build

test:
	go test *.go

build:
	go build

depends:
	go get github.com/stretchr/testify