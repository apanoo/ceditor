package main

import (
	"fmt"

	lua "github.com/yuin/gopher-lua"
)

func testLua(files []string) {
	// default build
	if len(files) == 0 {
		files = append(files, "lua/build.lua")
	}

	L := lua.NewState()
	defer L.Close()

	// lua bustm module
	L.PreloadModule("bustm", Loader)

	for _, file := range files {
		if err := L.DoFile(file); err != nil {
			fmt.Println(err.Error())
		}
	}
}
