# 文字コード：UTF-8

Name=node-js-socketio

build:
	docker build -t ${Name} .
.PHONY: build

run:
	docker run -d -it -p 8080:5000 ${Name}
.PHONY: run

stop:
	docker stop $(shell docker ps -a -q --filter ancestor=${Name} --format="{{.ID}}")
.PHONY: stop

