
package main

import (
    "fmt"
    "net/http"
    "strings"
    "log"
)

var cnt = 1

//执行函数
func hello(w http.ResponseWriter, r *http.Request) {

	//不获取网站图标
	if r.RequestURI == "/facicon.ico" {
		return
	}

	r.ParseForm()  				// 解析参数，默认是不会解析的
	// 以下为客户端请求的http数据
    fmt.Println("form:\t",r.Form)  		// 这些信息是输出到服务器端的打印信息
    fmt.Println("path:\t", r.URL.Path)
    fmt.Println("scheme:\t", r.URL.Scheme)
	fmt.Println()
    for k, v := range r.Form {
        fmt.Println("key:", k, "val:", strings.Join(v, ""))
	}
	// 将该信息作为响应返回给客户端

	fmt.Fprintf(w, "Hello hahah %d", cnt) 	// 这个写入到 w 的是输出到客户端的
	cnt++
	
}

func main() {
    http.HandleFunc("/", hello) 				// 设置访问的路由
    err := http.ListenAndServe(":9876", nil) 	// 设置监听的端口
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}