package main

import "os"
import "fmt"

func round(n int) int {

    a := int(n / 10) * 10
    b := a + 10

    if a - n > b {
        return a 
    } else if b - n > a {
        return b
    } else {
        return 0
    }

}

func o_file(fname string) []byte {

    f, err := os.Open("link.gbc")
    if err != nil {
        print(err)
        os.Exit(1)
    }

    l, _ := f.Seek(0, 2);f.Seek(0, 0)
    buff := make([]byte, l)
    f.Read(buff)

    if err != nil {
        print(err)
        os.Exit(1)
    }

    return buff
}

func draw(buf []byte) {

    flag := false

    for i:=0x00000000;i<0x100;i = i + 0x10 {
        fmt.Printf("%.8X: ", i)
        for j:=0x0;j<0x10;j++ {
            fmt.Printf("%.2X", buf[j+i])
            if flag {
                flag = false
                fmt.Print(" ")
                continue
            }
            flag = true
        }

        for z:=0x0;z<0x10;z++ {
            if buf[z+i] > 0x7e || buf[z+i] < 0x21 {
                fmt.Printf(".")
            } else if buf[z+i] == 0 {
                fmt.Printf(".")
            } else {
                fmt.Printf("%c", buf[z+i])
            }
        }
        fmt.Printf("\n")
    }
}

func main() {
    if len(os.Args) < 2{
        os.Exit(1)
    }
    buff := o_file(os.Args[1])
    fmt.Printf("%x\n", len(buff))
    draw(buff)
}
